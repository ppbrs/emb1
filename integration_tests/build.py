"""Helpers for buildability tests."""

import logging
import pathlib
import subprocess as sp

import elftools.elf.elffile  # type: ignore
from emb_spy import demangle  # type: ignore


def build_helper(
    target: str,  # target name
    toolchain: str,  # toolchain name
    sym_names_required: list[str],
    *,
    clean_up_after: bool = True,
) -> None:
    """
    Test buildability of a target with the provided toolchain.

    "$ make -B {target}" will be envoked.
    The resulting elf file will be checked with "elf_file_checker()" if it is provided.
    """
    logger = logging.getLogger(__name__)
    out_dir = pathlib.Path.cwd() / "bin"

    def clean_up() -> None:
        logger.info("Removing artifacts.")
        _ = [*map(lambda p: p.unlink(), out_dir.glob(f"{target}.*"))]

    clean_up()

    logger.info("Building `%s` with `%s`.", target, toolchain)

    cmd = f"make -B {target} EMB1_TOOLCHAIN={toolchain}"
    with sp.Popen(args=[cmd], shell=True, stdout=sp.PIPE, stderr=sp.PIPE) as child:
        stdout_b, stderr_b = child.communicate()
        exit_code = child.wait()
        stdout_lines = stdout_b.decode(encoding="ascii", errors="ignore").split("\n")
        stderr_lines = stderr_b.decode(encoding="ascii", errors="ignore").split("\n")
        if exit_code:
            for stdout_line in stdout_lines:
                logger.error(stdout_line)
            for stderr_line in stderr_lines:
                logger.error(stderr_line)
        assert exit_code == 0

    logger.info("Checking ELF file.")
    elf_path = pathlib.Path.cwd() / "bin" / f"{target}.{toolchain}.elf"
    assert elf_path.exists() and elf_path.is_file()
    if sym_names_required:
        with open(elf_path, "rb") as elf_fd:
            elf = elftools.elf.elffile.ELFFile(elf_fd)
            check_elf(elf=elf, sym_names_required=sym_names_required)
    else:
        logger.warning("🟨 Not checking required symbols.")

    if clean_up_after:
        clean_up()


def check_elf(
    elf: elftools.elf.elffile.ELFFile,
    sym_names_required: list[str],
) -> None:
    """Confirm that elf file contains all required segments/sections/symbols."""
    logger = logging.getLogger(__name__)
    assert isinstance(elf, elftools.elf.elffile.ELFFile)
    sym_names = []
    for section in elf.iter_sections(type="SHT_SYMTAB"):
        assert isinstance(section, elftools.elf.sections.SymbolTableSection)
        for symbol in section.iter_symbols():
            try:
                name = demangle(symbol.name)
            except ValueError:
                name = symbol.name
            sym_names.append(name)
    logger.info("%d symbols total.", len(sym_names))
    for name in sym_names_required:
        assert name in sym_names, f"'{name}' not found in elf."
    logger.info("✅ All required %d symbols were found.", len(sym_names_required))

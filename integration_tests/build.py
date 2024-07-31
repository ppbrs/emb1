"""Helpers for buildability tests."""
import logging
import pathlib
import subprocess as sp
from collections.abc import Callable

import elftools.elf.elffile  # type: ignore


def build_helper(
    target: str,  # target name
    toolchain: str,  # toolchain name
    elf_file_checker: Callable[[elftools.elf.elffile.ELFFile], None] | None,
    logger: logging.Logger,
) -> None:
    """
    Test buildability of a target with the provided toolchain.

    "$ make -B {target}" will be envoked.
    The resulting elf file will be checked with "elf_file_checker()" if it is provided.
    """
    out_dir = pathlib.Path.cwd() / "bin"

    def clean_up() -> None:
        logger.info("Removing artifacts.")
        _ = [*map(lambda p: p.unlink(), out_dir.glob(f"{target}.*"))]

    clean_up()

    logger.info("Building `%s` with `%s`.", target, toolchain)

    cmd = f"export EMB1_TOOLCHAIN={toolchain} && make -B {target}"
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
    with open(elf_path, "rb") as elf_fd:
        elf = elftools.elf.elffile.ELFFile(elf_fd)
        if elf_file_checker is not None:
            elf_file_checker(elf)

    clean_up()

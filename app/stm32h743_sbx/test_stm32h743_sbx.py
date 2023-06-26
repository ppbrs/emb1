"""
This module contains tests for the stm32h743-sbx project.
"""
# Standard library imports
import logging
import pathlib
import subprocess as sp
# Third party imports
import elftools.elf.elffile  # type: ignore
import pytest
# Local application/library imports

_logger = logging.getLogger(__name__)


@pytest.mark.parametrize("toolchain", ["gnu", "llvm"])
def test_build(toolchain: str) -> None:
    """
    Verify that the project can be built correctly.
    """
    target = "stm32h743-sbx"
    out_dir = pathlib.Path.cwd() / "bin"

    _logger.info("Removing existing artifacts.")
    _ = [*map(lambda p: p.unlink(), out_dir.glob(f"{target}.*"))]

    _logger.info("Building with `%s` toolchain.", toolchain)

    cmd = f"export EMB1_TOOLCHAIN=gnu && make -B {target}"
    with sp.Popen(args=[cmd], shell=True, stdout=sp.PIPE, stderr=sp.PIPE) as child:
        # outs_b, errs_b = child.communicate()
        exit_code = child.wait()
        # outs = outs_b.decode(encoding="ascii", errors="ignore").split("\n")
        # errs = errs_b.decode(encoding="ascii", errors="ignore").split("\n")
        assert exit_code == 0

    _logger.info("Checking ELF file.")

    elf_path = pathlib.Path.cwd() / "bin" / f"{target}.elf"
    assert elf_path.exists() and elf_path.is_file()
    with open(elf_path, "rb") as elf_file:
        _ = elftools.elf.elffile.ELFFile(elf_file)

    _logger.info("Removing artifacts.")
    _ = [*map(lambda p: p.unlink(), out_dir.glob(f"{target}.*"))]

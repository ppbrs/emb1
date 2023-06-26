"""
This module contains tests for the host-test subproject.
"""
import logging
import pathlib
import subprocess as sp
# Third party imports
import elftools.elf.elffile  # type: ignore
import pytest
# Local application/library imports

_logger = logging.getLogger(__name__)


@pytest.mark.parametrize("toolchain", ["gnu", "llvm"])
# @pytest.mark.parametrize("toolchain", ["gnu"])
def test_build_run(toolchain: str) -> None:
    """
    Verify that host-test can be built and runs without failures.
    """

    target_build = "host-tests"
    out_dir = pathlib.Path.cwd() / "bin"

    _logger.info("Removing existing artifacts.")
    _ = [*map(lambda p: p.unlink(), out_dir.glob(f"{target_build}.*"))]

    _logger.info("Building with `%s` toolchain.", toolchain)

    cmd = f"export EMB1_TOOLCHAIN=gnu && make -B {target_build}"

    cmd = "make -B host-tests"
    with sp.Popen(args=[cmd], shell=True, stdout=sp.PIPE, stderr=sp.PIPE) as child:
        exit_code = child.wait()
        assert exit_code == 0

    _logger.info("Checking ELF file.")

    elf_path = pathlib.Path.cwd() / "bin" / f"{target_build}.out"
    assert elf_path.exists() and elf_path.is_file()
    with open(elf_path, "rb") as elf_file:
        _ = elftools.elf.elffile.ELFFile(elf_file)

    _logger.info("Running tests.")

    cmd = "make host-tests-run"
    with sp.Popen(args=[cmd], shell=True, stdout=sp.PIPE, stderr=sp.PIPE) as child:
        exit_code = child.wait()
        assert exit_code == 0

    _logger.info("Removing artifacts.")
    _ = [*map(lambda p: p.unlink(), out_dir.glob(f"{target_build}.*"))]

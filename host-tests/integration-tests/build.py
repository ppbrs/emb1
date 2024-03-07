"""Integration tests for the host-test subproject."""
import logging
import pathlib
import shutil
import subprocess as sp

import elftools.elf.elffile  # type: ignore
import pytest

_logger = logging.getLogger(__name__)


def _remove_artifacts() -> None:
    """Delete binary, object, and temporary files."""
    out_dir = pathlib.Path.cwd() / "bin"
    obj_dir = pathlib.Path.cwd() / "obj"
    tmp_dir = pathlib.Path.cwd() / "tmp"
    if out_dir.exists():
        shutil.rmtree(out_dir)
    if obj_dir.exists():
        shutil.rmtree(obj_dir)
    if tmp_dir.exists():
        shutil.rmtree(tmp_dir)


@pytest.mark.pctest  # type: ignore
@pytest.mark.parametrize("toolchain", ["gnu", "llvm"])  # type: ignore
def test_build_run(toolchain: str) -> None:
    """Verify that host-test can be built and runs without failures."""
    target_build = "host-tests"
    target_run = "host-tests"

    _logger.info("Removing existing artifacts.")
    _remove_artifacts()

    _logger.info("Building with `%s` toolchain.", toolchain)

    cmd = f"export EMB1_TOOLCHAIN={toolchain} && make -B {target_build}"
    with sp.Popen(args=[cmd], shell=True, stdout=sp.PIPE, stderr=sp.PIPE) as child:
        exit_code = child.wait()
        assert exit_code == 0

    _logger.info("Checking ELF file.")

    elf_path = pathlib.Path.cwd() / "bin" / f"{target_build}.{toolchain}.out"
    assert elf_path.exists() and elf_path.is_file()
    with open(elf_path, "rb") as elf_file:
        _ = elftools.elf.elffile.ELFFile(elf_file)

    _logger.info("Running tests.")

    cmd = f"export EMB1_TOOLCHAIN={toolchain} && make {target_run}"
    with sp.Popen(args=[cmd], shell=True, stdout=sp.PIPE, stderr=sp.PIPE) as child:
        exit_code = child.wait()
        assert exit_code == 0

    _logger.info("Removing artifacts.")
    _remove_artifacts()

"""Integration tests for H743-zephyr-sbx projects."""
import logging
import os
import pathlib
import shutil
import subprocess as sp

import elftools.elf.elffile  # type: ignore
import pytest

_logger = logging.getLogger(__name__)


@pytest.mark.pctest  # type: ignore
@pytest.mark.skip(reason="Zephyr project is not stable yet.")
def test_build() -> None:
    """Check that stm32h743_zephyr_sbx project is buildable."""
    prj_path = pathlib.PosixPath(__file__).parent.parent
    _logger.debug("Project path: %s", prj_path)

    build_dir = prj_path / "build"

    def remove_artifacts() -> None:
        if build_dir.exists():
            _logger.debug("Removing %s", build_dir)
            shutil.rmtree(build_dir)

    remove_artifacts()

    board_name = "rijeka"

    zephyrproject_path = pathlib.PosixPath("~/zephyrproject/zephyr").expanduser()
    assert zephyrproject_path.exists() and zephyrproject_path.is_dir()

    _logger.info("Building the project ...")
    cwd = pathlib.Path.cwd()
    try:
        os.chdir(zephyrproject_path)
        rebuild_cmd = (
            "west "
            "build "
            "--pristine=always "
            f"-b={board_name} "
            f"{prj_path} "
            f"--build-dir {build_dir} "
        )
        with sp.Popen(args=[rebuild_cmd], shell=True, stdout=sp.PIPE, stderr=sp.PIPE) as child:
            exit_code = child.wait()
            assert exit_code == 0
    finally:
        os.chdir(cwd)
    _logger.info("... done")

    _logger.info("Checking ELF file ...")
    elf_path = build_dir / "zephyr" / "zephyr.elf"
    assert elf_path.exists() and elf_path.is_file()
    with open(elf_path, "rb") as elf_file:
        _ = elftools.elf.elffile.ELFFile(elf_file)
    _logger.info("... done")

    remove_artifacts()

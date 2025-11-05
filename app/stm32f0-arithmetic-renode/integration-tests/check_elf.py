"""Holds parameters for check_elf and is also callable."""

import os
import sys

sys.path.append(os.path.abspath(os.getcwd()))

import logging
import sys
import pathlib

import elftools.elf.elffile  # type: ignore
import pytest
from integration_tests.build import build_helper, check_elf



_sym_names_required = [
    "Test::suiteStarted",
    "Test::suiteFinished",
    "Test::startCount",
    "Test::finishCount",
    "Test::okCount",
    "Test::failCount",
]


@pytest.mark.pctest  # type: ignore
@pytest.mark.parametrize("toolchain", ["gnu-arm-none-eabi-10.3", "gnu-arm-none-eabi-14.3"])
def test_build(toolchain: str) -> None:
    """Check that stm32f0-arithmetic-renode project is buildable."""
    build_helper(
        target="stm32f0-arithmetic-renode",
        toolchain=toolchain,
        sym_names_required=_sym_names_required,
    )


if __name__ == "__main__":
    logging.basicConfig(
        level=logging.DEBUG,
        format="%(asctime)s %(levelname)-8s %(name)s:%(funcName)s:%(lineno)d: %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )
    assert len(sys.argv) == 2
    elf_path = pathlib.PosixPath(sys.argv[1])
    assert elf_path.exists()
    assert elf_path.is_file()
    with open(elf_path, "rb") as elf_fd:
        elf = elftools.elf.elffile.ELFFile(elf_fd)
        check_elf(elf=elf, sym_names_required=_sym_names_required)

"""
Tests for the stm32h743-sbx project.
"""
import logging

import pytest

from integration_tests.build import build_helper  # pylint: disable=import-error

_logger = logging.getLogger(__name__)


@pytest.mark.pctest  # type: ignore
@pytest.mark.parametrize("toolchain", ["gnu", "llvm"])  # type: ignore
def test_build(toolchain: str) -> None:
    """Check that stm32f051-sbx project is buildable."""
    build_helper(
        target="stm32h743-sbx",
        toolchain=toolchain,
        logger=_logger,
        elf_file_checker=None,
    )

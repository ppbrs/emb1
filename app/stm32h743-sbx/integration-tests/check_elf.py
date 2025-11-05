"""
Tests for the stm32h743-sbx project.
"""

import pytest

from integration_tests.build import build_helper  # pylint: disable=import-error


@pytest.mark.pctest  # type: ignore
@pytest.mark.parametrize("toolchain", ["gnu-arm-none-eabi-10.3"])  # type: ignore
def test_build(toolchain: str) -> None:
    """Check that stm32f051-sbx project is buildable."""
    build_helper(
        target="stm32h743-sbx",
        toolchain=toolchain,
        sym_names_required=[],
    )

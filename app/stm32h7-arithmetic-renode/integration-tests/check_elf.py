"""
Tests for the stm32h743-sbx project.
"""

import pytest

from integration_tests.build import build_helper  # pylint: disable=import-error

_sym_names_required = [
    "initialSpValue",
    "nvic::(anonymous namespace)::exceptionVectors",
    "nvic::(anonymous namespace)::interrupsVectors",
    "resetHandler",
]

@pytest.mark.pctest  # type: ignore
@pytest.mark.parametrize("toolchain", ["gnu-arm-none-eabi-14.3"])  # type: ignore
def test_build(toolchain: str) -> None:
    """Check that stm32h7-arithmetic-renode project is buildable."""
    build_helper(
        target="stm32h7-arithmetic-renode",
        toolchain=toolchain,
        sym_names_required=_sym_names_required,
    )

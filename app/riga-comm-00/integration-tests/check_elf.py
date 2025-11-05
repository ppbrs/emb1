"""
Tests for the riga-comm-00 project.

Checks that it builds.
"""

import pytest

from integration_tests.build import build_helper  # pylint: disable=import-error


_sym_names_required = [
    "tick::sysTickCnt",
    "app::(anonymous namespace)::rxCnt",
    "app::(anonymous namespace)::txCnt",
]


@pytest.mark.pctest  # type: ignore
@pytest.mark.parametrize("toolchain", ["gnu-arm-none-eabi-10.3", "gnu-arm-none-eabi-14.3"])  # type: ignore
def test_build(toolchain: str) -> None:
    """Check that riga-comm-00 project is buildable."""
    build_helper(
        target="riga-comm-00",
        toolchain=toolchain,
        sym_names_required=_sym_names_required,
    )

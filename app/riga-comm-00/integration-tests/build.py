"""
Tests for the riga-comm-00 project.

Checks that it builds.
"""
import logging

import elftools.elf.elffile  # type: ignore
import pytest
from cpp_demangle import demangle  # type: ignore  # pylint: disable=no-name-in-module

from integration_tests.build import build_helper  # pylint: disable=import-error

_logger = logging.getLogger(__name__)


@pytest.mark.pctest  # type: ignore
@pytest.mark.parametrize("toolchain", ["gnu", "llvm"])  # type: ignore
def test_build(toolchain: str) -> None:
    """Check that stm32f051-sbx project is buildable."""
    build_helper(
        target="riga-comm-00",
        toolchain=toolchain,
        logger=_logger,
        elf_file_checker=elf_file_checker,
    )


def elf_file_checker(
    elf: elftools.elf.elffile.ELFFile
) -> None:
    """Check the resulting elf file."""
    sym_names_required = [
        "tick::sysTickCnt",
        "app::(anonymous namespace)::rxCnt",
        "app::(anonymous namespace)::txCnt",
    ]

    sym_names = []
    for section in elf.iter_sections(type="SHT_SYMTAB"):
        assert isinstance(section, elftools.elf.sections.SymbolTableSection)
        logging.info("%d symbols total.", section.num_symbols())
        for symbol in section.iter_symbols():
            try:
                name = demangle(symbol.name)
            except ValueError:
                # logging.warning("Could not demangle `%s`.", symbol.name)
                name = symbol.name
            sym_names.append(name)

    for name in sym_names_required:
        assert name in sym_names

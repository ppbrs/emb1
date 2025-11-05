"""Holds elf_check and is also callable."""
import logging
import sys
import pathlib
import elftools.elf.elffile  # type: ignore
from emb_spy import demangle  # type: ignore


def elf_check(elf: elftools.elf.elffile.ELFFile) -> None:
    """Confirm that elf file contains all required segments/sections/symbols."""
    assert isinstance(elf, elftools.elf.elffile.ELFFile)

    sym_names_required = [
        "Test::suiteStarted",
        "Test::suiteFinished",
        "Test::startCount",
        "Test::finishCount",
        "Test::okCount",
        "Test::failCount",
    ]

    sym_names = []
    for section in elf.iter_sections(type="SHT_SYMTAB"):
        assert isinstance(section, elftools.elf.sections.SymbolTableSection)
        for symbol in section.iter_symbols():
            try:
                name = demangle(symbol.name)
            except ValueError:
                name = symbol.name
            sym_names.append(name)
    logging.info("%d symbols total.", len(sym_names))
    for name in sym_names_required:
        assert name in sym_names, f"'{name}' not found in elf."
    logging.info("All required symbols were found.")


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
        elf_check(elf=elf)

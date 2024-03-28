"""
Tests for the stm32f051-sbx project.
"""
import logging
import pathlib
import subprocess as sp

import elftools.elf.elffile  # type: ignore
import pytest

_logger = logging.getLogger(__name__)


@pytest.mark.pctest  # type: ignore
@pytest.mark.parametrize("toolchain", ["gnu", "llvm"])  # type: ignore
def test_build(toolchain: str) -> None:
    """Check that stm32f051-sbx project is buildable."""
    target = "stm32f051-sbx"
    out_dir = pathlib.Path.cwd() / "bin"

    _logger.info("Removing existing artifacts.")
    _ = [*map(lambda p: p.unlink(), out_dir.glob(f"{target}.*"))]

    _logger.info("Building with `%s` toolchain.", toolchain)

    cmd = f"export EMB1_TOOLCHAIN=gnu && make -B {target}"
    with sp.Popen(args=[cmd], shell=True, stdout=sp.PIPE, stderr=sp.PIPE) as child:
        stdout_b, stderr_b = child.communicate()
        exit_code = child.wait()
        stdout_lines = stdout_b.decode(encoding="ascii", errors="ignore").split("\n")
        stderr_lines = stderr_b.decode(encoding="ascii", errors="ignore").split("\n")
        if exit_code:
            for stdout_line in stdout_lines:
                _logger.error(stdout_line)
            for stderr_line in stderr_lines:
                _logger.error(stderr_line)
        assert exit_code == 0

    _logger.info("Checking ELF file.")

    elf_path = pathlib.Path.cwd() / "bin" / f"{target}.elf"
    assert elf_path.exists() and elf_path.is_file()
    with open(elf_path, "rb") as elf_file:
        _ = elftools.elf.elffile.ELFFile(elf_file)

    _logger.info("Removing artifacts.")
    _ = [*map(lambda p: p.unlink(), out_dir.glob(f"{target}.*"))]

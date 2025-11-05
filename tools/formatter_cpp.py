"""Search for C/C++ files in the project and apply clang-format."""
import logging
import pathlib
import subprocess as sp
import sys

import pytest

CLANG_FORMAT = "clang-format-19"
GLOBS_FORMAT = (
    "*.cpp",
    "*.h",
    ".c"
)
GLOBS_SKIP = (
    "./3party/**/*",
    "./tmp/**/*",
    "./tmp/**/*",
    "./app/stm32h743_zephyr_sbx/build/**/*",
    "./app/stm32f051_zephyr_sbx/build/**/*",
)


def _get_proj_dir() -> pathlib.PosixPath:
    proj_dir = pathlib.PosixPath.cwd()
    assert pathlib.PosixPath(".clang-format").exists(), \
        f".clang-format not found in the current directory ({proj_dir})."
    return proj_dir


def _get_cpp_paths() -> list[pathlib.PosixPath]:
    """Get a sorted list of C/C++ files that may be formatted."""
    proj_dir = _get_proj_dir()

    paths_format = set()
    paths_skip = set()
    for glob in GLOBS_FORMAT:
        for path in proj_dir.rglob(glob):
            paths_format.add(path.relative_to(proj_dir))
    for glob in GLOBS_SKIP:
        for path in proj_dir.rglob(glob):
            paths_skip.add(path.relative_to(proj_dir))

    paths_format -= paths_skip
    return sorted(paths_format)


def _format_one_file(path: pathlib.PosixPath) -> int:
    cmd = [CLANG_FORMAT, str(path), "--style=file", "-i"]
    with sp.Popen(args=cmd, stdout=None, stderr=None) as child:
        exit_code = child.wait()
    return exit_code


def _run() -> int:
    cpp_paths = _get_cpp_paths()
    result = 0
    if len(sys.argv) == 1:
        # Format all files in the project
        for path in cpp_paths:
            result += _format_one_file(path)
        return result

    proj_dir = pathlib.Path.cwd()
    for arg in sys.argv[1:]:
        path = pathlib.PosixPath(arg).relative_to(proj_dir)
        result += _format_one_file(path)
    return result


if __name__ == "__main__":
    sys.exit(_run())


@pytest.mark.pctest  # type: ignore
def test_format_cpp() -> None:
    """Check that all C/C++ files in the project are formatted."""
    logger = logging.getLogger(__name__)

    # Check that clang-format is installed.
    with sp.Popen(args=[CLANG_FORMAT, "--version"]) as child:
        exit_code = child.wait()
        assert exit_code == 0

    num_files_to_format = 0
    for path in _get_cpp_paths():
        with sp.Popen(args=[CLANG_FORMAT, str(path), "--style=file", "--dry-run", "--Werror"],
                      stdout=None, stderr=None) as child:
            exit_code = child.wait()
        if exit_code != 0:
            num_files_to_format += 1
            logger.error("`%s` not formatted.", path)
    if num_files_to_format == 1:
        assert False, "1 file is not formatted."
    assert num_files_to_format == 0, f"{num_files_to_format} files are not formatted."

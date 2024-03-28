"""
Integration tests checking "memory" command on stm32h743-zephyr-sbx project.

Regions of memory on this platform that can be read:
    ITCM: 0x00000000 .. 0x00010000
    User flash memory: 0x08000000 .. 0x08200000
    System flash memory: 0x1FF00000 ..0x1FF1FFFF

"""
import itertools
import logging

from integration_tests.sport import SPort

_logger = logging.getLogger()


def test_good(sport: SPort) -> None:
    """Test the `memory` command with correct options."""
    size_variants = range(1, 9)
    format_variants = ("u8", "u16", "u32", "u8h", "u16h", "u32h", "i8", "i16", "i32", )

    cnt = 1
    for size_, format_, short in itertools.product(size_variants, format_variants, (True, False)):
        if short:
            cmd = f"memory -a 0 -f {format_} -s {size_}"
        else:
            cmd = f"memory --address 0 --format {format_} --size {size_}"
        sport.write_line(cmd)
        line = sport.read_line()
        comps = line.split()
        assert len(comps) == 2 + size_, \
            f"Got {len(comps)} tokens in response, expected {1 + size_}."
        cnt += 1
    _logger.info("%d variants were tested.", cnt)


def test_bad_size(sport: SPort) -> None:
    """Size more than 8 is not supported; size less than 1 makes no sense."""
    cmd_resp_pairs = [
        ("memory -a 0 -f u32 -s 0", "memory: ERROR: Wrong size."),
        ("memory -a 0 -f u32 -s 9", "memory: ERROR: Wrong size."),
        ("memory -a 0 -f u32 --size 0", "memory: ERROR: Wrong size."),
        ("memory -a 0 -f u32 --size 10h", "memory: ERROR: Wrong size."),
        ("memory -a 0 -f u32 -s -1", "protocol: ERROR: Option parameter parse error."),
    ]
    for i, pair in enumerate(cmd_resp_pairs):
        cmd, resp_exp = pair
        sport.write_line(cmd)
        resp_got = sport.read_line()
        assert resp_got.startswith(resp_exp), f"#{i}: Got `{resp_got}`."


def test_bad_format(sport: SPort) -> None:
    """Check that the expected error message is sent when the format is not supported."""
    cmd_resp_pairs = [
        ("memory -a 0 -s 1 -f qwer", "memory: ERROR: Unknown format."),
        ("memory -a 0 -s 1 --format asdf", "memory: ERROR: Unknown format."),
    ]
    for i, pair in enumerate(cmd_resp_pairs):
        cmd, resp_exp = pair
        sport.write_line(cmd)
        resp_got = sport.read_line()
        assert resp_got.startswith(resp_exp), f"#{i}: Got `{resp_got}`."


def test_bad_address(sport: SPort) -> None:
    """Check that the expected error message is sent when there is a problem with address."""
    cmd_resp_pairs = [
        # Parsing problems:
        ("memory -a abcd -f u32 -s 1", "protocol: ERROR: Option parameter parse error."),
        ("memory -a -1 -f u32 -s 1", "protocol: ERROR: Option parameter parse error."),

        # Alignment problems:
        ("memory -a 0x08000001 -f u32 -s 1", "memory: ERROR: Bad alignment."),
        ("memory -a 0x08000002 -f u32 -s 1", "memory: ERROR: Bad alignment."),
        ("memory -a 0x08000003 -f u32 -s 1", "memory: ERROR: Bad alignment."),
        ("memory -a 0x08000001 -f u32h -s 1", "memory: ERROR: Bad alignment."),
        ("memory -a 0x08000002 -f u32h -s 1", "memory: ERROR: Bad alignment."),
        ("memory -a 0x08000003 -f u32h -s 1", "memory: ERROR: Bad alignment."),
        ("memory -a 0x08000001 -f i32 -s 1", "memory: ERROR: Bad alignment."),
        ("memory -a 0x08000002 -f i32 -s 1", "memory: ERROR: Bad alignment."),
        ("memory -a 0x08000003 -f i32 -s 1", "memory: ERROR: Bad alignment."),
        ("memory -a 0x08000001 -f u16 -s 1", "memory: ERROR: Bad alignment."),
        ("memory -a 0x08000001 -f u16h -s 1", "memory: ERROR: Bad alignment."),
        ("memory -a 0x08000001 -f i16 -s 1", "memory: ERROR: Bad alignment."),

        # Outside ITCM, which is from 0x00000000 to 0x00010000.
        ("memory -a 0x00010000 -f u32 -s 1", "memory: ERROR: Memory not readable."),
        ("memory -a 0x0000FFFC -f u32 -s 2", "memory: ERROR: Memory not readable."),

        # User flash memory: 0x08000000 .. 0x08200000
        ("memory -a 0x07FFFFFC -f u32 -s 1", "memory: ERROR: Memory not readable."),
        ("memory -a 0x08200000 -f u32 -s 1", "memory: ERROR: Memory not readable."),

        # System flash memory: 0x1FF00000 ..0x1FF1FFFF
    ]
    for i, pair in enumerate(cmd_resp_pairs):
        cmd, resp_exp = pair
        sport.write_line(cmd)
        resp_got = sport.read_line()
        assert resp_got.startswith(resp_exp), f"#{i}: Got `{resp_got}`."


def test_bad_option(sport: SPort) -> None:
    """Check that the expected error message is sent when the option is not supported."""
    cmd_resp_pairs = [
        ("memory -a 0 -s 1 -f u8 -o 123", "protocol: ERROR: Unknown option."),
    ]
    for i, pair in enumerate(cmd_resp_pairs):
        cmd, resp_exp = pair
        sport.write_line(cmd)
        resp_got = sport.read_line()
        assert resp_got.startswith(resp_exp), f"#{i}: Got `{resp_got}`."


def test_help(sport: SPort) -> None:
    """Check the help option."""
    sport.write_line("memory -h")
    resp = sport.read_all()
    assert len(resp) > 1

    sport.write_line("memory --help")
    resp = sport.read_all()
    assert len(resp) > 1

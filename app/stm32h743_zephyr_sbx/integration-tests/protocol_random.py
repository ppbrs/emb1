"""
Integration tests checking "random" command on stm32h743-zephyr-sbx project.
"""

import itertools
import logging

from integration_tests.sport import SPort

_logger = logging.getLogger()


def test_good(sport: SPort) -> None:
    """Test the `random` command with correct options."""
    size_variants = range(1, 9)
    format_variants = ("u8", "u16", "u32", "u8h", "u16h", "u32h", "i8", "i16", "i32", )
    crypto_variants = ("-c true", "-c false", "-c", "", "-c 0", "-c 1", "-c y", "-c n")

    cnt = 0
    for size_, format_, short, crypto in itertools.product(
            size_variants, format_variants, (True, False), crypto_variants):
        if short:
            cmd = f"random -f {format_} -s {size_} {crypto}"
        else:
            cmd = f"random --format {format_} --size {size_} {crypto}"
        sport.write_line(cmd)
        respln = sport.read_line()
        assert respln.startswith("random: ")
        comps = respln.split()
        assert len(comps) == 1 + size_, \
            f"Got {len(comps)} tokens in response, expected {1 + size_}."
        cnt += 1
    _logger.info("%d variants were tested.", cnt)


def test_bad_size(sport: SPort) -> None:
    """Size more than 8 is not supported; size less than 1 makes no sense."""
    resp_cmd = {
        "random: ERROR: Wrong size.": [
            "random -s 0",
            "random -s 9",
            "random --size 0",
            "random --size 10h",
        ],
        "protocol: ERROR: Option parameter parse error.": [
            "random -s -1",
            "random -s abcd",
        ],
    }
    for resp_exp, cmds in resp_cmd.items():
        for cmd in cmds:
            sport.write_line(cmd)
            resp_got = sport.read_line()
            assert resp_got.startswith(resp_exp), \
                f"Got `{resp_got}` on `{cmd}`. Expected `{resp_exp}`."


def test_bad_format(sport: SPort) -> None:
    """Check that the expected error message is sent when the format is not supported."""
    cmd_resp_pairs = [
        ("random -f qwer", "random: ERROR: Unknown format."),
        ("random --format asdf", "random: ERROR: Unknown format."),
    ]
    for i, pair in enumerate(cmd_resp_pairs):
        cmd, resp_exp = pair
        sport.write_line(cmd)
        resp_got = sport.read_line()
        assert resp_got.startswith(resp_exp), f"#{i}: Got `{resp_got}`."


def test_bad_crypto(sport: SPort) -> None:
    """Check that the expected error message is sent when the crypto is not supported."""
    cmd_resp_pairs = [
        ("random -c 10", "protocol: ERROR: Option parameter parse error."),
        ("random --crypto asdf", "protocol: ERROR: Option parameter parse error."),
    ]
    for i, pair in enumerate(cmd_resp_pairs):
        cmd, resp_exp = pair
        sport.write_line(cmd)
        resp_got = sport.read_line()
        assert resp_got.startswith(resp_exp), f"#{i}: Got `{resp_got}`."


def test_help(sport: SPort) -> None:
    """Check the help option."""
    sport.write_line("random -h")
    resp = sport.read_all()
    assert len(resp) > 1

    sport.write_line("random --help")
    resp = sport.read_all()
    assert len(resp) > 1

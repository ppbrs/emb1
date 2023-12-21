"""
Integration tests checking "random" command on stm32h743-zephyr-sbx project.
"""

import itertools
import logging

from integration_tests.serial_port import SerialPort

_logger = logging.getLogger()


def test_good(serial_port: SerialPort) -> None:
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
        serial_port.write_line(cmd)
        respln = serial_port.read_line()
        assert respln.startswith("random: ")
        comps = respln.split()
        assert len(comps) == 1 + size_, \
            f"Got {len(comps)} tokens in response, expected {1 + size_}."
        cnt += 1
    _logger.info("%d variants were tested.", cnt)


def test_bad_size(serial_port: SerialPort) -> None:
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
            serial_port.write_line(cmd)
            resp_got = serial_port.read_line()
            assert resp_got.startswith(resp_exp), \
                f"Got `{resp_got}` on `{cmd}`. Expected `{resp_exp}`."


def test_bad_format(serial_port: SerialPort) -> None:
    """Check that the expected error message is sent when the format is not supported."""
    cmd_resp_pairs = [
        ("random -f qwer", "random: ERROR: Unknown format."),
        ("random --format asdf", "random: ERROR: Unknown format."),
    ]
    for i, pair in enumerate(cmd_resp_pairs):
        cmd, resp_exp = pair
        serial_port.write_line(cmd)
        resp_got = serial_port.read_line()
        assert resp_got.startswith(resp_exp), f"#{i}: Got `{resp_got}`."


def test_bad_crypto(serial_port: SerialPort) -> None:
    """Check that the expected error message is sent when the crypto is not supported."""
    cmd_resp_pairs = [
        ("random -c 10", "protocol: ERROR: Option parameter parse error."),
        ("random --crypto asdf", "protocol: ERROR: Option parameter parse error."),
    ]
    for i, pair in enumerate(cmd_resp_pairs):
        cmd, resp_exp = pair
        serial_port.write_line(cmd)
        resp_got = serial_port.read_line()
        assert resp_got.startswith(resp_exp), f"#{i}: Got `{resp_got}`."


def test_help(serial_port: SerialPort) -> None:
    """Check the help option."""
    serial_port.write_line("random -h")
    resp = serial_port.read_all()
    assert len(resp) > 1

    serial_port.write_line("random --help")
    resp = serial_port.read_all()
    assert len(resp) > 1

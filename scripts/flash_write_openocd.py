"""Write flash via OpenOCD."""
import argparse
import pathlib
import logging

from emb_spy import Backend


def main() -> None:
    logging.basicConfig(level=logging.INFO)

    prsr = argparse.ArgumentParser(description="...")
    prsr.add_argument("--telnet", dest="use_telnet", action="store_true", help="use telnet")
    prsr.add_argument("--elf", dest="elf", nargs=1, action="store", help="elf")
    prsr.add_argument("--target", dest="target", nargs=1, action="store", help="target")

    args = prsr.parse_args()  # exits if sth is wrong

    print(args)
    elf_path = pathlib.PosixPath(args.elf[0])
    assert elf_path.exists() and elf_path.is_file()

    if args.use_telnet:
        cmd_list = [
            "reset halt",
            f"program {elf_path} verify",
            "reset run",
        ]

        with Backend(
            port=Backend.find_openocd_telnet_port(),
            target_name=args.target[0],
            restart_if_not_running=False,
            halt_if_running=True
        ) as backend:
            for cmd in cmd_list:
                backend.request(cmd=cmd, timeout=30)
    else:
        raise NotImplementedError


if __name__ == "__main__":
    main()

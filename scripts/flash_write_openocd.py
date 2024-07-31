"""
Program a board via OpenOCD.

Examples
--------
$ flash_write_openocd.py \
    --telnet --target stm32f0x.cpu \
    --elf bin/riga-comm-00.gnu.elf
programs a board the is already connected via OpenOCD.

$ flash_write_openocd.py \
    --swd
    --openocd-config boards/riga.openocd.cfg \
    --elf bin/riga-comm-00.gnu.elf
connects to a board via SWD interface and programs it.

"""
import argparse
import logging
import os
import pathlib
import sys

from emb_spy import Backend


def main() -> None:
    """Parse command line and execute commands."""
    logging.basicConfig(level=logging.INFO)
    logging.info("%s", pathlib.Path(sys.argv[0]).name)

    prsr = argparse.ArgumentParser(description="...")
    prsr.add_argument(
        "--telnet", dest="use_telnet", action="store_true", help="Use Telnet")
    prsr.add_argument(
        "--swd", dest="use_swd", action="store_true", help="Use SWD")
    prsr.add_argument(
        "--elf", dest="elf", nargs=1, action="store", help="elf")
    prsr.add_argument(
        "--openocd-config", dest="ood_cfg", nargs=1, action="store",
        help="OpenOCD configuration file.")
    prsr.add_argument(
        "--target", dest="target", nargs=1, action="store", help="target")

    args = prsr.parse_args()  # exits if sth is wrong
    logging.info("args: %s.", args.__dict__)

    elf_path = pathlib.PosixPath(args.elf[0])
    assert elf_path.exists() and elf_path.is_file()

    cmd_list = [
        "reset halt",
        f"program {elf_path} verify",
        "reset run",
    ]

    if args.use_telnet:
        logging.info("using Telnet")

        with Backend(
            port=Backend.find_openocd_telnet_port(),
            target_name=args.target[0],
            restart_if_not_running=False,
            halt_if_running=True
        ) as backend:
            for cmd in cmd_list:
                backend.request(cmd=cmd, timeout=30)

    elif args.use_swd:
        logging.info("using SWD")

        ood_cfg_path = pathlib.PosixPath(args.ood_cfg[0])
        ood_cfg_full_path = pathlib.PosixPath.cwd() / ood_cfg_path
        assert ood_cfg_full_path.exists() and ood_cfg_full_path.is_file()

        ood_cmd = f"program {elf_path} verify reset exit"
        cmd = f"openocd -f {ood_cfg_path} -c '{ood_cmd};'"
        logging.info("OpenOCD command: `%s`", cmd)
        os.system(cmd)
    else:
        raise NotImplementedError


if __name__ == "__main__":
    main()

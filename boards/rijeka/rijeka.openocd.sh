#!/bin/bash

PS3="Enter the number: "
OPT1="Connect on-the-fly."
OPT2="Connect under reset."
select opt in "$OPT1" "$OPT2"; do
	case $opt in
		$OPT1)
			echo "Selected option 1."
			echo
			openocd -f boards/rijeka.on-the-fly.openocd.cfg
			exit 0
			;;
		$OPT2)
			echo "Selected option 2."
			echo
			openocd -f boards/rijeka.reset.openocd.cfg
			exit 0
			;;
		*)
			echo "Selected invalid option."
			echo
			;;
	esac
done
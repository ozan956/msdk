#!/bin/bash
#
#

BOARD=""
EXAMPLE_MODE=""
MAKEGOAL="all"

while [[ $# -gt 0 ]]; do
	case $1 in
	--goal)
		MAKEGOAL="$2"
		shift # past argument
		shift # past value
		;;
	--board)
		BOARD="$2"
		shift # past argument
		shift # past value
		;;
	--mode)
		EXAMPLE_MODE="$2"
		shift # past argument
		shift # past value
		;;
	-*|--*)
		echo "Unknown option $1"
		exit 1
		;;
	*)
		shift # past argument
		;;
	esac
done

if [ "$BOARD" == "" ]; then
	echo "INFO: Default board will be used"
fi

# reset folder
git checkout ./


case ${EXAMPLE_MODE} in
"SYNC")
	sed -ri 's/#define[ ]*MASTERSYNC /#define MASTERSYNC \/\//g' ./main.c
	;;
"ASYNC")
	sed -ri 's/#define[ ]*MASTERSYNC /#define MASTERASYNC \/\//g' ./main.c
	;;
"DMA")
	sed -ri 's/#define[ ]*MASTERSYNC /#define MASTERDMA \/\//g' ./main.c
	;;
"DEFAULT")
	;;
*)
	;;
esac


make ${MAKEGOAL} -j 8 BOARD=${BOARD} 

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
"MSR_SDMA_INSTANCE_0")
	# Use instance 0
	sed -ri 's/#define[ ]*MSR_SDMA_INSTANCE /#define MSR_SDMA_INSTANCE 0 \/\//g' ./main.c
	;;
"MSR_SDMA_INSTANCE_1")
	# Use instance 1
	sed -ri 's/#define[ ]*MSR_SDMA_INSTANCE /#define MSR_SDMA_INSTANCE 1 \/\//g' ./main.c
	;;
"DEFAULT")
	;;
*)
	;;
esac


make ${MAKEGOAL} -j 8 BOARD=${BOARD} 

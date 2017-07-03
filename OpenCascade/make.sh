#!/bin/bash
SPEC=macx-llvm
if [ "$1" == "g++" ]; then
  SPEC=macx-g++
fi

export aSamplePath="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
if [ -e "${aSamplePath}/custom.sh" ]; then source "${aSamplePath}/env.sh"; fi
cd $aSamplePath
if test `uname -s` != "Darwin"; then
  qmake  -o Makefile Exercise0.pro -r
else
  qmake  -spec $SPEC -o Makefile Exercise0.pro -r
fi
make all

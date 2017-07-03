#!/bin/bash

DEB1="$1"
export aSamplePath="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
if [ -e "${aSamplePath}/custom.sh" ]; then source "${aSamplePath}/env.sh"; fi
cd $aSamplePath

host=`uname -s`
STATION=$host
RES_DIR="${aSamplePath}/res"

if test "${DEB1}" == "d"; then
    BIN_DIR="${aSamplePath}/${STATION}/bind"
else
    BIN_DIR="${aSamplePath}/${STATION}/bin"    
fi    

if [ "$STATION" == "Darwin" ]; then
  BIN_DIR="${BIN_DIR}/Exercise.app/Contents/MacOS"
fi

export CSF_ResourcesDefaults="${RES_DIR}"

export PATH="${BIN_DIR}:${PATH}"

if test ! -r "${BIN_DIR}/Exercise"; then
   echo "Executable \"${BIN_DIR}/Exercise\" not found."
   echo "You probably haven't compiled the application. Execute \"make\"."
   exit 1
fi

if [ $# -eq 0 ]
  then
    ${BIN_DIR}/Exercise
else
	${BIN_DIR}/Exercise <"$DEB1"
fi
	
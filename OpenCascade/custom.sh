#!/bin/bash

#Define CASROOT and QTDIR variables in order to generate Makefile files by qmake

export CASROOT="/home/aiman/6.9.1/occt-install"

export QTDIR="/usr/bin/" 

if test "${CASROOT}" == ""; then
   echo "Environment variable \"CASROOT\" was not defined."
   exit 1
fi

if test "${QTDIR}" == ""; then
   echo "Environment variable \"QTDIR\" was not defined."
   exit 1
fi

export PATH=${QTDIR}/bin:${PATH}

#!/bin/bash

if [ -e "${aSamplePath}/custom.sh" ]; then source "${aSamplePath}/custom.sh"; fi
source $CASROOT/env.sh
export CSF_OPT_INC="${CASROOT}/inc:${CSF_OPT_INC}"
#export CSF_OPT_LIB64="${CASROOT}/lin64:${CSF_OPT_LIB64}"

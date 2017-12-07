#!/bin/bash

# Providing fallback for multicore compilation
NCORES=$1
if ! [[ $NCORES =~ ^-?[0-9]+$ ]]
then
    NCORES=$(cat /proc/cpuinfo | grep processor | tail -1 | awk '{print $3+1 }')
fi

(cd crossSections && qmake && make -j $NCORES)
(cd ducts && qmake && make -j $NCORES)
(cd ftrExport && qmake && make -j $NCORES)

#!/bin/bash

mkdir -p ./build/

if cmake -S . -B build ; then
    if make -C ./build -j4 ; then
        ./build/Quester
    else
        printf "\n************\nMAKE FAILED\n************\n"
    fi
else
    printf "\n************\nCMAKE FAILED\n************\n"
fi
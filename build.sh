#!/bin/bash

gcc -O3 -S fmf.c -o fmf.asm
gcc -O3 fmf.c -o fmf_exec
./fmf_exec

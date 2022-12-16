#!/bin/bash

make
rm ex.cor
./asm ex.s
xxd ex.cor > our.txt
rm ex.cor
./eval_tests/asm ex.s
xxd ex.cor > ref.txt
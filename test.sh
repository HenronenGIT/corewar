#!/bin/bash

make
rm all_instructions.cor
./asm all_instructions.s
xxd all_instructions.cor > our.txt
rm all_instructions.cor
./eval_tests/asm all_instructions.s
xxd all_instructions.cor > ref.txt
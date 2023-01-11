#!/bin/bash

#compile all valid .s files with our asm and move to test folder

for FILE in eval_tests/tests/valid_files/*.s; do ./asm $FILE; done

for FILE in eval_tests/tests/valid_files/*.cor; do mv $FILE vm/cor_samples_our_asm/; done

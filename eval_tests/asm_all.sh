#!/bin/bash

for FILE in champs/*.s; do ./asm $FILE; done

for FILE in champs/*.cor; do mv $FILE ../corewar/cor_samples; done
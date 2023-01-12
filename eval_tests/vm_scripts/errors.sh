#!/bin/bash

#test basic error files
for FILE in vm_error_files/*.cor; do ../../corewar $FILE; done

#tests for the -n flag (substitute your own tests)
# champ1=$(ls cor_samples | sort -R | tail -n 1);
# champ2=$(ls cor_samples | sort -R | tail -n 1);
# champ3=$(ls cor_samples | sort -R | tail -n 1);
# champ4=$(ls cor_samples | sort -R | tail -n 1);

# echo $champ1
# echo $champ2
# echo $champ3
# echo $champ4

# ../../corewar -n 1 cor_samples/$champ1 -n 1 cor_samples/$champ2  cor_samples/$champ3 cor_samples/$champ4 -v 1


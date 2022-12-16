#!/bin/bash

# output will be diff'd but I reccomend using VScode's 'compare selected feature as well'
# the competitions can often take a long time (minutes)

champ1=$(ls cor_samples | sort -R | tail -n 1);
champ2=$(ls cor_samples | sort -R | tail -n 1);
champ3=$(ls cor_samples | sort -R | tail -n 1);
champ4=$(ls cor_samples | sort -R | tail -n 1);

echo $champ1
echo $champ2
echo $champ3
echo $champ4

./corewar cor_samples/$champ1 cor_samples/$champ2 cor_samples/$champ3 cor_samples/$champ4 -v 1 > mytest.txt &
../eval_tests/corewar cor_samples/$champ1 cor_samples/$champ2 cor_samples/$champ3 cor_samples/$champ4  > origtest.txt &
wait

diff mytest.txt origtest.txt
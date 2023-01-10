#!/bin/bash

# output will be diff'd but I reccomend using VScode's 'compare selected feature as well'
# the competitions can often take a long time (minutes)

champ1=$(ls cor_samples_ref | sort -R | tail -n 1);
champ2=$(ls cor_samples_ref | sort -R | tail -n 1);
champ3=$(ls cor_samples_ref | sort -R | tail -n 1);
champ4=$(ls cor_samples_ref | sort -R | tail -n 1);

echo $champ1
echo $champ2
echo $champ3
echo $champ4

leaks -atExit -- ../corewar cor_samples_ref/$champ1 cor_samples_ref/$champ2 cor_samples_ref/$champ3 cor_samples_ref/$champ4 -v 1 -dump 10000
#leaks -atExit -- ../eval_tests/corewar_ref cor_samples_ref/$champ1 cor_samples_ref/$champ2 cor_samples_ref/$champ3 cor_samples_ref/$champ4 > origtest.txt 
#wait

#diff mytest.txt origtest.txt
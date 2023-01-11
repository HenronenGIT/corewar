#!/bin/bash

champ1=$(ls cor_samples_ref | sort -R | tail -n 1);
champ2=$(ls cor_samples_ref | sort -R | tail -n 1);
champ3=$(ls cor_samples_ref | sort -R | tail -n 1);
champ4=$(ls cor_samples_ref | sort -R | tail -n 1);

echo $champ1
echo $champ2
echo $champ3
echo $champ4

../../corewar cor_samples_ref/$champ1 cor_samples_ref/$champ2 cor_samples_ref/$champ3 cor_samples_ref/$champ4 -v 21 -dump 10000 > mytest.txt &
../corewar_ref cor_samples_ref/$champ1 cor_samples_ref/$champ2 cor_samples_ref/$champ3 cor_samples_ref/$champ4  -v 20 -d 10000 > origtest.txt &
wait

diff mytest.txt origtest.txt

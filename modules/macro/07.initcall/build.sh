#!/bin/bash
gcc -E initcall.c >> expended_1
gcc -E expended_1 >> expended_2
vim expended_1 
vim expended_2
rm expended*

#!/bin/bash
gcc -E line_counter.c >> expended 
vimdiff line_counter.c expended
rm expended

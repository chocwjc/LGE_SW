#!/bin/bash
gcc  section.c -c section.o
objdump -s section.o
rm section.o

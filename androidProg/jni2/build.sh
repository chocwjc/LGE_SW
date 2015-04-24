#!/bin/sh

gcc Main.c -fPIC -I /usr/lib/jvm/java-1.7.0-openjdk-amd64/include -c -o Main.o
gcc Main.o --shared -o libhello.so

javac Main.java
java  -Djava.library.path=.  -classpath . com.lge.Main

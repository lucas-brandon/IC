#!/bin/bash

g++ $1.cpp -o $1 -lGL -lGLU -lglut `freetype-config --cflags` -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -I/usr/local/include  -L/usr/local/lib -lpng -lz -lfreetype 
./$1

#!/bin/bash

# Put your build command here
g++ -march=native -Ofast -fomit-frame-pointer main.cpp timer.cpp

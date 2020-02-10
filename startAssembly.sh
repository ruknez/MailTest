#!/bin/bash


mkdir build;
cd build || exit 1;
cmake .. $* || exit 2;
make || exit 3;


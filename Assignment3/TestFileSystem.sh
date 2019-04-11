#!/bin/bash

rm -r disk; mkdir disk
cd io
make
./File
cd ../apps
make
./test01; ./test02
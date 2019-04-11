#!/bin/bash

cd io
make
./File
cd ../apps
make
./test01; ./test02
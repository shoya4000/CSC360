#!/bin/bash

rm -r disk; mkdir disk
cd io
make
cd ../apps
make
#!/bin/bash

cd ..
make
cat tests/input_redirect.txt | ./bin/rshell > tests/output.txt
cd tests

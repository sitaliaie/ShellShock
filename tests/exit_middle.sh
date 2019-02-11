#!/bin/bash

cd ..
make
cat tests/exit_middle.txt | ./bin.rshell > tests/output.txt
cd test_cases

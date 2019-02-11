#!/bin/bash

cd ..
make
cat tests/exit_beginning.txt | ./bin.rshell > tests/output.txt
cd test_cases

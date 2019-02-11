#!/bin/bash

cd ..
make
cat tests/exit_end.txt | ./bin.rshell > tests/output.txt
cd test_cases

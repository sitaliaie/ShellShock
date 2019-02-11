#!/bin/bash

cd ..
make
cat tests/command.txt | ./bin.rshell > tests/output.txt
cd test_cases

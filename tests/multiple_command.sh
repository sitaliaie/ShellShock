#!/bin/bash

cd ..
make
cat tests/multiple_command.txt | ./bin/rshell > tests/output.txt
cd tests

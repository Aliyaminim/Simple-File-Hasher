#!/bin/bash

echo End-to-End testing has started!
echo
for file in e2e_test/* ; do
    echo $file
    ../build/driver $file
    echo
done
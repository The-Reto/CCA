#!/bin/bash

for d in {1..10}; do
    seed=$(cksum <<< "$(date)" | cut -f 1 -d ' ')
    touch ./Documentation/Validation/"two_keys_${seed}".txt
    echo "$d / 10"
    ./execs/tests/Test_Dieharder.run "${seed}" | dieharder -a -g 200 > ./Documentation/Validation/"two_keys_${seed}".txt
done
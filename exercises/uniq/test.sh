#!/bin/bash

for tc in {1..2}; do
    python uniq.py < tc${tc}-in.txt > tc-actual.txt
    diff tc${tc}-out.txt tc-actual.txt \
        && echo "tc-${tc} passed..." \
        || echo "tc-${tc} FAILED!!!"
done

echo "$(python uniq.py < uniq.py | tail -n 1) points"

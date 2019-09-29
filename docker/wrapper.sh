#!/bin/sh

echo "Running qmljsify"
set -e
cd /tmp
qmljsify "$@"
cp *.js /data

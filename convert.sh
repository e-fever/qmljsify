#!/bin/bash

cd /tmp
qmljsify convert $*
cp *.js /data

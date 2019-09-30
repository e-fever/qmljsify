#!/bin/bash

export XDG_RUNTIME_DIR=/tmp/xdg
mkdir -p $XDG_RUNTIME_DIR
export HOME=/tmp/home
mkdir -p $HOME
set -e
cd /tmp
qmljsify "$@"
cp *.js /data

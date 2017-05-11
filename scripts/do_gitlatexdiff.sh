#!/bin/bash
[ $# -ne 2 ] && echo "Usage: $0 <old sha1> <new sha1>" && exit 1
set -ex
#need to use latexpand that supports subimport
export PATH=$PWD/latexpand:$PATH
./git-latexdiff --tmpdirprefix $PWD --verbose --latexmk \
  --output cws-thesis.$1_$2.pdf --main cws-thesis.tex $1 $2

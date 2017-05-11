#!/bin/bash

# the first argument should be the pdf file
pdffile="$1"
echo $pdffile

# open the pdf
/usr/bin/osascript << EOF
  set theFile to POSIX file "${pdffile}" as alias
  tell application "Skim"
  open theFile
  end tell
EOF

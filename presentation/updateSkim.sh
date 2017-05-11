#!/bin/bash

# the first argument should be the pdf file
pdffile="$1"
echo $pdffile

# reload the pdf
/usr/bin/osascript << EOF
  set theFile to POSIX file "${pdffile}" as alias
  set thePath to POSIX path of theFile
  tell application "Skim"
  set theDocs to get documents whose path is thePath
  if (count of theDocs) > 0 then revert theDocs
  open theFile
  end tell
EOF

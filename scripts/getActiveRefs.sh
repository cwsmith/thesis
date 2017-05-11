#!/bin/bash
refs=$(grep bibitem out/cws-thesis.bbl)
count=$((0))
itemFile=$(mktemp)
for i in $refs; do 
  count=$((count+1))
  j=${i##\\bibitem\{}
  name=${j%%\}}
  res=$(grep -i ^@\.*$name scorec-refs/scorec-refs.bib)
  [ -z "$res" ] && echo "failed to find ref $name" && exit 1
  echo $res >> $itemFile
done
echo $count
sort $itemFile
echo "done"

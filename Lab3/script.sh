#!/bin/bash

table_name=""
counter=0
var1=""
var_col=""

while IFS= read -r line
do
if [[ "$counter" == 0 ]] ; then
  table_name=($line awk '{ gsub (" ", "", $0); print}')
elif [[ "$counter" == 1 ]] ; then
  var_col=$(echo "$line" | awk '{ gsub (" ", "", $0); print}')
  
  var1="INSERT INTO $table_name($var_col) VALUES"
else
 if [[ "$counter" -gt 2 ]] ; then
    echo "$var1" | sed 's/ //g'
  else
    echo "$var1"
  fi
  var1='('${line}'),'
fi
((counter++))
done < trees.csv
echo ${var1::-1}';'

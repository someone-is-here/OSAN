#!/bin/bash

table_name=""
counter=0
var1=""
while IFS= read -r line
do
if [[ "$counter" == 0 ]] ; then
  table_name=${line//[[:blank:]]/}
elif [[ "$counter" == 1 ]] ; then
  var1="INSERT INTO $table_name(${line//[[:blank:]]/}) VALUES"
else
  echo "$var1"
  var1='('${line//[[:blank:]]/}'),'
fi
((counter++))
done < trees.csv
echo ${var1::-1}';'


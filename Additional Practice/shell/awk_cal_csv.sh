#!/bin/bash

echo "请输入文件名"
read filename

echo "请输入列号"
read row

echo "请输入分隔符"
read div

reg="^[0-9]+(\\\\.[0-9]+)?(,[0-9]+(\\\\.[0-9]+)?)*$"

awk -F"${div}" -v row="${row}" -v reg="${reg}" 'BEGIN{sum=0;count=0} $0 ~ reg {sum+=$row;count++}END{if(count > 0)  {print sum,sum/count}}' "${filename}"

# /^[0-9]+(\.[0-9]+)?(,[0-9]+(\.[0-9]+)?)*$/

# echo # # #-F${div} \'BEGIN{sum=0;count=0} \/^[0-9]+(\.[0-9]+)?(,[0-9]+(\.[0-9]+)?)*$\/ {sum+=$${row};count++}END{print sum,sum/count}\' ${filename}`



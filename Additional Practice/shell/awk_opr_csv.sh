#!/bin/bash

echo "请输入文件名"
read filename

echo "请输入起始行号"
read col_start

echo "请输入结束行号"
read col_end

echo "请输入排序列号"
read row

awk -F ',' -v  filename="${filename}" '{for(i=1;i<=NF;i++) { if($i~/^[[:alpha:]]+$/) count[$i]++}} END {for (j in count) print j,count[j]}' "${filename}" | sort -r -n -k2

awk -F ',' -v filename="${filename}" -v c_start="${col_start}" -v c_end="${col_end}" -v row="${row}" 'NR>=c_start&&NR<=c_end' "${filename}" | sort -k${row}

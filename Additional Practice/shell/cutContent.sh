#! /bin/bash

echo "请输入文件名:"

read filename

echo "请输入分割列的列数"

read cut_row

echo "请输入分割字符的起始位置"

read cut_char_start

echo "请输入分割字符的结束位置"

read cut_char_end

echo ${filename}

echo `cut -d ',' -f ${cut_row} ${filename}`

echo `cut -c ${cut_char_start}-${cut_char_end} ${filename}`



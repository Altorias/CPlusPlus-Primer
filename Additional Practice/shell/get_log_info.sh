#!/bin/bash

id=$1
file="log/hu.log"

log_info=`grep "g_uid\[${id}\]" $file`

#echo $log_info



# 获取时间
#time0=`grep "g_uid\[${id}\]" $file | awk -F '[][]' '{print $2}'`
#echo $time0
#echo "-----"
#time1=`echo $log_info | awk -F '[][]' '{print $2}'`

#echo $time1
# 获取命令号
#command0=`grep "g_uid\[${id}\]" $file | awk -F '[=&]' '{for(i=1;i<=NF;i++) {if ($i ~ /command/ && $(i+1) !~ /^[0-9]/ ) print $(i+1)} }' `
#echo $command0

# 获取seq号
#seq=`grep "g_uid\[${id}\]" $file | awk -F '[]=]' '{print $(NF-1)}'`
#echo $seq

#res=`grep "g_uid\[${id}\]" $file | awk -F '[]=&[]' '{for(i=1;i<=NF;i++) {if ($i ~ /command/ && $(i+1) !~ /^[0-9]/ ){print $2,$(i+1),$(NF-1);}}}'`
#echo $res

grep "g_uid\[${id}\]" $file | awk -F '[]=&[]' '{for(i=1;i<=NF;i++) {if ($i ~ /command/ && $(i+1) !~ /^[0-9]/ ){print $2,$(i+1),$(NF-1);}}}' >> log_res.log

# grep "g_uid\[1013483\]" log/hu.log | awk -F '[]=&[]' '{for(i=1;i<=NF;i++) {if ($i ~ /command/ && $(i+1) !~ /^[0-9]/ ){print $2,$(i+1),$(NF-1);}}}'

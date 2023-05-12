#!/bin/bash

Cpu_max=50
Memory_max=50

# 日志文件路径
log_file=~/charliegu/practice/shell/log/server_monitor.log

# 无限循环，每隔一定时间检查一次CPU和内存使用率
# 更新：使用corntab运行，将循环部分注释掉
# while true; do
  # 获取CPU和内存使用率
  Cpu=$(top -bn1 | grep "Cpu(s)" | awk '{printf "%.2f\n", $2+$4}')
  Memory=$(free | awk '/Mem/{printf "%.2f", $3/$2*100}')
  
  echo $Cpu
  echo $Memory

  # 记录日志
  echo "log - $(date +"%Y-%m-%d %H:%M:%S") - CPU: ${Cpu}%, Memory: ${Memory}%" >> "${log_file}"

  # 检查是否需要发送告警信息
  if (( $(echo "${Cpu} >= ${Cpu_max}" | bc -l) )) || (( $(echo "${Memory} >= ${Memory_max}" | bc -l) )); then
      echo "warning - $(date +"%Y-%m-%d %H:%M:%S") - CPU: ${Cpu}%, Memory: ${Memory}%" >> "${log_file}"
  fi

  # 等待一段时间
  # sleep 10 # 10S
# done

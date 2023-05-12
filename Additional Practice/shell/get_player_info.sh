#!/bin/bash

# 玩家ID，作为参数传入
uid=$1

url="http://54.223.214.34:18010/westgame_hu_op?uid=${uid}&command=operate_login_get&checkac=0"

player_info=$(curl -s $url)

#echo $player_info
# 筛选数据
pattern=$(echo $player_info | sed -n 's/^.*"svr_player":{\(.*\)},"svr_player_chronicle".*$/\1/p')
# pattern=$(echo $player_info | sed -n 's/^.*"svr_player":{\(.*\)}.*$/')
# cut -d '"' -f 4
echo $pattern
player_name=$(echo $pattern | grep -o '"uin":"[^"]*"' | cut -d '"' -f 4)
player_level=$(echo $pattern | grep -o '"level":"[^"]*"' | cut -d '"' -f 4)
player_server=$(echo $pattern  | grep -o '"sid":"[^"]*"' | cut -d '"' -f 4)
echo "player name : ${player_name}"
echo "player level : ${player_level}"
echo "player server : ${player_server}"




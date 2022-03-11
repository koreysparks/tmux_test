#!/bin/bash
. /etc/profile
. ~/.bash_profile

index=$1

#mkdir -p /home/user0/cron/
TMUX=$(echo $(whereis tmux) |cut -d' ' -f2)

rem_dir=/home/jys/tmux_test/lib/debug/in_tmux/
s_name='tmux_win_'${index}''
w_bk_name='rem_bk'
w_rs_name='rem_rs'

usleep 300000s
${TMUX} send-keys -t${s_name}:${w_bk_name} C-m C-c
usleep 300000s
${TMUX} send-keys -t${s_name}:${w_rs_name} C-m C-c
usleep 300000s

${TMUX} send-keys -t${s_name}:${w_rs_name}  'exit' C-m
usleep 30000s
${TMUX} send-keys -t${s_name}:${w_rs_name}  'exit' C-m
usleep 30000s
${TMUX} send-keys -t${s_name}:${w_bk_name}  'exit' C-m
usleep 30000s
${TMUX} send-keys -t${s_name}:${w_bk_name}  'exit' C-m


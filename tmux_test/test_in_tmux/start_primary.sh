#!/bin/bash

. /etc/profile
. ~/.bash_profile

index=$1

TMUX=$(echo $(whereis tmux) |cut -d' ' -f2)

# rem¸ùÄ¿Â¼
rem_dir=/home/jys/tmux_test/lib/debug/in_tmux/

s_name='tmux_win_'${index}''
w_bk_name='rem_bk'
w_rs_name='rem_rs'

#mkdir -p /home/user0/cron/
WIN_ARR=(${w_bk_name} ${w_rs_name} )

cd ${rem_dir}
mkdir -p bk/${index}
cp exe bk/${index}/
mkdir -p rs/${index}
cp exe rs/${index}/

${TMUX} has-session -t${s_name} 
if [ $? != '0' ]
then
	${TMUX} new-session -d -s${s_name} -n${w_bk_name}
	ret=$?
	if [ $ret != '0' ]
	then
	exit $ret
	fi
else
	for WIN in ${WIN_ARR[*]}
	do
		${TMUX} list-window -t${s_name} | grep ${WIN} > /dev/null
		if [ $? == '0' ]
		then
			${TMUX} send-keys -t${s_name}:${WIN} C-m C-m
			${TMUX} send-keys -t${s_name}:${WIN} C-m C-m 'quit' C-m
			usleep 3000000
			${TMUX} send-keys -t${s_name}:${WIN} C-m C-c
			usleep 100000
			${TMUX} send-keys -t${s_name}:${WIN} C-m C-c
		fi
	done
fi

for WIN in ${WIN_ARR[*]}
	do
	#${TMUX} select-window -t${s_name}:${WIN}
	${TMUX} list-window -t${s_name} | grep ${WIN} > /dev/null
	if [ $? != '0' ]
	then
		${TMUX} new-window -d -t${s_name} -n${WIN} 
	#else
		#echo "tmux window" ${WIN} "does exist"
	fi
	done


usleep 10000

${TMUX} send-keys -t${s_name}:${w_bk_name} 'cd '${rem_dir}'bk/'${index}'' C-m
${TMUX} send-keys -t${s_name}:${w_bk_name} './exe '${index}'' C-m
usleep 10000
${TMUX} send-keys -t${s_name}:${w_rs_name} 'cd '${rem_dir}'rs/'${index}'' C-m
${TMUX} send-keys -t${s_name}:${w_rs_name} './exe '${index}'' C-m

${TMUX} select-window -t${s_name}:${w_ot_name}
#${TMUX} attach-session -t ${s_name}


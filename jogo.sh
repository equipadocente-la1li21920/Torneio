#!/bin/bash

if [[ $# -ne 2 ]]
then
	echo Usage: $0 Player1 Player2
	exit
fi

mkdir -p jogos
rm -f jogos/pos[0-9][0-9]

ulimit -t 2
jog1=$1
jog2=$2
dir=jogos

mov=1
atual=inicial
progs=($jog1 $jog2)
i=0


while ! ./ended $atual
do
	prog=${progs[$i]}
	prox=$(printf 'jogos/pos%02d' $mov)
	next=$(( ($i + 1) % 2 ))
	./$prog $atual $prox >& /dev/null
	echo
	tail -1 $prox
	if ! ./valida $atual $prox
	then
		echo DES $(( i + 1 ))
		echo END $(( $next + 1 ))
		exit
	fi
	head -8 $prox | sed -e 's/./& /g'
	atual=$prox
	mov=$(expr $mov + 1)
	i=$next
done

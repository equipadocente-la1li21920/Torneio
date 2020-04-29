#!/bin/bash

rm -f vencedores

for jogo in jogo_*_*.log
do
        C1C2=`echo $jogo | sed -e 's/^jogo_//; s/.log$//'`
        C1=`echo $C1C2 | cut -d_ -f1`
        C2=`echo $C1C2 | cut -d_ -f2`
	res=$(( `tail -n1 $jogo | cut -f2 -d\ ` - 1 ))
	jogs=($C1 $C2)
	echo ${jogs[$res]} >> vencedores
done

for jog in `sort -u vencedores`
do
	echo $jog `grep $jog vencedores | wc -l`
done | sort -n +1 -r

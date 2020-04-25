rm -f jogo_*.log

if [ ! -d concorrentes ]
then
	echo "Erro: diretoria de concorrentes não existe!"
	exit
fi

for c1 in concorrentes/*
do
	for c2 in concorrentes/*
	do
		if [[ "$c1" != "$c2" ]]
		then
			C1=${c1##concorrentes/}
			C2=${c2##concorrentes/}
			./jogo.sh $c1 $c2 > jogo_${C1}_${C2}.log
			echo -n "$C1 $C2 "
			tail -n 1 jogo_${C1}_${C2}.log
		fi
	done
done

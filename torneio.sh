rm -f jogo_*.log
rm -f jogo_*.mp4

get_logo() {
	if [ -f "logos/$1.png" ]
	then
		logo=logos/$1.png
	else
		logo=~/Downloads/5.jpg
	fi
	echo $logo
}

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

			cp inicial jogos/pos00
			logo1=$(get_logo $C1)
			logo2=$(get_logo $C2)
			./render.py $C1 $C2 $logo1 $logo2
			ffmpeg -r 1 -i jogos/pos%02d.svg -pix_fmt yuv420p jogo.mp4 &> /dev/null
			mv jogo.mp4 jogo_${C1}_${C2}.mp4
		fi
	done
done

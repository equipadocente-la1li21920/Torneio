CFLAGS=-std=gnu11 -Wall -Wextra -pedantic-errors -g
TABULEIROS=$(wildcard tab[0-9]) inicial
SCRIPTS=$(wildcard *.sh) $(wildcard *.py)

all: valida ended aleat preparar
valida: valida.c common.c
ended: ended.c common.c
aleat: aleat.c common.c
ff: ff.c common.c

preparar:
	mkdir -p campeonato
	mkdir -p campeonato/concorrentes
	mkdir -p campeonato/logos
	cp inicial valida ended $(SCRIPTS) campeonato

final.html: final.md
	file="final";data=`date`; pandoc -s "$$file.md" -M date="Last Update: $$data" -o "$$file.html"
	scp final.html rcm@shiva.di.uminho.pt:~/public_html/aulas/1920/lab

zip: $(wildcard *.h) $(wildcard *.c) $(SCRIPTS) $(TABULEIROS) Makefile final.md
	zip -9 torneio.zip $^

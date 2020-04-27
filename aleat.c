/*
 * Este jogador aleatório é super básico! Ele nem verifica se o jogo acabou
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "common.h"
#include "aleat.h"

/**
 * Escolhe a casa
 * */
COORDENADA escolher(CASA tab[8][8], char ultima[3]) {
	int lastL = '8' - ultima[1];
	int lastC = ultima[0] - 'a';
	COORDENADA poss[8];
	int possiveis = 0;

	FORVB(L, lastL - 1, lastL + 1) 
		FORVB(C, lastC - 1, lastC + 1) {
			if(C >= 0 && C < 8 && L >= 0 && L < 8 && vazia(tab[L][C])) {
				poss[possiveis++] = (COORDENADA) {L, C};
			}
		}
	
	return poss[rand() % possiveis];
}

COORDENADA escolher_qualquer(CASA tab[8][8], char ultima[3] __attribute__((unused))) {
	while(1) {
		int L = rand() % 8;
		int C = rand() % 8;
		if(vazia(tab[L][C]))
			return (COORDENADA) {L, C};
	}
}


int jogar(CASA tab[8][8], char ultima[3], char* movs[64], int *num_movs) {
	int lastL = '8' - ultima[1];
	int lastC = ultima[0] - 'a';
	COORDENADA coord;
	if(1 || rand() % 10 != 0)
		coord = escolher(tab, ultima);
	else
		coord = escolher_qualquer(tab, ultima);

	tab[lastL][lastC] = PRETA;
	tab[coord.linha][coord.coluna] = BRANCA;
	char *lst = calloc(3, 1);
	lst[0] = 'a' + coord.coluna;
	lst[1] = '8' - coord.linha;
	movs[(*num_movs)++] = lst;
	return 1;
}

int main(int argc, char **argv) {
	CASA tab[8][8];
	char ultima[3];
	char *movs[64];
	int num_movs = 0;

	struct timeval time;
	gettimeofday(&time,NULL);
	srand((time.tv_sec * 1000) + (time.tv_usec / 1000));

	if(argc != 3) {
		printf("Uso %s <tabuleiro a ler> <tabuleiro a escrever>\n", argv[0]);
		return 0;
	}

	if(testar(ler(argv[1], tab, ultima, movs, &num_movs), "Não consegui ler o tabuleiro %s\n", argv[1])) {
	} else
		return 1;

	jogar(tab, ultima, movs, &num_movs);
	gravar(argv[2], tab, movs, num_movs);
	return 0;
}

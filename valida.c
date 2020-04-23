#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

int delta(
	CASA tab1[8][8],
	CASA tab2[8][8]) {
	int diferentes = 0;
	FORVN(L, 8)
		FORVN(C, 8) {
			CASA fst = tab1[L][C];
			CASA snd = tab2[L][C];

			if(fst != snd) {
				if(
					(vazia(fst) && snd == BRANCA) ||
					(fst == BRANCA && snd == PRETA)
				  ) diferentes ++;
				else
					return 0;
			}
		}
	return diferentes == 2;
}

int main(int argc, char **argv) {
	CASA tab1[8][8];
	CASA tab2[8][8];
	char ultima[3];
	char *movs[64];
	int num_movs = 0;

	if(argc != 3) {
		printf("Uso %s <tabuleiro a ler> <tabuleiro a escrever>\n", argv[0]);
		return 0;
	}

	if(
		testar(ler(argv[1], tab1, ultima, movs, &num_movs), "Não consegui ler o tabuleiro %s\n", argv[1]) &&
		testar(ler(argv[2], tab2, ultima, movs, &num_movs), "Não consegui ler o tabuleiro %s\n", argv[2]) &&
		testar(delta(tab1, tab2), "O tabuleiro %s não corresponde a uma jogada depois do tabuleiro %s\n", argv[2], argv[1]))
		return 0;
	else
		return 1;
}

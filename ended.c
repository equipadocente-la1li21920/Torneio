#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

int ended(CASA tab[8][8], char *ultima, int num_movs) {
	int lastL = '8' - ultima[1];
	int lastC = ultima[0] - 'a';

	if(lastL == 7 && lastC == 0)
		return 1;

	if(lastL == 0 && lastC == 7)
		return 2;

	FORVB(L, lastL - 1, lastL + 1)
		FORVB(C, lastC - 1, lastC + 1)
			if(L >= 0 && C >= 0 && L < 8 && C < 8 && vazia(tab[L][C]))
				return 0;
	return 1 + ((num_movs + 1) % 2);
}

int main(int argc, char **argv) {
	CASA tab[8][8];
	char ultima[3];
	char *movs[64];
	int num_movs = 0;
	int which;

	if(argc != 2) {
		printf("Uso %s <tabuleiro a ler>\n", argv[0]);
		return 0;
	}


	testar(ler(argv[1], tab, ultima, movs, &num_movs), "Não consegui ler o tabuleiro %s\n", argv[1]);
	if((which = ended(tab, ultima, num_movs))) {
		printf("END %d\n", which);
		return 0;
	} else
		return 1;
}

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "common.h"

int testar(int condicao, const char *formato, ...) {
	int flag = 1;
	va_list args;
	va_start(args, formato);

	if(!condicao) {
		vprintf(formato, args);
		flag = 0;
	}

	va_end(args);
	return flag;
}

int carateres_validos(int lineno, char *s, int *moves) {
	static int num_brancas = 0;
	if(lineno == 0)
		num_brancas = 0;

	FORVN(I, 8) {
		if(lineno == 0 && I == 7) {
		       if(s[I] != DOIS && s[I] != BRANCA)
			       return 0;
		} else if(lineno == 7 && I == 0) {
		       if(s[I] != UM && s[I] != BRANCA)
			       return 0;
		} else if(strchr(".*#", s[I]) == NULL)
			return 0;
		if(s[I] == BRANCA) {
			num_brancas++;
			(*moves)++;
		}
		if(s[I] == PRETA) {
			(*moves)++;
		}
	}
	if(num_brancas > 1)
		return 0;
	return 1;
}

int contiguas(char *c1, char *c2) {
	int L1 = '8' - c1[1];
	int L2 = '8' - c2[1];
	int C1 = c1[0] - 'a';
	int C2 = c2[0] - 'a';

	return abs(L1 - L2) <= 1 && abs(C1 - C2) <= 1;
}


int coordenada_usada(char coord[3], CASA tab[8][8], int usado[8][8], char *ultima) {
	int L = '8' - coord[1];
	int C = coord[0] - 'a';
	if(strchr("*#", tab[L][C]) == NULL) return 0;
	if(usado[L][C]) return 0;
	if(!contiguas(ultima, coord))
		return 0;
	usado[L][C] = 1;
	strcpy(ultima, coord);
	return 1;
}

int e_branca(char coord[3], CASA tab[8][8]) {
	int L = '8' - coord[1];
	int C = coord[0] - 'a';
	return tab[L][C] == BRANCA;
}

int valida_jogada(FILE *f, int I, int num_jogs, CASA tab[8][8], int usado[8][8], char *ultima, char *movs[64], int *num_movs) {
	int L = I + 9;
	char buf[BUF_SIZ];
	int jog;
	char p1[3];
	char p2[3];
	if(!testar(fgets(buf, BUF_SIZ, f) != NULL, "Não consegui ler a linha %d\n", L))								return 0;
	if(num_jogs == 2 && !testar(strlen(buf) == 10, "Linha nº %d não tem 9 carateres: %s\n", L, buf))					return 0;
	if(num_jogs == 1 && !testar(strlen(buf) == 7, "Linha nº %d não tem 6 carateres: %s\n", L, buf))						return 0;
	if(!testar(sscanf(buf, "%d: %s %s", &jog, p1, p2) == num_jogs + 1, "Formato da linha %d está errado", L))				return 0;
	if(!testar(jog == I + 1, "Linha %d não corresponde à jogada %d mas sim à jogada %d\n", L, I + 1, jog))					return 0;
	if(!(testar(coordenada_usada(p1, tab, usado, ultima), "O primeiro movimento da linha %d é inválido: %s\n", L, p1)))			return 0;
	if(num_jogs == 2 && !(testar(coordenada_usada(p2, tab, usado, ultima), "O segundo movimento da linha %d é inválido: %s\n", L, p2)))	return 0;
	if(num_jogs == 2) {
		movs[(*num_movs)++] = strdup(p1);
		movs[(*num_movs)++] = strdup(p2);
		strcpy(ultima, p2);
	} else {
		movs[(*num_movs)++] = strdup(p1);
		strcpy(ultima, p1);
	}
	return 1;
}

int valida(FILE *f, CASA tab[8][8], char ultima[3], char *movs[64], int *num_movs) {
	char buf[BUF_SIZ];
	int movimentos = 0;
	int usado[8][8] = {0};

	FORVN(L, 8) {
		if(!(
			testar(fgets(buf, BUF_SIZ, f) != NULL, "Não consegui ler a linha %d\n", L + 1)		&&
			testar(strlen(buf) == 9, "Linha nº %d não tem 8 carateres: %s\n", L, buf)		&&
			testar(carateres_validos(L, buf, &movimentos), "Linha nº %d não é válida: %s\n", L, buf)
		    ))
			return 0;
		FORVN(C, 8)
			tab[L][C] = buf[C];
	}

	if(fgets(buf, BUF_SIZ, f) == NULL) {
		if(!testar(movimentos == 1, "Não consegui ler a linha em branco\n")) {
			return 0;
		} else {
			return 1;
		}
	}

	if(!testar(strcmp(buf, "\n") == 0, "Linha 9 não está em branco: %s\n", buf))
		return 0;

	FORVN(I, (movimentos - 1) / 2) {
		valida_jogada(f, I, 2, tab, usado, ultima, movs, num_movs);
	}
	if(movimentos % 2 == 0) {
		valida_jogada(f, movimentos / 2 - 1, 1, tab, usado, ultima, movs, num_movs);
	}

	if(!(testar(e_branca(ultima, tab), "O último movimento não corresponde a uma casa branca\n")))
		return 0;
	return 1;
}

int ler(char *filename, CASA tab[8][8], char ultima[3], char* movs[64], int *num_movs) {
	char buf[BUF_SIZ];
	FILE *f = fopen(filename, "r");
	if(f == NULL) {
		sprintf(buf, "Não consegui ler do tabuleiro %s", filename);
		perror(buf);
		return 0;
	}
	*num_movs = 0;
	strcpy(ultima, "e5");

	int ret = valida(f, tab, ultima, movs, num_movs);
	fclose(f);
	return ret;
}

int vazia(CASA val) {
	return val == VAZIO || val == UM || val == DOIS;
}

void gravar(char *filename, CASA tab[8][8], char *movs[64], int num_movs) {
	FILE *f = fopen(filename, "w");

	if(f == NULL) {
		perror("Ao gravar");
		abort();
	}

	FORVN(L, 8) {
		FORVN(C, 8) {
			fprintf(f, "%c", tab[L][C]);
		}
		fprintf(f, "\n");
	}
	fprintf(f, "\n");
	for(int I = 0, K = 0; I < num_movs; I += 2, K++) {
		if(I + 1 < num_movs)
			fprintf(f, "%02d: %s %s\n", K + 1, movs[I], movs[I + 1]);
		else
			fprintf(f, "%02d: %s\n", K + 1, movs[I]);
	}
	fclose(f);
}

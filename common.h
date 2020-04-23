#define BUF_SIZ	1024
#define FORVN(_var, _times) for(int _var = 0; _var < _times; _var++)
#define FORVB(_var, _inf, _sup) for(int _var = _inf; _var <= _sup; _var++)
#define FORN(_times) FORVN(_V, _times)
#define FOR_NEIGH(_VL, _VC, tab, L, C)	\
	FORVB(_VL, L - 1, L + 1) \
		FORVB(_VC, C - 1, C + 1) \
			if(_VC >= 0 && _VC < 8 && _VL >= 0 && _VL < 8 && vazia(tab[_VL][_VC]))

typedef enum {
	UM	= '1',
	DOIS	= '2',
	VAZIO	= '.',
	BRANCA	= '*',
	PRETA	= '#',
} CASA;

typedef struct {
	int linha;
	int coluna;
} COORDENADA;

int carateres_validos(int lineno, char *s, int *moves);
int coordenada_usada(char coord[3], CASA tab[8][8], int usado[8][8], char *ultima);
int e_branca(char coord[3], CASA tab[8][8]);
void gravar(char *filename, CASA tab[8][8], char *movs[64], int num_movs);
int ler(char *filename, CASA tab[8][8], char ultima[3], char* movs[64], int *num_movs);
int testar(int condicao, const char *formato, ...);
int valida(FILE *f, CASA tab[8][8], char ultima[3], char *movs[64], int *num_movs);
int valida_jogada(FILE *f, int I, int num_jogs, CASA tab[8][8], int usado[8][8], char *ultima, char *movs[64], int *num_movs);
int vazia(CASA val);

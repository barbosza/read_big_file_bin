#define ERRO_LISTA_VAAZIA -1
#define ERRO_POS_INVALIDA -1
#define ERROR_INVALID_CARACTER -2

typedef struct eleDuplo{
    void *info;
    struct eleDuplo *ant, *suc;
}ElementoDuplo;

typedef struct{
    int tamInfo;
    int campos;
    ElementoDuplo *cabeca;
    ElementoDuplo *fim;
}LDE;

int inicializa_inteiro(LDE *l,char *info);

void mostra_int(void *info);

ElementoDuplo *aloca_elemento(int tamInfo, void *info);

void inicializa_lista(LDE *l, int t);

int insereNoInicio(LDE *l, void *info);

int insereNoFim(LDE *l, void *info);

int removeNoInicio(LDE *l, void *info);

int removeNoFim(LDE *l, void *info);

int lista_vazia(LDE l);

void mostra_lista(LDE l, void (*mostra_info)(void *));

void limpa_lista(LDE *l);

int insereNaPosicao(LDE *l, void *info, int pos);

int removeNaPosicao(LDE *l, void *info, int pos);

int modifica(LDE *l, void *info, int pos);

int leValor(LDE *l, void *info, int pos);

int insereEmOrdem(LDE *l, void *info, int (*compara)(void *, void *));

int verificaStringNumero(char *linha);

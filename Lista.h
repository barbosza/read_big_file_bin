#define ERRO_LISTA_VAAZIA -1
#define ERRO_POSICAO_INVALIDA -2


typedef struct ele
{
    void *info;
    struct ele *proximo;
}Elemento;

typedef struct
{
    int tamInfo;
    Elemento *cabeca;
}Lista;

void inicializa_lista(Lista *l, int t);

int insereNoInicio(Lista *l, void *info);

int insereNoFim(Lista *l, void *info);

int removeNoInicio(Lista *l, void *info);

int removeNoFim(Lista *l, void *info);

int lista_vazia(Lista l);

Elemento *aloca_elemento(int tamInfo, void *info);

void mostra_lista(Lista l, void (*mostra_info)(void *));

void limpa_lista(Lista *l);

int insereNaPosicao(Lista *l,void *info,int pos);

int insereEmOrdem(Lista *l,void *info,int(*compara)(void*,void*));

int compara_float(void *a,void *b);

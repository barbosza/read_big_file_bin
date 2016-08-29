
#include "Lista.h"
#include <stdlib.h>
#include <stdio.h>

void inicializa_lista(Lista *l, int t)
{
    l->tamInfo = t;
    l->cabeca = NULL;
}

int insereNoInicio(Lista *l, void *info)
{
    Elemento *p = aloca_elemento(l->tamInfo, info);

    if(p == NULL)
        return 0;/*Erro na alocação.*/

    p->info = malloc(l->tamInfo);

    if(p->info == NULL)
    {
        free(p);
        return 0;/*Erro.*/
    }

    memcpy(p->info, info, l->tamInfo);

    p->proximo = l->cabeca;

    l->cabeca = p;

    return 1;
}

int insereNoFim(Lista *l, void *info)
{
    if(lista_vazia(*l))
        return insereNoInicio(l, info);

    Elemento *p = aloca_elemento(l->tamInfo, info);

    if(p == NULL)
        return 0;

    Elemento *aux = l->cabeca;

    while(aux->proximo != NULL)
        aux = aux->proximo;

    p->proximo = NULL;

    aux->proximo = p;

    return 1;
}

int removeNoInicio(Lista *l, void *info)
{
    if(lista_vazia(*l))
        return ERRO_LISTA_VAAZIA;

    Elemento *p = l->cabeca;

    l->cabeca = p->proximo;/*equivalentes l->cabeca = l->cabeca->proximo;*/

    memcpy(info, p->info, l->tamInfo);

    free(p->info);

    free(p);

    return 1;
}

int removeNoFim(Lista *l, void *info)
{
    if(lista_vazia(*l))
        return ERRO_LISTA_VAAZIA;

    if(l->cabeca->proximo == NULL)/* somente quando a lista tem um elemento */
        return removeNoInicio(l, info);

    Elemento *p = l->cabeca;

    while(p->proximo->proximo != NULL)
        p = p->proximo;

    memcpy(info, p->proximo->info, l->tamInfo);

    free(p->proximo->info);
    free(p->proximo);

    p->proximo = NULL;

    return 1;
}

int lista_vazia(Lista l)
{
    return l.cabeca == NULL;
}

Elemento *aloca_elemento(int tamInfo, void *info)
{
    Elemento *p = malloc(sizeof(Elemento));

    if(p == NULL)
        return NULL;

    p->info = malloc(tamInfo);

    if(p->info == NULL)
    {
        free(p);

        return NULL;
    }

    memcpy(p->info, info, tamInfo);

    return p;
}

void mostra_lista(Lista l, void (*mostra_info)(void *))
{
    if(lista_vazia(l))
        printf("Empty List\n");
    else
    {
        Elemento *p = l.cabeca;

        printf("Dados da Lista:\n");

        while(p != NULL)
        {
            mostra_info(p->info);
            p = p->proximo;
        }
    }
}

void limpa_lista(Lista *l)
{
    Elemento *p = l->cabeca;

    while(p != NULL)
    {
        Elemento *aux = p->proximo;

        free(p->info);
        free(p);

        p = aux;
    }

    l->cabeca = NULL;
}

int insereNaPosicao(Lista *l,void *info,int pos){
    if(pos<0)
        return ERRO_POSICAO_INVALIDA;
    if(pos==0)
        return insereNoFim(l,info);
    Elemento *p=l->cabeca;
    int cont =0;
    while(cont<pos-1 && p->proximo!=NULL){
        p=p->proximo;
        cont++;
    }
    if(cont!=pos-1)
        return ERRO_POSICAO_INVALIDA;
    Elemento *novo = aloca_elemento(l->tamInfo,info);
    if(novo==NULL)
        return 0; // ERRO ALOCACAO
    novo->proximo=p->proximo;
    p->proximo=novo;
    return 1;
}

int removeNaPosicao(Lista *l,void *info,int pos){
    if(lista_vazia(*l)) return ERRO_LISTA_VAAZIA;
    if(pos<0) return ERRO_POSICAO_INVALIDA;
    Elemento *p = l->cabeca;
    if(pos==0){
        removeNoInicio(l,info);
    }
    int cont;
    while(cont<pos-1 &&p->proximo!=NULL){
        p=p->proximo;
        cont++;
    }
    if(cont!=pos-1) return ERRO_POSICAO_INVALIDA;
    Elemento *aux = p->proximo;
    p->proximo = aux ->proximo;
    free(aux->info);
    free(aux);
    return 1;
}


int compara_float(void *a,void *b){
    float *p1=a,*p2=b;
    if(*p1>*p2) return 1;
    if(*p1<*p2) return -1;
    return 0;
}


int insereEmOrdem(Lista *l,void *info,int(*compara)(void*,void*)){
    int cont =0;
    Elemento *p = l->cabeca;
    while(p!=NULL && compara(info,p->info)>0){
        cont++;
        p=p->proximo;
    }
    return insereNaPosicao(l,info,cont);

}

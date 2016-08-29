
#include "LDE.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int lista_vazia(LDE l){
    return l.cabeca == NULL;
}

ElementoDuplo *aloca_elemento(int tamInfo, void *info){
    ElementoDuplo *p = malloc(sizeof(ElementoDuplo));

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

void inicializa_lista(LDE *l, int t){
    l->tamInfo = t;
    l->cabeca = NULL;
    l->campos = 0;
}

int insereNoInicio(LDE *l, void *info){

    ElementoDuplo *p = aloca_elemento(l->tamInfo, info);

    if(p == NULL){
        return 0;
    }

    p->suc = l->cabeca;
    p->ant = NULL;

    if (l->cabeca != NULL) {
        l->cabeca->ant = p;
    }
    l->cabeca = p;
    return 1;
}

int removeNoInicio(LDE *l, void *info){
    if(lista_vazia(*l)){
        return ERRO_LISTA_VAAZIA;
    }
    ElementoDuplo *p = l->cabeca;
    l->cabeca = p->suc;     /*equivalentes l->cabeca = l->cabeca->proximo;*/
    memcpy(info, p->info, l->tamInfo);
    free(p->info);
    free(p);

    if (l->cabeca != NULL) {
        l->cabeca->ant = NULL;
    }

    return 1;
}

int insereNoFim(LDE *l, void *info){
    if(lista_vazia(*l)){
        return insereNoInicio(l, info);
    }
    ElementoDuplo *p = aloca_elemento(l->tamInfo, info);

    if(p == NULL){
        return 0;
    }
    ElementoDuplo *aux = l->cabeca;

    while(aux->suc != NULL){
        aux = aux->suc;
    }
    p->suc = NULL;
    aux->suc = p;
    p->ant = aux;
    return 1;
}




int removeNoFim(LDE *l, void *info){
    if(lista_vazia(*l))
        return ERRO_LISTA_VAAZIA;

    if(l->cabeca->suc == NULL) // somente quando a lista tem um elemento
        return removeNoInicio(l, info);

    ElementoDuplo *p = l->cabeca;

    while(p->suc->suc != NULL)
        p = p->suc;

    memcpy(info, p->suc->info, l->tamInfo);

    free(p->suc->info);
    free(p->suc);

    p->suc = NULL;

    return 1;
}

void mostra_int(void *info){
    printf("%d", *(int*)info);
}


void mostra_lista(LDE l, void (*mostra_info)(void *)){
    if(lista_vazia(l))
        printf("A lista esta vazia\n");
    else
    {
        ElementoDuplo *p = l.cabeca;


        int aux,i=0;
        int aux2 = l.campos;
        while(p != NULL)
        {

            while(aux2>0){
                if(!(aux2%3) && p->ant != NULL){
                     printf(".");
                }

                mostra_info(p->info);
                p = p->suc;
                aux2--;
                aux++;
            }
        }

    }
    printf("\n\n");
}

void limpa_lista(LDE *l){
    ElementoDuplo *p = l->cabeca;

    while(p != NULL)
    {
        ElementoDuplo *aux = p->suc;

        free(p->info);
        free(p);

        p = aux;
    }

    l->cabeca = NULL;
}

int insereNaPosicao(LDE *l, void *info, int pos){
    if (pos<0) {
        return ERRO_POS_INVALIDA;
    }
    if (pos == 0) {
        return insereNoInicio(l, info);
    }
    ElementoDuplo *p = l -> cabeca;
    int cont = 0;
    while (cont < pos-1 && p->suc != NULL) {
        p = p -> suc;
        cont++;
    }
    if (cont != pos-1) {
        return ERRO_POS_INVALIDA;
    }
    ElementoDuplo *novo = aloca_elemento(l->tamInfo, info);
    if (novo == NULL) {
        return 0;   //ERRO DE ALOCACAO.
    }
    novo->suc = p->suc;
    p->suc = novo;
    novo->ant = p;
    if(novo->suc!=NULL){
      novo->suc->ant=novo;
    }
    return 1; //sucesso.
}

int removeNaPosicao(LDE *l, void *info, int pos){
    if (lista_vazia(*l)) {
        return ERRO_POS_INVALIDA;
    }
    if (pos < 0) {
        return ERRO_POS_INVALIDA;
    }
    if (pos == 0) {
        return removeNoInicio(l, info);
    }
    ElementoDuplo *p = l->cabeca;
    int cont = 0;
    while (cont<pos-1 && p->suc != NULL) {
        p = p->suc;
        cont ++;
    }
    if (cont != pos-1) {
        return ERRO_POS_INVALIDA;
    }
    ElementoDuplo *aux = p->suc;
    p->suc = aux->suc;
    free(aux->info);
    free(aux);
    if(p->suc!=NULL){
    p->suc->ant=p;
    }
    return 1;
}

int modifica(LDE *l, void *info, int pos){

    if (pos <0) {
        return ERRO_POS_INVALIDA;
    }
    ElementoDuplo *p = l->cabeca;
    int cont = 0;
    while (cont<pos && p->suc != NULL) {
        p = p->suc;
        cont ++;
    }
    if (cont != pos) {
        return ERRO_POS_INVALIDA;
    }
    memcpy(p->info, info, l->tamInfo);
    return 1;
}

int leValor(LDE *l, void *info, int pos){

    if (pos <0) {
        return ERRO_POS_INVALIDA;
    }
    ElementoDuplo *p = l->cabeca;
    int cont = 0;
    while (cont<pos && p->suc != NULL) {
        p = p->suc;
        cont ++;
    }
    if (cont != pos) {
        return ERRO_POS_INVALIDA;
    }
    memcpy(info, p -> info, l->tamInfo);
    return 1;
}

int insereEmOrdem(LDE *l, void *info, int (*compara)(void *, void *)){
    int cont = 0;
    ElementoDuplo *p = l->cabeca;
    while (p != NULL && compara(info, p->info) > 0) {
        cont++;
        p = p->suc;
    }
    return insereNaPosicao(l, info, cont);
}


int verificaStringNumero(char *linha){
    int i;
    for(i=0;linha[i]!='\0';i++){
            if(linha[i]>='0' && linha[i]<='9'){

            } else {
                printf("\nCaracter Invalido: %c",linha[i]);
                return 1;
            }
    }
    return 0;
}

int inicializa_inteiro(LDE *l,char *linha){

    inicializa_lista(l, 4);

    if(verificaStringNumero(linha)){
        printf("ERRO!");
        return 0;
    }
    int i;
    int x;
    for(i=0;linha[i]!='\0';i++){
        x = linha[i]-48;
        insereNoFim(l,&x);
        l->campos++;
    }
    remove_zero(l);
    return 1;
}

void soma_inteiros(LDE *a, LDE *b){

    int casas = a->campos-1;
    int casas2 = b->campos-1;
    int x = 0;


    if(a->campos == b->campos){

        ElementoDuplo *p = a->cabeca;

        while(p->suc != NULL){
            p = p->suc;
        }

        while(casas>-1){
            int count = 0;
            int aux = 0;
            int aux2 = 0;

            leValor(a,&aux,casas);
            leValor(b,&aux2,casas2);
            aux += aux2;

            if(aux>9 && p->ant != NULL) {
                aux = aux - 10;
                modifica(a,&aux,casas);
                leValor(a,&aux,casas-1);
                aux++;
                modifica(a,&aux,casas-1);
            }else if(aux>9 && p->ant == NULL){
                int um = 1;
                aux = aux - 10;
                modifica(a,&aux,casas);
                insereNoInicio(a, &um);
                a->campos++;
            } else {
                modifica(a,&aux,casas);
            }

            casas--;
            casas2--;
            p=p->ant;
        }
    }

    if(a->campos > b->campos){
        int count = 0;
        ElementoDuplo *q = b->cabeca;
        ElementoDuplo *p = a->cabeca;


        while(q->suc != NULL){
            q = q->suc;
        }

        while(p->suc != NULL){
            p = p->suc;
        }
        while (casas2 > -1) {
                count++;
                int aux = 0;
                int aux2 = 0;
                int um = 1;
                leValor(a,&aux,casas);
                leValor(b, &aux2, casas2);
                aux += aux2;

                if(aux > 9 && q->ant != NULL){
                    aux = aux - 10;
                    modifica(a,&aux,casas);
                    leValor(a,&aux,casas-1);
                    aux++;
                    modifica(a,&aux,casas-1);
                }else if(aux > 9 && q->ant == NULL){
                    aux = aux - 10;
                    modifica(a,&aux,casas);
                    leValor(a,&aux,casas-1);
                    aux++;
                    modifica(a, &aux, casas-1);
                    leValor(a,&aux,casas-1);
                    if(aux > 9 && b->campos == count && !b->campos%2){
                        leValor(a,&aux,casas);
                        aux++;
                        modifica(a, &aux, casas);
                    }
                    doit: while(p->ant != NULL){
                            casas--;
                            leValor(a,&aux,casas);
                            if(aux>9 && p->ant != NULL){
                                aux = aux - 10;
                                modifica(a,&aux,casas);
                                leValor(a,&aux,casas-1);
                                aux++;
                                modifica(a,&aux,casas-1);
                                if(casas == 0) {
                                    insereNoInicio(a, &um);
                                    a->campos++;
                                }
                            }
                            p = p->ant;

                    }

                } else {
                    aux += x;
                    modifica(a,&aux,casas);
                    x = 0;
                    leValor(a,&aux,casas);
                    if(aux>9){
                        aux = aux - 10;
                        modifica(a,&aux,casas);
                        leValor(a,&aux,casas-1);
                        aux++;
                        modifica(a, &aux, casas-1);
                        leValor(a,&aux,casas-1);
                    } if(casas > 0 && q->ant == NULL) goto doit;
                }
                casas--;
                casas2--;
                q=q->ant;
                p=p->ant;

            }


        }

    if(a->campos < b->campos){
        LDE temp;
        inicializa_lista(&temp, 4);
        copia_lista(&temp,b);
        soma_inteiros(&temp,a);
        copia_lista(a,&temp);
        limpa_lista(&temp);
    }
}

void copia_lista(LDE *a,LDE *b){
    limpa_lista(a);
    int i = 0;
    int aux;
    ElementoDuplo *p = b->cabeca;
    do{
        leValor(b,&aux,i);
        insereNoFim(a, &aux);
        p = p->suc;
        i++;
    }while(p != NULL);
    a->campos = i;
}

int compara_int(void *a,void *b){
    int *p1=a,*p2=b;
    if(*p1>*p2) return 1;
    if(*p1<*p2) return -1;
    return 0;
}



int subtracao_inteiros(LDE *a,LDE *b){

    int casas = a->campos-1;
    int casas2 = b->campos-1;


                LDE temp;
                inicializa_lista(&temp, 4); // Caso o resultado for negativo a temp retorna o valor de A
                copia_lista(&temp, a);


    if(a->campos < b->campos){
        //printf("\n\n Negative numbers aren't allowed!");
        return 0;
    }

    if(a->campos > b->campos){
    int aux;
    int count;
    ElementoDuplo *q = b->cabeca;
    ElementoDuplo *p = a->cabeca;


        while(q->suc != NULL){
            q = q->suc;
        }

        while(p->suc != NULL){
            p = p->suc;
        }

        leValor(b,&aux,casas2);

        while (casas2 > -1) {
            if(aux == 0 && q->ant == NULL) break;
                count++;
                int aux = 0;
                int aux2 = 0;
                leValor(a,&aux,casas);
                leValor(b, &aux2, casas2);
                aux -= aux2;
                leValor(a,&aux2,casas2-1);

                if(aux == 0 && q->ant != NULL){
                        leValor(a,&aux,casas-1);
                        leValor(b, &aux2, casas2-1);
                        aux -= aux2;
                        casas2--;
                        casas--;
                        modifica(a,&aux,casas);
                        if(aux<0) {
                                aux = aux + 10;
                                modifica(a,&aux,casas);
                                leValor(a,&aux,casas-1);
                                aux--;
                                modifica(a,&aux,casas-1);
                                goto doit;
                        }
                }

                if(aux < 0 && p->ant != NULL){
                    aux = aux + 10;
                    modifica(a,&aux,casas);
                    leValor(a,&aux,casas-1);
                    aux--;
                    modifica(a,&aux,casas-1);
                    if(aux < 0 && q->ant == NULL){
                            doit: while(p->ant != NULL){
                                casas--;
                                if(aux < 0 && p -> ant != NULL){
                                    aux = aux + 10;
                                    modifica(a,&aux,casas);
                                    leValor(a,&aux,casas-1);
                                    aux--;
                                    modifica(a,&aux,casas-1);
                                } else if (aux < 0 && q->ant == NULL){
                                    aux = 0;
                                    modifica(a,&aux,casas);
                                }
                                p = p->ant;

                            }

                    }
                } else {
                        modifica(a,&aux,casas);
                        leValor(a,&aux,casas);
                    if(aux<0 && q->ant != NULL){

                        aux = aux - 10;
                        modifica(a,&aux,casas);
                        leValor(a,&aux,casas-1);
                        aux--;
                        modifica(a, &aux, casas-1);
                    }

                }
                casas--;
                casas2--;
                q=q->ant;
                p=p->ant;
            }

    }
    if(a->campos == b->campos){

        int aux;

        ElementoDuplo *q = b->cabeca;
        ElementoDuplo *p = a->cabeca;

        while(p->suc != NULL){
            p = p -> suc;
        }

        while(q->suc != NULL){
           q = q -> suc;
        }

        while(casas > -1){
            int aux = 0;
            int aux2 = 0;
            leValor(a,&aux,casas);
            leValor(b, &aux2, casas2);
            aux -= aux2;
            if(aux < 0 && p->ant != NULL){
                aux = 10 + aux;
                modifica(a,&aux,casas);
                leValor(a,&aux,casas-1);
                aux--;
                modifica(a,&aux,casas-1);
                    if(aux <= 0 && p->ant == NULL){
                        removeNaPosicao(a,&aux,casas-1);
                        a->campos--;
                    }


            } else {
                modifica(a,&aux,casas);
            }
            casas--;
            casas2--;
            q=q->ant;
            p=p->ant;
            leValor(a,&aux2,0);
            if(aux2 < 0) {
                //printf("\n\n Negative numbers aren't allowed!");
                copia_lista(a,&temp);
                return 0;
            }

        }
    }

    remove_zero(a);
    return 1;

}

int remove_zero(LDE *a){
    int check = 0;
    int i = 0;
    int j;
    int aux = 0;

    ElementoDuplo *p = a->cabeca;
    while(p->suc != NULL){
        p=p->suc;
    }
    leValor(a,&aux,i);

    while(aux == 0 && p->ant != NULL){
        p=p->ant;
        i++;
        leValor(a,&aux,i);
        check++;
    }

    if(check==0) return 0;

    while(check>0){

        removeNoInicio(a,&j);
        check--;
        a->campos--;
    }

    return 1;
}

void multiblica_inteiros(LDE *a, LDE *b){

    int casas2 = b->campos-1;
    int x = 1,conta=0;
    LDE temp,temp2,um;
    int aux;
    leValor(b,&aux,0);
    inicializa_inteiro(&um,"1");
    inicializa_lista(&temp,4);
    inicializa_lista(&temp2,4);
    copia_lista(&temp2,b);
    copia_lista(&temp,a);
    diminui_inteiros(&temp2,&um);
    ElementoDuplo *p = b->cabeca;

    if(casas2 == 0 && p->ant == NULL && aux == 0){

        while(diminui_inteiros(a,&um));

    } else {    while(diminui_inteiros(&temp2,&um)){
        soma_inteiros(a,&temp);
    }
    }


/*  }

       while(casas2 > -1){
            int aux2,i = 1;
            leValor(b ,&aux2,casas2);
        if(aux2 != 0 && casas2 > 0) conta++;
            aux2 *=x;
                while (i < aux2) {
                    soma_inteiros(a, &temp);
                    i++;
                }
            casas2--;
            x = x * 10;
       }
*/



}

void exp_inteiros(LDE *a,LDE *b){
    int casas2 = b->campos-1;
    int x = 1,conta=0;
    LDE temp,um,temp2;
    inicializa_lista(&temp,4);
    inicializa_inteiro(&um,"1");
    inicializa_lista(&temp2,4);
    copia_lista(&temp,a);
    copia_lista(&temp2,b);
    diminui_inteiros(b,&um);
    while(diminui_inteiros(b,&um)){
            printf("Calculando...\n");
        multiblica_inteiros(a, &temp);
    }

    /*while(casas2 > -1){
            int aux2,i = 1;
            leValor(b ,&aux2,casas2);
        if(aux2 != 0 && casas2 > 0) conta++;
            aux2 *=x;
                while (i < aux2) {
                    multiblica_inteiros(a, &temp);
                    i++;
                }
            casas2--;
            x = x * 10;
       }*/

   /* while(conta > 0){
        conta--;
        multiblica_inteiros(a,&temp);
    }*/

}

void raiz_inteiros(LDE *a){
    LDE temp,unico,count,soma;
    LDE temp2;
    inicializa_lista(&temp2,4);

    copia_lista(&temp2,a);
    inicializa_inteiro(&count,"0");
    inicializa_inteiro(&soma,"1");
    inicializa_inteiro(&temp,"1");
    inicializa_inteiro(&unico,"2");


    while(diminui_inteiros(&temp2,&temp)){
        soma_inteiros(&temp,&unico);
        soma_inteiros(&count,&soma);
    }
    printf("\n\n Valor Positivo da Raiz:");
    mostra_lista(count,mostra_int);
    copia_lista(a,&temp2);



}


int divisao_inteiros(LDE *a,LDE *b){
    int casas2 = b->campos-1;
    int x = 1,conta=0;
    LDE temp,count,soma;
    inicializa_lista(&temp,4);
    copia_lista(&temp,a);
    inicializa_inteiro(&count,"0");
    inicializa_inteiro(&soma,"1");


       while(diminui_inteiros(&temp,b)){
           soma_inteiros(&count,&soma);;
       }
    printf("Valor da Divisao:\n");
    mostra_lista(count,mostra_int);
    printf("Resto:\n");
    mostra_lista(temp,mostra_int);

    /*while(conta > 0){
        conta--;
        soma_inteiros(a,&temp);
    }*/
}


int diminui_inteiros(LDE *a,LDE *b){

    int casas = a->campos-1;
    int casas2 = b->campos-1;


                LDE temp;
                inicializa_lista(&temp, 4); // Caso o resultado for negativo a temp retorna o valor de A
                copia_lista(&temp, a);


    if(a->campos < b->campos){
        //printf("\n\n Negative numbers aren't allowed!");
        return 0;
    }

    if(a->campos > b->campos){
    int aux;
    int count;
    ElementoDuplo *q = b->cabeca;
    ElementoDuplo *p = a->cabeca;


        while(q->suc != NULL){
            q = q->suc;
        }

        while(p->suc != NULL){
            p = p->suc;
        }

        leValor(b,&aux,casas2);

        while (casas2 > -1) {
            if(aux == 0 && q->ant == NULL) break;
                count++;
                int aux = 0;
                int aux2 = 0;
                leValor(a,&aux,casas);
                leValor(b, &aux2, casas2);
                aux -= aux2;
                if(aux < 0 && p->ant != NULL){
                    aux = aux + 10;
                    modifica(a,&aux,casas);
                    leValor(a,&aux,casas-1);
                    aux--;
                    modifica(a,&aux,casas-1);

                    if(aux < 0 && q->ant == NULL){
                            while(p->ant != NULL){
                                casas--;
                                if(aux < 0 && p -> ant != NULL){
                                    aux = aux + 10;
                                    modifica(a,&aux,casas);
                                    leValor(a,&aux,casas-1);
                                    aux--;
                                    modifica(a,&aux,casas-1);
                                } else if (aux < 0 && p->ant == NULL){
                                    aux = 0;
                                    modifica(a,&aux,casas);

                                }
                                p = p->ant;

                            }

                    }
                } else {
                    modifica(a,&aux,casas);
                    leValor(a,&aux,casas);
                    if(aux<0 ){
                        aux = aux - 10;
                        modifica(a,&aux,casas);
                        leValor(a,&aux,casas-1);
                        aux--;
                        modifica(a, &aux, casas-1);
                    }
                }
                casas--;
                casas2--;
                q=q->ant;
                p=p->ant;

            }

    }
    if(a->campos == b->campos){
        int aux;

        ElementoDuplo *q = b->cabeca;
        ElementoDuplo *p = a->cabeca;

        while(p->suc != NULL){
            p = p -> suc;
        }

        while(q->suc != NULL){
           q = q -> suc;
        }

        while(casas > -1){
            int aux = 0;
            int aux2 = 0;
            leValor(a,&aux,casas);
            leValor(b, &aux2, casas2);
            aux -= aux2;
            if(aux < 0 && p->ant != NULL){
                aux = 10 + aux;
                modifica(a,&aux,casas);
                leValor(a,&aux,casas-1);
                aux--;
                modifica(a,&aux,casas-1);
                    if(aux <= 0 && p->ant == NULL){
                        removeNaPosicao(a,&aux,casas-1);
                        a->campos--;
                    }
            } else {
                modifica(a,&aux,casas);
            }
            casas--;
            casas2--;
            q=q->ant;
            p=p->ant;
            leValor(a,&aux2,0);
            if(aux2 < 0) {
                //printf("\n\n Negative numbers aren't allowed!");
                copia_lista(a,&temp);
                return 0;
            }
        }
    }
    remove_zero(a);
    return 1;

}

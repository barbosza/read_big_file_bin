#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"



void mostra_registro(Diario *p){
    FILE *arq;
    arq = fopen("VAICABER.txt", "w");
    if(arq != NULL){
        fwrite(p,sizeof(Diario),1,arq);
        //printf("0");
        fclose(arq);
    } else{
        printf("erro!");
        }
    }
     //printf("%d %22s\n", p->matricula, p->nome, p->matricula);}

void mostra_float(void *info)
{
    printf("%f\n", *(float*)info);
}

int main()
{
    char arr[] = {'a','e','i','o','u'};
    Lista l1;
    int x = 0;
    Diario aux;
    inicializa_lista(&l1, sizeof(Diario));
    printf("%d\n\n",sizeof(Diario));
    while(x < 20000){

    aux.faltas = 1;
    aux.nome = "Marcos";
    aux.matricula = 0001;
    aux.notas = 4;


    insereNoInicio(&l1,&aux);
    x++;
    }
    mostra_lista(l1, mostra_registro);
   /* d1.notas = 3;
    d1.faltas = 2;
    inicializa_lista(&l1, sizeof(diario));
    insereNoInicio(&l1,&d1);
    mostra_lista(l1,mostra_int);
    return 0;  */
}

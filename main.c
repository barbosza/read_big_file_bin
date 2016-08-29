#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"
#define ENTITY 23


void mostra_registro(Diario *p){
    FILE *fp;
    fp = fopen("test.dat","w+b");
    fwrite(p,sizeof(Diario), ENTITY,fp);
    fclose(fp);
    printf("%d %10s %d%2d\n", p->matricula, p->nome, p->faltas, p->notas);
}

void registros(Diario *p){
    printf("%d %10s %d%2d\n", p->matricula, p->nome, p->faltas, p->notas);
}

void debulhaissoai(Lista *x,Diario* a){
    FILE *p;
    p = fopen("test.dat", "rb");
    fseek(p,0,SEEK_END);
    long fileSize = ftell(p);
    rewind(p);
    int Num = (int)(fileSize / (sizeof(Diario)));
    int loop;
    for(loop = 0;loop < Num;++loop){
        printf("\n\n Segue o Bagulho ->  %d\n\n",Num);
        fseek(p,(sizeof(Diario) * loop), SEEK_SET);
        fread(a,sizeof(Diario),1,p);
        insereNoInicio(x,a);
    }
       // fseek(p,4,sizeof(Diario));


    fclose(p);
}
void mostra_float(void *info)
{
    printf("%f\n", *(float*)info);
}

int main()
{

    int count = 0;
    char arr[] = {'a','e','i','o','u'};
    Lista l1,l2;
    int x = 0;
    Diario aux,aux2;
    inicializa_lista(&l1, sizeof(Diario));
    inicializa_lista(&l2, sizeof(Diario));
    printf("%d\n\n",sizeof(Diario));
    while(x < ENTITY){
    aux.faltas = 12;
    strcpy(aux.nome, "Ozorio");
    aux.matricula = x;
    aux.notas = 4;
    x++;
    insereNoInicio(&l1,&aux);
    }
    mostra_lista(l1, mostra_registro);

    debulhaissoai(&l2,&aux2);
    mostra_lista(l2,registros);


    return 0;
}

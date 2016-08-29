#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"



void mostra_registro(Diario *p){
    //FILE *fp;
    //fp = fopen("vaicaber.bin","wb");
    //fwrite(p,sizeof(Diario), 3276008,fp);
  //  fclose(fp);
     printf("%d %22s\n", p->matricula, p->nome, p->matricula);
}

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
    for(x=0;x<320000000000;x++){

    aux.faltas = 1;
    strcpy(aux.nome, "Marcos");
    aux.matricula = x;
    aux.notas = 4;

    insereNoInicio(&l1,&aux);

    }

  //  mostra_lista(l1, mostra_registro);
    return 0;
}

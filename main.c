#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"
#include <string.h>
#define ENTITY 20000
#define LOOP 16384
#define MB_SIZE 1048576

typedef struct {
    char nome[24];
    long long matricula;
    double notas;
    int faltas;
}Diario;


void mostra_float(void *info)
{
    printf("%f\n", *(float*)info);
}

int main()
{
    srand(time(NULL));
    long long globalCounter = 0;
    double complete;
    const char *strings[] = {
     "Ana","Bernardo"
    ,"Castiel","Diego","Ernani"
    ,"Frederico","Gustavo"
    ,"Helio","Italo"
    ,"Juarez","Kevin"
    ,"Leonardo","Matheus"
    ,"Natalia","Olavo"
    ,"Paula","Queiroz"
    ,"Ramiro","Silvio"
    ,"Tiago","Umberto"
    ,"Victor","Xandi"
    };

    int a,b,c;
    c = rand() % 10;
    int x,z = 0;
    Diario dac[ENTITY],aux[ENTITY];


    printf("%d",sizeof(dac));
    FILE *p;
    p = fopen("dba.bin","wb");
    for(x=0;x<=LOOP;++x){
        complete = ((double)x/(double)LOOP)*100;
        printf("%2.2lf%% Concluido",complete);

        for(z=0;z<ENTITY;++z){
            int media = 0;
            int temp = rand() % 10;
            b = 1 + rand() % 15;
            for(c = 1; c < b;c++){
                media += temp;
            }
            a = rand() % 23;
            dac[z].faltas = 23;
            strcpy(dac[z].nome, strings[a]);
            dac[z].matricula = globalCounter;
            dac[z].notas = (double)((double)media/(double)b);
            globalCounter++;
        }

        fwrite(dac,sizeof(Diario),ENTITY,p);
        system("cls");

    }
    fclose(p);
    p = fopen("dba.bin","rb");
    fseek(p,0,SEEK_END);
    long fileSize = ftell((p));
    rewind(p);
    //int numEntries = (int)(fileSize / (sizeof(Diario)));
    //fread(dac,sizeof(dac),ENTITY,p);
    char aluno;
    int y = 0;
    for(y=0;y<LOOP;y++){
        fread(&aux,sizeof(dac),1,p);
       //fseek(p,(sizeof(dac)*y),SEEK_SET);
        for(x = 0;x<ENTITY;x++){
                //fread(&aux,sizeof(Diario),1,p);
                if(aux[x].notas >= 7.0){
                    aluno = 'A';
                } else if(aux[x].notas < 7.0 && aux[x].notas > 1.3) {
                    aluno = 'E';;
                } else {
                    aluno = 'R';
                }
               // printf("%2lld%22s%22.2lf%5c\n\n",aux[x].matricula,aux[x].nome,aux[x].notas,aluno);
        }

    }
    printf("%ld MB and Entries\n\n", fileSize/MB_SIZE);
    fclose(p);
    return 0;
}


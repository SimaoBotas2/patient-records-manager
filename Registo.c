//
// Created by HP on 4/19/2024.
//

#include "Registo.h"
#include <stdlib.h>
#include "Data.h"
#include <stdio.h>
#include <string.h>

Registo * inicializa_registo(int id,Data * data,int tmax, int tmin,int peso,int altura){

    Registo * myregisto = (Registo*) malloc(sizeof(Registo));
    if(myregisto==NULL){
        return NULL;
    }

    else {
        myregisto->data = (Data*) malloc(sizeof(Data));
        if(myregisto->data!=NULL){
            myregisto->data=data; //data verificada antes
            myregisto->id_doente=id;
            myregisto->tensao_max=tmax;
            myregisto->tensao_min=tmin;
            myregisto->peso=peso;
            myregisto->altura=altura;
            return myregisto;
        }
        else {
            free(myregisto->data);
            free(myregisto);
            return NULL;
        }
    }
}

void erase_registo(Registo * reg){
    free(reg->data);
    free(reg);
}


void imprime_registo(Registo * reg){
    printf("Id  : %d\n",reg->id_doente);
    imprime_data(reg->data);
    printf("Tensao Max: %d\n",reg->tensao_max);
    printf("Tensao Min: %d\n",reg->tensao_min);
    printf("Peso: %dkg\n",reg->peso);
    printf("Altura: %dcm\n",reg->altura);
}

Registo * read_registo(FILE * f){
    char buffer[20];
    int id;
    char data[15];
    int tmax;
    int tmin;
    int peso;
    int altura;

    bool working = true;


    if(feof(f)){  //ficheiro acaba antes do esperado
        return NULL;
        }

    if(fgets(buffer,20,f)!=NULL){
        buffer[strlen(buffer)-1] = '\0';
        id = atoi(buffer);
    }
    else
        working = false;

    if(feof(f)) //ficheiro acaba antes do esperado
        return NULL;

    if(fgets(buffer,20,f)!=NULL){
        buffer[strlen(buffer)-1] = '\0';
        strcpy(data,buffer);
    }
    else
        working = false;


    if(feof(f)) //ficheiro acaba antes do esperado
        return NULL;

    if(fgets(buffer,20,f)!=NULL){
        buffer[strlen(buffer)-1] = '\0';
        tmax = atoi(buffer);
    }
    else
        working = false;

    if(feof(f)) //ficheiro acaba antes do esperado
        return NULL;

    if(fgets(buffer,20,f)!=NULL){
        buffer[strlen(buffer)-1] = '\0';
        tmin = atoi(buffer);
    }
    else
        working = false;

    if(feof(f)) //ficheiro acaba antes do esperado
        return NULL;

    if(fgets(buffer,20,f)!=NULL){
        buffer[strlen(buffer)-1] = '\0';
        peso = atoi(buffer);
    }
    else
        working = false;

    if(feof(f)) //ficheiro acaba antes do esperado
        return NULL;

    if(fgets(buffer,20,f)!=NULL){

        if(buffer[strlen(buffer)-1=='\n'])
            buffer[strlen(buffer)-1] = '\0';
        altura = atoi(buffer);
    }
    else
        working = false;



    if(working) {
        Registo * myregisto = inicializa_registo(id,string_to_data(data), tmax, tmin, peso,altura);
        return myregisto;
    }

    else {
        printf("Erro ao ler o registo\n");
        return NULL;
    }

}

void write_registo(FILE * f,Registo * reg){

    fprintf(f,"%d\n",reg->id_doente);
    fprintf(f,"%d/%d/%d\n",reg->data->dia,reg->data->mes,reg->data->ano);
    fprintf(f,"%d\n",reg->tensao_max);
    fprintf(f,"%d\n",reg->tensao_min);
    fprintf(f,"%d\n",reg->peso);
    fprintf(f,"%d\n",reg->altura);
}

Registo  * cria_registo(int id){

    Registo  * myreg = (Registo*) malloc(sizeof(Registo));

    if(myreg==NULL)
        return NULL;


    char data[20];
    int tmax;
    int tmin;
    int altura;
    int peso;


    printf("Introduza a data no formato DD/MM/AAAA\n");
    scanf("%s",data);
    Data * mydata = string_to_data(data);
    fflush(stdin);

    printf("Introduza a Tensao Maxima medida:\n");
    scanf(" %d",&tmax);
    fflush(stdin);

    printf("Introduza a Tensao Minima medida:\n");
    scanf(" %d",&tmin);
    fflush(stdin);

    printf("Introduza a Altura(em cm) medida:\n");
    scanf(" %d",&altura );
    fflush(stdin);

    printf("Introduza o Peso(em kg) medido:\n");
    scanf(" %d",&peso);
    fflush(stdin);

    myreg = inicializa_registo(id, string_to_data(data),tmax,tmin,peso,altura);

    if(myreg!=NULL)
        return myreg;

    else{
        printf("Erro ao criar registo:\n");
        return NULL;
    }
}
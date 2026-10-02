//
// Created by HP on 4/19/2024.
//


#ifndef PROJETO_REGISTO_H
#define PROJETO_REGISTO_H


#include "Data.h"
#include <stdio.h>

typedef struct {
    int id_doente;
    Data * data;
    int tensao_max;
    int tensao_min;
    int peso;  //em kg
    int altura; //em cm
}Registo;


Registo * inicialiaza_registo(int id,Data * data,int tmax, int tmin,int peso,int altura);
void erase_registo(Registo * reg);
int get_idR(Registo * reg);
void imprime_registo(Registo * reg);
Registo * read_registo(FILE * f);
void write_registo(FILE * f,Registo * reg);
Registo * cria_registo(int id);




#endif //PROJETO_REGISTO_H

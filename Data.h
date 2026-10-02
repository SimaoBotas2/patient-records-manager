//
// Created by HP on 4/24/2024.
//

#ifndef PROJETO_DATA_H
#define PROJETO_DATA_H

#include <stdbool.h>


typedef struct{
    int dia;
    int mes;
    int ano;
}Data;

Data * inicializa_data(int dia,int mes, int ano);
void imprime_data(Data * mydata);
Data * string_to_data(char * string);
int compara_datas(Data * a,Data * b);


#endif //PROJETO_DATA_H

//
// Created by HP on 5/16/2024.
//







#ifndef PROJETO_LISTAREGISTOS_H
#define PROJETO_LISTAREGISTOS_H


#include "Registo.h"

typedef struct noListaR {
    Registo * registo;
    struct noListaR * prox;
} noListaR;
typedef noListaR * rLista;


rLista criaR ();
int vaziaR (rLista * lista);
void destroiR (rLista * lista);
void procuraR (rLista lista, Data *chave, rLista *ant, rLista *actual);
void eliminaR (rLista * lista, Data * chave);
void insereR (rLista * lista, Registo * myDoente);
rLista pesquisaR (rLista * lista, Data * chave);
void imprime_listaR(rLista * lista);
void read_listaR(rLista * lista);
void write_listaR(rLista * lista);
void procuraR_sorted_tmax (rLista lista, int chave,rLista *ant, rLista *actual);
void insereR_sorted_tmax(rLista * lista, Registo * reg);
void destroiR_aux (rLista * lista);


#endif //PROJETO_LISTAREGISTOS_H

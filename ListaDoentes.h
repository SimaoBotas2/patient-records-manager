//
// Created by HP on 4/21/2024.
//

#ifndef PROJETO_LISTADOENTES_H
#define PROJETO_LISTADOENTES_H


#include "Doente.h"

typedef struct noLista {
    Doente * doente;
    struct noLista * prox;
} noLista;
typedef noLista * dLista;


dLista criaD ();
int vazia (dLista * lista);
void destroiD (dLista * lista);
void procura (dLista lista, int chave, dLista *ant, dLista *actual);
void elimina (dLista * lista, int chave);
void insere (dLista * lista, Doente * myDoente);
dLista pesquisa (dLista * lista, int chave);
void imprime_listaD(dLista * lista,int opcao);
void write_listaD(dLista * lista);
int last_id(dLista * lista);
void read_listaD(dLista * ,rLista *);
void imprime_doente_com_id(dLista * lista,int id,int opcao);
void imprime_doentes_com_tmax(dLista* lista ,int x);
void introduzir_novo_registo(dLista * lista,int id);
void insere_alfa(dLista*,Doente*);
void sort_lista_ordem_alfa(dLista * lista);
void procura_alfa (dLista lista, char * chave, dLista *ant, dLista *actual);
int compara_nomes(char*,char*);
void destroi_aux(dLista * lista);
void sort_lista_id(dLista * lista);
void imprime_listaR_com_doente(rLista * lista,dLista * listaD);


#endif //PROJETO_LISTADOENTES_H

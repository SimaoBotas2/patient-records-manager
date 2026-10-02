//
// Created by HP on 4/19/2024.
//

#ifndef PROJETO_DOENTE_H
#define PROJETO_DOENTE_H

#include <stdbool.h>
#include <stdio.h>
#include "Data.h"
#include "ListaRegistos.h"


typedef struct {
    int id_doente;
    char * nome;
    Data * data_nascimento;
    char * cartao_cidadao;
    long int telefone;
    char * email;
    rLista listaR;
}Doente;


Doente * inicializa_doente(int id, char * nome, Data * data,char * cc,long long  int nr,char * email);
int get_id(Doente * myDoente);
void imprime_doente(Doente * myDoente,int opcao);
void erase_doente(Doente *  myDoente);
bool confirma_nrtele(long int x); //confirma se o nr de telefone recebido tem 9 digitos
char * confirma_nome(char * nome);
char * confirma_email(char * email);
char * confirma_cc(char *cc);
void write_doente(FILE * , Doente * doente);
Doente * cria_doente(int id);
Doente * read_doente(FILE * d,rLista * );
int get_maior_tmax(Doente * mydoente);
#endif //PROJETO_DOENTE_H

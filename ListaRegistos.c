//
// Created by HP on 5/16/2024.
//
#include "ListaRegistos.h"
#include "Registo.h"
#include <stdlib.h>
#include <stdio.h>
#include "Data.h"


char fileR[] = "Registos.txt";


rLista criaR (){
    rLista aux;

    aux = (rLista) malloc (sizeof (noListaR));
    if (aux != NULL) {
        aux->registo = NULL;
        aux->prox = NULL;
    }
    return aux;
}

int vaziaR (rLista * lista) {
    if ((*lista)->prox == NULL) return 1;
    else return 0;
}

void destroiR (rLista * lista){

    if(lista== NULL){
        return;
    }

    rLista current = *lista;
    rLista next = NULL;

    while(current!=NULL){
        next=current->prox;
        if(current->registo != NULL)
            erase_registo(current->registo);
        free(current);
        current = next;
    }

    *lista = NULL;  //colocar header a NULL quando se termina a eliminação

}

void procuraR (rLista lista, Data * chave,rLista *ant, rLista *actual){
    *ant = lista; *actual = lista->prox;
    while ((*actual) != NULL && compara_datas((*actual)->registo->data,chave) ==1) {
        *ant = *actual;
        *actual = (*actual)->prox;
    }
    if ((*actual) != NULL && compara_datas((*actual)->registo->data,chave)!=0)
    {
        *actual = NULL; // elemento não encontrado
    }
}

void eliminaR (rLista * lista, Data * chave){
    rLista ant, actual;
    procuraR (*lista, chave, &ant, &actual);
    if (actual != NULL) {
        ant->prox = actual->prox;
        free (actual);
    }
}

void insereR (rLista* lista, Registo * myReg) {
    rLista no, ant, inutil;
    no = (rLista) malloc (sizeof (noListaR));
    if (no != NULL) {
        no->registo = myReg;
        procuraR (*lista, myReg->data, &ant, &inutil);
        no->prox = ant->prox;
        ant->prox = no;
    }
}

rLista pesquisaR (rLista * lista, Data * chave){
    rLista ant, actual;
    procuraR (*lista, chave, &ant, &actual);
    return (actual);
}


void imprime_listaR (rLista * lista) {


    if (lista == NULL) {
        printf("Erro ao imprimir\n");
        return;
    }
    if (vaziaR(lista)) {
        printf("Nao existem registos para este doente!\n");
        return;
    }

    rLista aux = (*lista)->prox; // salta o header
    while (aux != NULL) {
        imprime_registo(aux->registo);
        printf("\n");
        aux = aux->prox;
    }
}

void read_listaR(rLista * lista){
    FILE *f = fopen(fileR, "r");

    printf("A ler registos de doentes:\n");

    if(f==NULL) {
        printf("Erro ao abrir o ficheiro\n");
    }

    Registo * registo = read_registo(f);
    while (registo!= NULL) {
        insereR(lista,registo);
        registo = read_registo(f);
    }

    fclose(f);
}

void write_listaR(rLista * lista){
    //escreve a lista de registos no ficheiro
    FILE * f = fopen(fileR,"a");

    if(f==NULL)
        printf("Erro ao abrir o ficheiro!\n");

    rLista aux = (*lista)->prox; //salta o header

    while(aux!=NULL){
        write_registo(f,aux->registo);
        aux = aux->prox;
    }

    fclose(f);
}

void insereR_sorted_tmax(rLista * lista, Registo * reg){

    rLista no, ant, inutil;
    no = (rLista) malloc (sizeof (noListaR));
    if (no != NULL) {
        no->registo = reg;
        procuraR_sorted_tmax(*lista, reg->tensao_max, &ant, &inutil);
        no->prox = ant->prox;
        ant->prox = no;
    }


}

void procuraR_sorted_tmax (rLista lista, int chave,rLista *ant, rLista *actual){
    *ant = lista; *actual = lista->prox;
    while ((*actual) != NULL && chave < (*actual)->registo->tensao_max) {
        *ant = *actual;
        *actual = (*actual)->prox;
    }
    if ((*actual) != NULL && (*actual)->registo->tensao_max !=chave)
    {
        *actual = NULL; // elemento não encontrado
    }
}

void destroiR_aux (rLista * lista){ //destroi lista sem destroir os registos

    if(lista== NULL){
        return;
    }

    rLista current = *lista;
    rLista next = NULL;

    while(current!=NULL){
        next=current->prox;
        free(current);
        current = next;
    }

    *lista = NULL;  //colocar header a NULL quando se termina a eliminação

}


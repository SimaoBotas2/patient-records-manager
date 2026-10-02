//
// Created by HP on 4/21/2024.
//

#include <malloc.h>
#include "ListaDoentes.h"
#include "Doente.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


char file[] = "Doentes.txt";
char file_registos[] = "Registos.txt";

dLista criaD (){
    dLista aux;

    aux = (dLista) malloc (sizeof (noLista));
    if (aux != NULL) {
        aux->doente = NULL;
        aux->prox = NULL;
    }
    return aux;
}

int vazia (dLista * lista) {
    if ((*lista)->prox == NULL) return 1;
    else return 0;
}

void imprime_doente_com_id(dLista * lista,int id,int opcao){

   dLista aux = (*lista)->prox;

    procura(*lista,id,lista,&aux);
    if(aux!=NULL)
        imprime_doente(aux->doente,opcao);
    else
        printf("Doente nao encontrado!\n");
}

void destroiD (dLista * lista){

    if(lista== NULL){
        return;
    }

    dLista current = *lista;
    dLista next = NULL;

    while(current!=NULL){
        next=current->prox;
        if(current->doente != NULL) {
            erase_doente(current->doente);
        }
        current = next;
    }

    *lista = NULL;  //colocar header a NULL quando se termina a eliminação

}

void procura (dLista lista, int chave, dLista *ant, dLista *actual){   //a chave neste caso vai ser o id

    *ant = lista; *actual = lista->prox;

        while ((*actual) != NULL && (*actual)->doente->id_doente < chave) {
            *ant = *actual;
            *actual = (*actual)->prox;
        }
        if ((*actual) != NULL && (*actual)->doente->id_doente != chave)
            *actual = NULL; // elemento não encontrado
}

void elimina (dLista * lista, int chave){
    dLista ant, actual;
    procura (*lista, chave, &ant, &actual);
    if (actual != NULL) {
        ant->prox = actual->prox;
        erase_doente(actual->doente);
        free(actual);
    }
}

void insere (dLista* lista, Doente * myDoente) {
    dLista no, ant, inutil;
    no = (dLista) malloc (sizeof (noLista));
    if (no != NULL) {
        no->doente = myDoente;
        procura (*lista, myDoente->id_doente, &ant, &inutil);
        no->prox = ant->prox;
        ant->prox = no;
    }
}

dLista pesquisa (dLista * lista, int chave){
    dLista ant, actual;
    procura (*lista, chave, &ant, &actual);
    return (actual);
}


void imprime_listaD (dLista * lista,int opcao){
    dLista aux = (*lista)->prox; // salta o header
    while (aux!=NULL) {
        imprime_doente(aux->doente,opcao);
        aux = aux->prox;
    }
}

int last_id(dLista * lista){
    dLista aux = (*lista)->prox;
    int id = 0;
    while(aux){
        if(id<aux->doente->id_doente)  // desta forma nao importa como a lista esta sorted
            id= aux->doente->id_doente;
        aux = aux->prox;
    }
    return id;
}

void write_listaD(dLista * lista){
    //escreve a lista de doentes no ficheiro
    FILE * f = fopen(file,"w");

     FILE * r = fopen(file_registos,"w"); //abro o ficheiro de registos apenas para limpá-lo
     fclose(r);                                     //faço isto caso teha apagado algum doente, para nao escrever registos nao utilizaveis


    dLista aux = (*lista)->prox;
    while(aux!=NULL){
        write_doente(f,aux->doente);
        aux = aux->prox;
    }

    fclose(f);

}

void imprime_doentes_com_tmax(dLista * lista ,int x){
    dLista aux = (*lista)->prox;
    rLista aux2;
    rLista sorted = criaR();
    while(aux !=NULL){
        aux2 = aux->doente->listaR->prox;
        while(aux2!=NULL){
            if(aux2->registo->tensao_max>x) {
                insereR_sorted_tmax(&sorted,aux2->registo);
            }
            aux2=aux2->prox;
        }
        aux = aux->prox;
    }

    imprime_listaR_com_doente(&sorted,lista);

    destroiR_aux(&sorted);

}

void read_listaD(dLista * lista_doentes,rLista * lista_registos) {
    //le a lista atraves do ficheiro de doentes


    printf("A ler ficheiro de doentes:\n");

    FILE *f = fopen(file, "r");

    if(f==NULL) {
        printf("Erro ao abrir o ficheiro\n");
    }

    Doente *doente = read_doente(f,lista_registos);
        while (doente != NULL) {
            insere(lista_doentes,doente);
            doente = read_doente(f,lista_registos);
        }

    fclose(f);
}
void introduzir_novo_registo(dLista * lista,int id){

    dLista  aux = (*lista)->prox;

    Registo * myregisto = (Registo*) malloc(sizeof(Registo));

    procura(*lista,id,lista,&aux);
    if(aux==NULL){
        printf("Nao existe o doente indicado:\n");
        return;
    }

    if(myregisto!=NULL)
        myregisto = cria_registo(id);

    if(myregisto==NULL)
        return;



    insereR(&(aux->doente->listaR),myregisto);

}

void sort_lista_ordem_alfa(dLista * lista) {

    dLista sorted = criaD();

    dLista aux = (*lista)->prox; //salta o header

    while (aux != NULL){
        insere_alfa(&sorted, aux->doente);
        aux = aux->prox;
    }

    dLista current = (*lista)->prox;
    dLista next = NULL;

    while(current!=NULL) {  // apaga a lista mas nao apaga os doentes
        next = current->prox;
        free(current);
        current = next;
    }

    (*lista)->prox = NULL;

    aux = sorted->prox;

    while(aux!=NULL){
        insere_alfa(lista,aux->doente);
        aux = aux->prox;
    }


    destroi_aux(&sorted);
}

void insere_alfa (dLista* lista, Doente * myDoente) {
    dLista no, ant, inutil;
    no = (dLista) malloc (sizeof (noLista));
    if (no != NULL) {
        no->doente = myDoente;
        procura_alfa (*lista, myDoente->nome, &ant, &inutil);
        no->prox = ant->prox;
        ant->prox = no;
    }
}

void procura_alfa (dLista lista, char * chave, dLista *ant, dLista *actual){   //a chave neste caso vai ser o nome do doente

    *ant = lista; *actual = lista->prox;

    while ((*actual) != NULL && (compara_nomes(chave,(*actual)->doente->nome) == 1)) {
        *ant = *actual;
        *actual = (*actual)->prox;
    }
    if ((*actual) != NULL && compara_nomes(chave,(*actual)->doente->nome) != 0)
        *actual = NULL; // elemento não encontrado
}

int compara_nomes(char * a, char * b){

    char * aux1 = (char*) malloc(strlen(a));
    char * aux2 = (char*) malloc(strlen(b));

    if(aux1==NULL || aux2==NULL){
        printf("Erro ao alocar memoria\n");
        return -2;
    }

    strcpy(aux1,a);
    strcpy(aux2,b);


    while((*aux1)!= '\0' && (*aux2) != '\0'){
        if(*aux1 == ' ')
            aux1++;
        if(*aux2 == ' ')
            aux2++;
        else
        {
            if(toupper(*aux1)> toupper(*aux2)) {
                free(aux1);
                free(aux2);
                return 1;
            }
            if(toupper(*aux2)> toupper(*aux1)) {
                free(aux1);
                free(aux2);
                return -1;
            }
            aux1++;
            aux2++;
        }
    }
    if(*aux1 != '\0')
        return 1;
    else if(*aux2 != '\0')
        return -1;

    return 0;


}

void destroi_aux(dLista * lista){  //destroi a lista mas nao os doentes

    if(lista== NULL){
        return;
    }

    if(vazia(lista))
        lista = NULL;

    else{
        dLista current = *lista;
        dLista next = NULL;

        while(current!=NULL){
            next=current->prox;
            free(current);
            current = next;
        }

        *lista = NULL;  //colocar header a NULL quando se termina a eliminação
    }


}

void sort_lista_id(dLista * lista){
    dLista sorted = criaD();

    dLista aux = (*lista)->prox; //salta o header

    while (aux != NULL){
        insere(&sorted, aux->doente);
        aux = aux->prox;
    }

    dLista current = (*lista)->prox;
    dLista next = NULL;

    while(current!=NULL) {  // apaga a lista mas nao apaga os doentes
        next = current->prox;
        free(current);
        current = next;
    }

    (*lista)->prox = NULL;

    aux = sorted->prox;

    while(aux!=NULL){
        insere(lista,aux->doente);
        aux = aux->prox;
    }


    destroi_aux(&sorted);

}

void imprime_listaR_com_doente(rLista * lista,dLista * listaD) {


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
        imprime_doente_com_id(listaD,aux->registo->id_doente,1);
        imprime_registo(aux->registo);
        printf("\n");
        aux = aux->prox;
    }


}
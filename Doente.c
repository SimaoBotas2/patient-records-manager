//
// Created by HP on 4/19/2024.
//

#include "Doente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data.h"
#include "ListaRegistos.h"


int get_maior_tmax(Doente * mydoente){

    rLista aux = mydoente->listaR->prox;

    int max = 0;


    while(aux!=NULL){
        if(max<aux->registo->tensao_max)
            max = aux->registo->tensao_max;
        aux=aux->prox;
    }

    if(max>0)
        return max;
    else{
       // printf("Nao existem registos deste doente!\n");
        return -1;
    }

}



char *  confirma_nome(char * nome){
    bool beg = true;
    char * aux = malloc(strlen(nome));
    strcpy(aux,nome);
    while(*aux!= '\0'){
        if(beg == false){
            if(*aux == ' ')
                beg = true;
            else if(*aux >= 'A' && *aux<= 'Z')
                (*aux) += 32; //transforma maiusculas no meio da palavra em minusculas
            else if(*aux < 'A' || (*aux>'Z' && *aux<'a') || (*aux)>'z' )
                return NULL;
        }
        else {
            if (*aux >= 'a' && *aux <= 'z')
                (*aux) -= 32;
            else if (*aux == ' ')   // se houverem dois espaços seguidos
                return false;
            else if (*aux < 'A' || (*aux > 'Z' && *aux < 'a') || (*aux) > 'z')
                return false;
            beg = false;
        }
        aux++;
    }
    aux = aux - strlen(nome);

    return aux;
}


char * confirma_email(char * email){
    char *copia = malloc(strlen(email) + 1);
    if (copia == NULL) {
        return NULL;
    }
    strcpy(copia, email);


    char *nome = strtok(copia, "@");
    if (nome == NULL) {
        free(copia);
        return NULL;
    }


    //Valida o nome antes do @
    for (int i = 0; i < strlen(nome); i++) {
        if (!((nome[i] >= '!' && nome[i] <= ';') ||
              (nome[i] >= 'a' && nome[i] <= 'z') ||
              (nome[i] >= 'A' && nome[i] <= 'Z'))) {
            free(copia);
            return NULL;
        }
    }


    char *dominio = strtok(NULL, "@");
    if (dominio == NULL) {
        free(copia);
        return NULL;
    }

    //Valida o dominio, começando por ver se tem dois '.' seguidos ou se termina num '.'
    bool beg = false;
    for(int i =0;i< strlen(dominio);i++){
        if(dominio[i] == '.'){
            if(!beg)
                beg = true;
            else {
                free(copia);
                return NULL;
            }
        }
        else if(beg){
            beg = false;
        }
    }
    if(beg) {
        free(copia);
        return NULL;
    }

    char *token = strtok(dominio, ".");
    if (token == NULL) {
        free(copia);
        return NULL;
    }




    while (token != NULL) {
        for (int i = 0; i < strlen(token); i++) {

            if (!((token[i] >= '0' && token[i] <= '9') ||
                  (token[i] >= 'a' && token[i] <= 'z') ||
                  token[i] == '-'))
            {
                free(copia);
                return NULL;
            }


        }
        token = strtok(NULL, ".");

        beg = true;
    }


    free(copia);
    return email;
}


void write_doente(FILE * f,Doente * mydoente){


    char string[100];
    sprintf(string,"%d",mydoente->id_doente);
    fprintf(f, "%s\n",string);
    fprintf(f,"%s\n",mydoente->nome);
    fprintf(f,"%d/%d/%d\n",mydoente->data_nascimento->dia,mydoente->data_nascimento->mes,mydoente->data_nascimento->ano);
    fprintf(f,"%s\n",mydoente->cartao_cidadao);
    sprintf(string,"%ld",mydoente->telefone);
    fprintf(f,"%s\n",string);
    fprintf(f,"%s\n",mydoente->email);

    if(!vaziaR(&mydoente->listaR)){
        write_listaR(&mydoente->listaR);
    }


}



Doente * inicializa_doente(int id, char * nome, Data * data,char * cc,long long int nr,char * email){

    Doente * mydoente = (Doente*) malloc(sizeof(Doente));

    if(mydoente == NULL) {
        return NULL;
    }
    else {
        mydoente->nome = (char *) malloc(strlen(nome));
        mydoente->data_nascimento = (Data *) malloc(sizeof(Data));
        mydoente->cartao_cidadao = (char *) malloc(strlen(cc));
        mydoente->email = (char *) malloc(strlen(email));
        mydoente->listaR = criaR();

        if(mydoente->nome!=NULL && mydoente->data_nascimento!=NULL && mydoente->email!=NULL && mydoente->cartao_cidadao!=NULL){
            if(confirma_nrtele(nr)){
                mydoente->telefone = nr;
            }
            else{
                while(!confirma_nrtele(nr)){
                    printf("O numero de telefone introduzido nao e valido, introduza outro:\n");
                    scanf(" %lld",&nr);
                }
            }
            mydoente->id_doente = id;

            if(confirma_nome(nome)!=NULL)
                strcpy(mydoente->nome, confirma_nome(nome));
            else {
                char * aux = (char*) malloc(100);
                printf("O nome introduzido e invalido\n");
                printf("Introduza um novo:\n");
                while(confirma_nome(aux)==NULL){
                    gets(aux);
                }
                mydoente->nome = (char *) malloc(strlen(aux));
                strcpy(mydoente->nome, confirma_nome(aux));
                free(aux);
            }
            mydoente->data_nascimento=data;  //data já é confirmada antes
            strcpy(mydoente->cartao_cidadao,cc);


            if(confirma_email(email) == NULL) {
                char *aux = (char *) malloc(100);
                strcpy(aux,email);
                while (confirma_email(aux) == NULL) {
                    printf("O email introduzido e invalido, introduza um novo:\n");
                    scanf("%s", aux);
                }
                mydoente->email = (char *) malloc(strlen(aux));
                strcpy(mydoente->email,aux);
                free(aux);
            }
            else{
                strcpy(mydoente->email,email);
            }

            if(confirma_cc(cc) == NULL){
                char * aux = (char *) malloc(50);
                strcpy(aux,cc);
                while(confirma_cc(aux) == NULL){
                    printf("O cartao de cidadao introduzido e invalido, introduza um novo:\n");
                    scanf("%s",aux);
                }
                mydoente->cartao_cidadao = (char*) malloc(strlen(aux));
                strcpy(mydoente->cartao_cidadao,aux);
                free(aux);
            }
            else{
                strcpy(mydoente->cartao_cidadao,cc);
            }

            return mydoente;
        }
        else {
            free(mydoente->nome);
            free(mydoente->email);
            free(mydoente->cartao_cidadao);
            free(mydoente->data_nascimento);
            free(mydoente);
            return NULL;
        }
    }

}

int get_id(Doente * myDoente){
    return myDoente->id_doente;
}
void imprime_doente(Doente * myDoente,int opcao){
    if(opcao==0) {
        printf("Id   : %d\n", myDoente->id_doente);
        printf("Nome : %s\n", myDoente->nome);
        imprime_data(myDoente->data_nascimento);
        printf("Cartao de Cidadao : %s\n", myDoente->cartao_cidadao);
        printf("Telefone : %d\n", myDoente->telefone);
        printf("Email : %s\n", myDoente->email);
        printf("\nRegistos Medicos:\n");
        imprime_listaR(&myDoente->listaR);
    }
    if(opcao==1){
        printf("Id : %d\n",myDoente->id_doente);
        printf("Nome : %s\n",myDoente->nome);
    }
}

void erase_doente(Doente * myDoente){

        if(!vaziaR(&myDoente->listaR)){
            destroiR(&myDoente->listaR);
        }

        free(myDoente->nome);
        free(myDoente->data_nascimento);
        free(myDoente->cartao_cidadao);
        free(myDoente->email);
        free(myDoente);
}

bool confirma_nrtele(long int x){
    double aux = (double)x;


    if((aux / 1000000000)<1 && (aux/1000000000) > 0.1){  //tem nove digitos
        return true;
    }

    return false;
}

Doente * read_doente(FILE * d,rLista * all_registos){

    char fileRegistos[]= "Registos.txt";


    char buffer[100];
    int id=0;
    char nome[50];
    char data[15];
    char cc[20];
    long int nr;
    char email[50];
    bool work = true;


    if(feof(d)){
        printf("Fim de Ficheiro\n");
        return NULL;
    }

    if(fgets(buffer,100,d)!=NULL) {
        buffer[(strlen(buffer) - 1)] = '\0';
        id = atoi(buffer);
    }
    else
        work = false;


    if(feof(d)){
        printf("Erro ao ler o doente! (Fim de Ficheiro)\n");
        return NULL;
    }

    if(fgets(buffer,100,d)!=NULL) {
        buffer[(strlen(buffer) - 1)] = '\0';
        strcpy(nome, buffer);
    }
    else
        work = false;


    if(feof(d)){
        printf("Erro ao ler o doente! (Fim de Ficheiro)\n");
        return NULL;
    }


    if(fgets(buffer,100,d)!=NULL) {
        buffer[(strlen(buffer) - 1)] = '\0';
        strcpy(data, buffer);
    }
    else
        work = false;


    if(feof(d)){
        printf("Erro ao ler o doente! (Fim de Ficheiro)\n");
        return NULL;
    }

    if(fgets(buffer,100,d)!=NULL) {
        buffer[(strlen(buffer) - 1)] = '\0';
        strcpy(cc, buffer);
    }
    else
        work = false;


    if(feof(d)){
        printf("Erro ao ler o doente! (Fim de Ficheiro)\n");
        return NULL;
    }

    if(fgets(buffer,100,d)!=NULL) {
        buffer[(strlen(buffer) - 1)] = '\0';
        nr = atoi(buffer);
    }
    else
        work = false;

    if(feof(d)){
        printf("Erro ao ler o doente! (Fim de Ficheiro)\n");
        return NULL;
    }

    if(fgets(buffer,100,d)!=NULL) {
        buffer[(strlen(buffer) - 1)] = '\0';
        strcpy(email, buffer);
    }
    else
        work = false;


    if(work) {
        Doente *mydoente = inicializa_doente(id, nome, string_to_data(data), cc, nr, email);

        noListaR * aux = (*all_registos)->prox; //salta header
        while(aux!=NULL){
            if(aux->registo->id_doente==mydoente->id_doente)
                insereR(&mydoente->listaR,aux->registo);
            aux=aux->prox;
        }

        return mydoente;
    }

    else {
        printf("Erro ao ler o doente\n");
        return NULL;
    }


}

char * confirma_cc(char *cc){

    char copia[100];

    strcpy(copia,cc);

    char * numeros = strtok(copia,"-");
    if(strlen(numeros)!=8){
        return NULL;
    }
    else{
        char * aux = (char*) malloc(strlen(numeros));
        strcpy(aux,numeros);
        for(int i=0;i< strlen(numeros);i++){
            if(*(aux+i)>'9' || *(aux+i)<'0'){
                free(aux);
                return NULL;
            }
        }
        free (aux);
    } //primeiros 8 digitos corretos

    char * dig_ctrl = strtok(NULL,"-");
    if(dig_ctrl==NULL)
        return NULL;
    if(strlen(dig_ctrl) != 1) {
        return NULL;
    }
    if(*(dig_ctrl)>'9' || *(dig_ctrl) < '0') {
        return NULL;
    }


    char * last = strtok(NULL,"-");
    if(last==NULL)
        return NULL;
    char * aux = (char*) malloc(strlen(last));
    strcpy(aux,last);

    for(int i=0;i< strlen(last);i++){
        if(!((*(aux+i) >= '0' && *(aux+i) <= '9') || (*(aux+i) >= 'A' && *(aux+i) <= 'Z') || (*(aux+i) >= 'a' && *(aux+i)<='z'))){
            free(aux);
            return NULL;
        }
        if(*(aux+i) >= 'a' && *(aux+i)<='z'){
            *(aux+i) = *(aux+i) + 'A';
        }
    }
    free(aux);
    return cc;
}

Doente *  cria_doente(int id){
    //recebe o proximo id

   char * nome = (char*) malloc(100);
   if(nome==NULL)
       return NULL;
   char * data  = (char*) malloc(15);
   if(data==NULL)
       return NULL;
   char * cc = (char*) malloc(16);
   if(cc==NULL)
       return NULL;
   long long int nr_tele = 0;
   char * email = (char*) malloc(50);
   if(email==NULL)
       return NULL;



   printf("Introduza o seu nome:\n");
   gets(nome);

   while(confirma_nome(nome)==NULL){
       printf("Nome invalido, introduza um novo:\n");
       gets(nome);
   }

   printf("Introduza a data de nascimento no formato DD/MM/AAAA\n");
   scanf("%s",data);
   Data * mydata  = string_to_data(data);
   while(mydata == NULL) {
       printf("Data invalida, introduza uma nova:\n");
       gets(data);
       mydata = string_to_data(data);
   }
    fflush(stdin);
   printf("Introduza o Cartao de Cidadao no formato XXXXXXXX-X-XXX\n");
   gets(cc);
   while(confirma_cc(cc)==NULL){
       printf("Cartao de cidadao invalido, introduza um novo:\n");
       gets(cc);
   }
   printf("Introduza o seu numero de Telemovel:\n");
   scanf(" %lld",&nr_tele);
   while(!confirma_nrtele(nr_tele)){
       printf("Numero de telemovel invalido,introduza um novo:\n");
       scanf(" %lld",&nr_tele);
   }
   printf("Introduza o seu email:\n");
   scanf("%s",email);
   while(confirma_email(email)==NULL){
       printf("Email invalido,introduza um novo:\n");
       gets(email);
   }

   Doente * mydoente = malloc(sizeof(Doente));
   mydoente = inicializa_doente(id,nome,mydata,cc,nr_tele,email);

   return mydoente;

}

// Created by HP on 4/24/2024.
//

#include "Data.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>




Data * inicializa_data(int dia,int mes,int ano){

    Data * mydata = (Data*) malloc(sizeof(Data));
    if(mydata==NULL)
        return NULL;
    bool bissexto = false;

    if(ano<1900 || ano>2024){  //Decidir que ano utilizar para o primeiro
        printf("Ano invalido, introduza um novo:\n");
        scanf("%d",&ano);
        fflush(stdin);
    }
    if(mes>12 || mes<1){
        printf("Mes invalido,introduza um novo:\n");
            scanf("%d",&mes);
            fflush(stdin);
        }


    if(ano %400 == 0 ||(ano % 4 == 0 && ano % 100 != 0)){ //ano é bissexto
            bissexto = true;
    }

    switch(mes){
        case 1 :
            while(dia>31 || dia<1){
                printf("Dia introduzido nao e valido, introduza um numero entre 1 e 31:\n");
                scanf("%d", &dia);
                fflush(stdin);
            }
            break;
        case 2:
            if(bissexto){
                while(dia>29 || dia<1){
                    printf("Dia introduzido nao e valido, introduza um numero entre 1 e 29:\n");
                    scanf("%d", &dia);
                    fflush(stdin);
                }
            }
            else {
                while (dia > 28 || dia < 1) {
                    printf("Dia introduzido nao e valido, introduza um numero entre 1 e 28:\n");
                    scanf("%d", &dia);
                    fflush(stdin);
                }
            }
            break;
        case 3:
            while(dia>31 || dia<1){
                printf("Dia introduzido nao e valido, introduza um numero entre 1 e 31:\n");
                scanf("%d", &dia);
                fflush(stdin);
            }
            break;
        case 4:
            while(dia>30 || dia<1){
                printf("Dia introduzido nao e valido, introduza um numero entre 1 e 30:\n");
                scanf("%d", &dia);
                fflush(stdin);
            }
            break;
        case 5:
            while(dia>31 || dia<1){
                printf("Dia introduzido nao e valido, introduza um numero entre 1 e 31:\n");
                scanf("%d", &dia);
                fflush(stdin);
            }
            break;
        case 6:
            while(dia>30 || dia<1){
                printf("Dia introduzido nao e valido, introduza um numero entre 1 e 30:\n");
                scanf("%d", &dia);
                fflush(stdin);
            }
            break;
        case 7 :
            while(dia>31 || dia<1){
                printf("Dia introduzido nao e valido, introduza um numero entre 1 e 31:\n");
                scanf("%d", &dia);
                fflush(stdin);
            }
            break;
        case 8:
            while(dia>31 || dia<1){
                printf("Dia introduzido nao e valido, introduza um numero entre 1 e 31:\n");
                scanf("%d", &dia);
                fflush(stdin);
            }
            break;
        case 9:
            while(dia>30 || dia<1){
                printf("Dia introduzido nao e valido, introduza um numero entre 1 e 30:\n");
                scanf("%d", &dia);
                fflush(stdin);
            }
            break;
        case 10:
            while(dia>31 || dia<1){
                printf("Dia introduzido nao e valido, introduza um numero entre 1 e 31:\n");
                scanf("%d", &dia);
                fflush(stdin);
            }
            break;
        case 11:
            while(dia>30 || dia<1){
                printf("Dia introduzido nao e valido, introduza um numero entre 1 e 30:\n");
                scanf("%d", &dia);
                fflush(stdin);
            }
            break;
        case 12:
            while(dia>31 || dia<1){
                printf("Dia introduzido nao e valido, introduza um numero entre 1 e 31:\n");
                scanf("%d", &dia);
                fflush(stdin);
            }
            break;
        default:
            printf("MES INVALIDO:\n");
            return NULL;
    }

    mydata->dia=dia;
    mydata->mes=mes;
    mydata->ano=ano;
    return mydata;

}

Data * string_to_data(char * string){
    //Transforma a string recebida e devolve uma estrutura data


    char * aux = string;
    int counter_d = 0;
    int counter_m= 0;
    int counter_y = 0;
    int counter_b = 0;

    for(;(*aux) != '\0';aux++) {
        if (*aux == '/'){
            counter_b++;
            continue;
        }
        if(counter_b == 0 ){
            counter_d++;
        }
        if(counter_b == 1){
            counter_m++;
        }
        if(counter_b == 2){
            counter_y++;
        }
    }
    while(counter_d>2 || counter_d<0 || counter_m>2 || counter_m <0 || counter_y<0 || counter_y>4){
        printf("Data inserida invalida:\n");
        return NULL;
    }

    char * copia = malloc(strlen(string)+1);

    strcpy(copia,string);

    char *token = strtok(copia,"/");
    int dias = atoi(token);
    token = strtok(NULL,"/");
    int mes = atoi(token);
    token = strtok(NULL,"/");
    int ano = atoi(token);

    Data * mydata = inicializa_data(dias,mes,ano);

    free(copia);

    return mydata;
}

void imprime_data(Data * mydata){
    printf("Data : %d/%d/%d\n",mydata->dia,mydata->mes,mydata->ano);
}

int compara_datas(Data * a, Data * b){  //retorna 1 se a > b, 0 se a=b e , -1 se b>a


    if(a->ano>b->ano)
        return 1;
    if(b->ano>a->ano)
        return -1;

    if(a->mes > b->mes)
        return 1;
    if(b->mes>a->mes)
        return -1;

    if(a->dia>b->dia)
        return 1;
    if(b->dia>a->dia)
        return -1;

    return 0;


}


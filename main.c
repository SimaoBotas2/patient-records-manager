
#include <stdio.h>
#include "Doente.h"
#include "ListaDoentes.h"
#include "Data.h"
#include "ListaRegistos.h"
#include "Registo.h"
#include <stdlib.h>

void menu(int x,dLista listaD){
    int escolha= 0;
    bool in_menu = true;
    bool alfa = false; // indica se a lista esta ordenada por ordem alfabetica ou nao

    while(in_menu) {
        switch (x) {
            case(0):
                in_menu=false;
                break;
            case -1:
                printf("O que pretende fazer:\n");
                printf("0:Sair do Programa\n1:Imprimir todos os Doentes\n2:Imprimir toda a Informacao de um Doente\n3:Introduzir novo Doente\n4:Remover um Doente\n");
                printf("5:Introduzir novo Registo\n6:Imprimir doentes com tensao max superior a x\n7:Organizar Doentes por ordem Alfabetica\n8:Organizar Doentes por ordem de ID\n");
                scanf(" %d", &x);
                fflush(stdin);
                break;
            case 1:
                imprime_listaD(&listaD,1);
                printf("\n");
                x=-1;
                break;
            case 2:
                imprime_listaD(&listaD,1);
                printf("Escolha o id do Doente que pretende\n");
                scanf("%d",&escolha);
                imprime_doente_com_id(&listaD,escolha,0);
                fflush(stdin);
                x = -1;
                break;
            case 3:
                fflush(stdin);
                Doente * mydoente = cria_doente(last_id(&listaD)+1);
                if(mydoente==NULL)
                    printf("Erro ao criar o doente!\n");
                else {
                    if(!alfa)
                    insere(&listaD, mydoente);
                    else
                        insere_alfa(&listaD,mydoente);
                }
                x=-1;
                break;
            case 4:
                fflush(stdin);
                imprime_listaD(&listaD,1);
                printf("Escolha o id do Doente que pretende remover:\n");
                scanf("%d",&escolha);
                fflush(stdin);
                while(escolha>last_id(&listaD)){
                    printf("Introduza um numero valido:\n");
                    scanf("%d",&escolha);
                }
                elimina(&listaD,escolha);
                x=-1;
                break;
            case 5:
                fflush(stdin);
                imprime_listaD(&listaD,1);
                printf("Escolha o id do Doente que pretende adicionar o registo:\n");
                scanf("%d",&escolha);
                fflush(stdin);
                while(escolha>last_id(&listaD)){
                    printf("Introduza um numero valido:\n");
                    scanf("%d",&escolha);
                }
                introduzir_novo_registo(&listaD,escolha);
                x=-1;
                break;
            case 6:
                fflush(stdin);
                printf("Introduza o numero de tensao:\n");
                scanf("%d",&escolha);
                imprime_doentes_com_tmax(&listaD,escolha);
                x=-1;
                break;
            case 7:
                fflush(stdin);
               sort_lista_ordem_alfa(&listaD);  //faço uma lista auxiliar em que vou inserindo logo por ordem alfabetica
               imprime_listaD(&listaD,1);
               alfa = true;
               x=-1;
               break;
            case 8:
                fflush(stdin);
                sort_lista_id(&listaD);
                imprime_listaD(&listaD,1);
                alfa = false;
                x=-1;
                break;
            default:
                printf("Opcao nao reconhecida\n");
                x=-1;
                break;
        }
    }


}



int main() {

    //Inicio de Rotina
    rLista listaR = criaR();  //lista com todos os registos, lida do ficheiro
    read_listaR(&listaR);

    dLista listaD = criaD();  //lista com todos os doentes, lida do ficheiro
    read_listaD(&listaD,&listaR);
    //Fim do Inicio de Rotina

    //Main Code
    menu(-1,listaD);

    //Fim de Main Code

    //Inicio de Fim de Rotina

    sort_lista_id(&listaD);
    write_listaD(&listaD);
    destroiD(&listaD);

    //Fim de Fim de Rotina

    return 0;
}

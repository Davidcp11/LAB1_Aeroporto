/*  David Costa Pereira                               */
/*  Turma 3                                           */
/*  Exercicio 1: Torre de Controle                    */
/*                                                    */
/*  Programa compilado com CodeBlocks 20.03           */

#include<stdio.h>
#include "iostream"
#include <string.h>
typedef struct voo noh;
///Struct com os dados de cada voo
struct voo{
    int numbvoo;
    char from[32];
    noh *prox;
};

int main(){
    ///Declaracoes de variaveis
    FILE *entrada, *saida;
    entrada = fopen("entrada1.txt","r");
    saida = fopen("Lab1_David_Costa_Pereira.txt","w");
    noh *p, *inicio, *ant, *aux, *finalUrg;
    int voo_urg;
    char lixo[72], message[15];
    ///Atribuicao inicial aos ponteiros
    inicio=NULL;
    finalUrg=NULL;
    ///Mensagem inicial
    fprintf(saida,"Torre de Controle CABACITA\n");
    fprintf(saida,"Tenha uma otima experiencia\n");
    fprintf(saida,"AUTORIZACOES DE POUSO\n");
    fprintf(saida,"========================================\n");
    fprintf(saida,"FLIGHT  FROM\n\n");
    ///Ler as 7 primeiras linhas
    for(int i=0;i<7;i++)
        fgets(lixo,72,entrada);
    ///Lendo o INICIO, 0000 e o -
    fscanf(entrada," %s ", message);
    fgets(lixo,72,entrada);
    while(strcmp(message,"FIM")!=0){
        fscanf(entrada," %s ", message);
        if(strcmp(message,"pede_pouso")==0){
            ///Caso a fila esteja vazia
            if (inicio == NULL) {
                inicio = (noh *) malloc(sizeof(noh));
                fscanf(entrada," %d ", &inicio->numbvoo);
                fgets(inicio->from,32,entrada);
                inicio->from[strlen(inicio->from)-1]='\0';
                inicio->prox=NULL;
            }
            ///Caso a fila nao esteja vazia
            else{
                p=(noh*) malloc(sizeof(noh));
                fscanf(entrada," %d ", &p->numbvoo);
                fgets(p->from,32,entrada);
                p->from[strlen(p->from)-1]='\0';
                ///Inserindo no final da fila
                aux=inicio;
                while(aux->prox!=NULL){
                    aux=aux->prox;
                }
                aux->prox=p;
                p->prox=NULL;
            }
        }
        if(strcmp(message,"pista_liberada")==0){
            fgets(lixo,72,entrada);
            ///Atribuir NULL ao ponteiro do final da fila de urgencia, caso ele seja o aviao que vai pousar
            if(inicio!=NULL && finalUrg!=NULL)
                if(inicio->numbvoo==finalUrg->numbvoo)
                    finalUrg=NULL;
            ///Caso a fila nao esteja vazia, retiramos o primeiro
            if(inicio!=NULL){
                aux=inicio->prox;
                fprintf(saida,"%04d    ", inicio->numbvoo);
                fprintf(saida,"%s\n", inicio->from);
                free(inicio);
                inicio=aux;
            }
            ///Caso a fila esteja vazia
            else{
                fprintf(saida,"0000    Nenhum aviao pousando\n");
            }
        }
        if(strcmp(message,"URGENCIA")==0){
            fscanf(entrada," %d ", &voo_urg);
            fgets(lixo,72,entrada);
            ///Procurando o voo na fila
            ant=inicio;
            p=inicio->prox;
            bool achou= false;
            ///Verificar se estar no inicio
            if(voo_urg == inicio->numbvoo){
                achou= true;
                p=NULL;
            }
            while (!achou){
                if(voo_urg == p->numbvoo){
                    achou=true;
                }
                else {
                    ant=p;
                    p=p->prox;
                }
            }
            ///Inserindo apos o ultimo voo que pediu urgencia
            if(finalUrg==NULL){
                if(p!=NULL) {
                    ant->prox = p->prox;
                    p->prox = inicio;
                    inicio = p;
                    finalUrg = p;
                } else finalUrg=inicio;
            }
            else{
                    ant->prox=p->prox;
                    p->prox = finalUrg->prox;
                    finalUrg->prox = p;
                    finalUrg = p;
            }
        }
    }
    ///Situacao da fila
    fprintf(saida,"\nSituacao da fila\n\n");
    ///Fila vazia
    if(inicio==NULL){
        fprintf(saida,"livre");
    }
    ///Fila nao vazia
    else {
        while (inicio != NULL) {
            fprintf(saida, "%04d    %s\n", inicio->numbvoo, inicio->from);
            aux=inicio;
            inicio=inicio->prox;
            free(aux);
        }
    }
    ///Fechando arquivos de entrada e de saida
    fclose(entrada);
    fclose(saida);
    return 0;
}

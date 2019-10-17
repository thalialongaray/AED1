#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct contato{
    char nome[20];
    unsigned long int tel;
    struct contato *prox;
};

typedef struct contato contato;
contato *cria(void);
int menu(void);
void insere_no_inicio(contato *p);
void insere_no_fim(contato *p);
void imprime(contato *p);
void busca_nome(contato *p);
void busca_tel(contato *p);
void excluir_nome(contato *p);
void excluir_inicio(contato *p);
void excluir_fim(contato *p);
void ordena(contato *p);
void le(contato *p);
void grava(contato *p);

int main(){
    int escolha;
    contato *agenda;
    agenda=cria();
    for(;;){
        escolha=menu();
        switch(escolha){
        case 1:
            insere_no_inicio(agenda);
            break;
        case 2:
            insere_no_fim(agenda);
            break;
        case 3:
            busca_nome(agenda);
            break;
        case 4:
            busca_tel(agenda);
            break;
        case 5:
            excluir_nome(agenda);
            break;
        case 6:
            excluir_inicio(agenda);
            break;
        case 7:
            excluir_fim(agenda);
            break;
        case 8:
            ordena(agenda);
            break;
        case 9:
            imprime(agenda);
            break;
        case 10:
            grava(agenda);
            break;
        case 11:
            le(agenda);
            break;
        case 12:
            free(agenda);
            exit(0);
            break;
        }
    }
    return 0;
}

contato *cria(void){
    contato *inicio;
    inicio=(contato *)malloc(sizeof(contato));
    inicio->prox=NULL;

    return inicio;
}

int menu(void){
    int op;
    do{
        printf("MENU\n\t1.Inserir contato no inicio da agenda\n\t2.Inserir contato no final da agenda\n\t3.Buscar contato por nome\n\t4.Buscar contato por telefone\n\t5.Excluir contato por nome\n\t6.Excluir contato do inicio da agenda\n\t7.Excluir contato do final da agenda\n\t8.Ordenar contatos alfabeticamente\n\t9.Mostrar agenda\n\t10.Gravar em arquivo texto\n\t11.Ler arquivo texto\n\t12.Sair\nDigite sua escolha: ");
        scanf("%d",&op);
    } while(op<0 || op>12);
    getchar();

    return op;
}

void insere_no_inicio(contato *p){
    contato *nova;

    nova=(contato *)malloc(sizeof(contato));

    printf("Nome: ");
    scanf("%s",nova->nome);
    printf("Telefone: ");
    scanf("%lu",&nova->tel);
    nova->prox=p->prox;
    p->prox=nova;

    free(nova);
}

void insere_no_fim(contato *p){
    contato *nova, *fim;

    nova=(contato *)malloc(sizeof(contato));

    printf("Nome: ");
    scanf("%s",nova->nome);
    printf("Telefone: ");
    scanf("%lu",&nova->tel);

    for(fim=p; fim->prox!=NULL; fim=fim->prox);
    nova->prox=fim->prox;
    fim->prox=nova;

    free(nova);
}

void busca_nome(contato *p){
    contato *percorre;
    int i=1;
    char nome[20];
    printf("Nome para busca: ");
    scanf("%s",nome);
    for(percorre=p->prox; percorre!=NULL && strcmp(percorre->nome,nome)!=0; percorre=percorre->prox){
        i++;
    }
    if(percorre!=NULL){
        printf("Encontrado!\nContato %d\tNome: %s\tTelefone: %lu\n",i,percorre->nome,percorre->tel);
    } else{
        printf("Contato nao encontrado!\n");
    }
}

void busca_tel(contato *p){
    contato *percorre;
    int i=1;
    unsigned long int tel;
    printf("Telefone para busca: ");
    scanf("%lu",&tel);
    for(percorre=p->prox; percorre!=NULL && percorre->tel!=tel; percorre=percorre->prox){
        i++;
    }
    if(percorre!=NULL){
        printf("Encontrado!\nContato %d\tNome: %s\tTelefone: %lu\n",i,percorre->nome,percorre->tel);
    } else{
        printf("Contato nao encontrado!\n");
    }
}

void excluir_nome(contato *p){
    contato *i, *j;
    char nome[20];
    printf("Nome do contato que deseja excluir: ");
    scanf("%s",&nome);
    i=p;
    j=p->prox;
    while(j!=NULL && strcmp(j->nome,nome)!=0){
        i=j;
        j=j->prox;
    }
    if(j!=NULL){
        i->prox=j->prox;
        free(j);
    }
}

void excluir_inicio(contato *p){
    contato *q;
    q=p->prox;
    p->prox=q->prox;
    free(q);
}

void excluir_fim(contato *p){
    contato *percorre, *percorre2;
    percorre=p;
    percorre2=p->prox;
    for(;percorre2->prox!=NULL;){
        percorre=percorre2;
        percorre2=percorre2->prox;
    }
    percorre->prox=percorre2->prox;
    free(percorre2);
}

void ordena(contato *p){
    contato *i, *j;
    char aux[20];
    aux[0]='\0';
    unsigned long int auxi;
    for(i=p->prox; i->prox!=NULL; i=i->prox){
        for(j=i->prox; j!=NULL; j=j->prox){
            if(strcmp(i->nome,j->nome)>0){
                strcpy(aux, i->nome);
                strcpy(i->nome, j->nome);
                strcpy(j->nome, aux);
                auxi=i->tel;
                i->tel=j->tel;
                j->tel=auxi;
            }
        }
    }
}

void imprime(contato *p){
    int i=1;
    for(p=p->prox; p!=NULL; p=p->prox){
        printf("Contato %d\tNome: %s\tTelefone: %lu\n",i,p->nome,p->tel);
        i++;
    }
}

void le(contato *p){
    contato *nova, *fim;
    FILE *arquivo;

    if((arquivo=fopen("agenda.txt","r"))==NULL){
        printf("Arquivo nao encontrado");
        exit(0);
    } else{
        nova=(contato *)malloc(sizeof(contato));
		fscanf(arquivo,"%s",nova->nome);
		while(!feof(arquivo)){
			fscanf(arquivo,"%lu",&nova->tel);

			for(fim=p; fim->prox!=NULL; fim=fim->prox);
			nova->prox=fim->prox;
			fim->prox=nova;

			nova=(contato *)malloc(sizeof(contato));
			fscanf(arquivo,"%s",nova->nome);
		}
        fclose(arquivo);
        free(nova);
    }
}

void grava(contato *p){
    FILE *arquivo;
    contato *percorre;

    arquivo=fopen("agenda.txt","w");
    for(percorre=p->prox; percorre!=NULL; percorre=percorre->prox){
        fprintf(arquivo,"%s\n",percorre->nome);
        fprintf(arquivo,"%lu\n",percorre->tel);
    }
    fclose(arquivo);
}

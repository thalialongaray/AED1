#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

const int m=3;

struct Contato{
    char nome[10];
    int tel;
};

struct Pilha{
    struct Contato agenda[m];
    int topo;
    int base;
    int limite;
};

typedef struct Contato contato;
typedef struct Pilha pilha;
void reset(pilha *p);
bool empty(pilha *p);
bool full(pilha *p);
bool push(pilha *p);
void pop(pilha *p, contato *c);
void listar(pilha *p);
void clear(pilha *p);

int main(){
    pilha *p;
    p=(pilha *)malloc(sizeof(pilha));
    reset(p);

    int op;
    for(;;){
        do{
            printf("MENU\n1.Inserir contato (topo da pilha)\n2.Remover contato (topo da pilha)\n3.Listar contatos\n4.Conferir se agenda esta vazia\n5.Conferir se agenda esta cheia\n6.Limpar agenda\n7.Sair\n");
            scanf("%d",&op);
        } while(op>7||op<1);

        switch(op){
            case 1:
                if(push(p))
                    printf("Contato inserido\n");
                else
                    printf("Agenda cheia\n");
                break;
            case 2:
                if(empty(p)){
                    printf("Agenda vazia\n");
                    break;
                }
                contato *remover;
                remover=(contato *)malloc(sizeof(contato));
                pop(p,remover);
                free(remover);
                printf("Contato removido\n");
                break;
            case 3:
                listar(p);
                break;
            case 4:
                if(empty(p))
                    printf("Agenda vazia\n");
                else
                    printf("Agenda nao vazia\n");
                break;
            case 5:
                if(full(p))
                    printf("Agenda cheia\n");
                else
                    printf("Agenda nao cheia\n");
                break;
            case 6:
                clear(p);
                printf("Agenda limpa\n");
                p=(pilha *)malloc(sizeof(pilha));
                reset(p);
                break;
            case 7:
                exit(0);
                break;
        }
    }
    clear(p);
    return 0;
}

void reset(pilha *p){
    p->topo=0;
    p->base=0;
    p->limite=m;
}

bool empty(pilha *p){
    return p->topo==0;
}

bool full(pilha *p){
    return p->topo==p->limite;
}

bool push(pilha *p){
    if(full(p))
        return false;

    printf("Nome: ");
    scanf("%s",p->agenda[p->topo].nome);
    printf("Tel: ");
    scanf("%d",&p->agenda[p->topo].tel);

    p->topo++;
    return true;
}

void pop(pilha *p, contato *c){
    p->topo--;
    *c=p->agenda[p->topo];
}

void listar(pilha *p){
    if(empty(p)){
        printf("Agenda vazia\n");
        return;
    }

    pilha *auxp;
    auxp=(pilha *)malloc(sizeof(pilha));
    reset(auxp);

    contato *auxc;
    auxc=(contato *)malloc(sizeof(contato));

    int i;
    for(i=p->topo; i>0; i--){
        pop(p,auxc);
        auxp->agenda[auxp->topo]=*auxc;
        printf("Nome: %s\tTel: %d\n",auxp->agenda[auxp->topo].nome,auxp->agenda[auxp->topo].tel);
        auxp->topo++;
    }

    for(i=auxp->topo; i>0; i--){
        pop(auxp,auxc);
        p->agenda[p->topo]=*auxc;
        p->topo++;
    }

    free(auxc);
    clear(auxp);
}

void clear(pilha *p){
    contato *limpa;
    limpa=(contato *)malloc(sizeof(contato));

    int i;
    for(i=p->topo; i>0; i--){
        pop(p,limpa);
    }

    free(limpa);
    free(p);
}
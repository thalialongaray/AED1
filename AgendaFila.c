#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Contato{
    char nome[10];
    int tel;
};
typedef struct Contato contato;

struct TipoFila{
    contato c;
    struct TipoFila *next;
};
typedef struct TipoFila tipofila;

struct Fila{
    tipofila *first;
    tipofila *last;
};
typedef struct Fila fila;

fila *reset(void);
bool empty(fila *f);
void push(fila *f);
bool pop(fila *f);
void listar(fila *f);
void clear(fila *f);

int main(){
    fila *f;
    f=reset();
    
    int op;
    for(;;){
        do{
            printf("MENU\n1.Inserir contato (final da fila)\n2.Remover contato (inicio da fila)\n3.Listar contatos\n4.Conferir se agenda esta vazia\n5.Limpar agenda\n6.Sair\n");
            scanf("%d",&op);
        } while(op>6||op<1);

        switch(op){
            case 1:
                push(f);
                printf("Contato inserido\n");
                break;
            case 2:
                if(!pop(f))
                    printf("Agenda vazia\n");
                else
                    printf("Contato removido\n");
                break;
            case 3:
                listar(f);
                break;
            case 4:
                if(empty(f))
                    printf("Agenda vazia\n");
                else
                    printf("Agenda nao vazia\n");
                break;
            case 5:
                clear(f);
                printf("Agenda limpa\n");
                break;
            case 6:
                exit(0);
                break;
        }
    }
    clear(f);
    free(f);
    return 0;
}

fila *reset(void){
    fila *f;
    f=(fila *)malloc(sizeof(fila));
    f->first=NULL;
    f->last=NULL;

    return f;
}

bool empty(fila *f){
    return f->first==NULL;
}

void push(fila *f){
    contato cnovo;
    printf("Nome: ");
    scanf("%s",cnovo.nome);
    printf("Tel: ");
    scanf("%d",&cnovo.tel);

    tipofila *novo;
    novo=(tipofila *)malloc(sizeof(tipofila));
    novo->c=cnovo;
    novo->next=NULL;

    if(f->last!=NULL)
        f->last->next=novo;
    else
        f->first=novo;

    f->last=novo;
}

bool pop(fila *f){
    if(empty(f))
        return false;
    
    tipofila *remove;
    remove=f->first;
    f->first=f->first->next;

    if(empty(f))
        f->last=NULL;

    return true;
}

void listar(fila *f){
    if(empty(f)){
        printf("Agenda vazia\n");
        return;
    }
    
    tipofila *percorre;
    for(percorre=f->first; percorre!=NULL; percorre=percorre->next){
        printf("Nome: %s\tTel: %d\n",percorre->c.nome,percorre->c.tel);
    }
    
    free(percorre);
}

void clear(fila *f){
    if(empty(f))
        return;
    else{
        pop(f);
        clear(f);
    }
}

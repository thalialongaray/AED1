#include <stdio.h>
#include <stdlib.h>

Insertion(int *data, int n){
    int i, j, tmp;
    for(i=0; i<n; i++){
        j=i-1;
        tmp=*(data+i);
        while((j>=0) && (tmp<*(data+j))){
            *(data+(j+1))=*(data+j);
            j--;
        }
        *(data+(j+1))=tmp;
    }
}

Bubble(int *data, int n){
    int i, j, tmp;
    for(i=0; i<n-1; i++){
        for(j=0; j<n-i-1; j++){
            if(*(data+j)>*(data+(j+1))){
                tmp=*(data+j);
                *(data+j)=*(data+(j+1));
                *(data+(j+1))=tmp;
            }
        }
    }
}

Select(int *data, int n){
    int i, j, tmp, min, minid;
    for(i=0; i<n-1; i++){
        min=*(data+i);
        tmp=*(data+i);
        minid=i;
        for(j=i+1; j<n; j++){
            if(min>*(data+j)){
                min=*(data+j);
                minid=j;
            }
        }
        *(data+i)=*(data+minid);
        *(data+minid)=tmp;
        minid=i+1;
    }
}

Quick(int *data, int left, int right){
    int i, j, tmp, pivo;
    i=left;
    j=right;
    pivo=*(data+((left+right)/2));
    do{
        while(*(data+i)<pivo){
            i++;
        }
        while(pivo<*(data+j)){
            j--;
        }
        if(i<=j){
            tmp=*(data+i);
            *(data+i)=*(data+j);
            *(data+j)=tmp;
            i++;
            j--;
        }
    }while(i<=j);
    if(left<j){
        Quick(data,left,j);
    }
    if(i<right){
        Quick(data,i,right);
    }
}

Imprime(int *data, int n){
    int i;
    printf("%d",*(data+0));
    for(i=1; i<n; i++){
        printf(" %d",*(data+i));
    }
    printf("\n");
}

int main(){
    int *data, n, op, i;
    for(;;){
        printf("Menu\n\t1.Ordenar com InsertionSort\n\t2.Ordenar com SelectSort\n\t3.Ordenar com BubbleSort\n\t4.Ordenar com QuickSort\n\t5.Sair\nOpcao ");
        scanf("%d",&op);
        if(op<6 && op>0)
        switch(op){
            case 1:
            printf("Quantidade de elementos: ");
            scanf("%d",&n);
            data=(int *)malloc(n*sizeof(int));
            printf("Elementos: ");
            for(i=0; i<n; i++){
                scanf("%d",&*(data+i));
            }
            Insertion(data,n);
            Imprime(data,n);
            free(data);
            break;

            case 2:
            printf("Quantidade de elementos: ");
            scanf("%d",&n);
            data=(int *)malloc(n*sizeof(int));
            printf("Elementos: ");
            for(i=0; i<n; i++){
                scanf("%d",&*(data+i));
            }
            Select(data,n);
            Imprime(data,n);
            free(data);
            break;

            case 3:
            printf("Quantidade de elementos: ");
            scanf("%d",&n);
            data=(int *)malloc(n*sizeof(int));
            printf("Elementos: ");
            for(i=0; i<n; i++){
                scanf("%d",&*(data+i));
            }
            Bubble(data,n);
            Imprime(data,n);
            free(data);
            break;

            case 4:
            printf("Quantidade de elementos: ");
            scanf("%d",&n);
            data=(int *)malloc(n*sizeof(int));
            printf("Elementos: ");
            for(i=0; i<n; i++){
                scanf("%d",&*(data+i));
            }
            Quick(data,-1,n);
            Imprime(data,n);
            break;

            case 5:
            exit(0);
            break;
        }
    }
    return 0;
}

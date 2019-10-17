#include <stdio.h>
#include <stdlib.h>

Insertion(int *data, int n){
    int i, j, tmp;
    for(i=1; i<n; i++){
        j=i-1;
        tmp=*(data+i);
        while((j>=0) && (tmp<*(data+j))){
            *(data+(j+1))=*(data+j);
            j--;
        }
        *(data+(j+1))=tmp;
    }
}

Bubble(int *data2, int n){
    int i, j, tmp;
    for(i=0; i<n-1; i++){
        for(j=0; j<n-i-1; j++){
            if(*(data2+j)>*(data2+(j+1))){
                tmp=*(data2+j);
                *(data2+j)=*(data2+(j+1));
                *(data2+(j+1))=tmp;
            }
        }
    }
}

int main(){
    int *data, *data2, i, n;
    scanf("%d",&n);
    data=(int *)malloc(n*sizeof(int));
    data2=(int *)malloc(n*sizeof(int));

    for(i=0; i<n; i++){
        scanf("%d",&*(data+i));
        *(data2+i)=*(data+i);
    }

    Insertion(data,n);
    Bubble(data2,n);

    for(i=0; i<n; i++){
        printf("%d ",*(data+i));
    }
    printf("\n");
    for(i=0; i<n; i++){
        printf("%d ",*(data2+i));
    }

    return 0;
}
//Thalía Djune Costa Longaray

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Vertice{
    int n;
    unsigned int aresta[20];
    char letra;
    char predecessor;
    bool marcacao;
};

struct VerticeAGM{
    unsigned int aresta[20];
    char letra;
    char predecessor;
    char *posterior;
    int contpost;
    bool marcacao;
};

typedef struct Vertice vertice;
typedef struct VerticeAGM verticeagm;
void imprimeVertices(vertice *a);
vertice *inicializaMatriz();
void imprimeMatriz(vertice *a);
void imprimeArestas(vertice *a);
vertice *algoritmo(vertice *a);
void Insertion(unsigned int *a, char *v, int n);

int main(){
    printf("\t\tALGORITMO DE KRUSKAL\n");

    vertice *arvore;
    arvore=inicializaMatriz();
    printf("\nMatriz resultante: \n");
    imprimeMatriz(arvore);
    
    vertice *agm;
    agm=algoritmo(arvore);

    char op;
    if(agm==NULL){
        printf("Tentar novamente? [S/N] ");
        scanf("\n%c", &op);
        switch(op){
            case 'S':
                free(arvore);
                arvore=inicializaMatriz();
                printf("\nMatriz resultante: \n");
                imprimeMatriz(arvore);
                agm=algoritmo(arvore);
                if(agm!=NULL){
                    printf("\nMatriz AGM: \n");
                    imprimeMatriz(agm);
                    printf("\nArestas AGM: \n");
                    imprimeArestas(agm);
                    free(agm);
                }
                break;
            case 'N':
                break;
        }
    } else{
        printf("\nMatriz AGM: \n");
        imprimeMatriz(agm);
        printf("\nArestas AGM: \n");
        imprimeArestas(agm);
        free(agm);
    }
    free(arvore);

    return 0;
}

void imprimeVertices(vertice *a){
    int i;
    printf("\t-");
    for(i=0; i<a[0].n; i++){
        printf("--%c", a[i].letra);
    }
    printf("\n");
}

vertice *inicializaMatriz(){
    printf("\nInicializacao do grafo:\n");

    int num;
 
    printf("Numero de vertices (maximo -> 20): ");
    scanf("%d", &num);

    vertice *a;
    a=(vertice *)malloc(num*sizeof(vertice));
    a[0].n=num;
    
    int i, j, k;
    unsigned int teste;
    char vert, matriz[59];

    for(i=0; i+65<a[0].n+65; i++){
        a[i].letra=i+65;
        a[i].n=a[0].n;
        for(j=0; j<a[0].n; j++){
            a[i].aresta[j]=0;
        }
        for(j=a[0].n; j<20; j++){
            a[i].aresta[j]=1000;
        }
    }

    printf("(Peso maximo por aresta -> 99\nVertices sem conexao -> Peso 0)\n");
    imprimeVertices(a);

    for(i=0; i<a[0].n; i++){
        k=0;
        printf("\t%c-", a[i].letra);
        scanf("%s", matriz);
        for(j=0; matriz[j]!='\0'; j++){
            if(j!=0){
                j++;
            }
            if(matriz[j]=='-'){
                a[i].aresta[k]=matriz[++j]-'0';
            } else if(matriz[j+1]=='-'){
                a[i].aresta[k]=matriz[j]-'0';
            } else if(matriz[j+1]=='\0'){
                a[i].aresta[k]=matriz[j]-'0';
                break;
            } else{
                a[i].aresta[k]=(10*(matriz[j]-'0'))+(matriz[++j]-'0');
            }
            k++;
        }
    }

    return a;
}

void imprimeMatriz(vertice *a){
    int i, j;
    imprimeVertices(a);
    for(i=0; i<a[0].n; i++){
        printf("\t%c-", a[i].letra);
        for(j=0; j<a[0].n; j++){
            if(a[i].aresta[j]<10){
                printf("-%d", a[i].aresta[j]);
            } else{
                printf("%d", a[i].aresta[j]);
            }

            if(j<(a[0].n)-1){
                printf("-");
            } else{
                printf("\n");
            }
        }
    }
}

void imprimeArestas(vertice *a){
    int i, j;
    for(i=0; i<a[0].n; i++){
        for(j=0; j<a[0].n; j++){
            if(a[i].aresta[j]>0 && a[i].aresta[j]==a[j].aresta[i] && j>i){
                printf("%c-%c\t%d\n", a[i].letra, j+65, a[i].aresta[j]);
            }
        }
    }
}

vertice *algoritmo(vertice *a){
    unsigned int *arestasord;       //arestas grafo de entrada
    char *verticesord;              //vertices ligados pelas arestas

    arestasord=(unsigned int *)malloc(a[0].n*a[0].n*sizeof(unsigned int));
    verticesord=(char *)malloc(a[0].n*a[0].n*2*sizeof(char));

    int i, j, k=0, l;
    bool arestaadc;                 //flag p/ evitar duplicação de arestas
    for(i=0; i<a[0].n; i++){
        for(j=0; j<a[0].n; j++){
            for(l=0; l<k; l++){
                arestaadc=false;
                if(*(arestasord+l)==a[i].aresta[j] && *(verticesord+(l*2))==j+65 && *(verticesord+(l*2)+1)==a[i].letra){
                    arestaadc=true;
                    break;
                }
            }
            if(a[i].aresta[j]>0 && i!=j && !arestaadc){
                *(arestasord+k)=a[i].aresta[j];
                *(verticesord+(k*2))=a[i].letra;
                *(verticesord+(k*2)+1)=j+65;
                k++;                                //quantidade de arestas já adicionadas a arestasord
            }
        }
    }

    arestasord=(unsigned int *)realloc(arestasord, k*sizeof(unsigned int));
    verticesord=(char *)realloc(verticesord, k*2*sizeof(char));

    Insertion(arestasord, verticesord, k);          //ordena (em ordem crescente de arestas) arestasord e verticesord

    if(k>0)
        printf("\nArestas (ordem crescente): \n");
    for(i=0; i<k; i++){
        printf("%c-%c\t%d\n", *(verticesord+(i*2)), *(verticesord+(i*2)+1), *(arestasord+i));
    }

    verticeagm *agm;
    agm=(verticeagm *)malloc(a[0].n*sizeof(verticeagm));
    
    for(i=0; i<a[0].n; i++){
        agm[i].letra=a[i].letra;
        for(j=0; j<20; j++){
            agm[i].aresta[j]=0;
        }
        agm[i].predecessor='\0';                //vertice que liga o vertice agm[i] aos demais já pertencentes a agm
        agm[i].posterior=(char *)malloc(sizeof(char));
        agm[i].posterior[0]='\0';               //vertices que o vertice agm[i] liga a agm
        agm[i].contpost=0;                      //quantidade de vertices que o vertice agm[i] liga a agm
    }

    char conjuntos[a[0].n][a[0].n];             //conjuntos (cada um corresponde a um vertice)

    for(i=0; i<a[0].n; i++){
        conjuntos[i][0]=agm[i].letra;
        conjuntos[i][1]='\0';
    }

    int m, n;
    bool marcacao;                              //flag p/ verificação de ligação a agm -> quando true, todos os vértices do conjunto1 já pertencem a agm
    char conjuntoatual, conjunto1, conjunto2;   //conjunto1: conjunto destino do vertice; conjunto2: conjunto origem do vertice
    //conjuntoatual: se o vertice não está no seu respectivo conjunto por já ter ligação com outro vertice, conjuntoatual armazena o novo conjunto em que o vertice está;
            //caso contrário, conjuntoatual armazena o respectivo conjunto do vertice
    for(i=0; i<k; i++){
        j=0;
        marcacao=false;
        conjuntoatual='\0';
        conjunto1='\0';
        conjunto2='\0';
        if(!agm[verticesord[i*2]-65].marcacao || !agm[verticesord[(i*2)+1]-65].marcacao){   //se algum dos vertices ligados pela aresta i ainda não pertence a agm
            if(i==0){                                                                       //se primeiro vertice da primeira aresta (pai da agm)
                agm[verticesord[i*2]-65].aresta[0]=0;
                agm[verticesord[i*2]-65].predecessor='#';
            }
            if(conjuntos[verticesord[i*2]-65][0]==agm[verticesord[i*2]-65].letra && conjuntos[verticesord[(i*2)+1]-65][0]==agm[verticesord[(i*2)+1]-65].letra){
                //se os dois vertices ainda estão em seus respectivos conjuntos
                conjunto1=verticesord[i*2];
                conjunto2=verticesord[(i*2)+1];
                conjuntoatual=agm[verticesord[(i*2)+1]-65].letra;
            } else if(conjuntos[verticesord[i*2]-65][0]==agm[verticesord[i*2]-65].letra || conjuntos[verticesord[(i*2)+1]-65][0]==agm[verticesord[(i*2)+1]-65].letra){
                //se algum dos dois vertices ainda está em seu respectivo conjunto
                if(conjuntos[verticesord[i*2]-65][0]==agm[verticesord[i*2]-65].letra){      //se primeiro vertice da aresta i ainda está em seu respectivo conjunto
                    conjunto1=verticesord[i*2];
                    conjunto2=verticesord[(i*2)+1];
                } else if(conjuntos[verticesord[(i*2)+1]-65][0]==agm[verticesord[(i*2)+1]-65].letra){       //se segundo vertice da aresta i ainda está em seu respectivo conjunto
                    conjunto1=verticesord[(i*2)+1];
                    conjunto2=verticesord[i*2];
                }
                for(m=0; m<a[0].n; m++){
                    for(n=0; n<a[0].n; n++){
                        if(conjuntos[m][n]==agm[conjunto2-65].letra){
                            conjuntoatual=agm[m].letra;                 //encontra conjunto no qual o vertice que já tem ligações está
                            break;
                        }
                    }
                    if(conjuntoatual!='\0')                             //quando conjuntoatual encontrado, sai do laço
                        break;
                }
            } else{                                                     //nenhum dos dois vertices está em seu respectivo conjunto
                for(m=0; m<a[0].n; m++){
                    for(n=0; n<a[0].n; n++){
                        if(conjuntos[m][n]==agm[verticesord[i*2]-65].letra){
                            conjunto1=agm[m].letra;                     //encontra conjunto no qual o primeiro vertice da aresta i está
                            break;
                        }
                    }
                    if(conjunto1!='\0')
                        break;
                }
                for(m=0; m<a[0].n; m++){
                    for(n=0; n<a[0].n; n++){
                        if(conjuntos[m][n]==agm[verticesord[(i*2)+1]-65].letra){
                            conjunto2=agm[m].letra;                     //encontra conjunto no qual o segundo vertice da aresta i está
                            break;
                        }
                    }
                    if(conjunto2!='\0')
                        break;
                }
                if(conjunto1!='\0' && conjunto2!='\0'){                 //se ambos os conjuntos forem encontrados
                    for(m=0; m<a[0].n; m++){                            //transfere todos os vertices do conjunto no qual o primeiro vertice da aresta i está p/ o respectivo conjunto do primeiro vertice
                        conjuntos[verticesord[i*2]-65][m]=conjuntos[conjunto1-65][m]; 
                        conjuntos[conjunto1-65][m]='\0';
                    }
                    conjuntoatual=conjunto2;                            //conjuntoatual é o conjunto no qual o segundo vertice da aresta i está
                    conjunto1=agm[verticesord[i*2]-65].letra;
                    conjunto2=agm[verticesord[(i*2)+1]-65].letra;
                }
            }
            if(conjuntoatual!=conjunto1){                               //se conjuntoatual diferente de conjunto1 (conjunto destino)
                while(conjuntos[conjunto1-65][j]!='\0'){                //enquanto a posição do conjunto1 não estiver vaga
                    if(conjuntos[conjunto1-65][j]==verticesord[0]){     //se pai da agm está em alguma posição no conjunto1
                        marcacao=true;                                  //conjunto1 ja pertence a agm
                        agm[conjunto1-65].posterior=(char *)realloc(agm[conjunto1-65].posterior, ((agm[conjunto1-65].contpost)+1)*sizeof(char));
                        agm[conjunto1-65].posterior[agm[conjunto1-65].contpost++]=conjunto2;        //conjunto1 liga conjunto2 a agm
                        agm[conjunto2-65].aresta[conjunto1-65]=arestasord[i];                       //pela aresta i
                        agm[conjunto2-65].predecessor=conjunto1;
                    }
                    j++;
                }
                l=0;
                while(conjuntos[conjuntoatual-65][l]!='\0'){        //enquanto houver algum vertice no conjuntoatual
                    conjuntos[conjunto1-65][j++]=conjuntos[conjuntoatual-65][l];                    //copia p/ conjunto1 (conjunto destino)
                    conjuntos[conjunto1-65][j]='\0';
                    if(conjuntos[conjuntoatual-65][l]==verticesord[0]){                             //se pai da agm está em alguma posição no conjuntoatual
                        marcacao=true;                                                              //conjuntoatual ja pertence a agm
                        agm[conjunto2-65].posterior=(char *)realloc(agm[conjunto2-65].posterior, ((agm[conjunto2-65].contpost)+1)*sizeof(char));
                        agm[conjunto2-65].posterior[agm[conjunto2-65].contpost++]=conjunto1;        //conjunto2 (correspondente ao segundo vertice da aresta i) liga conjunto1 a agm 
                        agm[conjunto1-65].aresta[conjunto2-65]=arestasord[i];                       //pela aresta i
                        agm[conjunto1-65].predecessor=conjunto2;
                    }
                    conjuntos[conjuntoatual-65][l++]='\0';                                          //remove de conjuntoatual
                }
                if(marcacao){                                       //se pai da agm estava em algum dos conjuntos
                    for(m=j-1; m>=0; m--){
                        agm[conjuntos[conjunto1-65][m]-65].marcacao=true;                           //todos os vertices do conjunto1 (conjunto destino) ja pertencem a agm
                    }
                } else{                                             //conjunto1 ainda não pertence a agm
                    agm[conjunto1-65].posterior=(char *)realloc(agm[conjunto1-65].posterior, ((agm[conjunto1-65].contpost)+1)*sizeof(char));
                    agm[conjunto1-65].posterior[agm[conjunto1-65].contpost++]=conjunto2;            //conjunto1 se liga ao conjunto2
                    agm[conjunto2-65].aresta[conjunto1-65]=arestasord[i];                           //pela aresta i
                    agm[conjunto2-65].predecessor=conjunto1;
                }
            }
        }
    }

    vertice *finalagm;                                              //cópia final da agm p/ retorno
    finalagm=(vertice *)malloc(a[0].n*sizeof(vertice));

    for(i=0; i<a[0].n; i++){
        finalagm[i].n=a[0].n;
        finalagm[i].letra=agm[i].letra;
        finalagm[i].predecessor=agm[i].predecessor;
        if(!agm[i].marcacao){                                       //se houver vertice sem conexão com a agm
            printf("\nVertice %c nao conectado. Impossivel obter AGM!\n", agm[i].letra);
            free(arestasord);
            free(verticesord);
            free(agm);
            free(finalagm);
            return NULL;
        } else{
            finalagm[i].marcacao=true;
        }
        for(j=0; j<20; j++){
            finalagm[i].aresta[j]=0;
        }
    }

    for(i=0; i<a[0].n; i++){                                        //copia arestas de modo que agm seja não orientada
        for(j=0; j<agm[i].contpost; j++){
            finalagm[i].aresta[agm[i].posterior[j]-65]=agm[agm[i].posterior[j]-65].aresta[i];
            finalagm[agm[i].posterior[j]-65].aresta[i]=agm[agm[i].posterior[j]-65].aresta[i];
        }
    }

    free(arestasord);
    free(verticesord);
    free(agm);
    return finalagm;
}

void Insertion(unsigned int *a, char *v, int n){    //adaptação InsertionSort
    int i, j, tmp;
    char tmpv[2];
    for(i=0; i<n; i++){
        j=i-1;
        tmp=*(a+i);
        tmpv[0]=*(v+(i*2));
        tmpv[1]=*(v+(i*2)+1);
        while((j>=0) && (tmp<*(a+j))){
            *(a+(j+1))=*(a+j);
            *(v+((j+1)*2))=*(v+(j*2));
            *(v+((j+1)*2)+1)=*(v+(j*2)+1);
            j--;
        }
        *(a+(j+1))=tmp;
        *(v+((j+1)*2))=tmpv[0];
        *(v+((j+1)*2)+1)=tmpv[1];
    }
}

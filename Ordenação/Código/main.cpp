#include <iostream>

//REIMPLEMENTAR OS ALGORITMOS COM VETORES DESSA STRUCT E CONTAGEM DE INSTRUÇÕES
typedef struct strItem{
    int chave;
    //Informações (podemos adicionar mais coisa):
    int info;
}Item;



//AUXILIARES:
void troca (int* vet, int a, int b){
    int aux = vet[a];
    vet[a] = vet[b];
    vet[b] = aux;
}
//

//SELECTIONSORT
void selectionSort(int *vet, int n)
{
    int iaux, i,j;
    for(i=0;i<n-1;i++)
    {
        iaux=i;
        for(j=i+1;j<n;j++)
            if(vet[j]<vet[iaux])
                iaux=j;

        if(iaux != i)
        troca(vet,iaux,i);
    }
}
//

//BUBBLESORT
void bubbleSort(int *vet, int n){
    int i,j;
    for(i=n-1;i>=0;i--){
        for(j=0;j<i;j++){
            if(vet[j]>vet[j+1])
                troca(vet,j,j+1);
        }
    }
}
//

//INSERTIONSORT
void insertionSort(int * vet, int n){
    int i,j,aux;
    for(i =1;i<n;i++){
        aux = vet[i];
        for(j=i-1;j>=0 && vet[j]>aux;j--){
            vet[j+1] = vet[j];
        }
        vet[j+1] = aux;
    }
}
//

//MERGESORT
void intercala(int v[],int L1, int L2, int F){
    int iL1 = L1, iL2 = L2, aux = 0;
    int vAux[F-L1];
    while(iL1<L2 && iL2<F){
        if(v[iL1]<v[iL2]){
            vAux[aux] = v[iL1];
            iL1++;
        }else{
            vAux[aux] = v[iL2];
            iL2++;
        }
        aux++;
    }
    while(iL1<L2){
        vAux[aux] = v[iL1];
        aux++;
        iL1++;
    }
    while(iL2<F){
        vAux[aux] = v [iL2];
        aux++;
        iL2++;
    }

    for(aux = L1;aux<F;aux++){
        v[aux] = vAux[aux-L1];
    }
}

void mergeSort(int v[],int inicio, int fim){
    if(inicio<fim-1){
        int meio = (inicio + fim)/2 ;
        mergeSort(v,inicio,meio);
        mergeSort(v,meio,fim);
        intercala(v,inicio,meio,fim);
    }
}
//

//QUICKSORT
int particao(int* vet, int esq, int dir){
    int indPivo = esq;
    esq++;
    while(esq<dir){
        while(vet[esq]<vet[indPivo])
            esq++;
        while(vet[dir]>vet[indPivo])
            dir--;
        if(esq<dir){
            int aux = vet[esq];
            vet[esq] = vet[dir];
            vet[dir] = aux;
        }
    }
    int aux = vet[dir];
    vet[dir] = vet[indPivo];
    vet[indPivo] = aux;
    return dir;
}

void quickSort(int *vet, int esq, int dir){
    if(esq<dir){
        int j = particao(vet,esq,dir);
        quickSort(vet,esq,j-1);
        quickSort(vet,j+1,dir);
    }
}
//

//HEAPSORT
void max_heapfy(int* vet, int pos, int tam){
    int maior = pos ,esq = 2*pos+1,dir = 2*pos+2;

    if(esq<tam && vet[esq]>vet[pos])
        maior = esq;
    else
        maior = pos;

    if(dir<tam && vet[dir]>vet[maior])
        maior = dir;

    if(maior!=pos){
        troca(vet,maior,pos);
        max_heapfy(vet,maior,tam);
    }

}

void build_maxHeap(int* vet, int tam){
    int i;
    for(i=tam/2;i>=0;i--){
        max_heapfy(vet,i,tam);
    }
}

void heapSort(int *vet, int tam){
    int i;
    build_maxHeap(vet,tam);
    for(i=tam-1;i>=1;i--){
        troca(vet,0,i);
        max_heapfy(vet,0,i);
    }
}
//

int main()
{
    //Fazer geradores para os vetores.
    return 0;
}

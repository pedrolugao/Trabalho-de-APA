#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>

//REIMPLEMENTAR OS ALGORITMOS COM VETORES DESSA STRUCT E CONTAGEM DE INSTRUÇÕES
typedef struct strItem{
    int chave;
    //Informações (podemos adicionar mais coisa):
    int info;
}Item;

enum vetType {
    SORTED,
    REVERSE,
    ALMOST,
    RANDOM,
    AMOUNT_OF_TYPES = 4
};

enum sortMethod {
    SELECTION,
    BUBBLE,
    INSERTION,
    MERGE,
    QUICK,
    HEAP,
    AMOUNT_OF_METHODS = 6
};


class my_bool : public std::numpunct< char > {
protected:
    std::string do_truename() const { return "Ordenado";  }
    std::string do_falsename() const { return "Não ordenado"; }
};


//AUXILIARES:
void troca (Item* vet, int a, int b){
    Item aux = vet[a];
    vet[a] = vet[b];
    vet[b] = aux;
}

Item* gera (int amount, vetType type) {
    Item* vet = new Item[amount];
    int i;

    switch (type) {
        case SORTED:
            for (i = 0; i < amount; i++)
                vet[i].chave = i;
            break;
        case REVERSE:
            for (i = 0; i < amount; i++)
                vet[i].chave = (amount - 1) - i;
            break;
        case ALMOST:
            for (i = 0; i < amount; i++)
                vet[i].chave = i;
            troca(vet, 0, amount - 1);
            break;
        case RANDOM:
            vet = gera(amount, SORTED);
            for (i = 0; i < amount; i++)
                troca(vet, i, rand() % amount);
            break;
    }

    return vet;
}

void imprime (Item* vet, int n) {
    int i;
    for (i = 0; i < n - 1; i++)
        std::cout << vet[i].chave << ", ";
    std::cout << vet[i].chave << std::endl;
}

bool isSorted(Item* vet, int n) {
    int i;
    for (i = 1; i < n - 1; i++)
        if (vet[i].chave < vet[i-1].chave)
            return false;
    return true;
}

Item* clona(Item* vet, int n) {
    Item* vet2 = new Item[n];
    int i;
    for (i = 0; i < n; i++)
        vet2[i] = vet[i];
    return vet2;
}
//

//SELECTIONSORT
void selectionSort(Item *vet, int n)
{
    int iaux, i,j;
    for(i=0;i<n-1;i++)
    {
        iaux=i;
        for(j=i+1;j<n;j++)
            if(vet[j].chave <vet[iaux].chave)
                iaux=j;

        if(iaux != i)
        troca(vet,iaux,i);
    }
}
//

//BUBBLESORT
void bubbleSort(Item *vet, int n){
    int i,j;
    for(i=n-1;i>=0;i--){
        for(j=0;j<i;j++){
            if(vet[j].chave > vet[j+1].chave)
                troca(vet,j,j+1);
        }
    }
}
//

//INSERTIONSORT
void insertionSort(Item * vet, int n){
    int i,j;
    Item aux;
    for(i =1;i<n;i++){
        aux = vet[i];
        for(j=i-1;j>=0 && vet[j].chave > aux.chave;j--){
            vet[j+1] = vet[j];
        }
        vet[j+1] = aux;
    }
}
//

//MERGESORT
void intercala(Item v[],int L1, int L2, int F){
    int iL1 = L1, iL2 = L2, aux = 0;
    Item vAux[F-L1];
    while(iL1<L2 && iL2<F){
        if(v[iL1].chave<v[iL2].chave){
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

void mergeSort(Item v[],int inicio, int fim){ //fim = tamanho do vetor
    if(inicio<fim-1){
        int meio = (inicio + fim)/2 ;
        mergeSort(v,inicio,meio);
        mergeSort(v,meio,fim);
        intercala(v,inicio,meio,fim);
    }
}
//

//QUICKSORT
int particao(Item* vet, int esq, int dir){
    int indPivo = esq;
    esq++;
    while(esq<=dir){
        while(vet[esq].chave <vet[indPivo].chave )
            esq++;
        while(vet[dir].chave>vet[indPivo].chave)
            dir--;
        if(esq<dir){
            troca(vet,esq,dir);
        }
    }

    troca(vet,dir,indPivo);
    return dir;
}

void quickSort(Item *vet, int esq, int dir){
    if(esq<dir){
        int j = particao(vet,esq,dir);
        quickSort(vet,esq,j-1);
        quickSort(vet,j+1,dir);
    }
}
//

//HEAPSORT
void max_heapfy(Item* vet, int pos, int tam){
    int maior = pos ,esq = 2*pos+1,dir = 2*pos+2;

    if(esq<tam && vet[esq].chave>vet[pos].chave)
        maior = esq;
    else
        maior = pos;

    if(dir<tam && vet[dir].chave>vet[maior].chave)
        maior = dir;

    if(maior!=pos){
        troca(vet,maior,pos);
        max_heapfy(vet,maior,tam);
    }

}

void build_maxHeap(Item* vet, int tam){
    int i;
    for(i=tam/2;i>=0;i--){
        max_heapfy(vet,i,tam);
    }
}

void heapSort(Item *vet, int tam){
    int i;
    build_maxHeap(vet,tam);
    for(i=tam-1;i>=1;i--){
        troca(vet,0,i);
        max_heapfy(vet,0,i);
    }
}
//

//SORT
bool sortVet(Item* vet, int n, sortMethod method) {
    switch (method) {
        case SELECTION:
            selectionSort(vet, n);
            break;
        case BUBBLE:
            bubbleSort(vet, n);
            break;
        case INSERTION:
            insertionSort(vet, n);
            break;
        case MERGE:
            mergeSort(vet, 0, n);
            break;
        case QUICK:
            quickSort(vet, 0, n - 1);
            break;
        case HEAP:
            heapSort(vet, n);
            break;
    }
    return isSorted(vet, n);
}
//

int main()
{
    srand(5);
    std::cout.imbue(std::locale(std::locale(), new my_bool));
    std::cout << std::boolalpha;
    setlocale (LC_ALL, "PORTUGUESE");

    int i, j;

    int AMOUNT_OF_SIZES = 4;

    int* sizes = new int[AMOUNT_OF_SIZES];
    for (i = 0; i < AMOUNT_OF_SIZES; i++)
        sizes[i] = (int) round(pow(10, i + 1));

    Item** sortedVets = new Item*[AMOUNT_OF_SIZES];
    Item** reverseVets = new Item*[AMOUNT_OF_SIZES];
    Item** almostVets = new Item*[AMOUNT_OF_SIZES];
    Item** randomVets = new Item*[AMOUNT_OF_SIZES];

    for (i = 0; i < AMOUNT_OF_SIZES; i++) {
        sortedVets[i] = gera(sizes[i], SORTED);
        reverseVets[i] = gera(sizes[i], REVERSE);
        almostVets[i] = gera(sizes[i], ALMOST);
        randomVets[i] = gera(sizes[i], RANDOM);
    }

    sortMethod methods[AMOUNT_OF_METHODS] = {SELECTION, BUBBLE, INSERTION, MERGE, QUICK, HEAP};
    std::string methodsNames[AMOUNT_OF_METHODS] = {"Selection", "Bubble", "Insertion", "Merge", "Quick", "Heap"};

    //PARA TESTAR 1 MÉTODO COM TODOS OS TAMANHOS DE 1 TIPO DE VETOR
    sortMethod method = QUICK;

    for (i = 0; i < AMOUNT_OF_SIZES; i++) {
        Item* vet = clona(randomVets[i], sizes[i]);
        std::cout << "Tamanho do vetor: " << sizes[i] << std::endl;
        std::cout << "Tipo de vetor: Aleatório" << std::endl;
        std::cout << "Método: " << methodsNames[method] << std::endl;
        std::cout << "Resultado: " << sortVet(vet, sizes[i], method) << std::endl << std::endl;
        free(vet);
    }


    /* PARA TESTAR TODOS OS MÉTODOS COM TODOS OS TAMANHOS DE TODOS OS TIPOS DE VETOR
    for (j = 0; j < AMOUNT_OF_METHODS; j++) {
        sortMethod method = methods[j];

        for (i = 0; i < AMOUNT_OF_SIZES; i++) {
            Item* vet = clona(sortedVets[i], sizes[i]);
            std::cout << "Tamanho do vetor: " << sizes[i] << std::endl;
            std::cout << "Tipo de vetor: Ordenado" << std::endl;
            std::cout << "Método: " << methodsNames[method] << std::endl;
            std::cout << "Resultado: " << sortVet(vet, sizes[i], method) << std::endl << std::endl;
            free(vet);
        }

        for (i = 0; i < AMOUNT_OF_SIZES; i++) {
            Item* vet = clona(reverseVets[i], sizes[i]);
            std::cout << "Tamanho do vetor: " << sizes[i] << std::endl;
            std::cout << "Tipo de vetor: Inversamente Ordenado" << std::endl;
            std::cout << "Método: " << methodsNames[method] << std::endl;
            std::cout << "Resultado: " << sortVet(vet, sizes[i], method) << std::endl << std::endl;
            free(vet);
        }

        for (i = 0; i < AMOUNT_OF_SIZES; i++) {
            Item* vet = clona(almostVets[i], sizes[i]);
            std::cout << "Tamanho do vetor: " << sizes[i] << std::endl;
            std::cout << "Tipo de vetor: Quase Ordenado" << std::endl;
            std::cout << "Método: " << methodsNames[method] << std::endl;
            std::cout << "Resultado: " << sortVet(vet, sizes[i], method) << std::endl << std::endl;
            free(vet);
        }

        for (i = 0; i < AMOUNT_OF_SIZES; i++) {
            Item* vet = clona(randomVets[i], sizes[i]);
            std::cout << "Tamanho do vetor: " << sizes[i] << std::endl;
            std::cout << "Tipo de vetor: Aleatoriamente Ordenado" << std::endl;
            std::cout << "Método: " << methodsNames[method] << std::endl;
            std::cout << "Resultado: " << sortVet(vet, sizes[i], method) << std::endl << std::endl;
            free(vet);
        }
    }*/

    //LIMPANDO
    for (i = 0; i < AMOUNT_OF_SIZES; i++) {
        Item* vet1 = sortedVets[i];
        Item* vet2 = reverseVets[i];
        Item* vet3 = almostVets[i];
        Item* vet4 = randomVets[i];
        free(vet1);
        free(vet2);
        free(vet3);
        free(vet4);
    }

    free(sortedVets);
    free(reverseVets);
    free(almostVets);
    free(randomVets);
    //

    return 0;
}

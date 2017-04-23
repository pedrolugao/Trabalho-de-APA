#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<time.h>

//REIMPLEMENTAR OS ALGORITMOS COM VETORES DESSA STRUCT E CONTAGEM DE INSTRU��ES
typedef struct strItem{
    int chave;
    //Informa��es (podemos adicionar mais coisa):
    int info;
}Item;

//! Enum referente aos tipos de vetores (ordenado, inversamente ordenado,
//! quase ordenado e aleatoriamente ordenado). Usado na fun��o gera()
enum vetType {
    SORTED,
    REVERSE,
    ALMOST,
    RANDOM,
    AMOUNT_OF_TYPES = 4
};

//! Enum referente aos m�todos de sort. Usado na fun��o sortVet()
enum sortMethod {
    SELECTION,
    BUBBLE,
    INSERTION,
    MERGE,
    QUICK,
    HEAP,
    AMOUNT_OF_METHODS = 6
};

//! Classe do tipo std::numpunct que tem como objetivo sobreescrever
//! parte das strings que o std::cout imprime na tela, no caso os booleans.
//! O que essa classe faz � imprimir "Ordenado" quando true e "N�o ordenado" quando false
class my_bool : public std::numpunct< char > {
protected:
    std::string do_truename() const { return "Ordenado";  }
    std::string do_falsename() const { return std::string() + "N" + char(198) + "o Ordenado"; }
};

int contadorComparacoes;
int contadorAtribuicoes;

//AUXILIARES:
void troca (Item* vet, int a, int b){
    Item aux = vet[a];
    vet[a] = vet[b];
    vet[b] = aux;
    contadorAtribuicoes++;
}

//! Gera um vetor recebendo o tamanho desejado e o tipo, de acordo com o enum vetType
Item* gera (int amount, vetType type) {
    Item* vet = new Item[amount];
    int i;

    switch (type) {
        case SORTED: //! Vetor onde um elemento � sempre menor que o pr�ximo
            for (i = 0; i < amount; i++)
                vet[i].chave = i;
            break;
        case REVERSE: //! Vetor onde um elemento � sempre maior que o pr�ximo
            for (i = 0; i < amount; i++)
                vet[i].chave = (amount - 1) - i;
            break;
        case ALMOST: //! Vetor igual o ordenado s� que com o primeiro e o �ltimo elementos trocados
            for (i = 0; i < amount; i++)
                vet[i].chave = i;
            troca(vet, 0, amount - 1);
            break;
        case RANDOM: //! � gerado um vetor ordenado e depois v�rios elementos s�o trocados de lugar de acordo com a fun��o rand()
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
        for(j=i+1;j<n;j++){
            contadorComparacoes++;
            if(vet[j].chave <vet[iaux].chave)
                iaux=j;
        }
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
            contadorComparacoes++;
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
        contadorComparacoes++;
        for(j=i-1;j>=0 && vet[j].chave > aux.chave;j--){
            contadorComparacoes++;
            contadorAtribuicoes++;
            vet[j+1] = vet[j];
        }
        vet[j+1] = aux;
        contadorAtribuicoes++;
    }
}
//

//MERGESORT
void intercala(Item v[],int L1, int L2, int F){
    int iL1 = L1, iL2 = L2, aux = 0;
    Item vAux[F-L1];
    while(iL1<L2 && iL2<F){
        contadorComparacoes++;
        if(v[iL1].chave<v[iL2].chave){
            vAux[aux] = v[iL1];
            iL1++;
        }else{
            vAux[aux] = v[iL2];
            iL2++;
        }
        contadorAtribuicoes++;
        aux++;
    }

    while(iL1<L2){
        vAux[aux] = v[iL1];
        aux++;
        iL1++;
        contadorAtribuicoes++;
    }


    while(iL2<F){
        vAux[aux] = v [iL2];
        aux++;
        iL2++;
        contadorAtribuicoes++;

    }

    for(aux = L1;aux<F;aux++){
        contadorAtribuicoes++;
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
        while(vet[esq].chave <vet[indPivo].chave ){
            contadorComparacoes++;
            esq++;
        }
        while(vet[dir].chave>vet[indPivo].chave){
            contadorComparacoes++;
            dir--;
        }
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
    contadorComparacoes++;
    if(esq<tam && vet[esq].chave>vet[pos].chave)
        maior = esq;
    else
        maior = pos;

    if(dir<tam && vet[dir].chave>vet[maior].chave){
        maior = dir;
    }

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
//! Ordena um vetor recebendo o vetor, o tamanho e qual m�todo deve ser usado, de acordo como enum sortMethod
//! Retorna um bool que indica se o vetor resultado est� ordenado ou n�o
bool sortVet(Item* vet, int n, sortMethod method) {
    clock_t inicio, fim;
    contadorComparacoes = 0;
    contadorAtribuicoes = 0;

    inicio = clock();


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

    fim = clock();
    int tempo = fim - inicio;
    tempo = tempo;

    std::cout << "Tempo consumido (em clocks): "<< tempo << std::endl;

    std::string stringNumComparacoes = std::string() + "N" + char(163) + "mero de compara" + char(135) + char(228) + "es: ";
    std::cout << stringNumComparacoes << contadorComparacoes << std::endl;

    std::string stringNumAtribuicoes = std::string() + "N" + char(163) + "mero de atribui" + char(135) + char(228) + "es: ";
    std::cout << stringNumAtribuicoes << contadorAtribuicoes << std::endl;

    return isSorted(vet, n);
}
//

int main()
{
    srand(5); //! Inicia o gerador de n�meros aleat�rios com seed 5, para que os n�meros gerados sejam sempre iguais
    std::cout.imbue(std::locale(std::locale(), new my_bool)); //! Define que a classe criada no in�cio do arquivo seja usada
    std::cout << std::boolalpha; //! Define que booleans devem ser imprimidos como texto ao inv�s de 0 ou 1

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

    //PARA TESTAR 1 M�TODO COM TODOS OS TAMANHOS DE 1 TIPO DE VETOR
    /*
    sortMethod method = INSERTION;

    for (i = 0; i < AMOUNT_OF_SIZES; i++) {
        Item* vet = clona(randomVets[i], sizes[i]);
        std::cout << "Tamanho do vetor: " << sizes[i] << std::endl;
        std::cout << "Tipo de vetor: Aleat" << char(162) << "rio" << std::endl;
        std::cout << "M" << char(130) << "todo: " << methodsNames[method] << std::endl;
        std::cout << "Resultado: " << sortVet(vet, sizes[i], method) << std::endl << std::endl;
        free(vet);
    }
    */

    // PARA TESTAR TODOS OS M�TODOS COM TODOS OS TAMANHOS DE TODOS OS TIPOS DE VETOR
    for (j = 0; j < AMOUNT_OF_METHODS; j++) {
        sortMethod method = methods[j];

        for (i = 0; i < AMOUNT_OF_SIZES; i++) {
            Item* vet = clona(sortedVets[i], sizes[i]);
            std::cout << "Tamanho do vetor: " << sizes[i] << std::endl;
            std::cout << "Tipo de vetor: Ordenado" << std::endl;
            std::cout << "M�todo: " << methodsNames[method] << std::endl;
            std::cout << "Resultado: " << sortVet(vet, sizes[i], method) << std::endl << std::endl;
            free(vet);
        }

        for (i = 0; i < AMOUNT_OF_SIZES; i++) {
            Item* vet = clona(reverseVets[i], sizes[i]);
            std::cout << "Tamanho do vetor: " << sizes[i] << std::endl;
            std::cout << "Tipo de vetor: Inversamente Ordenado" << std::endl;
            std::cout << "M�todo: " << methodsNames[method] << std::endl;
            std::cout << "Resultado: " << sortVet(vet, sizes[i], method) << std::endl << std::endl;
            free(vet);
        }

        for (i = 0; i < AMOUNT_OF_SIZES; i++) {
            Item* vet = clona(almostVets[i], sizes[i]);
            std::cout << "Tamanho do vetor: " << sizes[i] << std::endl;
            std::cout << "Tipo de vetor: Quase Ordenado" << std::endl;
            std::cout << "M�todo: " << methodsNames[method] << std::endl;
            std::cout << "Resultado: " << sortVet(vet, sizes[i], method) << std::endl << std::endl;
            free(vet);
        }

        for (i = 0; i < AMOUNT_OF_SIZES; i++) {
            Item* vet = clona(randomVets[i], sizes[i]);
            std::cout << "Tamanho do vetor: " << sizes[i] << std::endl;
            std::cout << "Tipo de vetor: Aleatoriamente Ordenado" << std::endl;
            std::cout << "M�todo: " << methodsNames[method] << std::endl;
            std::cout << "Resultado: " << sortVet(vet, sizes[i], method) << std::endl << std::endl;
            free(vet);
        }
    }

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

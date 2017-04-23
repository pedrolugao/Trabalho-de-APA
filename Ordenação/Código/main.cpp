#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<time.h>

//!Utilizamos essa biblioteca para fazer os testes de tempo
//!Todos os códigos relativos a isso estarão comentados pois não funcionam em linux
//#include<windows.h>

typedef struct strItem{
    int chave;
    int info;
}Item;

//! Enum referente aos tipos de vetores (ordenado, inversamente ordenado,
//! quase ordenado e aleatoriamente ordenado). Usado na função gera()
enum vetType {
    SORTED,
    REVERSE,
    ALMOST,
    RANDOM,
    AMOUNT_OF_TYPES = 4
};

//! Enum referente aos métodos de sort. Usado na função sortVet()
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
//! O que essa classe faz é imprimir "Ordenado" quando true e "Não ordenado" quando false
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
        case SORTED: //! Vetor onde um elemento é sempre menor que o próximo
            for (i = 0; i < amount; i++)
                vet[i].chave = i;
            break;
        case REVERSE: //! Vetor onde um elemento é sempre maior que o próximo
            for (i = 0; i < amount; i++)
                vet[i].chave = (amount - 1) - i;
            break;
        case ALMOST: //! Vetor igual o ordenado só que com o primeiro e o último elementos trocados
            for (i = 0; i < amount; i++)
                vet[i].chave = i;
            troca(vet, 0, amount - 1);
            break;
        case RANDOM: //! É gerado um vetor ordenado e depois vários elementos são trocados de lugar de acordo com a função rand()
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

//!SELECTIONSORT
//A função recebe um vetor e seu tamanho
//A cada iteração externa, busca o maior elemento com a iteração interna e coloca no fim do vetor
//Ao fim da execução, o vetor estar ordenado
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

//!BUBBLESORT
//A função recebe um vetor e seu tamanho
//A cada iteração interna, coloca o maior elemento de duas posições seguidas na maior posição entre eles.
//A cada iteração externa, coloca o maior elemento do vetor na última posição
//Ao fim de execução, o vetor estará ordenado
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

//!INSERTIONSORT
//A função recebe um vetor e seu tamanho
//A cada iteração interna, encontra a posição de um elemento na parte ordenada do vetor (todos os elementos com posição menor que ele)
//A cada iteração externa, aumenta em 1 ao tamanho da parte ordenada do vetor
//Ao fim da execução, todo o vetor estará ordenado
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

//! MERGESORT

//Intercala: recebe um vetor, a posição de inicio de duas partições do vetor, e o seu tamanho
//A função considera os elementos de L1 a L2 como um vetor, e os elementos de L2 a F como outro.
//Assume-se que ambos os vetores estejam ordenados, e com isso a função os une de maneira ordenada em um novo vetor
//Por fim, copia os elementos em ordem substituindo os elementos no vetor original
//Ao fim de execução, os elementos de L1 a F do vetor estarão ordenados
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

//MergeSort: Função principal, recebe o vetor, a posição do primeiro elemento, e o seu tamanho.
//Divide recursivamente os vetores em 2 até atingir tamanho unitário (um elemento = vetor ordenado), e a partir daí os une com a função de intercala;
//Ao fim de execução, o vetor estará ordenado
void mergeSort(Item v[],int inicio, int fim){ //fim = tamanho do vetor
    if(inicio<fim-1){
        int meio = (inicio + fim)/2 ;
        mergeSort(v,inicio,meio);
        mergeSort(v,meio,fim);
        intercala(v,inicio,meio,fim);
    }
}
//

//! QUICKSORT

//Particao: recebe um vetor, o indice inicial e o final da parte do vetor a ser considerada
//Seleciona o primeiro elemento à esquerda como pivô, e coloca os elementos menores que ele à sua esquerda, e os maiores à direita.
//Retorna a posição final do pivô
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

//QuickSort: função principal, recebe um vetor, a primeira e a última posição do vetor.
//Executa a partição com todos os elementos, mas rodando recursivamente em cada uma das partes dividida pelo pivô em cada execução
//Ao fim da execução, o vetor estará ordenado
void quickSort(Item *vet, int esq, int dir){
    if(esq<dir){
        int j = particao(vet,esq,dir);
        quickSort(vet,esq,j-1);
        quickSort(vet,j+1,dir);
    }
}
//

//! HEAPSORT

//Max_heapfy : recebe uma heap, uma posição de um elemento, e seu tamanho
//Com isso, confere se o elemento na posição satisfaz a propriedade de max-heap (se seus filhos são menores)
//Caso contrário, troca o elemento de lugar com o maior filho e reexecuta o código para ver se o elemento agora segue à propriedade de max-heap
//Ao fim da execução, o elemento estará seguindo a propriedade de max-heap
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

//Build_maxHeap : recebe uma heap e seu tamanho
//Executa a função max_heapfy em todos os elementos que não são folha da heap (elementos até a metade do vetor)
//Ao fim da execução, todos os elementos estarão seguindo a propriedade de max-heap, e a heap será uma max-heap
void build_maxHeap(Item* vet, int tam){
    int i;
    for(i=tam/2;i>=0;i--){
        max_heapfy(vet,i,tam);
    }
}

//HeapSort: função principal, recebe um vetor (heap) e seu tamanho
//Consiste em pegar a raiz de uma max-heap, trocar com o ultimo elemento, e construir uma nova max-heap desconsiderando a raiz tirada;
//A execução para quando não há mais elementos para criar uma max-heap
//Ao fim da execução, o vetor estará ordenado
void heapSort(Item *vet, int tam){
    int i;
    build_maxHeap(vet,tam);
    for(i=tam-1;i>=1;i--){
        troca(vet,0,i);
        max_heapfy(vet,0,i);
    }
}
//

//! SORT
//Ordena um vetor recebendo o vetor, o tamanho e qual método deve ser usado, de acordo como enum sortMethod
//Retorna um bool que indica se o vetor resultado está ordenado ou não
bool sortVet(Item* vet, int n, sortMethod method) {
    clock_t inicio, fim;
    contadorComparacoes = 0;
    contadorAtribuicoes = 0;

    //!LARGE_INTEGER start, eNd, frequency;
    //!QueryPerformanceCounter(&start);



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

    //!QueryPerformanceCounter(&eNd);
    //!double tempo =  (double)(eNd.QuadPart - start.QuadPart)

    //!std::cout << "Tempo consumido (em clocks): "<< tempo << std::endl;

    std::string stringNumComparacoes = std::string() + "N" + char(163) + "mero de compara" + char(135) + char(228) + "es: ";
    std::cout << stringNumComparacoes << contadorComparacoes << std::endl;

    std::string stringNumAtribuicoes = std::string() + "N" + char(163) + "mero de atribui" + char(135) + char(228) + "es: ";
    std::cout << stringNumAtribuicoes << contadorAtribuicoes << std::endl;

    return isSorted(vet, n);
}
//

int main()
{
    srand(5); //! Inicia o gerador de números aleatórios com seed 5, para que os números gerados sejam sempre iguais
    std::cout.imbue(std::locale(std::locale(), new my_bool)); //! Define que a classe criada no início do arquivo seja usada
    std::cout << std::boolalpha; //! Define que booleans devem ser imprimidos como texto ao invés de 0 ou 1

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



    // PARA TESTAR TODOS OS MÉTODOS COM TODOS OS TAMANHOS DE TODOS OS TIPOS DE VETOR
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

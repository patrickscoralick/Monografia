#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para a função tolower
#include <time.h>
#include "lista.h"

// Declarações de funções
void    insertionSort(Livro** array, int tamanho, int criterio);
void    bucketSort(Livro** array, int tamanho, int criterio);
void    mergeSort(Livro** array, int inicio, int fim, int criterio);
void    merge(Livro** array, int inicio, int meio, int fim, int criterio);
Livro*  GerarLivrosAleatorios(int quantidade);

typedef struct livro{
    int     cod;
    char    titulo[50];
    int dia, mes, ano;
    struct livro* prox;
} Livro;

int     tamanhoLista(Livro* lista){
    int tamanho = 0;
    while(lista != NULL){
        tamanho++;
        lista = lista->prox;
    }
    return tamanho;
}

void    listaParaArray(Livro* lista, Livro** array){
    int i = 0;
    while(lista != NULL){
        array[i++] = lista;
        lista = lista->prox;
    }
}

Livro*    arrayParaLista(Livro** array, int tamanho){
    Livro* novaLista = NULL;
    for(int i = tamanho - 1; i >= 0; i--){
        array[i]->prox = novaLista;
        novaLista = array[i];
    }
    return novaLista;
}

Livro*  GerarLivrosAleatorios(int quantidade){
    Livro* lista = NULL;
    char tituloBase[] = "Livro ";
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    for (int i = 0; i < quantidade; i++) {
        char titulo[50];
        sprintf(titulo, "%s%d", tituloBase, i + 1); // Cria um título fictício
        int dia = rand() % 31 + 1; // Dia entre 1 e 31
        int mes = rand() % 12 + 1; // Mês entre 1 e 12
        int ano = 2000 + rand() % 24; // Ano entre 2000 e 2024
        lista = InsereLivro(lista, i + 1, titulo, dia, mes, ano);
    }
    return lista;
}

Livro* OrdenaEstante(Livro* lista, int criterio, int algoritmo) {
    int tamanho = tamanhoLista(lista);
    Livro** array = (Livro**)malloc(tamanho * sizeof(Livro*));

    if (array == NULL) {
        printf("Erro ao alocar memória para ordenação!\n");
        return lista;
    }

    listaParaArray(lista, array);

    switch (algoritmo) {
        case 1: // Insertion Sort
            insertionSort(array, tamanho, criterio);
            break;
        case 2: // Bucket Sort
            bucketSort(array, tamanho, criterio);
            break;
        case 3: // Merge Sort
            mergeSort(array, 0, tamanho - 1, criterio);
            break;
        default:
            printf("Algoritmo inválido!\n");
            free(array);
            return lista;
    }

    Livro* novaLista = arrayParaLista(array, tamanho);
    free(array);
    return novaLista;
}

void insertionSort(Livro** array, int tamanho, int criterio) {
    for (int i = 1; i < tamanho; i++) {
        Livro* chave = array[i];
        int j = i - 1;

        while (j >= 0 && (
            (criterio == 1 && strcmp(array[j]->titulo, chave->titulo) > 0) || 
            (criterio == 2 && (
                (array[j]->ano > chave->ano) || 
                (array[j]->ano == chave->ano && array[j]->mes > chave->mes) || 
                (array[j]->ano == chave->ano && array[j]->mes == chave->mes && array[j]->dia > chave->dia)
            ))
        )) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = chave;
    }
}

void bucketSort(Livro** array, int tamanho, int criterio) {
    int i, j, k;
    const int NUM_BUCKETS = 26; // 26 letras do alfabeto para títulos
    Livro* buckets[NUM_BUCKETS];

    // Inicializa os baldes
    for (i = 0; i < NUM_BUCKETS; i++) {
        buckets[i] = NULL;
    }

    // Distribui os elementos nos baldes
    for (i = 0; i < tamanho; i++) {
        int bucketIndex;
        if (criterio == 2) { // Critério de data
            bucketIndex = array[i]->mes - 1; // Índice do balde (0 a 11)
        } else { // Critério de título
            char primeiraLetra = tolower(array[i]->titulo[0]);
            bucketIndex = (primeiraLetra >= 'a' && primeiraLetra <= 'z') ? (primeiraLetra - 'a') : 0;
        }
        Livro* novo = array[i];
        novo->prox = buckets[bucketIndex];
        buckets[bucketIndex] = novo;
    }

    // Ordena cada balde e junta os resultados
    k = 0;
    for (i = 0; i < NUM_BUCKETS; i++) {
        if (buckets[i] != NULL) {
            Livro* auxArray[tamanho];
            int bucketSize = 0;

            Livro* current = buckets[i];
            while (current != NULL) {
                auxArray[bucketSize++] = current;
                current = current->prox;
            }

            // Ordena o balde individualmente
            insertionSort(auxArray, bucketSize, criterio);

            // Adiciona os elementos ordenados ao array principal
            for (j = 0; j < bucketSize; j++) {
                array[k++] = auxArray[j];
            }
        }
    }
}

void merge(Livro** array, int inicio, int meio, int fim, int criterio) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    Livro* L[n1], *R[n2];

    for (int i = 0; i < n1; i++) L[i] = array[inicio + i];
    for (int j = 0; j < n2; j++) R[j] = array[meio + 1 + j];

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if ((criterio == 1 && strcmp(L[i]->titulo, R[j]->titulo) <= 0) ||
            (criterio == 2 && (
                L[i]->ano < R[j]->ano || 
                (L[i]->ano == R[j]->ano && L[i]->mes < R[j]->mes) || 
                (L[i]->ano == R[j]->ano && L[i]->mes == R[j]->mes && L[i]->dia <= R[j]->dia)
            ))) {
            array[k++] = L[i++];
        } else {
            array[k++] = R[j++];
        }
    }

    while (i < n1) array[k++] = L[i++];
    while (j < n2) array[k++] = R[j++];
}

void mergeSort(Livro** array, int inicio, int fim, int criterio) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        mergeSort(array, inicio, meio, criterio);
        mergeSort(array, meio + 1, fim, criterio);
        merge(array, inicio, meio, fim, criterio);
    }
}

Livro*  Inicializa(void){
    return NULL;
}

Livro*  InsereLivro(Livro* lista, int cod, char* titulo, int dia, int mes, int ano){
    Livro* novo = (Livro*) malloc(sizeof(Livro));
    if (novo == NULL){
        printf("Erro ao alocar memória! \n");
        exit(1);
    }
    novo->cod = cod;
    strcpy(novo->titulo, titulo);
    novo->dia = dia;
    novo->mes = mes;
    novo->ano = ano;
    novo->prox = lista;
    return novo;
}

void    ImprimeLivros(Livro* lista) {
    Livro* p = lista;
    printf(" __________________________________________________________________________ \n");
    printf("|                               ESTANTE VIRTUAL                            |\n");
    printf("|--------------------------------------------------------------------------| \n");
    while (p != NULL){
        printf("| Codigo: %d | Titulo: %s | Data de Publicacao: %02d/%02d/%04d |\n", p->cod, 
        p-> titulo, p->dia, p->mes, p->ano);
        p = p->prox;
        printf("-------------------------------------------------------------------------- \n");
    }
}

void    AtualizaLivro(Livro* lista, int cod){
    Livro* p = lista;
    while(p != NULL){
        if (p->cod == cod){
            printf("Livro encontrado! Digite os novos dados.\n");
            printf("Digite o novo titulo: ");
            scanf(" %[^\n]", p->titulo);
            printf("Digite a nova data de publicacao (DD MM AAAA): ");
            scanf("%d %d %d", &p->dia, &p->mes, &p->ano);
            printf("Livro atualizado com sucesso!\n");
            return;
        }
        p = p->prox;
    }
    printf("Livro com codigo %d nao encontrado. \n", cod);
}

Livro* ExcluiLivro(Livro* lista, int cod){
    Livro* anterior = NULL;
    Livro* atual = lista;

    while(atual != NULL){
        if (atual->cod == cod){
            if (anterior == NULL){
                lista = atual->prox; //Primeiro nó
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Livro com codigo %d removido com sucesso! \n", cod);
            return lista;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Livro com codigo %d nao encontrado. \n", cod);
    return lista;
}
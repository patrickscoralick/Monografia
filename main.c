#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lista.h"

void    IniciaMenu(Livro** lista);
void    EscolhaMenu(Livro** lista);
void    CadastraLivro(Livro** lista);
void    AtualizaLivroMenu(Livro* lista);
void    ExcluiLivroMenu(Livro** lista);
void    OrdenaEstanteMenu(Livro** lista);
void    ExibirResumoAlgoritmo(int algoritmo);
void    DesempenhoTeste();

void    FechaPrograma(){
    printf("!!! ENCERRANDO O PROGRAMA !!! \n");
    exit(0);
}

void DesempenhoTeste() {
    int quantidade, criterio;
    printf("Digite a quantidade de livros para simular: ");
    scanf("%d", &quantidade);

    printf("Escolha o criterio de ordenacao:\n");
    printf("[1] Titulo (Ordem Alfabetica)\n");
    printf("[2] Data de Publicacao (Ordem Cronologica)\n");
    scanf("%d", &criterio);

    // Gerar livros aleatórios
    Livro* listaOriginal = GerarLivrosAleatorios(quantidade);

    // Conversão para array
    int tamanho = tamanhoLista(listaOriginal);
    Livro** array = (Livro**)malloc(tamanho * sizeof(Livro*));
    listaParaArray(listaOriginal, array);

    // Teste dos algoritmos
    clock_t inicio, fim;
    double tempoInsertion, tempoBucket, tempoMerge;

    // Insertion Sort
    Livro** copiaArray = (Livro**)malloc(tamanho * sizeof(Livro*));
    memcpy(copiaArray, array, tamanho * sizeof(Livro*));
    inicio = clock();
    insertionSort(copiaArray, tamanho, criterio);
    fim = clock();
    tempoInsertion = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // Bucket Sort
    memcpy(copiaArray, array, tamanho * sizeof(Livro*));
    inicio = clock();
    bucketSort(copiaArray, tamanho, criterio);
    fim = clock();
    tempoBucket = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // Merge Sort
    memcpy(copiaArray, array, tamanho * sizeof(Livro*));
    inicio = clock();
    mergeSort(copiaArray, 0, tamanho - 1, criterio);
    fim = clock();
    tempoMerge = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // Exibir resultados
    printf("\nResultados do Teste de Desempenho:\n");
    printf("-------------------------------------------------------------\n");
    printf("| Algoritmo         | Tempo de Execucao (s)                 |\n");
    printf("-------------------------------------------------------------\n");
    printf("| Insertion Sort    | %f                                   |\n", tempoInsertion);
    printf("| Bucket Sort       | %f                                   |\n", tempoBucket);
    printf("| Merge Sort        | %f                                   |\n", tempoMerge);
    printf("-------------------------------------------------------------\n");

    // Limpeza de memória
    free(array);
    free(copiaArray);
}

void    ExibirResumoAlgoritmo(int algoritmo){
    printf("\nResumo do algoritmo escolhido:\n");
    switch (algoritmo) {
        case 1: // Insertion Sort
            printf("- Insertion Sort: Imagine pegar um livro de cada vez e coloca-lo na posicao correta em uma pilha ja ordenada.\n");
            break;
        case 2: // Bucket Sort
            printf("- Bucket Sort: Imagine dividir os livros em varias categorias (baldes), organiza-los individualmente e depois junta-los novamente.\n");
            break;
        case 3: // Merge Sort
            printf("- Merge Sort: Imagine dividir os livros em pequenos grupos, ordenar cada grupo e depois combinar os grupos ordenados.\n");
            break;
        default:
            printf("- Algoritmo inválido para resumo.\n");
    }    
}

void    OrdenaEstanteMenu(Livro** lista){
     int criterio, algoritmo;

    printf("Escolha o criterio de ordenacao:\n");
    printf("[1] Titulo (Ordem Alfabetica)\n");
    printf("[2] Data de Publicacao (Ordem Cronologica)\n");
    scanf("%d", &criterio);

    printf("Escolha o algoritmo de ordenacao:\n");
    printf("[1] Insertion Sort\n");
    printf("[2] Bucket Sort\n");
    printf("[3] Merge Sort\n");
    scanf("%d", &algoritmo);

    *lista = OrdenaEstante(*lista, criterio, algoritmo);
    printf("Estante ordenada com sucesso!\n");

    ExibirResumoAlgoritmo(algoritmo);
}

void CadastraLivro(Livro** lista) {
    int cod, dia, mes, ano;
    char titulo[50];

    while (1) {
        printf("Digite o codigo do livro: ");
        if (scanf("%d", &cod) == 1) { // Verifica se a entrada é um número inteiro
            break;
        } else {
            printf("Entrada invalida! Digite um numero inteiro.\n");
        }
    }
    printf("Digite o titulo do livro: ");
    scanf(" %[^\n]", titulo);

    printf("Digite o dia da publicacao (DD): ");
    scanf("%d", &dia);

    printf("Digite o mes da publicacao (MM): ");
    scanf("%d", &mes);

    printf("Digite o ano da publicacao (AAAA): ");
    scanf("%d", &ano);

    *lista = InsereLivro(*lista, cod, titulo, dia, mes, ano);
    printf("Livro cadastrado com sucesso!\n");
}

void    AtualizaLivroMenu(Livro* lista){
    int cod;
    printf("Digite o codigo do livro que deseja atualizar: ");
    scanf("%d", &cod);
    AtualizaLivro(lista, cod);
}

void    ExcluiLivroMenu(Livro** lista){
    int cod;
    printf("Digite o codigo do livro que deseja excluir: ");
    scanf("%d", &cod);
    *lista = ExcluiLivro(*lista, cod);
}

void    EscolhaMenu(Livro** lista){
    int escolhaMenu;
    do {
        printf("* ######## MENU ######## *\n");
        printf("*                        *\n");
        printf("*[1] Cadastrar Livro     *\n");
        printf("*[2] Verificar Estante   *\n");
        printf("*[3] Atualizar Livro     *\n");
        printf("*[4] Excluir Livro       *\n");
        printf("*[5] Ordenar Estante     *\n");
        printf("*[6] Desempenho (Teste)  *\n");
        printf("*[9] Fechar o programa!  *\n");
        printf("*                        *\n");
        printf(" ######################## \n");
        printf("\n");
        printf("Escolha a atividade a ser realizada: ");
        scanf("%d", &escolhaMenu);
        switch (escolhaMenu) {
            case 1 :
            CadastraLivro(lista);
            break;

            case 2 :
            ImprimeLivros(*lista);
            break;

            case 3 :
            AtualizaLivroMenu(*lista);
            break;

            case 4 :
            ExcluiLivroMenu(lista);
            break;

            case 5 :
            OrdenaEstanteMenu(lista);
            break;

            case 6 :
            DesempenhoTeste();
            break;
            
            case 9 :
            FechaPrograma();
            break;

            default :
            printf("Valor invalido! Digite um numero correspondente!\n");
        }
    }  while (escolhaMenu != 9);
}

void    IniciaMenu(Livro** lista){
    printf(" ------------------------ \n");
    printf("|                        |\n");
    printf("|  BIBLIOTECA DO PATRICK |\n");
    printf("|                        |\n");
    printf(" ------------------------ \n");
    printf("\n");
    EscolhaMenu(lista);
}

int main(){
    Livro* lista = Inicializa(); //Inicializa a lista de livros
    IniciaMenu(&lista); //Inicia o menu principal
    return 0;
}
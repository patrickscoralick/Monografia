#ifndef LISTA_H
#define LISTA_H

typedef struct livro Livro;

Livro*      Inicializa(void);
Livro*      InsereLivro(Livro* livro, int cod, char* titulo, int dia, int mes, int ano);
void        ImprimeLivros(Livro* lista);
void        AtualizaLivro(Livro* lista, int cod);
Livro*      ExcluiLivro(Livro* lista, int cod);
Livro*      OrdenaEstante(Livro* lista, int criterio, int algoritmo);
int tamanhoLista(Livro* lista);
void listaParaArray(Livro* lista, Livro** array);
Livro* GerarLivrosAleatorios(int quantidade);
void insertionSort(Livro** array, int tamanho, int criterio);
void bucketSort(Livro** array, int tamanho, int criterio);
void mergeSort(Livro** array, int inicio, int fim, int criterio);

#endif
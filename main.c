#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define M 10
#define N 10

int conjuntos[M][N] = {0};
int cont = 0;

bool verificaValor(int conjunto[], int tam, int valor) {
  for (int i = 0; i < tam; i++) {
    if (conjunto[i] == valor) {
      return true;
    }
  }
  return false;
}

void criarConjunto() {
  if (cont < M) {
    cont++;
    printf("O conjunto foi criado com sucesso!\n");
  } else {
    printf("O limite máximo de conjuntos atingido!\n");
  }
}

void inserirValor() {
  int proxIndice, valor, j, indice;
  printf("Informe o índice do conjunto (0 a %d): ", cont - 1);
  scanf("%d", &indice);
  if (indice > cont - 1) {
    printf("ERRO: O conjunto %d não foi criado! \n", indice);
  } else {
    for (j = 0; j < N; j++) {
      if (conjuntos[indice][j] == 0) {
        proxIndice = j;
        break;
      }
    }if(proxIndice<N){
      printf("Informe os valores a serem inseridos no conjunto (0 para sair):\n");
    }
    while (proxIndice < N) {
      scanf("%d", &valor);
      if (valor == 0) {
        break;
      } else if (proxIndice >= N) {
        break;
      } else {
        int valorRepetido = 0;
        for (j = 0; j < proxIndice; j++) {
          if (conjuntos[indice][j] == valor) {
            valorRepetido = 1;
            break;
          }
        }
        if (valorRepetido) {
          printf("ERRO: O valor já está inserido no conjunto. Informe um valor "
                 "diferente.\n");
        } else {
          conjuntos[indice][proxIndice] = valor;
          proxIndice++;
        }
      }
    }
    if (proxIndice >= N+1) {
      printf("ERRO:Não é possível inserir mais valores no conjunto. O "
             "limite máximo de valores no conjunto foi alcançado!\n");
    } else {
      printf("Os valores foram inseridos no conjunto %d.\n", indice);
    }
  }
}

void removerConjunto() {
  int indice, i;
  printf("Informe o índice do conjunto que deseja remover (0 a %d): ",
         cont - 1);
  scanf("%d", &indice);
  if (indice >= 0 && indice < cont) {
    cont--;
    for (i = indice; i < cont; i++) {
      int k;
      for (k = 0; k < N; k++) {
        conjuntos[i][k] = conjuntos[i + 1][k];
      }
    }
    for (i = 0; i < N; i++) {
      conjuntos[cont][i] = 0;
    }
    printf("Conjunto removido com sucesso.\n");
  } else {
    printf("ERRO: O conjunto %d não foi encontrado!\n", indice);
  }
}

void uniaoConjuntos() {
  if (cont == N) {
    printf("Não é possível criar um novo conjunto: limite máximo de conjuntos "
           "atingido!\n");
    return;
  }
  int indiceConjunto1, indiceConjunto2;
  printf("Informe o índice do primeiro conjunto a ser unido (0 a %d): ",
         cont - 1);
  scanf("%d", &indiceConjunto1);
  printf("Informe o índice do segundo conjunto a ser unido (0 a %d): ",
         cont - 1);
  scanf("%d", &indiceConjunto2);
  if (indiceConjunto1 < 0 || indiceConjunto1 >= cont || indiceConjunto2 < 0 ||
      indiceConjunto2 >= cont) {
    printf("ERRO: Os indíces dos conjuntos são inválidos\n");
    return;
  }
  int conjUniao[M];
  int tamanhoConjUniao = 0;
  for (int i = 0; i < M; i++) {
    if (conjuntos[indiceConjunto1][i] != 0) {
      conjUniao[tamanhoConjUniao] = conjuntos[indiceConjunto1][i];
      tamanhoConjUniao++;
    }
  }
  for (int i = 0; i < M; i++) {
    if (conjuntos[indiceConjunto2][i] != 0) {
      int elemento = conjuntos[indiceConjunto2][i];
      int jaExiste = 0;
      for (int j = 0; j < tamanhoConjUniao; j++) {
        if (conjUniao[j] == elemento) {
          jaExiste = 1;
          break;
        }
      }
      if (!jaExiste) {
        if (tamanhoConjUniao >= M) {
          printf("Erro: A união ultrapassou o limite de elementos!\n");
          return;
        }
        conjUniao[tamanhoConjUniao] = elemento;
        tamanhoConjUniao++;
      }
    }
  }

  for (int i = 0; i < tamanhoConjUniao; i++) {
    conjuntos[cont][i] = conjUniao[i];
  }
  cont++;
  printf("Conjunto união criado!\n");
}

void interseccaoConjuntos() {
  if (cont == M) {
    printf("ERRO: Não é possível realizar a intersecção de conjuntos. O limite "
           "máximo de conjuntos foi atingido!\n");
    return;
  }
  int indice1, indice2, indice3;
  printf("Informe o índice do primeiro conjunto (0 a %d): ", cont - 1);
  scanf("%d", &indice1);
  printf("Informe o índice do segundo conjunto (0 a %d): ", cont - 1);
  scanf("%d", &indice2);
  if (indice1 >= 0 && indice1 < cont && indice2 >= 0 && indice2 < cont) {
    indice3 = cont;
    cont++;
    for (int i = 0; i < N; i++) {
      int elemento = conjuntos[indice1][i];
      int presente = 0;
      for (int j = 0; j < N; j++) {
        if (elemento == conjuntos[indice2][j]) {
          presente = 1;
          break;
        }
      }
      if (presente) {
        conjuntos[indice3][i] = elemento;
      }
    }
    printf("A intersecção entre os conjuntos %d e %d criada com sucesso!\n", indice1,
           indice2);
  } else {
    printf("ERRO: Os indíces dos conjuntos são inválidos\n");
  }
}

void imprimirConjunto() {
  int i, j, indice;

  printf("Informe o índice do conjunto (0 a %d): ", cont - 1);
  scanf("%d", &indice);

  if (indice >= 0 && indice < cont) {
    printf("Conjunto %d: { ", indice);

    for (i = 0; i < N; i++) {
      if (conjuntos[indice][i] != 0) {
        printf("%d ", conjuntos[indice][i]);
      }
    }

    printf("}\n");
  } else {
    printf("ERRO: O conjunto %d não foi encontrado!\n", indice);
  }
}

void imprimirConjuntos() {
  if (cont != 0) {
    printf("Conjuntos:\n");
    for (int i = 0; i < cont; i++) {
      printf("Conjunto %d: { ", i);
      for (int j = 0; j < N; j++) {
        if (conjuntos[i][j] != 0) {
          printf("%d ", conjuntos[i][j]);
        }
      }
      printf("}\n");
    }
  } else {
    printf("Não há nenhum conjunto criado.\n");
  }
}

void buscarValor() {
  int valor, i, j, resultado = 0, aux = 0;
  printf("Informe o valor a ser procurado: ");
  scanf("%d", &valor);

  for (i = 0; i < cont; i++) {
    for (j = 0; j < N; j++) {
      if (conjuntos[i][j] == valor) {
        if (aux == 0) {
          aux++;
          printf("Conjuntos que contêm o valor %d \n", valor);
        }
        printf("Conjunto %d \n", i);
        resultado = 1;
      }
    }
  }

  if (!resultado) {
    printf("O valor não encontrado em nenhum dos conjunto!\n");
  }
}

int main() {
  int option;
  do {
    printf("\nMenu:\n");
    printf("1 - Criar um novo conjunto vazio\n");
    printf("2 - Inserir dados em um conjunto\n");
    printf("3 - Remover um conjunto\n");
    printf("4 - Fazer a uniao entre dois conjuntos\n");
    printf("5 - Fazer a intersecção entre dois conjuntos\n");
    printf("6 - Imprimir um conjunto\n");
    printf("7 - Imprimir todos os conjuntos\n");
    printf("8 - Fazer busca por um valor\n");
    printf("9 - Sair do programa\n");
    printf("Digite uma opção: ");
    scanf("%d", &option);
    switch (option) {
    case 1:
      criarConjunto();
      break;
    case 2:
      inserirValor();
      break;
    case 3:
      removerConjunto();
      break;
    case 4:
      uniaoConjuntos();
      break;
    case 5:
      interseccaoConjuntos();
      break;
    case 6:
      imprimirConjunto();
      break;
    case 7:
      imprimirConjuntos();
      break;
    case 8:
      buscarValor();
      break;
    case 9:
      printf("Encerrando o programa. Até mais!\n");
      exit(0);
      break;
    default:
      printf("Opção inválida!\n");
      break;
    }
  } while (option != 9);
  return 0;
}

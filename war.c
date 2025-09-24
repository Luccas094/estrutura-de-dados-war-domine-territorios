#include <stdio.h>
#include <string.h>

#define MAX 5
#define TAM_NOME 50
#define TAM_COR 20

// Estrutura do território
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

int main() {
    Territorio territorios[MAX];

    printf("=== Cadastro de Territórios (Nível Novato) ===\n");

    for (int i = 0; i < MAX; i++) {
        printf("\n--- Território %d ---\n", i + 1);

        printf("Nome: ");
        fgets(territorios[i].nome, TAM_NOME, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remove \n

        printf("Cor do exército: ");
        fgets(territorios[i].cor, TAM_COR, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0'; // remove \n

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); // limpar buffer
    }

    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < MAX; i++) {
        printf("Território %d: %s | Exército: %s | Tropas: %d\n",
               i + 1,
               territorios[i].nome,
               territorios[i].cor,
               territorios[i].tropas);
    }

    return 0;
}

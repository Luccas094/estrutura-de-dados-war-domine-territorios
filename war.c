#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TERRITORIOS 5

// Estrutura de território
typedef struct {
    char nome[50];
    char cor[20];
    int tropas;
} Territorio;

// Funções utilitárias
void exibirMapa(Territorio *mapa, int n) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d: %s | Exército: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("======================\n");
}

void cadastrarTerritorios(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nCadastro do território %d\n", i + 1);
        printf("Nome: ");
        getchar(); // limpa buffer
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove \n

        printf("Cor do exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

int dado() {
    return (rand() % 6) + 1; // retorna de 1 a 6
}

void atacar(Territorio *mapa, int atacante, int defensor) {
    if (mapa[atacante].tropas <= 1) {
        printf("\nO território %s não tem tropas suficientes para atacar!\n", mapa[atacante].nome);
        return;
    }

    printf("\n%s (%s) está atacando %s (%s)!\n",
           mapa[atacante].nome, mapa[atacante].cor,
           mapa[defensor].nome, mapa[defensor].cor);

    int dadoAtq = dado();
    int dadoDef = dado();

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtq, dadoDef);

    if (dadoAtq >= dadoDef) {
        mapa[defensor].tropas--;
        printf("%s perdeu 1 tropa!\n", mapa[defensor].nome);
        if (mapa[defensor].tropas <= 0) {
            printf("%s foi conquistado por %s!\n",
                   mapa[defensor].nome, mapa[atacante].nome);
            strcpy(mapa[defensor].cor, mapa[atacante].cor);
            mapa[defensor].tropas = mapa[atacante].tropas / 2;
            mapa[atacante].tropas -= mapa[defensor].tropas;
        }
    } else {
        mapa[atacante].tropas--;
        printf("%s perdeu 1 tropa!\n", mapa[atacante].nome);
    }
}

int verificarMissao(Territorio *mapa, int n) {
    int conquistados = 0;
    int verdeDestruido = 1;

    for (int i = 0; i < n; i++) {
        if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas > 0) {
            verdeDestruido = 0;
        }
        if (mapa[i].tropas > 0) {
            conquistados++;
        }
    }

    if (verdeDestruido) {
        printf("\nMissão cumprida: Exército Verde foi destruído!\n");
        return 1;
    }
    if (conquistados >= 3) {
        printf("\nMissão cumprida: Você conquistou 3 territórios!\n");
        return 1;
    }
    printf("\nMissão ainda não cumprida.\n");
    return 0;
}

// Programa principal
int main() {
    srand(time(NULL));
    int opcao, atacante, defensor;

    Territorio *mapa = (Territorio *)calloc(NUM_TERRITORIOS, sizeof(Territorio));

    printf("=== DESAFIO WAR ESTRUTURADO ===\n");
    cadastrarTerritorios(mapa, NUM_TERRITORIOS);

    do {
        exibirMapa(mapa, NUM_TERRITORIOS);
        printf("\nMenu:\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Escolha o território atacante (1 a %d): ", NUM_TERRITORIOS);
                scanf("%d", &atacante);
                printf("Escolha o território defensor (1 a %d): ", NUM_TERRITORIOS);
                scanf("%d", &defensor);
                if (atacante >= 1 && atacante <= NUM_TERRITORIOS &&
                    defensor >= 1 && defensor <= NUM_TERRITORIOS &&
                    atacante != defensor) {
                    atacar(mapa, atacante - 1, defensor - 1);
                } else {
                    printf("Escolha inválida!\n");
                }
                break;
            case 2:
                if (verificarMissao(mapa, NUM_TERRITORIOS)) {
                    printf("\nParabéns! Você venceu o jogo!\n");
                    opcao = 0;
                }
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    free(mapa);
    return 0;
}

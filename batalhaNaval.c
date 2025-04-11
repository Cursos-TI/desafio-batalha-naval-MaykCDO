#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3
#define VALOR_HABILIDADE 5
#define TAMANHO_HABILIDADE 5

// Função para exibir o tabuleiro com letras e números
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (char letra = 'A'; letra < 'A' + TAMANHO_TABULEIRO; letra++) {
        printf(" %c", letra);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Cone virado para cima (pirâmide invertida)
void criarCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = 0;
        }
    }

    matriz[2][0] = 1; matriz[2][1] = 1; matriz[2][2] = 1; matriz[2][3] = 1; matriz[2][4] = 1;
    matriz[1][1] = 1; matriz[1][2] = 1; matriz[1][3] = 1;
    matriz[0][2] = 1;
}

// Cruz simples
void criarCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int meio = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = (i == meio || j == meio) ? 1 : 0;
        }
    }
}

// Octaedro (losango estreito)
void criarOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = 0;
        }
    }

    matriz[0][2] = 1;
    matriz[1][1] = 1; matriz[1][2] = 1; matriz[1][3] = 1;
    matriz[2][2] = 1;
}

// Aplica a matriz de habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linhaOrigem, int colunaOrigem) {
    int offset = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linhaTabuleiro = linhaOrigem - offset + i;
            int colunaTabuleiro = colunaOrigem - offset + j;

            if (linhaTabuleiro >= 0 && linhaTabuleiro < TAMANHO_TABULEIRO &&
                colunaTabuleiro >= 0 && colunaTabuleiro < TAMANHO_TABULEIRO) {

                if (matriz[i][j] == 1 && tabuleiro[linhaTabuleiro][colunaTabuleiro] == VALOR_AGUA) {
                    tabuleiro[linhaTabuleiro][colunaTabuleiro] = VALOR_HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Posiciona os navios no tabuleiro
    int linhaHorizontal = 2;
    int colunaHorizontal = 4;
    int linhaVertical = 5;
    int colunaVertical = 1;

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaHorizontal][colunaHorizontal + i] = VALOR_NAVIO;
        tabuleiro[linhaVertical + i][colunaVertical] = VALOR_NAVIO;
    }

    // Navios diagonais
    int linhaDiag1 = 0;
    int colunaDiag1 = 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaDiag1 + i][colunaDiag1 + i] = VALOR_NAVIO;
    }

    int linhaDiag2 = 0;
    int colunaDiag2 = 9;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaDiag2 + i][colunaDiag2 - i] = VALOR_NAVIO;
    }

    // Matrizes de habilidades
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplicar habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 6, 6);       // Cone com origem em G7
    aplicarHabilidade(tabuleiro, cruz, 3, 3);       // Cruz com origem em D4
    aplicarHabilidade(tabuleiro, octaedro, 8, 8);   // Octaedro com origem em I9

    // Exibir resultado final
    printf("Tabuleiro final com habilidades especiais:\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}

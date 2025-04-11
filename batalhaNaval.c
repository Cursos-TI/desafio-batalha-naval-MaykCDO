#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3

// Função para exibir o tabuleiro com letras e números
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Imprime o cabeçalho com letras das colunas
    printf("   ");
    for (char letra = 'A'; letra < 'A' + TAMANHO_TABULEIRO; letra++) {
        printf(" %c", letra);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Imprime o número da linha (1 a 10), alinhado
        printf("%2d ", i + 1);

        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == VALOR_AGUA) {
                printf(" 0"); // Água
            } else if (tabuleiro[i][j] == VALOR_NAVIO) {
                printf(" 3"); // Parte do navio
            }
        }
        printf("\n");
    }
}

// Verifica se pode posicionar navio sem sair dos limites e sem sobreposição
int podePosicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                   int linha, int coluna, int deltaLinha, int deltaColuna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + i * deltaLinha;
        int c = coluna + i * deltaColuna;

        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO) {
            return 0; // Saiu dos limites
        }

        if (tabuleiro[l][c] == VALOR_NAVIO) {
            return 0; // Já tem navio ali
        }
    }
    return 1;
}

// Posiciona um navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                     int linha, int coluna, int deltaLinha, int deltaColuna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + i * deltaLinha;
        int c = coluna + i * deltaColuna;
        tabuleiro[l][c] = VALOR_NAVIO;
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Coordenadas dos navios
    int linhaHorizontal = 2, colunaHorizontal = 4;
    int linhaVertical = 5, colunaVertical = 1;
    int linhaDiagonal1 = 0, colunaDiagonal1 = 0;     // ↘
    int linhaDiagonal2 = 3, colunaDiagonal2 = 7;     // ↙

    // Verifica e posiciona navio horizontal
    if (podePosicionar(tabuleiro, linhaHorizontal, colunaHorizontal, 0, 1)) {
        posicionarNavio(tabuleiro, linhaHorizontal, colunaHorizontal, 0, 1);
    } else {
        printf("Erro ao posicionar navio horizontal.\n");
    }

    // Verifica e posiciona navio vertical
    if (podePosicionar(tabuleiro, linhaVertical, colunaVertical, 1, 0)) {
        posicionarNavio(tabuleiro, linhaVertical, colunaVertical, 1, 0);
    } else {
        printf("Erro ao posicionar navio vertical.\n");
    }

    // Verifica e posiciona navio diagonal ↘
    if (podePosicionar(tabuleiro, linhaDiagonal1, colunaDiagonal1, 1, 1)) {
        posicionarNavio(tabuleiro, linhaDiagonal1, colunaDiagonal1, 1, 1);
    } else {
        printf("Erro ao posicionar navio diagonal ↘.\n");
    }

    // Verifica e posiciona navio diagonal ↙
    if (podePosicionar(tabuleiro, linhaDiagonal2, colunaDiagonal2, 1, -1)) {
        posicionarNavio(tabuleiro, linhaDiagonal2, colunaDiagonal2, 1, -1);
    } else {
        printf("Erro ao posicionar navio diagonal ↙.\n");
    }

    // Exibe o tabuleiro final com todos os navios posicionados
    printf("\nTabuleiro com quatro navios (reto e diagonal):\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}

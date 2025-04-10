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

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Coordenadas do navio horizontal (linha, coluna inicial)
    int linhaHorizontal = 2;
    int colunaHorizontal = 4;

    // Coordenadas do navio vertical (linha inicial, coluna)
    int linhaVertical = 5;
    int colunaVertical = 1;

    // Verifica se os navios cabem no tabuleiro
    if (colunaHorizontal + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
        linhaVertical + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {

        int sobreposicao = 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaHorizontal][colunaHorizontal + i] == VALOR_NAVIO ||
                tabuleiro[linhaVertical + i][colunaVertical] == VALOR_NAVIO) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            // Posiciona navio horizontal
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaHorizontal][colunaHorizontal + i] = VALOR_NAVIO;
            }

            // Posiciona navio vertical
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaVertical + i][colunaVertical] = VALOR_NAVIO;
            }

            printf("Tabuleiro com navios posicionados:\n\n");
            exibirTabuleiro(tabuleiro);
        } else {
            printf("Erro: Sobreposição de navios detectada.\n");
        }
    } else {
        printf("Erro: Um ou ambos os navios não cabem no tabuleiro nas coordenadas fornecidas.\n");
    }

    return 0;
}

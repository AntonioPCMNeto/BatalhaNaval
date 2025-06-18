#include <stdio.h>

int main() {
    int tabuleiro[10][10];
    int linha, coluna;

    // Inicializa o tabuleiro com água (0)
    for (linha = 0; linha < 10; linha++) {
        for (coluna = 0; coluna < 10; coluna++) {
            tabuleiro[linha][coluna] = 0;
        }
    }

    // Posiciona dois navios fixos no tabuleiro (valor 3)
    // Navio horizontal tamanho 3
    int nav1_lin = 1, nav1_col = 2;
    for (int i = 0; i < 3; i++) {
        tabuleiro[nav1_lin][nav1_col + i] = 3;
    }

    // Navio vertical tamanho 3
    int nav2_lin = 4, nav2_col = 0;
    for (int i = 0; i < 3; i++) {
        tabuleiro[nav2_lin + i][nav2_col] = 3;
    }

    // Define o tamanho fixo das matrizes de habilidades
    int hab_tam = 5;
    int meio = hab_tam / 2; // índice central da matriz (2 para 5x5)

    // Declara as matrizes para as habilidades (5x5)
    int cone[5][5] = {0};
    int cruz[5][5] = {0};
    int octaedro[5][5] = {0};

    // ======================
    // Criando a matriz do CONE (apontando para baixo)
    // ======================
    // lógica: o "cone" começa no topo (linha=0)
    // e vai aumentando a largura (colunas com 1) até a base (linha=4)
    // Exemplo:
    // linha 0: só o meio
    // linha 1: meio - 1 até meio + 1
    // linha 2: meio - 2 até meio + 2
    // linha 3 e 4 igual a linha 2 (pode limitar para triângulo)
    for (linha = 0; linha < hab_tam; linha++) {
        // define o raio do cone na linha atual
        int raio = linha; // aumenta conforme a linha desce
        if (raio > meio) {
            raio = meio; // limita o cone para largura máxima
        }
        for (coluna = 0; coluna < hab_tam; coluna++) {
            // ativa as posições dentro do cone
            if (coluna >= meio - raio && coluna <= meio + raio) {
                cone[linha][coluna] = 1;
            }
        }
    }

    // ======================
    // Criando a matriz da CRUZ
    // ======================
    // lógica: ativa a linha do meio e a coluna do meio
    for (linha = 0; linha < hab_tam; linha++) {
        for (coluna = 0; coluna < hab_tam; coluna++) {
            if (linha == meio || coluna == meio) {
                cruz[linha][coluna] = 1;
            }
        }
    }

    // ======================
    // Criando a matriz do OCTAEDRO (losango)
    // ======================
    // lógica: ativa as posições que formam um losango central
    // distância de (linha, coluna) ao centro <= meio
    for (linha = 0; linha < hab_tam; linha++) {
        for (coluna = 0; coluna < hab_tam; coluna++) {
            int dist = (linha > meio) ? (linha - meio) : (meio - linha);
            int dist_col = (coluna > meio) ? (coluna - meio) : (meio - coluna);
            // soma das distâncias deve ser <= meio para formar losango
            if (dist + dist_col <= meio) {
                octaedro[linha][coluna] = 1;
            }
        }
    }

    // ======================
    // Define pontos de origem para cada habilidade no tabuleiro
    // (linha, coluna) - posição central da habilidade
    // ======================
    int origem_cone_lin = 0;
    int origem_cone_col = 4;

    int origem_cruz_lin = 5;
    int origem_cruz_col = 5;

    int origem_octa_lin = 8;
    int origem_octa_col = 2;

    // ======================
    // Função para sobrepor habilidade no tabuleiro
    // marca as posições afetadas com 5 (se estiverem dentro dos limites e não forem navio)
    // ======================
    for (linha = 0; linha < hab_tam; linha++) {
        for (coluna = 0; coluna < hab_tam; coluna++) {
            // CONE
            if (cone[linha][coluna] == 1) {
                int tab_lin = origem_cone_lin + (linha - meio);
                int tab_col = origem_cone_col + (coluna - meio);
                // verifica limites do tabuleiro
                if (tab_lin >= 0 && tab_lin < 10 && tab_col >= 0 && tab_col < 10) {
                    // marca só se não for navio (3)
                    if (tabuleiro[tab_lin][tab_col] != 3) {
                        tabuleiro[tab_lin][tab_col] = 5;
                    }
                }
            }

            // CRUZ
            if (cruz[linha][coluna] == 1) {
                int tab_lin = origem_cruz_lin + (linha - meio);
                int tab_col = origem_cruz_col + (coluna - meio);
                if (tab_lin >= 0 && tab_lin < 10 && tab_col >= 0 && tab_col < 10) {
                    if (tabuleiro[tab_lin][tab_col] != 3) {
                        tabuleiro[tab_lin][tab_col] = 5;
                    }
                }
            }

            // OCTAEDRO
            if (octaedro[linha][coluna] == 1) {
                int tab_lin = origem_octa_lin + (linha - meio);
                int tab_col = origem_octa_col + (coluna - meio);
                if (tab_lin >= 0 && tab_lin < 10 && tab_col >= 0 && tab_col < 10) {
                    if (tabuleiro[tab_lin][tab_col] != 3) {
                        tabuleiro[tab_lin][tab_col] = 5;
                    }
                }
            }
        }
    }

    // ======================
    // Exibe o tabuleiro completo com navios e áreas de habilidade
    // 0 = água, 3 = navio, 5 = área afetada
    // ======================
    printf("Tabuleiro com Navios e Áreas de Habilidade:\n\n");
    for (linha = 0; linha < 10; linha++) {
        for (coluna = 0; coluna < 10; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    return 0;
}

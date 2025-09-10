#include <stdio.h>
#include <stdbool.h>

#define TAM 8

// Função para validar posição no tabuleiro
bool posicaoValida(int lin, int col) {
    return lin >= 0 && lin < TAM && col >= 0 && col < TAM;
}

// ---------------- Nível Mestre ----------------
// Torre recursiva (5 casas para a direita)
void torreRecursiva(int lin, int col, int passos) {
    if (passos == 0 || !posicaoValida(lin, col)) return;
    printf("(%d, %d)\n", lin, col);
    torreRecursiva(lin, col + 1, passos - 1);
}

// Bispo com loops aninhados (5 casas diagonal direita/cima)
void bispoLoops(int lin, int col) {
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            if (i == j) {
                int novaLin = lin - i;
                int novaCol = col + j;
                if (posicaoValida(novaLin, novaCol)) {
                    printf("(%d, %d)\n", novaLin, novaCol);
                }
            }
        }
    }
}

// Rainha recursiva (8 casas para a esquerda)
void rainhaEsquerda(int lin, int col, int passos) {
    if (passos == 0 || !posicaoValida(lin, col)) return;
    printf("(%d, %d)\n", lin, col);
    rainhaEsquerda(lin, col - 1, passos - 1);
}

// Cavalo Mestre (1 L para cima/direita, com continue/break)
void cavaloMestre(int lin, int col) {
    int movimentos[8][2] = {
        {-2, 1}, {-1, 2}, {1, 2}, {2, 1},
        {2, -1}, {1, -2}, {-1, -2}, {-2, -1}
    };

    for (int i = 0; i < 8; i++) {
        int novaLin = lin + movimentos[i][0];
        int novaCol = col + movimentos[i][1];

        if (!(movimentos[i][0] == -2 && movimentos[i][1] == 1)) {
            continue; // só queremos cima + direita
        }

        if (!posicaoValida(novaLin, novaCol)) break;

        printf("(%d, %d)\n", novaLin, novaCol);
    }
}

// ---------------- Nível Novato ----------------
void movimentosBispo(int lin, int col) {
    for (int i = 1; i < TAM; i++) {
        if (posicaoValida(lin + i, col + i)) printf("(%d, %d)\n", lin + i, col + i);
        if (posicaoValida(lin - i, col + i)) printf("(%d, %d)\n", lin - i, col + i);
        if (posicaoValida(lin + i, col - i)) printf("(%d, %d)\n", lin + i, col - i);
        if (posicaoValida(lin - i, col - i)) printf("(%d, %d)\n", lin - i, col - i);
    }
}

void movimentosTorre(int lin, int col) {
    for (int i = 1; i < TAM; i++) {
        if (posicaoValida(lin, col + i)) printf("(%d, %d)\n", lin, col + i);
    }
}

void movimentosRainha(int lin, int col) {
    for (int i = 1; i < TAM; i++) {
        if (posicaoValida(lin, col - i)) printf("(%d, %d)\n", lin, col - i);
    }
}

// ---------------- Nível Aventureiro ----------------
void cavaloAventureiro(int lin, int col) {
    int passos = 0;
    for (int dx = 1; dx <= 2; dx++) {
        int dy = 1;
        while (dy <= 2) {
            if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
                int novaLin = lin + dx;
                int novaCol = col - dy;
                if (posicaoValida(novaLin, novaCol)) {
                    printf("(%d, %d)\n", novaLin, novaCol);
                    passos++;
                }
            }
            dy++;
        }
    }
    printf("Total de movimentos: %d\n", passos);
}

int main() {
    int nivel, peca, lin, col;

    printf("Escolha o nivel:\n1 - Novato\n2 - Aventureiro\n3 - Mestre\n> ");
    scanf("%d", &nivel);

    printf("Digite a posicao inicial (linha coluna): ");
    scanf("%d %d", &lin, &col);

    if (!posicaoValida(lin, col)) {
        printf("Posicao invalida!\n");
        return 0;
    }

    switch (nivel) {
        case 1:
            printf("Escolha a peca (1=Bispo, 2=Torre, 3=Rainha): ");
            scanf("%d", &peca);
            if (peca == 1) movimentosBispo(lin, col);
            else if (peca == 2) movimentosTorre(lin, col);
            else if (peca == 3) movimentosRainha(lin, col);
            else printf("Peca invalida.\n");
            break;

        case 2:
            cavaloAventureiro(lin, col);
            break;

        case 3:
            printf("Escolha a peca (1=Bispo, 2=Torre, 3=Rainha, 4=Cavalo): ");
            scanf("%d", &peca);
            if (peca == 1) bispoLoops(lin, col);
            else if (peca == 2) torreRecursiva(lin, col + 1, 5);
            else if (peca == 3) rainhaEsquerda(lin, col - 1, 8);
            else if (peca == 4) cavaloMestre(lin, col);
            else printf("Peca invalida.\n");
            break;

        default:
            printf("Nivel invalido.\n");
    }

    return 0;
}

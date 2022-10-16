#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "imagem.h"

#define M_PI 3.14159265358979323846

#define MARGEM_FATOR 0.02

// ================================================
//          Funções para manipular uma imagem
// ================================================

static imagem_p criar_imagem_dimensoes(int largura, int altura) {
    imagem_p img;
    int i;
    img = malloc(sizeof(*img));
    assert(img);
    img->largura = largura;
    img->altura = altura;
    img->pixels = malloc(sizeof(*img->pixels) * altura);
    assert(img->pixels);
    for (i = 0; i < img->altura; i++) {
        img->pixels[i] = calloc(largura, sizeof(**img->pixels));
        assert(img->pixels[i]);
    }
    img->cabeca.x = largura / 2;
    img->cabeca.y = altura / 2;
    img->cabeca.direcao = 0;
    img->caixa.x0 = img->cabeca.x;
    img->caixa.x1 = img->cabeca.x;
    img->caixa.y0 = img->cabeca.y;
    img->caixa.y1 = img->cabeca.y;
    return img;
}

imagem_p criar_imagem() {
    return criar_imagem_dimensoes(LARGURA_MAX, ALTURA_MAX);
}

static void atualizar_caixa(imagem_p img, int x, int y) {
    if (img->caixa.x0 > x)
        img->caixa.x0 = x;
    if (img->caixa.y0 > y)
        img->caixa.y0 = y;
    if (img->caixa.x1 < x)
        img->caixa.x1 = x;
    if (img->caixa.y1 < y)
        img->caixa.y1 = y;
}

imagem_p ler_imagem(char *nome_arquivo) {
    imagem_p img;
    char peek;
    int i, j;
    char v;
    int largura, altura;

    FILE *arquivo = fopen(nome_arquivo, "r");
    assert(arquivo);
    assert(fscanf(arquivo, "P1 ") == 0);
    while((peek = fgetc(arquivo)) == '#') fscanf(arquivo, "%*[^\r\n]%*[\r\n]");
    ungetc(peek, arquivo);
    assert(fscanf(arquivo, "%d %d", &largura, &altura) == 2);
    img = criar_imagem(largura, altura);
    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++) {
            assert(fscanf(arquivo, " %c", &v) == 1);
            img->pixels[i][j] = v - '0';
        }
    }
    fclose(arquivo);
    atualizar_caixa(img, 0, 0);
    atualizar_caixa(img, largura - 1, altura - 1);

    return img;
}

static void imprimir_imagem_arquivo(imagem_p img, FILE *arquivo) {
    int x, y;
    int x0, y0, x1, y1;
    int largura, altura;
    int margem;

    largura = img->caixa.x1 - img->caixa.x0 + 1;
    altura = img->caixa.y1 - img->caixa.y0 + 1;
    margem = largura > altura ? MARGEM_FATOR * largura : MARGEM_FATOR * altura;
    if (margem < 1) margem = 1;
    x0 = img->caixa.x0 - margem;
    y0 = img->caixa.y0 - margem;
    x1 = img->caixa.x1 + margem;
    y1 = img->caixa.y1 + margem;
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 >= img->largura) x1 = img->largura - 1;
    if (y1 >= img->altura) y1 = img->altura - 1;
    largura = x1 - x0 + 1;
    altura = y1 - y0 + 1;

    fprintf(arquivo, "P1\n%d %d\n", largura, altura);
    for (y = y0; y <= y1; y++) {
        for (x = x0; x <= x1; x++) {
            fprintf(arquivo, "%d",  img->pixels[y][x]);
        }
        fprintf(arquivo, "\n");
    }
}

void imprimir_imagem(imagem_p img) {
    imprimir_imagem_arquivo(img, stdout);
}

void salvar_imagem(imagem_p img, char *nome_arquivo) {
    FILE *arquivo;
    char novo_nome[1000] = "imagens/";
    int len;

    strcpy(novo_nome + 8, nome_arquivo);
    len = strlen(novo_nome);
    if (len < 4 || strcmp(novo_nome + len - 4, ".pbm") != 0)
        strcat(novo_nome, ".pbm");
    arquivo = fopen(novo_nome, "w");
    assert(arquivo);
    imprimir_imagem_arquivo(img, arquivo);
    fclose(arquivo);
}

void liberar_imagem(imagem_p img) {
    int i;
    for (i = 0; i < img->altura; i++)
        free(img->pixels[i]);
    free(img->pixels);
    free(img);
}

// ================================================
//          Funções auxiliares
// ================================================

int largura_caixa_pintada(imagem_p img) {
    return img->caixa.x1 - img->caixa.x0 + 1;
}

int altura_caixa_pintada(imagem_p img) {
    return img->caixa.y1 - img->caixa.y0 + 1;
}

int largura_imagem(imagem_p img) {
    return img->largura;
}

int altura_imagem(imagem_p img) {
    return img->altura;
}

static double radianos(int graus) {
    return graus * M_PI / 180.0;
}

static void pintar_pixel_cor(imagem_p img, int x, int y, int cor) {
    if (x < 0 || y < 0 || x >= img->largura || y >= img->altura)
        return ;
    img->pixels[y][x] = cor;
    atualizar_caixa(img, x, y);
}

void pintar_pixel(imagem_p img, int x, int y) {
    pintar_pixel_cor(img, x, y, 1);
}

void limpar_pixel(imagem_p img, int x, int y) {
    pintar_pixel_cor(img, x, y, 0);
}

void desenhar_linha(imagem_p img, int x0, int y0, int x1, int y1) {

    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;

    for (;;) {
        pintar_pixel(img, x0, y0);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

// ================================================
//          Funções para manipular a tartaruga
// ================================================

void andar_cabeca(imagem_p img, int comprimento) {
    double next_x, next_y;

    comprimento -= 1; // conta pixel da cabeça
    next_x = img->cabeca.x + cos(radianos(img->cabeca.direcao)) * comprimento;
    next_y = img->cabeca.y - sin(radianos(img->cabeca.direcao)) * comprimento;
    desenhar_linha(img, img->cabeca.x, img->cabeca.y, next_x, next_y);
    img->cabeca.x = next_x;
    img->cabeca.y = next_y;
}

void girar_cabeca(imagem_p img, int angulo) {
    img->cabeca.direcao += angulo;
}

tartaruga obter_tartaruga(imagem_p img) {
    tartaruga res;

    res.x = img->cabeca.x;
    res.y = img->cabeca.y;
    res.direcao = img->cabeca.direcao;

    return res;
}

void posicionar_tartaruga(imagem_p img, tartaruga cabeca) {
    img->cabeca.x = cabeca.x;
    img->cabeca.y = cabeca.y;
    img->cabeca.direcao = cabeca.direcao;
}

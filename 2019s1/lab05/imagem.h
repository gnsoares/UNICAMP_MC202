#ifndef IMAGEM_H
#define IMAGEM_H

#define LARGURA_MAX 3000
#define ALTURA_MAX 3000

// ================================================
//			Tipos de dados
// ================================================

/*
 * Indica a posição e direção da tartaruga
 */
typedef struct tartaruga
{
	double x, y;
    int direcao;
} tartaruga;

/*
 * Indica a área da imagem que está preenchida
 */
typedef struct area
{
	int x0, y0;
    int x1, y1;
} area;

/*
 * Imagem, representada pela altura, largura, uma matriz de pixels, a tartaruga e a área desenhada
 */
struct imagem 
{
    int largura, altura;
    char **pixels;
    tartaruga cabeca;
    area caixa;
};

/*
 * Tipo apontador para uma imagem
 */
typedef struct imagem *imagem_p;

// ================================================
//			Funções para manipular uma imagem
// ================================================

/*
 * Cria uma imagem vazia, preenchida com zeros, de altura e largura máximas
 * A tartaruga inicia no meio da imagem, fazendo 0 graus com o eixo x
 * A caixa inicializa vazia
 */
imagem_p criar_imagem();
/*
 * Libera a memória usada por uma imagem
 */
void liberar_imagem(imagem_p imgs);
/*
 * Imprime imagem na saída padrão, stdout
 */
void imprimir_imagem(imagem_p img);

// ================================================
//			Funções para manipular a tartaruga
// ================================================

/*
 * Anda a cabeça da tartaruga comprimento pixels na direção que ela está apontando
 */
void andar_cabeca(imagem_p img, int comprimento);
/*
 * Gira a cabeça da tartaruga angulo graus
 */
void girar_cabeca(imagem_p img, int angulo);
/*
 * Obtem a posição e direção atual da tartaruga
 */
tartaruga obter_tartaruga(imagem_p img);
/*
 * Reposicina a tartaruga na posição e direção indicada por cabeca
 */
void posicionar_tartaruga(imagem_p img, tartaruga cabeca);

// =============================================================================
//		As função abaixo NÃO são necessárias para resolver o laboratório.
//  Você pode utilizá-las para ajudar a debugar ou para exercitar programação.
// =============================================================================

/*
 * Retornan largura e altura da imagem, respectivamente
 */
int largura_imagem(imagem_p img);
int altura_imagem(imagem_p img);
/*
 * Retornan largura e altura da área preenchida (caixa), respectivamente
 */
int largura_caixa_pintada(imagem_p img);
int altura_caixa_pintada(imagem_p img);

/*
 * Pinta um pixel (preenche com 1)
 */
void pintar_pixel(imagem_p img, int x, int y);
/*
 * Limpa um pixel (preenche com 0)
 */
void limpar_pixel(imagem_p img, int x, int y);
/*
 * Desenha uma linha ligando os pontos (x0, y0) e (x1, y1)
 */
void desenhar_linha(imagem_p img, int x0, int y0, int x1, int y2);

/*
 * Lê uma imagem a partir de um arquivo .pbm
 */
imagem_p ler_imagem(char *nome_arquivo);
/*
 * Salva imagem em um arquivo .pbm, na pasta "imagens/"
 */
void salvar_imagem(imagem_p img, char *nome_arquivo);

#endif

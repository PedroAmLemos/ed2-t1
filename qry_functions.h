#ifndef QRY_FUNCTIONS_H_
#define QRY_FUNCTIONS_H_


#include "hash_table.h"
#include "avl_tree.h"
#include "city.h"

/*
 * Remove a quadra cep, os moradores que nela residirem e as ofertas de locação que nela existirem.
 * Pré: um ponteiro para a cidade, um cep, o arquivo txt e o arquivo svg.
 * Pós:
 * SVG: quadra deve ser colocada uma linha vertical com início no centro do elemento removido até o topo
 * do mapa. Também colocar (no topo) ao lado da linha vertical o cep.
 * TXT: reportar todos os dados relacionados aos elementos removidos.
 */
void del(City_t city, char *cep, FILE *qryTXTFile, FILE *qrySVGFile);

/*
 * Moradores da quadra cujo cep é cep.
 * Pré: recebe um ponteiro do tipo void* para a cidade, um cep e o arquivo txt.
 * Pós:
 * TXT: listar todos os dados dos moradores(nome, endereço, etc.). Reporta mensagem de erro se quadra não existir.
 */
void m(City_t city, char cep[], FILE *qryTXTFile);

/*
 * Imprime todos os dados do morador identificado pelo cpf
 * Pré: recebe um ponteiro do tipo void* para a cidade, um cpf o arquivo txt e o arquivo svg.
 * Pós:
 * TXT: dados pessoais, seu endereço e se moradia é alugada.
 * SVG: colocar uma linha vertical do endereço do morador até a margem superior do mapa. Anotar ao lado da linha o cpf,
 * nome e endereço do morador
 */
void dm(City_t _city, char cpf[], FILE *qryTXTFile, FILE *qrySVGFile);

/*
 * A pessoa identificada por cpf muda-se para o endereço determinado pelos parâmetros
 * Pré: recebe um ponteiro do tipo void* para a cidade, os dados para mudança e os arquivos txt e svg.
 * Pós:
 * TXT: mostrar os dados da pessoa (nome, etc.), o endereço antigo e o novo endereço.
 * SVG: uma linha vermelha grossa do endereço antigo ao endereço novo. Um pequeno círculo vermelho no endereço antigo,
 * outro círculo azul no novo endereço. Ambos círculos com borda branca grossa.
 */
void mud(City_t city, char cpf[], char cep[], char face, int num, char compl[], FILE *qryTXTFile, FILE *qrySVGFile);

/*
 * Oferta de locação. Imóvel do endereço especificado, de área ar m2 é ofertado para locação por R$ v mensais.
 * Pré: recebe um ponteiro do tipo void* para a cidade, os dados para a locação e os arquivos txt e svg.
 * Pós:
 */
void oloc(City_t city, char id[], char cep[], char side, int num, char compl[], double ar, double v);

/*
 * Quais são os imóveis disponíveis para locação na região especificada.
 * Pré: recebe um ponteiro do tipo void* para a cidade, a área passada e os arquivos txt e svg.
 * Pós:
 * TXT: relatar dados do imóvel e da locação.
 * SVG: marcar no svg a região (um retângulo com bordas tracejadas) e os imóveis disponíveis (com ‘*’).
 */
void oloc_i(City_t _city, double x, double y, double w, double h, FILE *qryTXTFile, FILE *qrySVGFile);

/*
 * Pessoa identificada por cpf aluga o imóvel cuja oferta é identificada por id. O imóvel deixa de estar disponível
 * para alocação. O indivíduo passa a ser morador do referido imóvel.
 * Pré: recebe um ponteiro do tipo void* para a cidade, o id da locação e cpf do locatário, e os arquivos txt e svg.
 * Pós:
 * TXT: reportar dados do imóvel, da locação e da pessoa.
 * SVG: marcar endereço do imóvel, traçar uma reta vertical do imóvel até a borda superior do desenho e, ao lado,
 * colocar informações sobre morador, imóvel e locação
 */
void loc(City_t city, char id[], char cpf[], FILE *qryTXTFile, FILE *qrySVGFile);

/*
 * Qual a situação da oferta de locação?
 * Pré: recebe um ponteiro do tipo void* para a cidade, o id da locação e os arquivos txt e svg.
 * Pós:
 * TXT: reportar os dados da moradia, se ela está alocada, se está disponível para locação. Caso esteja locada,
 * reportar os dados pessoais do morador.
 * SVG: marcar o local da moradia com ‘*’ se está locada; ‘$’ se está disponível para locação;
 */
void loc_i(City_t city, char id[], FILE *txtFile, FILE *svgFile);

/*
 * Locatário encerra contrato de locação. A oferta é removida.
 * Pré: recebe um ponteiro do tipo void* para a cidade, o id do contrato e os arquivos txt e svg.
 * Pós:
 * TXT: reportar dados pessoais e sobre a moradia.
 * SVG: semelhante à loc.
 */
void dloc(City_t city, char id[], FILE *txtFile, FILE *svgFile);

/*
 * Homens que moram dentro da região especificada.
 * Pré: recebe um ponteiro do tipo void* para a cidade, uma área identificada por um ponto x, y, uma largura w e altura h
 * e os arquivos txt e svg.
 * Pós:
 * TXT: reportar dados da pessoa e da moradia
 * SVG: marcar posição da moradia com uma pequena elipse azul.
 */

void hom(City_t city, double x, double y, double w, double h, FILE *txtFile, FILE *qrySVGFile);

/*
 * Semelhante à hom. Seleciona as mulheres. Pinta a elipse de rosa.
 */
void mul(City_t city, double x, double y, double w, double h, FILE *txtFile, FILE *qrySVGFile);

/*
 * Imprime o estado atual da árvore no arquivo <arq>-sfx.dot
 * Pré: recebe um ponteiro do tipo void* para a cidade, o nome do arquivo e o caminho de saída.
 * Pós:
 */
void dmpt(City_t city, char *fileName, char *outPath);

/*
 * Remover as quadras, moradores que estejam inteiramente contidas na região delimitada pelo retângulo x, y, w, h.
 * Ofertas de locação na região também deve ser removidas.
 * Pré: recebe um ponteiro do tipo void* para a cidade, e a área de busca identificada por um ponto x, y, uma largura
 * w e altura h e os arquivos txt e svg.
 * Pós:
 */
void catac(City_t city, double x, double y, double w, double h, FILE *txtFile, FILE *svgFile);
#endif //QRY_FUNCTIONS_H_

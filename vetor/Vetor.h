/*
 * MIT License
 *
 * Copyright (c) [year] [fullname]
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * =============================================================================
 *
 * NVetor | TVetor | TVetor3D
 * Javascript Object
 *
 * @author     Jean Carlo de Elias Moreira | https://www.jeancarloem.com
 * @license    MIT | https://opensource.org/licenses/MIT
 * @copyright  © 2017 Jean Carlo EM
 * @git        https://github.com/JeanCarloEM/NVetor
 * @site       https://opensource.jeancarloem.com/NVetor
 * @dependency RNG | https://github.com/ademakov/RNG
 *
 */

#ifndef VETOR_H
#define VETOR_H

#include <stddef.h>

/* https://sourceforge.net/p/predef/wiki/OperatingSystems/ */
#ifdef DLLVETOR
  #ifdef MAKEDLLVETOR
    #define DLLVETORIMEXPORT DLLEXPORT
  #else
    #define DLLVETORIMEXPORT DLLIMPORT
  #endif
#else
  #define DLLVETORIMEXPORT
#endif

  namespace NVetor {
    /*
     * DEFINE UM UM TIPO DE DADOS, DO TIPO CALLBACK
     * PARA LIBERAR DA MEMORIA OS ITEMS DA PILHA
     *
     * @param {void**}  item    eh o ponteiro para o item(indice) do array c
     * @para  {void*}   vetor   eh o ponteiro para a classe TVetor
     */
    typedef bool (*PFreeInitVetorItemP)(void **item, void *vetor);
    typedef bool (*PFreeInitVetorItemN)(int item, void *vetor);

    /*
     * UMA ESTRATURA DE DADOS A SER FORNECIDA PARA O CONTRUTOR DE Tvetor
     */
    typedef struct SCallBackFreeInitVetorItem {
      PFreeInitVetorItemP p;
      PFreeInitVetorItemN n;

      SCallBackFreeInitVetorItem(): p(NULL), n(NULL)
      {}
    } TCallBackFreeInitVetorItem;

    /*
     * UMA MATRIZ DE PONTEIRO - HETEROGENEA
     */
    class TVetor {
    #ifndef MAKEDLLVETOR
    private:
      /* ONDE DE FATO OS ITENS SAO ARMAZENADOS */
      void **items = NULL;  // PONTEIRO PARA PONTEIROS

      void *pai = NULL;     // Pai aponta para um Tvetor
                            // em caso de multidimencional

      ulint qtd = 0,        // QUANTIDADE DE ELEMENTOS
            initeds = 0,    // QUANTIDADE DE ELEMENTOS INICIALIZADO
            reservedQTD = 0;// QUANTIDADE DE ELEMENTOS ALOCADOS

      /* CALLBACK A SER USADO PARA INICIALIZAR E LIBERAR ITENS */
      SCallBackFreeInitVetorItem _freeItem; // ELIMINADOR / CALLBACK
      SCallBackFreeInitVetorItem _initItem; // INICIALIZADOR / CALLBACK

      /* O MESMO QUE ncfreeItem, POREM SEM VERIFICACOES
       * PODE CAUSAR ESTOURO DE PILHA | MAIS RAPIDO
       *
       * @param {uliunt} i    o numero do indice no vetor do item a ser liberado
       * @return {bool}       true se sucesso
       */
      bool ncfreeItem(ulint i);
      /*
       * LIBERA/DESTROI/DESALOCA UM ITEM ESPECIFICO
       * EVITA ESTOURO DE PILHA COM VERIFICACOES | MAIS LENTO
       *
       * @param {uliunt} i    o numero do indice no vetor do item a ser liberado
       * @return {bool}       true se sucesso
       */
      bool freeItem(ulint i);
      /* LIBERA TODOS OS ITENS, COM ncfreeItem
       *
       * @param {uliunt} i    o numero do indice no vetor do item a ser liberado
       * @return {bool}       true se sucesso
       */
      bool freeAll();
      /*
       * INICIALIZA UM ITEM ESPECIFICO
       *
       * @param {uliunt} i    o numero do indice no vetor do item a ser liberado
       * @return {bool}       true se sucesso
       */
      bool initItem(ulint i);

      /* REALOCA O ARRAY DE PONTEIRO EFETIVAMENTE
       *
       * SETA LIMITE A REALLOCAR items MAS NAO FAZ FREE OU INIT DE NENHUM DELES
       * A RESPONSABILIDADE DE FREE/INI EH DE LENGTH
       *
       * @return {bool}       true se sucesso
       */
      bool re_alocar(ulint size, bool forceRealloc = false);

    #endif
    public:
      /*
       * CONSTRUTOR
       *
       * @param {TCallBackFreeInitVetorItem}  f   Funcao Callback para Liberar Items
       * @param {TCallBackFreeInitVetorItem}  i   Funcao Callback para Iniciar Items
       * @param {void*}                       pai um ponteiro para o pai, geralmennte um vetor
       */
      DLLVETORIMEXPORT TVetor(TCallBackFreeInitVetorItem f, TCallBackFreeInitVetorItem i, void *pai);
      /*
       * CONSTRUTOR DE ITENS VAZIOS
       */
      DLLVETORIMEXPORT TVetor();
      /*
       * DESTRUTOR
       */
      DLLVETORIMEXPORT ~TVetor();
      /*
       * QUANTIDADE DE ELEMENTOS RESERVADO/ALOCADOS
       *
       * @return {ulin}
       */
      DLLVETORIMEXPORT ulint reservados();

      /*
       * QUANTIDADE DE ELEMENTOS (INICIALIZADOS), NAO EH O TAMANHO DO VETOR
       * A QUANTIDADE DE ELEMENTOS PODE SER DIFERENTE DO TAMANHO DO VETOR QUANDO
       * VOCÊ TEM, NESTE CASO, UM VETOR DE 100 ITEMS VOID**, POREM DESSES, APENAS
       * 50 FORAM INICIALIZADOS(ALOCADOS/CRIADOS)
       * PORTANTO COUNT CONTA OS ELEMENTOS EXISTENTE, NAO O TAMANHO DO VETOR
       *
       * @return {ulint}
       */
      DLLVETORIMEXPORT ulint count();

      /*
       * SIZE E LENGTH CONTAM O TAMANHO TOTAL DO VETOR, OU SEJA
       * O TAMANHO DA MATRIZ **items.
       * NAO NECESSARIAMENTE EXISTEM A MESMA QUANTIDADE DE ELEMENTOS
       *
       * @return {ulint}
       */
      DLLVETORIMEXPORT ulint size();

      /* ALEM DE OBTER O TAMANHO, SIMILAR A SIZE, PERMITE ALTERAR O TAMANHO DO VETOR
       * PERMITE SETAR O TAMANHO - REDIMENCIONAR
       *
       * SIZE E LENGTH CONTAM O TAMANHO TOTAL DO VETOR, OU SEJA
       * O TAMANHO DA MATRIZ **items.
       * NAO NECESSARIAMENTE EXISTEM A MESMA QUANTIDADE DE ELEMENTOS
       *
       * @param {ulint}   size    se zero, apenas retorno a quantidade
       * @return {ulint}
       */
      DLLVETORIMEXPORT ulint length(ulint size = 0); // LINK NAME

      /*
       * RETORNA DE O VETOR ESTA ALOCADO NA MEMORIA
       *
       * @return {bool}
       */
      DLLVETORIMEXPORT bool alocado();

      /* OBTEM UM ITEM, SEM FAZER VERIFICACAO DO TAMANHO/QUANTIDADE
       * OBTEM UM PONTEIRO UMA CELULA
       *
       * @param {ulint}     index   coordenada z
       * @param {void**}            item  um ponteiro para retornar
       * @return {bool}             true se setou o ponteiro corretamente
       */
      DLLVETORIMEXPORT bool ncitem(ulint index, void **item);
      /* RETORNA UM ITEM, SEM FAZER VERIFICACAO DO TAMANHO/QUANTIDADE
       * RETORNA UM PONTEIRO UMA CELULA
       *
       * @param {ulint}     index   coordenada z
       * @return {void*}
       */
      DLLVETORIMEXPORT void *ncitem(ulint index);
      /* RETORNA UM PONTEIRO PARA INDICE, SEM FAZER VERIFICACAO DO TAMANHO/QUANTIDADE
       * RETORNA UM PONTEIRO PARA O INDICE DE UMA CELULA
       *
       * @param {ulint}     index   coordenada z
       * @return {void**}
       */
      DLLVETORIMEXPORT void **ncitemP(ulint index);

      /* OBTEM UM ITEM, FAZENDO A VERIFICACAO DO TAMANHO/QUANTIDADE
       * OBTEM UM PONTEIRO UMA CELULA
       *
       * @param {ulint}     index   coordenada z
       * @param {void**}    item    um ponteiro para retornar
       * @return {bool}             true se setou o ponteiro corretamente
       */
      DLLVETORIMEXPORT bool item(ulint index, void **item);
      /* RETORNA UM ITEM, FAZENDO A VERIFICACAO DO TAMANHO/QUANTIDADE
       * RETORNA UM PONTEIRO UMA CELULA
       *
       * @param {ulint}     index   coordenada z
       * @return {void*}
       */
      DLLVETORIMEXPORT void *item(ulint index);
      /* RETORNA UM PONTEIRO PARA O INDICE DO ITEM, FAZENDO A VERIFICACAO DO TAMANHO/QUANTIDADE
       * RETORNA UM PONTEIRO PARA O INDICE DE UMA CELULA
       *
       * @param {ulint}     index   coordenada z
       * @return {void*}
       */
      DLLVETORIMEXPORT void **itemP(ulint index);

      /* SETA UM ITEM, SEM FAZER A VERIFICACAO DO TAMANHO/QUANTIDADE
       *
       * CONFIGURA UMA CELULA PARA QUE APONTE PARA UM NOVO PONTEIRO
       * OU SEJA, DEFINE O NOVO VALOR DA CELULA
       * ESTA FUNCAO TENTA LIBERAR EVENTUAL CONTEUDO PREEXISTENTE NA CELULA
       *
       * @param {ulint}                       index   coordenada z
       * @return {bool}                               true se sucesso
       */
      DLLVETORIMEXPORT bool ncsetItem(ulint index, void *p);

      /* SETA UM ITEM, FAZENDO A VERIFICACAO DO TAMANHO/QUANTIDADE
       *
       * CONFIGURA UMA CELULA PARA QUE APONTE PARA UM NOVO PONTEIRO
       * OU SEJA, DEFINE O NOVO VALOR DA CELULA
       * ESTA FUNCAO TENTA LIBERAR EVENTUAL CONTEUDO PREEXISTENTE NA CELULA
       *
       * @param {ulint}                       index   coordenada z
       * @return {bool}                               true se sucesso
       */
      DLLVETORIMEXPORT bool setItem(ulint index, void *p);

      /*
       * ADICIONA UM ITEM AO VETOR, REDIMENCIONANDO-O AUTOMATICAMENTE
       *
       * @param {void}  item  o ponteiro para o item a ser adicionado
       * @return {bool}       true se sucesso
       */
      DLLVETORIMEXPORT bool push(void *item);
      /*
       * OBTEM UM PONTEIRO PARA UMA DAS CELULAS
       *
       * @param {void}  item  o ponteiro para o item a ser adicionado
       * @return {bool}       true se sucesso
       */
      DLLVETORIMEXPORT bool top(void **item);
      /*
       * OBTEM UM PONTEIRO PARA UMA DAS CELULAS E, ELIMINA A MESMA DO VETOR
       * REDIMENCIONANNDO (TALVEZ - PROVAVELMENTE NAO)
       *
       * @param {void}  item  o ponteiro para o item a ser adicionado
       * @return {bool}       true se sucesso
       */
      DLLVETORIMEXPORT bool pop(void **item);
      /*
       * REINICIALIZA O VETOR, ELIMINANDO EVENTUAIS ITEMS
       *
       * @return {bool} true se sucesso
       */
      DLLVETORIMEXPORT bool reset();
      /*
       * EFETUA O EMBARALHAMENTO (ORDEM) DO VETOR
       *
       * https://gist.github.com/sundeepblue/10501662
       * https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#The_modern_algorithm
       */
      DLLVETORIMEXPORT void shuffle();
      /*
       * VERIFICA SE A FUNCAO DE INICIALIZAR OS ITEM FOI INFORMADA
       *
       * @return {bool}     true se sim
       */
      DLLVETORIMEXPORT bool validInitCallBack();
      /*
       * VERIFICA SE A FUNCAO DE LIBERAR OS ITEM FOI INFORMADA
       *
       * @return {bool}     true se sim
       */
      DLLVETORIMEXPORT bool validFreeCallBack();
    };

    /*================================================
     * ESPECIALIZACOES - TVETOR
     *================================================*/

    DLLVETORIMEXPORT bool freeItemTVetor(void **item);
    DLLVETORIMEXPORT bool pushVetor(TVetor *p, TVetor *v);
    DLLVETORIMEXPORT bool pushNewVetor(TVetor *p, TVetor *v, TCallBackFreeInitVetorItem f, TCallBackFreeInitVetorItem i);
    DLLVETORIMEXPORT bool itemAsVetor(TVetor *p, ulint i, TVetor **v);
    DLLVETORIMEXPORT TVetor *itemAsVetor(TVetor *p, ulint i);
    DLLVETORIMEXPORT bool topVetor(TVetor *p, TVetor **v);
    DLLVETORIMEXPORT bool popFloat(TVetor *p, TVetor **v);

    /*================================================
     * ESPECIALIZACOES - INT
     *================================================*/

    DLLVETORIMEXPORT bool pushInt(TVetor *p, int i);
    DLLVETORIMEXPORT bool iteamAsInt(TVetor *p, ulint i, int **v);
    DLLVETORIMEXPORT int *iteamAsInt(TVetor *p, ulint i);
    DLLVETORIMEXPORT bool topInt(TVetor *p, int **i);
    DLLVETORIMEXPORT bool popInt(TVetor p, int **i);

  /*================================================
   * ESPECIALIZACOES - CHAR
   *================================================*/

    DLLVETORIMEXPORT bool pushChar(TVetor *p, char c);
    DLLVETORIMEXPORT bool iteamAsChar(TVetor *p, ulint i, char **c);
    DLLVETORIMEXPORT char *iteamAsChar(TVetor *p, ulint i);
    DLLVETORIMEXPORT bool topChar(TVetor *p, int **c);
    DLLVETORIMEXPORT bool popChar(TVetor *p, int **c);
  };

#if (defined(DLLVETOR) && defined(MAKEDLLVETOR)) || !defined(DLLVETOR)
#include "Vetor.cpp"
#endif

#endif /* VETOR_H */
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

#ifndef VETOR3D_H
#define VETOR3D_H

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

  #include "Vetor.h"

  namespace NVetor {
    class TVetor3D;

    class TVetor3D{
    #ifndef MAKEDLLVETOR
    private:
      TVetor *vetor = NULL;

      TCallBackFreeInitVetorItem _freeItem; // ELIMINADOR / CALLBACK
      TCallBackFreeInitVetorItem _initItem; // INICIALIZADOR / CALLBACK

      /*
       * LIBERA/DESTROI/DESALOCA UM ITEM ESPECIFICO
       * EVITA ESTOURO DE PILHA COM VERIFICACOES | MAIS LENTO
       *
       * @param {uliunt} i    o numero do indice no vetor do item a ser liberado
       * @return {bool}       true se sucesso
       */
      bool freeItem(ulint i);

      /*
       * INICIALIZA UM ITEM ESPECIFICO
       *
       * @param {uliunt} i    o numero do indice no vetor do item a ser liberado
       * @return {bool}       true se sucesso
       */
      bool initItem(ulint i);

      /*
       * LIBERA/DESTROI/DESALOCA TODOS OS ITENS DO VETOR
       *
       * @return {bool}       true se sucesso
       */
      bool freeItems();

      /*
       * REALOCA O ARRAY DE PONTEIRO EFETIVAMENTE
       *
       * SETA LIMITE A REALLOCAR items MAS NAO FAZ FREE OU INIT DE NENHUM DELES
       * A RESPONSABILIDADE DE FREE/INI EH DE LENGTH
       *
       * @return {bool}       true se sucesso
       */
      bool re_alocar(ulint size);
    #endif
    public:
      /*
       * CONSTRUTOR
       *
       * @param {TCallBackFreeInitVetorItem}  f   Funcao Callback para Liberar Items
       * @param {TCallBackFreeInitVetorItem}  i   Funcao Callback para Iniciar Items
       * @param {ulint}                       z   numero de items no eixo z
       * @param {ulint}                       x   numero de items no eixo x
       * @param {ulint}                       y   numero de items no eixo y
       */
      DLLVETORIMEXPORT TVetor3D(TCallBackFreeInitVetorItem f, TCallBackFreeInitVetorItem i, ulint z, ulint x, ulint y);
      /*
       * CONSTRUTOR
       *
       * @param {TCallBackFreeInitVetorItem}  f   Funcao Callback para Liberar Items
       * @param {ulint}                       z   numero de items no eixo z
       * @param {ulint}                       x   numero de items no eixo x
       * @param {ulint}                       y   numero de items no eixo y
       */
      DLLVETORIMEXPORT TVetor3D(TCallBackFreeInitVetorItem i, ulint z, ulint x, ulint y);
      /*
       * CONSTRUTOR
       *
       * @param {ulint}                       z   numero de items no eixo z
       * @param {ulint}                       x   numero de items no eixo x
       * @param {ulint}                       y   numero de items no eixo y
       */
      DLLVETORIMEXPORT TVetor3D(ulint z, ulint x, ulint y);
      /*
       * CONSTRUTOR DE ITENS VAZIOS
       *
       * @param {TCallBackFreeInitVetorItem}  f   Funcao Callback para Liberar Items
       * @param {TCallBackFreeInitVetorItem}  i   Funcao Callback para Iniciar Items
       */
      DLLVETORIMEXPORT TVetor3D(TCallBackFreeInitVetorItem f, TCallBackFreeInitVetorItem i);
      /*
       * CONSTRUTOR DE ITENS VAZIOS
       */
      DLLVETORIMEXPORT TVetor3D();
      /*
       * DESTRUTOR
       */
      DLLVETORIMEXPORT ~TVetor3D();

      /*
       * RETORNA A QUANTIDADE DE CELULAS
       *
       * @return {ulin}
       */
      DLLVETORIMEXPORT ulint cellCount();
      /*
       * RETORNA DE O VETOR ESTA ALOCADO NA MEMORIA
       *
       * @return {bool}
       */
      DLLVETORIMEXPORT bool alocado();
      /*
       * REINICIALIZA O VETOR, ELIMINANDO EVENTUAIS ITEMS
       *
       * @return {bool} true se sucesso
       */
      DLLVETORIMEXPORT bool reset();
      /*
       * SETA O TAMANHO DO VETOR 3D
       *
       * @param {ulint}                       z   numero de items no eixo z
       * @param {ulint}                       x   numero de items no eixo x
       * @param {ulint}                       y   numero de items no eixo y
       * @return {ulin}                           a quantidade de celulas total
       */
      DLLVETORIMEXPORT ulint setSize(ulint z, ulint x, ulint y);
      /*
       * OBTEM UM PONTEIRO UMA CELULA
       *
       * @param {ulint}                       z     coordenada z
       * @param {ulint}                       x     coordenada x
       * @param {ulint}                       y     coordenada y
       * @param {void**}                      item  um ponteiro para retornar
       * @return {ulin}                             true se setou o ponteiro corretamente
       */
      DLLVETORIMEXPORT bool item(ulint z, ulint x, ulint y, void **item);
      /*
       * RETORNA UM PONTEIRO PARA UMA CELULA
       *
       * @param {ulint}                       z   coordenada z
       * @param {ulint}                       x   coordenada x
       * @param {ulint}                       y   coordenada y
       * @return {void*}
       */
      DLLVETORIMEXPORT void *item(ulint z, ulint x, ulint y);
      /*
       * RETORNA UM PONTEIRO PARA O INDICE DE UM ITEM
       *
       * @param {ulint}                       z   coordenada z
       * @param {ulint}                       x   coordenada x
       * @param {ulint}                       y   coordenada y
       * @return {void**}
       */
      DLLVETORIMEXPORT void **itemP(ulint z, ulint x, ulint y);
      /*
       * CONFIGURA UMA CELULA PARA QUE APONTE PARA UM NOVO PONTEIRO
       * OU SEJA, DEFINE O NOVO VALOR DA CELULA
       * ESTA FUNCAO TENTA LIBERAR EVENTUAL CONTEUDO PREEXISTENTE NA CELULA
       *
       * @param {ulint}                       z   coordenada z
       * @param {ulint}                       x   coordenada x
       * @param {ulint}                       y   coordenada y
       * @return {bool}                           true se sucesso
       */
      DLLVETORIMEXPORT bool setItem(ulint z, ulint x, ulint y, void *p);
      /*
       * RETORNA A QUANTIDADE DE ITEMS NO EIXO Z
       *
       * QUANTIDADE DE ELEMENTOS (INICIALIZADOS), NAO EH O TAMANHO DO VETOR
       * A QUANTIDADE DE ELEMENTOS PODE SER DIFERENTE DO TAMANHO DO VETOR QUANDO
       * VOCÊ TEM, NESTE CASO, UM VETOR DE 100 ITEMS VOID**, POREM DESSES, APENAS
       * 50 FORAM INICIALIZADOS(ALOCADOS/CRIADOS)
       * PORTANTO COUNT CONTA OS ELEMENTOS EXISTENTE, NAO O TAMANHO DO VETOR
       *
       * @return {ulint}
       */
      DLLVETORIMEXPORT ulint Zcount();
      /*
       * RETORNA A QUANTIDADE DE ITEMS NO EIXO X
       *
       * QUANTIDADE DE ELEMENTOS (INICIALIZADOS), NAO EH O TAMANHO DO VETOR
       * A QUANTIDADE DE ELEMENTOS PODE SER DIFERENTE DO TAMANHO DO VETOR QUANDO
       * VOCÊ TEM, NESTE CASO, UM VETOR DE 100 ITEMS VOID**, POREM DESSES, APENAS
       * 50 FORAM INICIALIZADOS(ALOCADOS/CRIADOS)
       * PORTANTO COUNT CONTA OS ELEMENTOS EXISTENTE, NAO O TAMANHO DO VETOR
       *
       * @param {ulint}                       z   coordenada z
       * @return {ulint}
       */
      DLLVETORIMEXPORT ulint Xcount(ulint z);
      /*
       * RETORNA A QUANTIDADE DE ITEMS NO EIXO Y
       *
       * QUANTIDADE DE ELEMENTOS (INICIALIZADOS), NAO EH O TAMANHO DO VETOR
       * A QUANTIDADE DE ELEMENTOS PODE SER DIFERENTE DO TAMANHO DO VETOR QUANDO
       * VOCÊ TEM, NESTE CASO, UM VETOR DE 100 ITEMS VOID**, POREM DESSES, APENAS
       * 50 FORAM INICIALIZADOS(ALOCADOS/CRIADOS)
       * PORTANTO COUNT CONTA OS ELEMENTOS EXISTENTE, NAO O TAMANHO DO VETOR
       *
       * @param {ulint}                       z   coordenada z
       * @param {ulint}                       x   coordenada x
       * @return {ulint}
       */
      DLLVETORIMEXPORT ulint Ycount(ulint z, ulint x);
      /*
       * RETORNA O TAMANHO DE ALOCACAO NA MEMORIA, MESMO QUE NAO USADO
       * POR ITEMS - NAO PRENCHIDO, NO EIXO Z
       *
       * SIZE E LENGTH CONTAM O TAMANHO TOTAL DO VETOR, OU SEJA
       * O TAMANHO DA MATRIZ **items.
       * NAO NECESSARIAMENTE EXISTEM A MESMA QUANTIDADE DE ELEMENTOS
       *
       * @return {ulint}
       */
      DLLVETORIMEXPORT ulint Zsize(ulint size = 0);
      /*
       * RETORNA O TAMANHO DE ALOCACAO NA MEMORIA, MESMO QUE NAO USADO
       * POR ITEMS - NAO PRENCHIDO, NO EIXO X
       *
       * SIZE E LENGTH CONTAM O TAMANHO TOTAL DO VETOR, OU SEJA
       * O TAMANHO DA MATRIZ **items.
       * NAO NECESSARIAMENTE EXISTEM A MESMA QUANTIDADE DE ELEMENTOS
       *
       * @param {ulint}                       z   coordenada z
       * @return {ulint}
       */
      DLLVETORIMEXPORT ulint Xsize(ulint size = 0);
      /*
       * RETORNA O TAMANHO DE ALOCACAO NA MEMORIA, MESMO QUE NAO USADO
       * POR ITEMS - NAO PRENCHIDO, NO EIXO Y
       *
       * SIZE E LENGTH CONTAM O TAMANHO TOTAL DO VETOR, OU SEJA
       * O TAMANHO DA MATRIZ **items.
       * NAO NECESSARIAMENTE EXISTEM A MESMA QUANTIDADE DE ELEMENTOS
       *
       * @param {ulint}                       z   coordenada z
       * @param {ulint}                       x   coordenada x
       * @return {ulint}
       */
      DLLVETORIMEXPORT ulint Ysize(ulint size = 0);
      /*
       * EVOCADORES DAS FUNCOES DE CALLBACK FORNECIDAS NO CONSTRUTOR
       */
      DLLVETORIMEXPORT TCallBackFreeInitVetorItem getFreeItem();
      /*
       * EVOCADORES DAS FUNCOES DE CALLBACK FORNECIDAS NO CONSTRUTOR
       */
      DLLVETORIMEXPORT TCallBackFreeInitVetorItem getInitItem();
    };

    /*
     * FUNCOES DE CALLBACK PARA OS EIXOS INTERMEDIARIOS
     * QUE NAO NAO MANUSEADOS DIRETAMENTE PELO USUARIO/PROGRAMADOR
     */
    bool freeSubZVetor(void **item, void *vetor);
    bool initSubZVetor(void **item, void *vetor);

    bool freeSubXVetor(void **item, void *vetor);
    bool initSubXVetor(void **item, void *vetor);

    bool freeZXItem(void **item, void *vetor);


  /*================================================
   * ESPECIALIZACOES - CHAR
   *================================================*/

    DLLVETORIMEXPORT bool iteam3DAsChar(TVetor3D *p, ulint z, ulint x, ulint y, char **c);
    DLLVETORIMEXPORT char *iteam3DAsChar(TVetor3D *p, ulint z, ulint x, ulint y);
  };

#if (defined(DLLVETOR) && defined(MAKEDLLVETOR)) || !defined(DLLVETOR)
#include "Vetor3D.cpp"
#endif

#endif /* VETOR3D_H */


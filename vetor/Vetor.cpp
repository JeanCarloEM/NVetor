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

#ifndef _VETOR_CPP // SE AINDA NAO INCLUIDO (DEINIDO) INCLUA
#define _VETOR_CPP // DEFINA PARA EVITAR REINCLUSAO

#include "Vetor.h"
#include <stdlib.h>
#include "../lib/comum.h"

namespace NVetor {

  /* OBTEM UM ITEM, FAZENDO A VERIFICACAO DO TAMANHO/QUANTIDADE
   * OBTEM UM PONTEIRO UMA CELULA
   *
   * @param {ulint}     index   coordenada z
   * @param {void**}    item    um ponteiro para retornar
   * @return {bool}             true se setou o ponteiro corretamente
   */
  bool TVetor::item(ulint index, void **item) {
    *item = NULL;
    if (this->alocado() && (index < this->size())) {
      return this->ncitem(index, item);
    }

    return false;
  }

  /* OBTEM UM ITEM, SEM FAZER VERIFICACAO DO TAMANHO/QUANTIDADE
   * OBTEM UM PONTEIRO UMA CELULA
   *
   * @param {ulint}     index   coordenada z
   * @param {void**}            item  um ponteiro para retornar
   * @return {bool}             true se setou o ponteiro corretamente
   */
  bool TVetor::ncitem(ulint index, void **item) {
    *item = this->items[index];
    return (item != NULL);
  }

  /* RETORNA UM ITEM, FAZENDO A VERIFICACAO DO TAMANHO/QUANTIDADE
   * RETORNA UM PONTEIRO UMA CELULA
   *
   * @param {ulint}     index   coordenada z
   * @return {void*}
   */
  void *TVetor::item(ulint index) {
    void *item = NULL;
    if (this->item(index, &item)) {
      return item;
    }

    return NULL;
  }

  /* RETORNA UM ITEM, SEM FAZER VERIFICACAO DO TAMANHO/QUANTIDADE
   * RETORNA UM PONTEIRO UMA CELULA
   *
   * @param {ulint}     index   coordenada z
   * @return {void*}
   */
  void *TVetor::ncitem(ulint index) {
    void *item = NULL;
    this->ncitem(index, &item);
    return item;
  }

  /* RETORNA UM PONTEIRO PARA O INDICE DO ITEM, FAZENDO A VERIFICACAO DO TAMANHO/QUANTIDADE
   * RETORNA UM PONTEIRO PARA O INDICE DE UMA CELULA
   *
   * @param {ulint}     index   coordenada z
   * @return {void*}
   */
  void **TVetor::itemP(ulint index){
    if (this->alocado() && (index < this->size())) {
      return &this->items[index];
    }

    return NULL;
  }

  /* RETORNA UM PONTEIRO PARA INDICE, SEM FAZER VERIFICACAO DO TAMANHO/QUANTIDADE
   * RETORNA UM PONTEIRO PARA O INDICE DE UMA CELULA
   *
   * @param {ulint}     index   coordenada z
   * @return {void**}
   */
  void **TVetor::ncitemP(ulint index){
    return &this->items[index];
  }


  /*
   * REINICIALIZA O VETOR, ELIMINANDO EVENTUAIS ITEMS
   *
   * @return {bool} true se sucesso
   */
  bool TVetor::reset() {
    if (this->alocado()) {
      // LIBERA TODOS OS ITEMS
      if (this->freeAll()) {
        this->re_alocar(0);

        free(this->items);
        this->items = NULL;
        this->reservedQTD = 0;

        return true;
      }
    }

    return (!this->alocado());
  }

  /* LIBERA TODOS OS ITENS, COM ncfreeItem
   *
   * @param {uliunt} i    o numero do indice no vetor do item a ser liberado
   * @return {bool}       true se sucesso
   */
  bool TVetor::freeAll() {
    if (this->alocado()) {
      for (int item = this->count()-1; item >= 0; item--){
        if (!this->freeItem(item)){
          throw VetException(__func__, __LINE__, __FILE__, "Falha ao efetuar a liberao de items.");
          return false;
        }
      }
    }

    return true;
  }

  /*
   * DESTRUTOR
   */
  TVetor::~TVetor() {
    this->reset();
  }

  /*
   * CONSTRUTOR
   *
   * @param {TCallBackFreeInitVetorItem}  f   Funcao Callback para Liberar Items
   * @param {TCallBackFreeInitVetorItem}  i   Funcao Callback para Iniciar Items
   * @param {void*}                       pai um ponteiro para o pai, geralmennte um vetor
   */
  TVetor::TVetor(TCallBackFreeInitVetorItem f, TCallBackFreeInitVetorItem i, void *pai = NULL) {
    // DESALOCA A VETOR SE ESTIVER ALOCADA
    this->reset();

    // INICIALIZA
    this->_freeItem = f;
    this->_initItem = i;
    this->pai = pai;
  }

  /*
   * CONSTRUTOR DE ITENS VAZIOS
   */
  TVetor::TVetor() {
    // DESALOCA A VETOR SE ESTIVER ALOCADA
    this->reset();
  }

  /*
   * RETORNA DE O VETOR ESTA ALOCADO NA MEMORIA
   *
   * @return {bool}
   */
  bool TVetor::alocado() {
    return (this->items != NULL);
  }

  /*
   * VERIFICA SE A FUNCAO DE INICIALIZAR OS ITEM FOI INFORMADA
   *
   * @return {bool}     true se sim
   */
  bool TVetor::validInitCallBack(){
    return ((this->_initItem.p != NULL) || (this->_initItem.n != NULL));
  }

  /*
   * VERIFICA SE A FUNCAO DE LIBERAR OS ITEM FOI INFORMADA
   *
   * @return {bool}     true se sim
   */
  bool TVetor::validFreeCallBack(){
    return ((this->_freeItem.p != NULL) || (this->_freeItem.n != NULL));
  }

  /*
   * LIBERA/DESTROI/DESALOCA UM ITEM ESPECIFICO
   * EVITA ESTOURO DE PILHA COM VERIFICACOES | MAIS LENTO
   *
   * @param {uliunt} i    o numero do indice no vetor do item a ser liberado
   * @return {bool}       true se sucesso
   */
  bool TVetor::freeItem(ulint i) {
    if ((this->alocado()) && (i < this->size()) && (i < this->count())) {
      return this->ncfreeItem(i);
    }

    return false;
  }

  /* O MESMO QUE ncfreeItem, POREM SEM VERIFICACOES
   * PODE CAUSAR ESTOURO DE PILHA | MAIS RAPIDO
   *
   * @param {uliunt} i    o numero do indice no vetor do item a ser liberado
   * @return {bool}       true se sucesso
   */
  bool TVetor::ncfreeItem(ulint i) {
    if (this->validFreeCallBack()){
      try {
        bool r = false;

        if (this->_freeItem.p!=NULL){
          r = this->_freeItem.p(&this->items[i], (this->pai!=NULL)?this->pai:this);
        }else{
          r = this->_freeItem.n(i, (this->pai!=NULL)?this->pai:this);
        }

        if (!r){
          throw VetException(__func__ , __LINE__ , __FILE__, "Insucesso ao liberar item da memoria.");
        }else{
          this->items[i] = NULL;
        }
      } catch (int e) {
        throw VetException(__func__ , __LINE__ , __FILE__, "Falha ao executar callback de liberacao de item da memoria.");
      }
    }else{
      if (this->items[i] != NULL){
        free(this->items[i]);
        this->items[i] = NULL;
      }
    }

    if (this->items[i] != NULL){
      throw VetException(__func__ , __LINE__ , __FILE__, "Liberacao de item da memoria falhou.");
    }

    if (this->items[i] == NULL){
      this->initeds--;
      return true;
    }

    return false;
  }

  /*
   * INICIALIZA UM ITEM ESPECIFICO
   *
   * @param {uliunt} i    o numero do indice no vetor do item a ser liberado
   * @return {bool}       true se sucesso
   */
  bool TVetor::initItem(ulint i) {
    if ((this->alocado()) && (this->validFreeCallBack()) && (i < this->size()) && (i >= this->count())) {
      try {
          bool r = false;

          this->items[i] = NULL;

          if (this->_initItem.p!=NULL){
            r = this->_initItem.p(&this->items[i], (this->pai!=NULL)?this->pai:this);
          }else{
            r = this->_initItem.n(i, (this->pai!=NULL)?this->pai:this);
          }

          if (!r){
            throw VetException(__func__ , __LINE__ , __FILE__, "Insucesso ao inicializar item da memoria.");
          }

          this->initeds++;

          return true;
      } catch (int e) {
        throw VetException(__func__ , __LINE__ , __FILE__, "Um erro previsto, porem injustificavel ocorreu.");
      }
    }

    return false;
  }

  /*
   * QUANTIDADE DE ELEMENTOS (INICIALIZADOS), NAO EH O TAMANHO DO VETOR
   * A QUANTIDADE DE ELEMENTOS PODE SER DIFERENTE DO TAMANHO DO VETOR QUANDO
   * VOCÊ TEM, NESTE CASO, UM VETOR DE 100 ITEMS VOID**, POREM DESSES, APENAS
   * 50 FORAM INICIALIZADOS(ALOCADOS/CRIADOS)
   * PORTANTO COUNT CONTA OS ELEMENTOS EXISTENTE, NAO O TAMANHO DO VETOR
   *
   * @return {ulint}
   */
  ulint TVetor::count() {
    return this->initeds;
  }

  /*
   * SIZE E LENGTH CONTAM O TAMANHO TOTAL DO VETOR, OU SEJA
   * O TAMANHO DA MATRIZ **items.
   * NAO NECESSARIAMENTE EXISTEM A MESMA QUANTIDADE DE ELEMENTOS
   *
   * @return {ulint}
   */
  ulint TVetor::size() {
    return this->qtd;
  }
  /*
   * QUANTIDADE DE ELEMENTOS RESERVADO/ALOCADOS
   *
   * @return {ulin}
   */
  ulint TVetor::reservados(){
    return this->reservedQTD;
  }

  /* REALOCA O ARRAY DE PONTEIRO EFETIVAMENTE
   *
   * SETA LIMITE A REALLOCAR items MAS NAO FAZ FREE OU INIT DE NENHUM DELES
   * A RESPONSABILIDADE DE FREE/INI EH DE LENGTH
   *
   * @return {bool}       true se sucesso
   */
  bool TVetor::re_alocar(ulint size, bool forceRealloc) {
    if ((size > 0) && ((size > this->reservados()) ||  ((size < this->reservados()) && (forceRealloc)))) {
      if (((this->items == NULL) && (this->size() > 0)) || ((this->items != NULL) && (this->size() == 0))) {
        throw VetException(__func__ , __LINE__ , __FILE__, "Ponteiro e alocacoes divergentes com a contagem de elementos." );
      }

      // REALOCANDO
      if ((this->items == NULL) && (this->size() == 0)) {
        this->items = (void **) malloc(size * sizeof (void *));
      } else {
        this->items = (void **) realloc(this->items, size * sizeof (void *));
      }

      if (this->items != NULL){
        /* INICIANDO OS PONTEIROS COMO NULOS, PARA FIM DE IDENTIFICACAO */
        for (int i = this->size(); i < size; i++){
          this->items[i] = NULL;
        }
      }

      if (this->items == NULL){
        throw VetException(__func__ , __LINE__ , __FILE__, "Falha ao (re)alocar os itens do vetor." );
      }else{
        this->reservedQTD = size;
      }
    }

    if ((this->items != NULL) || (size == 0)) {
      this->qtd = size;

      if (size < this->count()){
        this->initeds = size;
      }

      return true;
    }

    return false;
  }

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
  ulint TVetor::length(ulint size) {
    ulint osize = this->size();

    if ((size > 0) && (size != osize)) {
      // LIBERANDO OS FILHOS PRIMEIRAMENTE
      if (this->alocado() && (size < osize)) {
        for (ulint i = (osize - 1); i >= size; i--) {
          this->freeItem(i);
        }
      }

      // REALOCANDO
      if (this->re_alocar(size)) {
        if ((size > osize) && (this->validInitCallBack())) {
          for (ulint i = osize; i < size; i++) {
            this->items[i] = NULL; // SIGNIFICA NAO INICIALIZADO
            this->initItem(i);
          }
        }

        return this->size();
      }
    } else if ((size == 0) || ((size > 0) && (size == osize))){
      return this->size();
    }

    return 0;
  }

  /* SETA UM ITEM, SEM FAZER A VERIFICACAO DO TAMANHO/QUANTIDADE
   *
   * CONFIGURA UMA CELULA PARA QUE APONTE PARA UM NOVO PONTEIRO
   * OU SEJA, DEFINE O NOVO VALOR DA CELULA
   * ESTA FUNCAO TENTA LIBERAR EVENTUAL CONTEUDO PREEXISTENTE NA CELULA
   *
   * @param {ulint}                       index   coordenada z
   * @return {bool}                               true se sucesso
   */
  bool TVetor::ncsetItem(ulint index, void *p){
    if (this->items[index] != NULL){
      this->freeItem(index);
    }

    this->items[index] = p;
    this->initeds++;

    return true;
  }

  /* SETA UM ITEM, FAZENDO A VERIFICACAO DO TAMANHO/QUANTIDADE
   *
   * CONFIGURA UMA CELULA PARA QUE APONTE PARA UM NOVO PONTEIRO
   * OU SEJA, DEFINE O NOVO VALOR DA CELULA
   * ESTA FUNCAO TENTA LIBERAR EVENTUAL CONTEUDO PREEXISTENTE NA CELULA
   *
   * @param {ulint}                       index   coordenada z
   * @return {bool}                               true se sucesso
   */
  bool TVetor::setItem(ulint index, void *p){
    if ((p != NULL) && (index < this->size())){
      /* LEMBRANDO QUE count EH O TOTAL, SENDO O PROXIMO A SER SETADO
       * O PROPRIO TOTAL DE count, POR ISSO,
       * INDEX = this->count() PODE SER USADO, MAS NAO MAIS QUE ISSO */
      if (index > this->count()){
        throw VetException(__func__, __LINE__, __FILE__, "Foi pedido para setar um item, pulando items nao count. Isso nao deve/pode ser feito.");
      }

      this->ncsetItem(index, p);

      return true;
    }else{
      throw VetException(__func__, __LINE__, __FILE__, "Nao eh possivel setar um item de vetor que nao exista.");
    }

    return false;
  }

  /*
   * ADICIONA UM ITEM AO VETOR, REDIMENCIONANDO-O AUTOMATICAMENTE
   *
   * @param {void}  item  o ponteiro para o item a ser adicionado
   * @return {bool}       true se sucesso
   */
  bool TVetor::push(void *item) {
    if (item != NULL){
      if (this->count() >= this->size()){
        this->re_alocar(this->size() + 1);
      }

      if (this->count() < this->size()){
        return this->ncsetItem(this->count(), item);
      }
    }

    throw VetException(__func__ , __LINE__ , __FILE__, "Falha ao fazer push dos dados, item e NULO.");

    return false;
  }

  /*
   * OBTEM UM PONTEIRO PARA UMA DAS CELULAS
   *
   * @param {void}  item  o ponteiro para o item a ser adicionado
   * @return {bool}       true se sucesso
   */
  bool TVetor::top(void **item) {
    if (this->alocado() && (this->count() > 0)) {
      *item = this->item(this->count() - 1);
      return (*item != NULL);
    }

    return false;
  }

  /*
   * OBTEM UM PONTEIRO PARA UMA DAS CELULAS E, ELIMINA A MESMA DO VETOR
   * REDIMENCIONANNDO (TALVEZ - PROVAVELMENTE NAO)
   *
   * @param {void}  item  o ponteiro para o item a ser adicionado
   * @return {bool}       true se sucesso
   */
  bool TVetor::pop(void **item) {
    if (this->top(item)) {
      this->initeds--;
      return this->re_alocar(this->size() - 1);
    }

    return false;
  }

  /*
   * EFETUA O EMBARALHAMENTO (ORDEM) DO VETOR
   *
   * https://gist.github.com/sundeepblue/10501662
   * https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#The_modern_algorithm
   */
  void TVetor::shuffle() {
    /* O PRIMEIRO ELEMENTO (ULTIMO ELEMENTO DO FOR) NAO EH TOCADO DIRETAMENTE,
     * SEGUNDO FISHER MODERNO, POR ISSO, "i > 0", E NAO "i >= 0"
     */
    for (lint i = (this->count() - 1); i > 0; i--) {
      /* 0 <= X >= i
       * OU SEJA, DEVE INCLUIR O 0 E IR ATEH O I,
       * A FUNCAO sortear, JAH INCLUIR O i, POR ISSO NAO
       * HA NECESSIDADE DE EFETUAR A SOMA (i+1)
       *
       * FAZ A TROCA DOS PONTEIROS
       */
      swapP(&this->items[i], &this->items[sortear(0, i)]);
    }
  }

  /*================================================
   * ESPECIALIZACOES - TVetor
   *================================================*/

  bool freeItemTVetor(void **item, void *vetor){
    delete (TVetor *)*item;
  }


  /*
   */
  bool pushVetor(TVetor *p, TVetor *v) {
    if (p->alocado() && (v != NULL)) {
      return p->push((void *) v);
    }

    return false;
  }


  bool setVetorItem(TVetor *p, ulint index, TVetor *v){
    if (v != NULL) {
      return p->setItem(index, (void *)v);
    }

    return false;
  }

  /*
   */
  bool pushNewVetor(TVetor *p, TVetor *v, TCallBackFreeInitVetorItem f, TCallBackFreeInitVetorItem i) {
    if (p != NULL) {
      TVetor *item;

      if (i.p != NULL){
        i.p((void **)&item, p);
      }else{
        TCallBackFreeInitVetorItem fd;
        fd.p = freeItemTVetor;

        item = new TVetor(((f.p!=NULL||f.n!=NULL)?f:fd), i);
      }

      if (item != NULL) {
        if (pushVetor(p, item)) {
          v = item;
          return true;
        }else{
          delete item;
        }
      }
    }

    return false;
  }

  bool itemAsVetor(TVetor *p, ulint i, TVetor **v) {
    return p->item(i, (void **) v);
  }

  TVetor *itemAsVetor(TVetor *p, ulint i) {
    void *r = p->item(i);

    return (r!=NULL) ? ((TVetor *) r): NULL;
  }

  /*
   */
  bool topVetor(TVetor *p, TVetor **v) {
    return p->top((void **) v);
  }

  /*
   */
  bool popFloat(TVetor *p, TVetor **v) {
    return p->pop((void **) v);
  }



  /*================================================
   * ESPECIALIZACOES - INT
   *================================================*/

  /*
   */
  bool pushInt(TVetor *p, int i) {
    void *item = (void *) malloc(sizeof(int));

    if (item != NULL) {
      *((int *)item) = i;

      if (p->push(item)){
        return true;
      }else{
        free(item);
      }
    }

    return false;
  }

  bool setIntItem(TVetor *p, ulint index, int i){
    void *item = (void *) malloc(sizeof(int));

    if (item != NULL) {
      *((int *)item) = i;

      if (p->setItem(index, item)){
        return true;
      }else{
        free(item);
      }
    }

    return false;
  }

  bool iteamAsInt(TVetor *p, ulint i, int **v) {
    return p->item(i, (void **)v);
  }

  int *iteamAsInt(TVetor *p, ulint i) {
    return (int *) p->item(i);
  }

  /*
   */
  bool topInt(TVetor *p, int **i) {
    return p->top((void **) i);
  }

  /*
   */
  bool popInt(TVetor *p, int **i) {
    return p->pop((void **) i);
  }


  /*================================================
   * ESPECIALIZACOES - CHAR
   *================================================*/

  /*
   */
  /*
   */
  bool pushChar(TVetor *p, char c) {
    void *item = (void *) malloc(sizeof(char));

    if (item != NULL) {
      *((char *)item) = c;

      if (p->push(item)){
        return true;
      }else{
        free(item);
      }
    }

    return false;
  }

  bool setCharItem(TVetor *p, ulint index, char c){
    void *item = (void *) malloc(sizeof(char));

    if (item != NULL) {
      *((int *)item) = c;

      if (p->setItem(index, item)){
        return true;
      }else{
        free(item);
      }
    }

    return false;
  }

  bool iteamAsChar(TVetor *p, ulint i, char **c) {
    return p->item(i, (void **)c);
  }

  char *iteamAsChar(TVetor *p, ulint i) {
    return (char *) p->item(i);
  }

  /*
   */
  bool topChar(TVetor *p, char **c) {
    return p->top((void **) c);
  }

  /*
   */
  bool popChar(TVetor *p, char **c) {
    return p->pop((void **) c);
  }
}
#endif /* VETOR_C */
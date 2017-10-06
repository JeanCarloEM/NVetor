/*
 * MIT License
 *
 * Copyright (c) 2017 Jean Carlo de Elias Moreira
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

#include "Vetor3D.h"

namespace NVetor {
  /*
   * REINICIALIZA O VETOR, ELIMINANDO EVENTUAIS ITEMS
   *
   * @return {bool} true se sucesso
   */
  bool TVetor3D::reset() {
    if (this->alocado()) {
      delete this->vetor;
    }

    TCallBackFreeInitVetorItem fd;
    TCallBackFreeInitVetorItem id;

    fd.p = freeZXItem;
    id.p = initSubZVetor;

    this->vetor = new TVetor(fd, id, (void *)this);

    return (!this->alocado());
  }

  /*
   * RETORNA A QUANTIDADE DE CELULAS
   *
   * @return {ulin}
   */
  lint TVetor3D::cellCount(){
    if (this->alocado()){
      return (this->vetor->size() * itemAsVetor(this->vetor, 0)->size() * itemAsVetor(itemAsVetor(this->vetor, 0), 0)->size());
    }

    return 0;
  }

  /*
   * CONSTRUTOR DE ITENS VAZIOS
   *
   * @param {TCallBackFreeInitVetorItem}  f   Funcao Callback para Liberar Items
   * @param {TCallBackFreeInitVetorItem}  i   Funcao Callback para Iniciar Items
   */
  TVetor3D::TVetor3D(TCallBackFreeInitVetorItem f, TCallBackFreeInitVetorItem i){
    // DESALOCA A VETOR SE ESTIVER ALOCADA
    this->reset();

    // INICIALIZA
    this->_freeItem = f;
    this->_initItem = i;
  }

  /*
   * CONSTRUTOR
   *
   * @param {TCallBackFreeInitVetorItem}  f   Funcao Callback para Liberar Items
   * @param {TCallBackFreeInitVetorItem}  i   Funcao Callback para Iniciar Items
   * @param {lint}                       z   numero de items no eixo z
   * @param {lint}                       x   numero de items no eixo x
   * @param {lint}                       y   numero de items no eixo y
   */
  TVetor3D::TVetor3D(TCallBackFreeInitVetorItem f, TCallBackFreeInitVetorItem i, lint z, lint x, lint y){
    // DESALOCA A VETOR SE ESTIVER ALOCADA
    this->reset();

    // INICIALIZA
    this->_freeItem = f;
    this->_initItem = i;

    this->setSize(z, x, y);
  }

  /*
   * CONSTRUTOR
   *
   * @param {TCallBackFreeInitVetorItem}  f   Funcao Callback para Liberar Items
   * @param {lint}                       z   numero de items no eixo z
   * @param {lint}                       x   numero de items no eixo x
   * @param {lint}                       y   numero de items no eixo y
   */
  TVetor3D::TVetor3D(TCallBackFreeInitVetorItem i, lint z, lint x, lint y){
    this->reset();
    this->_initItem = i;
    this->setSize(z, x, y);
  }
  /*
   * CONSTRUTOR
   *
   * @param {lint}                       z   numero de items no eixo z
   * @param {lint}                       x   numero de items no eixo x
   * @param {lint}                       y   numero de items no eixo y
   */
  TVetor3D::TVetor3D(lint z, lint x, lint y){
    this->reset();
    this->setSize(z, x, y);
  }
  /*
   * CONSTRUTOR DE ITENS VAZIOS
   */
  TVetor3D::TVetor3D(){
    this->reset();
  }
  /*
   * DESTRUTOR
   */
  TVetor3D::~TVetor3D(){
    delete this->vetor;
  }

  /*
   * RETORNA DE O VETOR ESTA ALOCADO NA MEMORIA
   *
   * @return {bool}
   */
  bool TVetor3D::alocado() {
    return (this->vetor != NULL);
  }

  /*
   * EVOCADORES DAS FUNCOES DE CALLBACK FORNECIDAS NO CONSTRUTOR
   */
  TCallBackFreeInitVetorItem TVetor3D::getFreeItem(){
    return this->_freeItem;
  }

  /*
   * EVOCADORES DAS FUNCOES DE CALLBACK FORNECIDAS NO CONSTRUTOR
   */
  TCallBackFreeInitVetorItem TVetor3D::getInitItem(){
    return this->_initItem;
  }

  /*
   * RETORNA A QUANTIDADE DE ITEMS NO EIXO Z
   *
   * QUANTIDADE DE ELEMENTOS (INICIALIZADOS), NAO EH O TAMANHO DO VETOR
   * A QUANTIDADE DE ELEMENTOS PODE SER DIFERENTE DO TAMANHO DO VETOR QUANDO
   * VOCÊ TEM, NESTE CASO, UM VETOR DE 100 ITEMS VOID**, POREM DESSES, APENAS
   * 50 FORAM INICIALIZADOS(ALOCADOS/CRIADOS)
   * PORTANTO COUNT CONTA OS ELEMENTOS EXISTENTE, NAO O TAMANHO DO VETOR
   *
   * @return {lint}
   */
  lint TVetor3D::Zcount(){
    if (this->alocado()){
      if (this->vetor != NULL){
        return this->vetor->count();
      }
    }

    return 0;
  }

  /*
   * RETORNA A QUANTIDADE DE ITEMS NO EIXO X
   *
   * QUANTIDADE DE ELEMENTOS (INICIALIZADOS), NAO EH O TAMANHO DO VETOR
   * A QUANTIDADE DE ELEMENTOS PODE SER DIFERENTE DO TAMANHO DO VETOR QUANDO
   * VOCÊ TEM, NESTE CASO, UM VETOR DE 100 ITEMS VOID**, POREM DESSES, APENAS
   * 50 FORAM INICIALIZADOS(ALOCADOS/CRIADOS)
   * PORTANTO COUNT CONTA OS ELEMENTOS EXISTENTE, NAO O TAMANHO DO VETOR
   *
   * @param {lint}                       z   coordenada z
   * @return {lint}
   */
  lint TVetor3D::Xcount(lint z = 0){
    if (this->alocado()){
      if (this->Zcount() > z){
        return itemAsVetor(this->vetor, z)->count();
      }
    }

    return 0;
  }

  /*
   * RETORNA A QUANTIDADE DE ITEMS NO EIXO Y
   *
   * QUANTIDADE DE ELEMENTOS (INICIALIZADOS), NAO EH O TAMANHO DO VETOR
   * A QUANTIDADE DE ELEMENTOS PODE SER DIFERENTE DO TAMANHO DO VETOR QUANDO
   * VOCÊ TEM, NESTE CASO, UM VETOR DE 100 ITEMS VOID**, POREM DESSES, APENAS
   * 50 FORAM INICIALIZADOS(ALOCADOS/CRIADOS)
   * PORTANTO COUNT CONTA OS ELEMENTOS EXISTENTE, NAO O TAMANHO DO VETOR
   *
   * @param {lint}                       z   coordenada z
   * @param {lint}                       x   coordenada x
   * @return {lint}
   */
  lint TVetor3D::Ycount(lint z = 0, lint x = 0){
    if (this->alocado()){
      if ((this->Zcount() > z) && (this->Xcount() > x)) {
        return itemAsVetor(itemAsVetor(this->vetor, z), x)->count();
      }
    }

    return 0;
  }

  /*
   * RETORNA O TAMANHO DE ALOCACAO NA MEMORIA, MESMO QUE NAO USADO
   * POR ITEMS - NAO PRENCHIDO, NO EIXO Z
   *
   * SIZE E LENGTH CONTAM O TAMANHO TOTAL DO VETOR, OU SEJA
   * O TAMANHO DA MATRIZ **items.
   * NAO NECESSARIAMENTE EXISTEM A MESMA QUANTIDADE DE ELEMENTOS
   *
   * @return {lint}
   */
  lint TVetor3D::Zsize(lint size){
    if (this->alocado()){
      if((size > 0) && (this->vetor->length(size) != size)){
        throw VetException(__func__ , __LINE__ , __FILE__, "Falha ao redimencionar Vetor 3D, exito Z.");
      }

      return this->vetor->size();
    }

    return 0;
  }

  /*
   * RETORNA O TAMANHO DE ALOCACAO NA MEMORIA, MESMO QUE NAO USADO
   * POR ITEMS - NAO PRENCHIDO, NO EIXO X
   *
   * SIZE E LENGTH CONTAM O TAMANHO TOTAL DO VETOR, OU SEJA
   * O TAMANHO DA MATRIZ **items.
   * NAO NECESSARIAMENTE EXISTEM A MESMA QUANTIDADE DE ELEMENTOS
   *
   * @param {lint}                       z   coordenada z
   * @return {lint}
   */
  lint TVetor3D::Xsize(lint size){
    if (this->alocado()){
      if (size > 0){
        lint zsize = this->vetor->size();

        for (lint i = 0; i < zsize; i++){
          if ((size > 0) && (itemAsVetor(this->vetor, i)->length(size) != size)){
            throw VetException(__func__ , __LINE__ , __FILE__, "Falha ao redimencionar Vetor 3D, exito X.");
          }
        }
      }

      if (this->Zsize() > 0){
        TVetor *it = itemAsVetor(this->vetor, 0);

        lint r = it->size();

        if (r == 0){

        }
        return r;
      }
    }

    return 0;
  }

  /*
   * RETORNA O TAMANHO DE ALOCACAO NA MEMORIA, MESMO QUE NAO USADO
   * POR ITEMS - NAO PRENCHIDO, NO EIXO Y
   *
   * SIZE E LENGTH CONTAM O TAMANHO TOTAL DO VETOR, OU SEJA
   * O TAMANHO DA MATRIZ **items.
   * NAO NECESSARIAMENTE EXISTEM A MESMA QUANTIDADE DE ELEMENTOS
   *
   * @param {lint}                       z   coordenada z
   * @param {lint}                       x   coordenada x
   * @return {lint}
   */
  lint TVetor3D::Ysize(lint size){
    if (this->alocado()){
      if (size > 0){
        for (lint i = 0; i < this->vetor->size(); i++){
          TVetor *x = itemAsVetor(this->vetor, i);

          for (lint j = 0; j < x->size(); j++){
            if (itemAsVetor(x, j)->length(size) <= 0){
              throw VetException(__func__ , __LINE__ , __FILE__, "Falha ao redimencionar item");
            }
          }
        }
      }

      if ((this->Zsize() > 0) && (this->Xsize() > 0)){
        return itemAsVetor(itemAsVetor(this->vetor, 0), 0)->size();
      }
    }

    return 0;
  }

  /*
   * SETA O TAMANHO DO VETOR 3D
   *
   * @param {lint}                       z   numero de items no eixo z
   * @param {lint}                       x   numero de items no eixo x
   * @param {lint}                       y   numero de items no eixo y
   * @return {ulin}                           a quantidade de celulas total
   */
  lint TVetor3D::setSize(lint z, lint x, lint y){
    if ((z > 0) && (x > 0) && (y > 0)){
      lint zz = this->Zsize(z);

      if (zz == z){
        lint xx = this->Xsize(x);

        if (xx == x){
          if (this->Ysize(y) == y){
            return x*y*x;
          }
        }
      }
    }

    return 0;
  }

  /*
   * OBTEM UM PONTEIRO UMA CELULA
   *
   * @param {lint}                       z     coordenada z
   * @param {lint}                       x     coordenada x
   * @param {lint}                       y     coordenada y
   * @param {void**}                      item  um ponteiro para retornar
   * @return {ulin}                             true se setou o ponteiro corretamente
   */
  bool TVetor3D::item(lint z, lint x, lint y, void **item){
    if (this->alocado() && (z < this->Zsize()) && (x < this->Xsize()) && (y < this->Ysize()) && (item != NULL)){
      *item = itemAsVetor(itemAsVetor(this->vetor, z), x)->item(y);
      return (*item != NULL);
    }

    return false;
  }

  /*
   * RETORNA UM PONTEIRO PARA UMA CELULA
   *
   * @param {lint}                       z   coordenada z
   * @param {lint}                       x   coordenada x
   * @param {lint}                       y   coordenada y
   * @return {void*}
   */
  void *TVetor3D::item(lint z, lint x, lint y){
    void *item = NULL;

    if (this->item(z, x, y, &item) && (item != NULL)) {
      return item;
    }

    return NULL;
  }

  /*
   * RETORNA UM PONTEIRO PARA O INDICE DE UM ITEM
   *
   * @param {lint}                       z   coordenada z
   * @param {lint}                       x   coordenada x
   * @param {lint}                       y   coordenada y
   * @return {void**}
   */
  void **TVetor3D::itemP(lint z, lint x, lint y){
    if (this->alocado() && (z < this->Zsize()) && (x < this->Xsize()) && (y < this->Ysize())){
      return itemAsVetor(itemAsVetor(this->vetor, z), x)->itemP(y);
    }

    return NULL;
  }

  /*
   * CONFIGURA UMA CELULA PARA QUE APONTE PARA UM NOVO PONTEIRO
   * OU SEJA, DEFINE O NOVO VALOR DA CELULA
   * ESTA FUNCAO TENTA LIBERAR EVENTUAL CONTEUDO PREEXISTENTE NA CELULA
   *
   * @param {lint}                       z   coordenada z
   * @param {lint}                       x   coordenada x
   * @param {lint}                       y   coordenada y
   * @return {bool}                           true se sucesso
   */
  bool TVetor3D::setItem(lint z, lint x, lint y, void *p){
    if ((this->alocado()) && (p != NULL) && (z < this->Zsize()) && (x < this->Xsize()) && (y < this->Ysize())){
      return itemAsVetor(itemAsVetor(this->vetor, z), x)->setItem(y, p);
    }

    return false;
  }

  /*================================================
   * CALLBACK INTERMEDIARIOS
   *================================================*/

  bool freeZXItem(void **item, void *vetor = NULL){
    if ((item != NULL) && ((void *)*item != NULL)){
      delete (TVetor *)*item;
      *item = NULL;
      return true;
    }

    return false;
  }

  bool initSubXVetor(void **item, void *vetor = NULL){
    if (vetor != NULL){
      TVetor3D *v = (TVetor3D *) vetor;
      TVetor *i = new TVetor(v->getFreeItem(), v->getInitItem(), (void *)v);

      if (i != NULL){
        if (i->length(v->Xsize())){
          *item = (void *)i;
          return (*item != NULL);
        }
      }

      return false;
    }

    return  false;
  }

  bool initSubZVetor(void **item, void* vetor){
    TCallBackFreeInitVetorItem fd;
    TCallBackFreeInitVetorItem id;

    fd.p = freeZXItem;
    id.p = initSubXVetor;

    TVetor *i = new TVetor(fd, id, vetor);
    if (i != NULL){
      TVetor3D *v = (TVetor3D *) vetor;

      if ((v->Zsize() > 1) && (v->Zcount() > 0)){
        i->length(v->Xsize());
      }

      *item = (void *)i;
      return true;
    }

		return false;
  }

  /*================================================
   * ESPECIALIZACOES - CHAR
   *================================================*/

  bool iteam3DAsChar(TVetor3D *p, lint z, lint x, lint y, char **c){
    return p->item(z, x, y, (void **)c);
  }

  char *iteam3DAsChar(TVetor3D *p, lint z, lint x, lint y){
    return (char *) p->item(z, x, y);
  }

  bool set3DChar(TVetor3D *p, lint z, lint x, lint y, char c){
    char *cc = (char *) malloc(sizeof(char));

    if (cc != NULL){
      *cc = c;
      if(p->setItem(z, x, y, cc)){
        return true;
      }else{
        free(cc);
      }
    }

    return false;
  }
}
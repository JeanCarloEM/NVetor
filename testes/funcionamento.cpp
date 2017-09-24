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

#include <stdio.h>
#include "../lib/comum.h"
#include "../vetor/Vetor.h"
#include "../vetor/Vetor3D.h"
#include <math.h>
#include <time.h>
#include <chrono>


void testeSorteio(){
  for (int i = 0; i < 10; i++){
    printf("%d\n", NVetor::sortear(1, 10));
  }
};

/*
bool vetoresIntTesteFree(void **item, void *pai) {
  //debug("Liberando...");
  //printf("@@ %d\n", *(int *) *item);
  free(*item);
  *item = NULL;
  return true;
}

bool vetoresIntTesteInit(void **item, void *pai) {
  debug("Init...");
}
*/
void tVetor1DExibir(NVetor::TVetor *v) {
  printf("\nEXIBINDO...\n");
  printf(" - QTD..........: %ld\n", v->size());
  printf(" - Inicializados: %ld\n", v->count());

  for (int g = 0; g < v->size(); g++) {
    printf("%d = %d\n", g, *NVetor::iteamAsInt(v, g));
  }
}

/*
 * FAZ TESTE DE INSERCAO USANDO TANTO "pushInt", QUANTO "setItem"
 */
void tVetor1DInsert(NVetor::TVetor *v, int i, int resto) {
  int criar = NVetor::sortear(7, 1000);

  if ((i % 2) == resto) {
    for (int g = 0; g < criar; g++) {
      NVetor::pushInt(v, g * 10);
    }
  } else {
    NVetor::lint osize = v->size();
    NVetor::lint direct = NVetor::sortear(1, ((criar > osize) ? osize - 1 : criar));
    v->length(osize + (criar - direct));

    osize = v->size();
    NVetor::ulint initeds = v->count();
    int start = initeds - direct;
    start = (start < 0) ? 0 : start;

    for (int g = start; g < (start+criar); g++) {
      NVetor::setIntItem(v, g, g*100);
    }
  }
}

void tMassive1D(NVetor::TVetor *v) {
  int total = NVetor::sortear(100, 1000);
  int *k = NULL;

  printf("\n==================================================");
  printf("\n==================================================");
  printf("\n=============== 1D TESTE MASSIVO =================");
  printf("\n==================================================");
  printf("\n>>> TESTES: %d.", total);
  printf("\n==================================================\n\n");

  int resto = NVetor::aleatorio() % 2;
  int percent = (int) ((total - (total % 100)) / 100);

  for (int i = 0; i < total; i++) {
    //printf("A1\n");
    // OBTEM O TOPO DO ELEMENTO SEM EFETUAR REDUCAO
    NVetor::topInt(v, &k);

    // FAZ INSERCOES ALEATORIAS
    // FAZ TESTE DE INSERCAO USANDO TANTO "pushInt", QUANTO "setItem"
    tVetor1DInsert(v, i, resto);
    //printf("A1-2\n");
    // A CADA 5 INTERECOES, REALIZA UMA REORGANIZACAO DO VETOR
    if ((i % 5) == 0) {
      //printf("A1-2a\n");
      //printf("A1-2a\n");
      v->shuffle();
    }

    //printf("A1-3\n");
    //printf("A1-3\n");
    // A CADA 3 ITERACOES, UMA CONTINUA REMOCAO "POP" DO VETOR
    // DE ATEH A TODALIDADE DO VETOR
    if ((i % 3) == 0) {
      int m = NVetor::sortear((int) floor((int) (v->count()-(v->count() % 2)) / 2), v->count());
      int start = NVetor::sortear(0, v->count() - m);
      for (int t = start; t < m; t++) {
        k = NULL;
        if (NVetor::popInt(v, &k)){
          free(k);
        }
      }
    }
    //printf("A2\n");

    // ALTERA O TAMANHO DO VETOR DE ATEH DUAS VEZES O VALOR DO VETOR
    // ISSO GARANTE QUE HAJA TANTO REDUCOES, QUANTO INCREMENTO DO TAMANHO DO
    // VETOR COM ITENS NAO INICIALIZADOS, O QUE PERMITE VERIFICAR FALHA NO
    // TRATAMENTO DESTA CONDICAO
    // AO CONTRARIO DO QUE OCORRE COM "tVetor1DInsert", ONDE OS ITENS SEMPRE
    // SERAO INICIALIZADOS
    v->length(NVetor::sortear(1, 2 * v->size()));
    //v->length(NVetor::sortear(1, v->size()-1));
    //printf("A3\n");
    //printf("A3\n");
    if (i > 1) {
      if ((percent <= 1) || ((i % percent) == 0)) {
        printf("%d, ", i);
      } else {
        if ((percent > 1) && ((i % (percent * 10)) == 0)) {
          printf(".");
        } else {
          if ((percent > 1) && ((i % (percent * 100)) == 0)) {
            printf("|");
          }
        }
      }
    }
  }

  printf("\n\n##################################################");
  printf("\n##################################################\n\n");
}

/*
 */
void tVetor1D() {
  // garante o flush imetdiato do printf
  setbuf(stdout, NULL);

  auto global_start = std::chrono::steady_clock::now();

  int *k = NULL;

  /*
  NVetor::TCallBackFreeInitVetorItem fi;
  NVetor::TCallBackFreeInitVetorItem in;

  fi.p = &vetoresIntTesteFree;
  in.p = &vetoresIntTesteInit;
   * */
  NVetor::TVetor *v = new NVetor::TVetor(/*fi, in*/);

  printf("\nCRIANDO...\n");

  for (int i = 15; i < 20; i++) {
    NVetor::pushInt(v, i);
  }

  tVetor1DExibir(v);

  printf("\nPOP...\n");

  while (NVetor::popInt(v, &k)) {
    printf(" - %d, total = %d\n", *k, v->size());
    free(k);
  }

  printf("\nRECRIANDO...\n");

  for (int i = 15; i < 20; i++) {
    NVetor::pushInt(v, i);
  }

  printf("\nPOP...\n");

  NVetor::popInt(v, &k);
  printf(" - %d, total = %d\n", *k, v->size());
  free(k);

  printf("\nInserindo...\n");

  for (int i = 50; i < 60; i++) {
    NVetor::pushInt(v, i);
  }

  tVetor1DExibir(v);

  printf("\nSORTENDADO...\n");

  v->shuffle();

  tVetor1DExibir(v);

  printf("\nPOP...\n");

  NVetor::popInt(v, &k);
  printf(" - %d, total = %d\n", *k, v->size());
  free(k);

  printf("\ninserindo...\n");

  for (int i = 100; i < 125; i++) {
    NVetor::pushInt(v, i);
  }

  tVetor1DExibir(v);

  printf("\nAlterando valor...\n");

  NVetor::setIntItem(v, 5, 123456789);

  tVetor1DExibir(v);

  printf("\n\n");

  v->length(15);

  tMassive1D(v);

  delete v;

  std::chrono::duration<double> diff = std::chrono::steady_clock::now() - global_start;
  std::cout << "\n\tGlobal Lapso: \t" << diff.count() << " sec\n\n";
}


void fill1DVector(NVetor::TVetor *v, ulint i, ulint f){
  for (; i < f; i++){
    NVetor::setIntItem(v, i, i*10);
  }
}

void fill1DStdVector(std::vector<int> *v, ulint i, ulint f){
  for (; i < f; i++){
    (*v)[i] = i*10;
  }
}

double read1DVector(NVetor::TVetor *v){
  double r;
  for (int i = 0; i < v->count(); i++){
    r += *iteamAsInt(v, i) * 10;
  }

  return r;
}

double read1DStdVector(std::vector<int> *v){
  double r;
  for (int i = 0; i < v->size(); i++){
    r += (*v)[i] * 10;
  }

  return r;
}

void cronTVetor(){
  NVetor::TCallBackFreeInitVetorItem fi;
  NVetor::TCallBackFreeInitVetorItem in;

  //fi.p = &vetoresIntTesteFree;
  //in.p = &vetoresIntTesteInit;

  std::chrono::duration<double> cron_resize;
  auto cron_resize_start = std::chrono::steady_clock::now();

  std::chrono::duration<double> cron_read;
  auto cron_read_start = std::chrono::steady_clock::now();

  std::chrono::duration<double> cron_write;
  auto cron_red_write = std::chrono::steady_clock::now();

  std::cout << "\n\nTVETOR \n\n";

  // INICIANDO
  auto global_start = std::chrono::steady_clock::now();

  NVetor::TVetor *v = new NVetor::TVetor();

  int loops = 0;

  do{
    if (v->size() <= 0){
      v->length(50);
      fill1DVector(v, 0, 49);
    }

    // READ
    cron_read_start = std::chrono::steady_clock::now();
    read1DVector(v);
    cron_read += std::chrono::steady_clock::now() - cron_read_start;

    // RESIZE - MENOR
    cron_resize_start = std::chrono::steady_clock::now();
    v->length((int)((float)v->size() / (float)2));
    cron_resize += std::chrono::steady_clock::now() - cron_resize_start;

    // READ
    cron_read_start = std::chrono::steady_clock::now();
    read1DVector(v);
    cron_read += std::chrono::steady_clock::now() - cron_read_start;

    // RESIZE - MAIOR
    cron_resize_start = std::chrono::steady_clock::now();
    v->length(v->size()*4);
    cron_resize += std::chrono::steady_clock::now() - cron_resize_start;

    // WRITE
    cron_red_write = std::chrono::steady_clock::now();
    fill1DVector(v, 0, v->size()-1);
    cron_write += std::chrono::steady_clock::now() - cron_red_write;

    loops++;
  }while (v->size() < 100000);

  std::chrono::duration<double> diff = std::chrono::steady_clock::now() - global_start;

  std::cout << "\n\tTotal de Loops: " << loops;
  std::cout << "\n\tGlobal Lapso..: \t" << diff.count() << " sec\n\n";

  delete v;
}

void cronStdVector(){
  std::chrono::duration<double> cron_resize;
  auto cron_resize_start = std::chrono::steady_clock::now();

  std::chrono::duration<double> cron_read;
  auto cron_read_start = std::chrono::steady_clock::now();

  std::chrono::duration<double> cron_write;
  auto cron_red_write = std::chrono::steady_clock::now();

  // INICIANDO
  auto global_start = std::chrono::steady_clock::now();

  std::cout << "\n\nSTD::VECTOR \n\n";

  std::vector<int> *v = new std::vector<int>(0);

  int loops = 0;

  do{
    if (v->size() <= 0){
      v->resize(50);
      fill1DStdVector(v, 0, 49);
    }

    // READ
    cron_read_start = std::chrono::steady_clock::now();
    read1DStdVector(v);
    cron_read += std::chrono::steady_clock::now() - cron_read_start;

    // RESIZE - MENOR
    cron_resize_start = std::chrono::steady_clock::now();
    v->resize((int)((float)v->size() / (float)2));
    cron_resize += std::chrono::steady_clock::now() - cron_resize_start;

    // READ
    cron_read_start = std::chrono::steady_clock::now();
    read1DStdVector(v);
    cron_read += std::chrono::steady_clock::now() - cron_read_start;

    // RESIZE - MAIOR
    cron_resize_start = std::chrono::steady_clock::now();
    v->resize(v->size()*4);
    cron_resize += std::chrono::steady_clock::now() - cron_resize_start;

    // WRITE
    cron_red_write = std::chrono::steady_clock::now();
    fill1DStdVector(v, 0, v->size()-1);
    cron_write += std::chrono::steady_clock::now() - cron_red_write;

    loops++;
  }while (v->size() < 100000);

  std::chrono::duration<double> diff = std::chrono::steady_clock::now() - global_start;

  std::cout << "\n\tTotal de Loops: " << loops;
  std::cout << "\n\tGlobal Lapso..: \t" << diff.count() << " sec\n\n";

  delete v;
}

void VetorVSVector(){
  // garante o flush imetdiato do printf
  setbuf(stdout, NULL);

  cronTVetor();
  cronStdVector();
}


/*
 */
int print3d(NVetor::TVetor3D *p) {
  if (p != NULL) {
    NVetor::ulint x = p->Xsize(), y = p->Ysize(), z = p->Zsize(),
            za, xa, ya;

    printf("================================================================");

    printf("\nZ-size = %ld", z);
    printf("\nX-size = %ld", x);
    printf("\nY-size = %ld\n", y);

    NVetor::ulint zzz = p->Zcount();
    NVetor::ulint xxx = p->Xcount(0);
    NVetor::ulint yyy = p->Ycount(0);

    printf("\niZ-size = %ld", zzz);
    printf("\niX-size = %ld", xxx);
    printf("\niY-size = %ld", yyy);
    printf("\n----------------------------------------------------------------");

    for (za = 0; za < z; za++) {
      //printf("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Z [%ld|y=%ld] \n\n", za, y);
      printf("\n");

      for (ya = 0; ya < y; ya++) {
        //printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! LINE [%ld|x=%ld]\t", ya, x);
        printf("\n");

        for (xa = 0; xa < x; xa++) {
          char *c = ((char *) p->item(za, xa, ya));

          if (c != NULL) {
            printf("%c", *c);
          } else {
            printf("[CARACTER APONTADO INVALIDO | %ld/%ld]\n", xa, x - 1);
            return 1;
          }
        }
      }
    }

    printf("\n================================================================\n\n");
  }

  return 0;
}
/*
void stdVectorShuffle(){
  std::vector<int> v;

  for (int g = 0; g < 5; g++){
    v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    printf("\n\nORIGINAL:\n");
    for (int i = 0 ; i < v.size(); i++){
      printf("%d", v[i]);
    }

    shuffleVector(v);

    printf("\n\nSORTEADO:\n");
    for (int i = 0 ; i < v.size(); i++){
      printf("%d", v[i]);
    }

    printf("\n\n\n");
  }
}
*/
/*
 */
void encher3D(NVetor::TVetor3D *p, char start) {
  if (p != NULL) {
    NVetor::ulint x = p->Xsize(), y = p->Ysize(), z = p->Zsize(),
            za, xa, ya;

    //printf("\n");

    for (za = 0; za < z; za++) {
      //printf("ZA = %d\n", za);
      for (ya = 0; ya < y; ya++) {
        //printf("XA = %d\n", xa);
        for (xa = 0; xa < x; xa++) {
          //printf("YA = %d\n", ya);
          set3DChar(p, za, xa, ya, start++);
        }
      }
    }
  }
}

/*
 */
int teste3D() {
  setbuf(stdout, NULL);

  NVetor::TVetor3D *p = new NVetor::TVetor3D(2, 7, 5);

  encher3D(p, 33);
  print3d(p);

  int zs, xs, ys;

  for (int i = 0; i < 10; i++) {
    zs = NVetor::sortear(1, 3);
    xs = NVetor::sortear(3, 7);
    ys = NVetor::sortear(3, 7);

    printf("%d #############################################################\n", i);
    //printf("Andar: %d\n", zs);
    //printf("Cols.: %d\n", xs);
    //printf("Lins.: %d\n", ys);

    p->setSize(zs, xs, ys);
    encher3D(p, 33);
    print3d(p);
  }

  int total = NVetor::sortear(50, 200);
  int percent = (int) ((total - (total % 100)) / 100);

  printf("\n==================================================");
  printf("\n==================================================");
  printf("\n=============== 3D TESTE MASSIVO =================");
  printf("\n==================================================");
  printf("\n>>> TESTES: %d.", total);
  printf("\n==================================================\n\n");

  for (int i = 0; i < total; i++) {
    p->setSize(NVetor::sortear(1, 20), NVetor::sortear(1, 100), NVetor::sortear(1, 100));
    encher3D(p, 33);

    if (i > 1) {
      if ((percent <= 1) || ((i % percent) == 0)) {
        printf("%d, ", i);
      } else {
        if ((percent > 1) && ((i % (percent * 10)) == 0)) {
          printf(".");
        } else {
          if ((percent > 1) && ((i % (percent * 100)) == 0)) {
            printf("|");
          }
        }
      }
    }
  }

  printf("\n\n##################################################");
  printf("\n##################################################\n\n");

  delete p;
  return 0;
}
/*
void tMapa(){
  setbuf(stdout, NULL);

  clock_t tStart = clock();

  printf("\n\n\nCRIANDO...\n");
  Lab::TMapa *lmap = new Lab::TMapa(1, 11, 11, 4);
  printf("TERMINADO\n\n");
  printf("RunTime: %.4fs\n\n\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

  std::cout << lmap->toJson();

  printf("\n\n");

  delete lmap;
}
 * */
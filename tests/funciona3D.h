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

#pragma once

#ifndef FUNCIONAMENTO_CPP
#define FUNCIONAMENTO_CPP

#include "../src/comum.h"
#include "../src/Vetor.h"
#include "../src/Vetor3D.h"

#include <stdio.h>
#include <iostream>
#include <chrono>

namespace tests {
  /*
   *
  inline int print3d(NVetor::TVetor3D *p) {
          if (p != NULL) {
                  NVetor::lint x = p->Xsize(), y = p->Ysize(), z = p->Zsize(),
                                                  za, xa, ya;

                  printf("================================================================");

                  printf("\nZ-size = %lld", z);
                  printf("\nX-size = %lld", x);
                  printf("\nY-size = %lld\n", y);

                  NVetor::lint zzz = p->Zcount();
                  NVetor::lint xxx = p->Xcount(0);
                  NVetor::lint yyy = p->Ycount(0, 0);

                  printf("\niZ-size = %lld", zzz);
                  printf("\niX-size = %lld", xxx);
                  printf("\niY-size = %lld", yyy);
                  printf("\n----------------------------------------------------------------");

                  for (za = 0; za < z; za++) {
                          //printf("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Z [%lld|y=%lld] \n\n", za, y);
                          printf("\n");

                          for (ya = 0; ya < y; ya++) {
                                  //printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! LINE [%lld|x=%lld]\t", ya, x);
                                  printf("\n");

                                  for (xa = 0; xa < x; xa++) {
                                          char *c = ((char *) p->item(za, xa, ya));

                                          if (c != NULL) {
                                                  printf("%c", *c);
                                          } else {
                                                  printf("[CARACTER APONTADO INVALIDO | %lld/%lld]\n", xa, x - 1);
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
   *
  inline void encher3D(NVetor::TVetor3D *p, char start) {
          if (p != NULL) {
                  NVetor::lint x = p->Xsize(), y = p->Ysize(), z = p->Zsize(),
                                                  za, xa, ya;

                  //printf("\n");

                  for (za = 0; za < z; za++) {
                          //printf("ZA = %d\n", za);
                          for (ya = 0; ya < y; ya++) {
                                  //printf("XA = %d\n", xa);
                                  for (xa = 0; xa < x; xa++) {
                                          //printf("YA = %d\n", ya);
                                          // set3DChar(p, za, xa, ya, start++);
                                  }
                          }
                  }
          }
  }

  /*
   *
  inline int teste3D() {
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
   *
  inline void tMapa(){
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
*/
}
#endif /* FUNCIONAMENTO_CPP */
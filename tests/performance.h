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

#ifndef PERFORMANCE_CPP
#define PERFORMANCE_CPP

#include "../src/Vetor.h"

#include <chrono>
#include <math.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>

#include <vector>
#include <array>

#define __MASIVE__ 3

/* DEDFINE CORES PARA FACILITAR A VISUALIZAÇÃO */
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

namespace tests {

  typedef std::chrono::duration<double> cronom;

  typedef struct SItems {
    cronom tvetor,
    puro,
    vector;

    SItems() : tvetor(0), puro(0), vector(0) {
    }

  } TItems;

  typedef struct {
    TItems criacao,
    leitura,
    gravacao,
    destruicao;
  } TTestes;


  const long int __SIZE__ = 1000;
  long int MULT_EXAUSTIVE = 1;

  /*
   */
  inline void printItem(TItems *part) {
    printf("\n==================================================");
    std::cout << "\n\tTVetor....: " << std::fixed << std::setprecision(9) << part->tvetor.count() << " sec.";
    std::cout << "\n\tMatriz C..: " << std::fixed << std::setprecision(9) << part->puro.count() << " sec.";
    std::cout << "\n\tVector STL: " << std::fixed << std::setprecision(9) << part->vector.count() << " sec.";
    printf("\n==================================================\n");
  }

  /*
   *
   */
  inline void compareCreate(TItems *part, NVetor::TVetor **tvetor, int **puro, std::vector<int> **vector) {
    /*
     * TVetor
     */
    auto cron_start = std::chrono::steady_clock::now();

    *tvetor = new NVetor::TVetor();
    (*tvetor)->length(MULT_EXAUSTIVE);

    part->tvetor = std::chrono::steady_clock::now() - cron_start;

    /*
     * PURA
     */
    cron_start = std::chrono::steady_clock::now();

    *puro = (int *) malloc(sizeof (int) * MULT_EXAUSTIVE);

    part->puro = std::chrono::steady_clock::now() - cron_start;

    /*
     * VECTOR
     */
    cron_start = std::chrono::steady_clock::now();

    *vector = new std::vector<int>(MULT_EXAUSTIVE);

    part->vector = std::chrono::steady_clock::now() - cron_start;
  }

  /*
   *
   */
  inline void compareWrite(TItems *part, NVetor::TVetor *tvetor, int *puro, std::vector<int> *vector) {
    /*
     * TVetor
     */
    auto cron_start = std::chrono::steady_clock::now();

    for (int i = 0; i < MULT_EXAUSTIVE; i++) {
      NVetor::setIntItem(tvetor, i, i + 1);
    }

    part->tvetor = std::chrono::steady_clock::now() - cron_start;

    /*
     * PURO
     */
    cron_start = std::chrono::steady_clock::now();

    for (int i = 0; i < MULT_EXAUSTIVE; i++) {
      puro[i] = i + 1;
    }

    part->puro = std::chrono::steady_clock::now() - cron_start;

    /*
     * VECTOR
     */
    cron_start = std::chrono::steady_clock::now();

    for (int i = 0; i < MULT_EXAUSTIVE; i++) {
      (*vector)[i] = i + 1;
    }

    part->vector = std::chrono::steady_clock::now() - cron_start;
  }

  /*
   *
   */
  inline long long int compareRead(TItems *part, NVetor::TVetor *tvetor, int *puro, std::vector<int> *vector) {
    long long int r = 0;

    /*
     * TVetor
     */
    auto cron_start = std::chrono::steady_clock::now();

    for (int i = 0; i < MULT_EXAUSTIVE; i++) {
      r += *NVetor::iteamAsInt(tvetor, i) * 3;
    }

    part->tvetor = std::chrono::steady_clock::now() - cron_start;

    /*
     * PURO
     */
    cron_start = std::chrono::steady_clock::now();

    for (int i = 0; i < MULT_EXAUSTIVE; i++) {
      r += puro[i] * 3;
    }

    part->puro = std::chrono::steady_clock::now() - cron_start;

    /*
     * VECTOR
     */
    cron_start = std::chrono::steady_clock::now();

    for (int i = 0; i < MULT_EXAUSTIVE; i++) {
      r -= (*vector)[i] * 2;
    }

    part->vector = std::chrono::steady_clock::now() - cron_start;

    return r;
  }

  /*
   *
   */
  inline void compareFree(TItems *part, NVetor::TVetor **tvetor, int **puro, std::vector<int> **vector) {
    /*
     * TVetor
     */
    auto cron_start = std::chrono::steady_clock::now();

    delete *tvetor;

    part->tvetor = std::chrono::steady_clock::now() - cron_start;

    /*
     * PURA
     */
    cron_start = std::chrono::steady_clock::now();

    free(*puro);

    part->puro = std::chrono::steady_clock::now() - cron_start;

    /*
     * VECTOR
     */
    cron_start = std::chrono::steady_clock::now();

    delete *vector;

    part->vector = std::chrono::steady_clock::now() - cron_start;
  }

  /*
   */
  inline int decToInt(double v) {
    std::stringstream p;
    p << std::fixed << std::setprecision(9) << v;

    std::string pp = p.str().substr(2, 9);

    std::string::size_type sz;
    return std::stoi(pp, &sz);
  }

  /*
   */
  inline void MassivCSV(const char *filename) {
    TTestes T[__MASIVE__];

    /* TVetor */
    NVetor::TVetor *tvetor = NULL;

    /* ARRAY C */
    int *puro = NULL;

    /* STD::VECTOR */
    std::vector<int> *vector;

    for (int i = 0; i < __MASIVE__; i++) {
      compareCreate(&T[i].criacao, &tvetor, &puro, &vector);
      compareWrite(&T[i].gravacao, tvetor, puro, vector);
      compareRead(&T[i].leitura, tvetor, puro, vector);
      compareFree(&T[i].destruicao, &tvetor, &puro, &vector);
    }

    std::string str = "\n  ";
    TItems *item;

    std::stringstream p;
    for (int i = 0; i < __MASIVE__; i++) {
      p << ", " << std::setfill(' ') << std::setw(9) << std::to_string(i + 1);
    }

    str.append(p.str());

    for (int teste = 0; teste < 4; teste++) {
      char nome = (teste == 0) ? 'C' : (teste == 1) ? 'G' : (teste == 2) ? 'L' : 'D';

      for (int indice = 0; indice < 3; indice++) {
        str.append("\n");
        str.push_back(nome);
        str.append(std::to_string(indice + 1));

        for (int i = 0; i < __MASIVE__; i++) {
          switch (teste) {
            case 0:
              item = &T[i].criacao;
              break;

            case 1:
              item = &T[i].gravacao;
              break;

            case 2:
              item = &T[i].leitura;
              break;

            case 3:
              item = &T[i].destruicao;
              break;
          }

          /* NECESSARIO PRECISAO FRACIONAL DE 9 DIGITOS, POR ISSO NAO USA
           * OPERADOR '+'
           */
          std::stringstream part;
          part << ", " << std::setfill(' ') << std::setw(9) << decToInt(((indice == 0) ? item->puro : (indice == 1) ? item->tvetor : item->vector).count());

          str.append(part.str());
        }
      }
    }

    std::ofstream mapa(filename);
    mapa << str;

    std::cout << "\n\n==";
    for (int i = 0; i < __MASIVE__; i++) {
      std::cout << "==" << std::setfill('=') << std::setw(9) << "=";
    }

    std::cout << str;

    std::cout << "\n==";
    for (int i = 0; i < __MASIVE__; i++) {
      std::cout << "==" << std::setfill('=') << std::setw(9) << "=";
    }

    std::cout << "\n- Salvo em " << filename << ".\n\n";
  }

  /*
   */
  inline void compare(const char *filename, bool exautive, bool more, bool further) {
    // garante o flush imetdiato do printf
    setbuf(stdout, NULL);

    /* DEFINE O TAMAMNHO DOS VETORES */
    MULT_EXAUSTIVE = __SIZE__ * (exautive ? 100 : 1) * (exautive && more ? 10 : 1) * (exautive && more && further ? 10 : 1);

    /* TVetor */
    NVetor::TVetor *tvetor = NULL;

    /* ARRAY C */
    int *puro = NULL;

    /* STD::VECTOR */
    std::vector<int> *vector;

    /*
     * COMPARANDO
     */
    MassivCSV(filename);

    /* INFORMA O TAMANO DOS VETORES */
    printf("\n\nTAMAMNHO DOS VETORES: %d.\n\n", MULT_EXAUSTIVE);
  }
}

#endif /* PERFORMANCE_CPP */
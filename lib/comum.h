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

#ifndef COMUM_H
#define COMUM_H

#include "RNG/rng.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

#if (!defined(__WINDOWS__)) && (defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__))
#define __WINDOWS__
#elif defined(__GNUC__) || defined(linux)
#define __LINUX__
#endif

#if defined(__WINDOWS__)
  #define DLLEXPORT __declspec(dllexport) __stdcall
  #define DLLIMPORT __declspec(dllimport) __stdcall
  #elif defined(__LINUX__)
  #define DLLEXPORT __attribute__((visibility("default")))
  #define DLLIMPORT
#else
  #define DLLEXPORT
  #define DLLIMPORT
#endif

typedef unsigned long long int ulint;
typedef long long int lint;

namespace NVetor {
  int aleatorio();
  int sortear(int min, int max);
  void swapP(void **o, void **d);

  /*
   * CLASSE DE EXCECAO USADA PARA PRINTAR ERROS FORMATADOS
   * NO TERMINAL
   */
  struct VetException : public std::exception {
    const char *s, *f, *a;
    int l;

    VetException(const char *ff, int ll, const char *fi, const char *ss)
      : s(ss), f(ff), l(ll), a(fi)
    {}

    ~VetException() throw () {
    }

    unsigned int slen(const char *c) const;
    const char* what() const throw ();
  };
}

#if (defined(DLLVETOR) && defined(MAKEDLLVETOR)) || !defined(DLLVETOR)
#include "comum.c"
#endif

#endif /* COMUM_H */
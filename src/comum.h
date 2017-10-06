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

#ifndef COMUM_H
#define COMUM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER // VISUAL STUDIO
#endif

#include "RNG/rng.h"
#include <exception>

/* https://sourceforge.net/p/predef/wiki/OperatingSystems/ */
#ifdef DLLVETOR
  #if defined(__WINDOWS__) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__)
    #define DLLEXPORT __declspec(dllexport) __stdcall
    #define DLLIMPORT __declspec(dllimport) __stdcall
  #elif defined(__LINUX__)
    #define DLLEXPORT __attribute__((visibility("default")))
    #define DLLIMPORT
#endif

  #ifdef MAKEDLLVETOR
    #define DLLVETORIMEXPORT DLLEXPORT
  #else
    #define DLLVETORIMEXPORT DLLIMPORT
  #endif
#else
  #define DLLVETORIMEXPORT
#endif

namespace NVetor {
  typedef long long int lint;

  DLLVETORIMEXPORT int aleatorio();
  DLLVETORIMEXPORT int sortear(int min, int max);
  DLLVETORIMEXPORT void swapP(void **o, void **d);

  /*
   * CLASSE DE EXCECAO USADA PARA PRINTAR ERROS FORMATADOS
   * NO TERMINAL
   */
  struct VetException : public std::exception {
    const char *s, *f, *a;
    int l;

    DLLVETORIMEXPORT VetException(const char *ff, int ll, const char *fi, const char *ss)
    : s(ss), f(ff), l(ll), a(fi) {
    }

    DLLVETORIMEXPORT ~VetException() throw () {
    };

    DLLVETORIMEXPORT unsigned int slen(const char *c) const;
    DLLVETORIMEXPORT const char* what() const throw ();
  };
}


#endif /* COMUM_H */
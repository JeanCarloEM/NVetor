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

#include "comum.h"
#include <string.h>
#include <stdlib.h>

namespace NVetor {
  /*
   * RETORNA UM NUMERO PSEUDO-ALEATORIO
   * UTILIZA AS MELHORES PRATICAS
   */
  int aleatorio() {
    rng::tsc_seed seed;
    rng::rng128 gen(seed());
    return gen();
  }

  /*
   * SORTE ENTRE UMA VALOR MINIMO E MAXIMO, INCLUINDO OS MESMOS
   *
   * @param   int
   */
  int sortear(int min, int max) {
    if ((min < max) && (max > 0)) {
      if (max == min) return max;
      //printf("\nmin = %d\nmax = %d\ndivisor = %d\n\n", min, max, (max - min + 1));    ry{
      return min + (std::abs(aleatorio()) % (max - min + 1));
    } else {
      return 0;
    }
  }

  /*
   * TROCA O CONTEUDO (PONTEITO) PARA APONTAR PARA OUTRO
   * FAZ A TROCA DE PONTEIRO ENTRE PONTEIROS
   * 
   * @param {void**}  o     origem
   * @param {void**}  d     destino
   */
  void swapP(void **o, void **d) {
    if ((o != NULL) && (d != NULL) && ((*o != NULL) || (*d != NULL))) {
      void **tmp = (void **) malloc(sizeof (void *));

      if (tmp != NULL) {
        *tmp = *o;
        *o = *d;
        *d = *tmp;
        free(tmp);
      }
    }
  }

  /*
   * IMPLEMENTACAO DE EXCECAO PARA AVISO DE ERROS EM TELA
   */
  const char* VetException::what() const throw() {
    unsigned int size = slen(s) + slen(f) + /*slen(l) +*/ slen(a) + 10;
    char *text = (char *) malloc(size * sizeof (char));

    strcpy(text, "\n\n");
    strcat(text, s);
    strcat(text, " \n");
    strcat(text, a);
    //strcat(text, "', ");
    //strcat(text, l);
    strcat(text, "\n[::");
    strcat(text, f);
    strcat(text, "]\n\n");

    return text;
  }

  /*
   * IMPLEMENTACAO DE EXCECAO PARA AVISO DE ERROS EM TELA
   */
  unsigned int VetException::slen(const char *c) const {
    unsigned int r = 0;

    if (c != NULL) {
      while ((c[r] != EOF) && (c[r] != '\n') && (c[r] != '\0')) {
        r++;
      }
    }

    return r;
  }
};
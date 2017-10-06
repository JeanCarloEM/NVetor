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
 * =============================================================================
 *
 * g++ compile command: g++ -std=c++11 -O3 tests.cpp -o tests
 *
 */

#include "tests/performance.h"
#include "tests/funciona1D.h"
#include "tests/funciona3D.h"

/*
 *
 */
int main(int argc, char** argv) {
	// FAZ TESTES DE FUNCIONAMENTO DO VETOR
  tests::tVetor1D();

	// FAZ TESTE DE FUNCIONAMENTO DO VETOR 3D
  //tests::teste3D();

	// COMPARE VETOR, ARRAY E STD::VECTOR
  tests::compare((argc > 1) ? argv[1] : "saida.csv", (argc > 2) ? true : false, (argc > 3) ? true : false, (argc > 4) ? true : false);

	getchar();

  return 0;
}
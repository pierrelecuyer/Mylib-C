#include "gdef.h"
#include "mylib_utest.h"
#include "num_utest.h"
#include "num2_utest.h"
#include "bitvector_utest.h"
#include "bitmatrix_utest.h"
#include "rngstream_utest.h"
#include "bitset_utest.h"
#include <stdio.h>
#include <math.h>

#ifdef USE_GMP
#include <gmp.h>
#endif

void mylib_utest_testall() {
	num_utest_all();
	num2_utest_all();
	bitvector_utest_all();
	bitmatrix_utest_all();
	rngstream_utest_all();
	bitset_utest_all();
	printf("<------------------------->\n");
	printf("| All unit tests succeded.|\n");
	printf("<------------------------->\n");
}

int main(void) {
	mylib_utest_testall();
}

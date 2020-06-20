#include "gdef.h"
#include "unit.h"
#include "num_utest.h"
#include "num2_utest.h"
#include <stdio.h>
#include <math.h>

#ifdef USE_GMP
#include <gmp.h>
#endif

lebool compare(double n1, double n2) {
	if (fabs(n1-n2) < 0.00001)
		return TRUE;
	return FALSE;
}

void unit_all() {
	num_utest_all();
	num2_utest_all();
	printf("<------------------------->\n");
	printf("| All unit tests succeded.|\n");
	printf("<------------------------->\n");
}


// int main(void) {
//     unit_all();
// }

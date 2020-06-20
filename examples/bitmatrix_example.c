#include "bitmatrix.h"
#include  <stdio.h>

int main(void) {
	bitmatrix_matrix m1;
	bitmatrix_allocate(&m1,128,128,1);
	bitvector_canonical(&m1.rows[0][0],0);
	bitmatrix_display(&m1,1,128,128);

	int i,j;
	for (i=0; i<m1.r; i++) {
		for (j=0; j<m1.t; j++) {
			bitvector_canonical(&m1.rows[i][j],i);
		}
	}

	bitmatrix_matrix m2;
	bitmatrix_allocate(&m2,128,128,1);
	bitmatrix_display(&m2,1,128,128);
	bitmatrix_copypart(&m2,&m1,128,1);
	bitmatrix_display(&m2,1,128,128);

	bitmatrix_free(&m1);
	bitmatrix_free(&m2);
	bitmatrix_allocate(&m1,128,64,2);
	bitmatrix_allocate(&m2,128,64,2);

	for (i=0; i<m1.r/2; i++) {
		bitvector_canonical(&m1.rows[i][0],i);
	}
    for (i=m1.r/2; i<m1.r; i++) {
		bitvector_canonical(&m1.rows[i][1],i-m1.b);
	}
	bitmatrix_display(&m1,2,64,128);

    int col[] = {1};
    bitmatrix_copySpecial(&m2,&m1,128,col,2);
    bitmatrix_display(&m2,2,64,128);

    bitmatrix_free(&m1);
    bitmatrix_free(&m2);

    bitmatrix_allocate(&m1,64,64,2);
    bitmatrix_allocate(&m2,64,64,2);

    for (i=0; i<m1.r; i++) {
        for (j=0; j<m1.t; j++) {
            bitvector_canonical(&m1.rows[i][j],i);
        }
    }

    bitmatrix_transpose(&m2,&m1,64,2,64);
    bitmatrix_display(&m2,2,64,64);

    bitmatrix_exchangeRows(&m2,0,1);
    bitmatrix_display(&m2,2,64,64);

    bitmatrix_xorVect(&m2,1,2,0,2);
    bitmatrix_display(&m2,2,64,64);


    bitmatrix_free(&m2);
    bitmatrix_allocate(&m2,64,64,3);


    for (i=0; i<m2.r; i++) {
        for (j=0; j<m2.t; j++) {
            bitvector_canonical(&m2.rows[i][j],i);
        }
    }

    int gr;
    bitvector_clearVector(&m2.rows[5][1]);
    printf("%d\n",bitmatrix_diagonalize(&m2,64,3,64,&gr));
    printf("%d\n",gr);


	bitmatrix_free(&m2);
	bitmatrix_allocate(&m2,128,64,2);
	for (i=0; i<m2.r/2; i++) {
		bitvector_canonical(&m2.rows[i][0],i);
	}
	for (i=m2.r/2; i<m2.r; i++) {
		bitvector_canonical(&m2.rows[i][1],i-m2.b);
	}
	bitmatrix_display(&m2,2,64,128);

	bitvector_clearVector(&m2.rows[3][0]);
	printf("%d\n",bitmatrix_gaussianElimination(&m2,128,64,2));

	printf("%d\n",bitmatrix_completeElimination(&m2,128,64,2));

	bitmatrix_free(&m1);
	bitmatrix_free(&m2);
	bitmatrix_allocate(&m1,128,128,1);
	bitmatrix_allocate(&m2,128,128,1);

	for (i=0; i<m1.r; i++) {
		for (j=0; j<m1.t; j++) {
			bitvector_canonical(&m1.rows[i][j],i);
		}
	}
	bitmatrix_display(&m1,1,128,128);
	printf("%d",bitmatrix_inverse(&m2,&m1));
	bitmatrix_display(&m2,1,128,128);

	bitvector_vector v1;
	bitvector_vector v2;
	bitvector_allocate(&v1,128);
	bitvector_allocate(&v2,128);
	bitvector_canonical(&v1,3);
	bitvector_setBit(&m2.rows[0][0],3);

	bitmatrix_productByVector(&v2,&m2,&v1);
	bitvector_display(&v2,64);
	printf("\n");

	bitmatrix_matrix m3;
	bitmatrix_allocate(&m3,128,128,1);
	bitmatrix_product(&m3,&m2,&m1);

	bitmatrix_display(&m3,1,128,128);
	bitmatrix_matrix m4;
	bitmatrix_allocate(&m4,128,128,1);
	bitmatrix_powerOfTwo(&m4,&m3,1);
	bitmatrix_display(&m4,1,128,128);

	bitmatrix_matrix m5;
	bitmatrix_matrix m6;
	bitmatrix_allocate(&m5,32,32,1);
	bitmatrix_allocate(&m6,32,32,1);
	bitvector_setBit(&m5.rows[0][0],3);
	bitmatrix_display(&m5,1,32,32);
	bitmatrix_power(&m6,&m5,2);
	bitmatrix_display(&m6,1,32,32);

	return 0;
}

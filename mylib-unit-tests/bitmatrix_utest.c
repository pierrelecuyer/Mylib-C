#include "gdef.h"
#include "util.h"
#include "mylib_utest.h"
#include "bitmatrix.h"
#include <stdio.h>
#include <string.h>

void bitmatrix_utest_copypart() {
    printf("bitmatrix : Executing copypart unit tests.\n");

    bitmatrix_matrix m1;
    bitmatrix_matrix m2;
    bitmatrix_allocate(&m1,128,64,2);
    bitmatrix_allocate(&m2,128,64,2);

    int i,j;
    for (i=0; i<m2.r/2; i++) {
        bitvector_canonical(&m2.rows[i][0],i);
    }
    for (i=m2.r/2; i<m2.r; i++) {
        bitvector_canonical(&m2.rows[i][1],i-m2.b);
    }

    bitmatrix_copypart(&m1,&m2,128,2);
    assert_int(bitmatrix_weight(&m1),128);

    bitmatrix_free(&m1);
    bitmatrix_free(&m2);
}

void bitmatrix_utest_copySpecial() {
    printf("bitmatrix : Executing copySpecial unit tests.\n");

    bitmatrix_matrix m1;
    bitmatrix_matrix m2;
    bitmatrix_allocate(&m1,128,64,2);
    bitmatrix_allocate(&m2,128,64,2);

    int i,j;
    for (i=0; i<m2.r/2; i++) {
        bitvector_canonical(&m2.rows[i][0],i);
    }
    for (i=m2.r/2; i<m2.r; i++) {
        bitvector_canonical(&m2.rows[i][1],i-m2.b);
    }

    int col[] = {1};
    bitmatrix_copySpecial(&m1,&m2,128,col,2);
    assert_int(bitvector_getBit(&m1.rows[0][0],0),1);
    assert_int(bitvector_getBit(&m1.rows[127][1],63),1);
    assert_int(bitmatrix_weight(&m1),128);

    bitmatrix_free(&m1);
    bitmatrix_free(&m2);
}

void bitmatrix_utest_transpose() {
    printf("bitmatrix : Executing transpose unit tests.\n");

    bitmatrix_matrix m1;
    bitmatrix_matrix m2;
    bitmatrix_allocate(&m1,64,64,2);
    bitmatrix_allocate(&m2,64,64,2);
    bitvector_setBit(&m2.rows[4][0],0);
    bitvector_setBit(&m2.rows[5][1],63);

    bitmatrix_transpose(&m1,&m2,64,2,64);
    assert_int(bitvector_getBit(&m1.rows[0][0],4),1);
    assert_int(bitvector_getBit(&m1.rows[63][1],5),1);
    assert_int(bitmatrix_weight(&m1),2);

    bitmatrix_free(&m1);
    bitmatrix_free(&m2);
}

void bitmatrix_utest_exchangeRows() {
    printf("bitmatrix : Executing exchangeRows unit tests.\n");

    bitmatrix_matrix m1;
    bitmatrix_allocate(&m1,128,64,2);
    bitvector_setAllOnes(&m1.rows[0][0]);
    bitvector_setAllOnes(&m1.rows[0][1]);

    bitmatrix_exchangeRows(&m1,0,127);
    assert_int(bitmatrix_hammingWeight(&m1,127),128);
    assert_int(bitmatrix_hammingWeight(&m1,0),0);

    bitmatrix_free(&m1);
}

void bitmatrix_utest_xorVect() {
    printf("bitmatrix : Executing xorVect unit tests.\n");

    bitmatrix_matrix m1;
    bitmatrix_allocate(&m1,128,64,2);
    bitvector_setBit(&m1.rows[0][0],0);
    bitvector_setBit(&m1.rows[0][1],0);
    bitvector_setBit(&m1.rows[0][0],1);
    bitvector_setBit(&m1.rows[0][1],1);
    bitvector_setBit(&m1.rows[1][0],0);
    bitvector_setBit(&m1.rows[1][1],0);

    bitmatrix_xorVect(&m1,0,1,0,1);
    assert_int(bitvector_getBit(&m1.rows[0][0],0),0);
    assert_int(bitvector_getBit(&m1.rows[0][1],0),1);
    bitmatrix_xorVect(&m1,0,1,1,2);
    assert_int(bitvector_getBit(&m1.rows[0][0],0),0);
    assert_int(bitvector_getBit(&m1.rows[0][1],0),0);
    assert_int(bitmatrix_hammingWeight(&m1,0),2);

    bitmatrix_free(&m1);
}

void bitmatrix_utest_diagonalize() {
    printf("bitmatrix : Executing diagonalize unit tests.\n");

    bitmatrix_matrix m1;
    bitmatrix_allocate(&m1,128,64,2);

    int i;
    for (i=0; i<m1.r/2; i++) {
        bitvector_canonical(&m1.rows[i][0],i);
    }
    for (i=m1.r/2; i<m1.r; i++) {
        bitvector_canonical(&m1.rows[i][1],i-m1.b);
    }
    bitmatrix_exchangeRows(&m1,0,63);

    int gr = 2;
    assert_int(bitmatrix_diagonalize(&m1,128,2,64,&gr),1);
    assert_int(gr,2);
    bitvector_clearBit(&m1.rows[64][1],0);
    assert_int(bitmatrix_diagonalize(&m1,128,2,64,&gr),0);
    assert_int(gr,1);

    bitmatrix_free(&m1);
}

void bitmatrix_utest_gaussianElimination() {
    printf("bitmatrix : Executing gaussianElimination unit tests.\n");

    bitmatrix_matrix m1;
    bitmatrix_allocate(&m1,128,64,2);

    int i;
    for (i=0; i<m1.r/2; i++) {
        bitvector_canonical(&m1.rows[i][0],i);
    }
    for (i=m1.r/2; i<m1.r; i++) {
        bitvector_canonical(&m1.rows[i][1],i-m1.b);
    }

    assert_int(bitmatrix_gaussianElimination(&m1,128,64,2),128);
    bitvector_clearBit(&m1.rows[64][1],0);
    assert_int(bitmatrix_gaussianElimination(&m1,128,64,2),127);

    bitmatrix_free(&m1);
}

void bitmatrix_utest_specialGaussianElimination() {
    printf("bitmatrix : Executing specialGaussianElimination unit tests.\n");

    bitmatrix_matrix m1;
    bitmatrix_allocate(&m1,128,64,2);

    int i;
    for (i=0; i<m1.r/2; i++) {
        bitvector_canonical(&m1.rows[i][0],i);
    }
    for (i=m1.r/2; i<m1.r; i++) {
        bitvector_canonical(&m1.rows[i][1],i-m1.b);
    }

    int indices[] = {0,1};

    assert_int(bitmatrix_specialGaussianElimination(&m1,128,64,2,indices),128);
    bitvector_clearBit(&m1.rows[0][0],0);
    assert_int(bitmatrix_specialGaussianElimination(&m1,128,64,1,indices),63);

    bitmatrix_free(&m1);
}


void bitmatrix_utest_completeElimination() {
    printf("bitmatrix : Executing completeElimination unit tests.\n");

    bitmatrix_matrix m1;
    bitmatrix_allocate(&m1,128,64,2);

    int i;
    for (i=0; i<m1.r/2; i++) {
        bitvector_canonical(&m1.rows[i][0],i);
    }
    for (i=m1.r/2; i<m1.r; i++) {
        bitvector_canonical(&m1.rows[i][1],i-m1.b);
    }

    assert_int(bitmatrix_completeElimination(&m1,128,64,2),128);
    bitvector_clearBit(&m1.rows[0][0],0);
    assert_int(bitmatrix_completeElimination(&m1,128,64,2),0);

    bitmatrix_free(&m1);
}

void bitmatrix_utest_inverse() {
    printf("bitmatrix : Executing inverse unit tests.\n");

    bitmatrix_matrix m1;
    bitmatrix_matrix m2;
    bitmatrix_allocate(&m1,64,64,1);
    bitmatrix_allocate(&m2,64,64,1);

    int i;
    for (i=0; i<m1.r; i++) {
        bitvector_canonical(&m1.rows[i][0],i);
    }
    bitmatrix_exchangeRows(&m1,0,63);

    assert_int(bitmatrix_inverse(&m2,&m1),1);
    assert_int(bitvector_getBit(&m2.rows[0][0],63),1);
    assert_int(bitvector_getBit(&m2.rows[63][0],0),1);
    bitvector_clearVector(&m1.rows[0][0]);
    assert_int(bitmatrix_inverse(&m2,&m1),0);

    bitmatrix_free(&m1);
    bitmatrix_free(&m2);
}


void bitmatrix_utest_productByVector() {
    printf("bitmatrix : Executing productByVector unit tests.\n");

    bitmatrix_matrix m1;
    bitmatrix_allocate(&m1,64,64,1);

    int i;
    for (i=0; i<m1.r; i++) {
        bitvector_canonical(&m1.rows[i][0],i);
    }

    bitvector_vector v1;
    bitvector_vector v2;
    bitvector_allocate(&v1,64);
    bitvector_allocate(&v2,64);
    bitvector_canonical(&v1,3);

    bitmatrix_productByVector(&v2,&m1,&v1);
    assert_int(bitvector_getBit(&v2,3),1);
    assert_int(bitvector_hammingWeight(&v2),1);
    bitvector_clearVector(&m1.rows[3][0]);
    bitmatrix_productByVector(&v2,&m1,&v1);
    assert_int(bitvector_getBit(&v2,3),0);
    assert_int(bitvector_hammingWeight(&v2),0);

    bitmatrix_free(&m1);
}

void bitmatrix_utest_product() {
    printf("bitmatrix : Executing product unit tests.\n");

    bitmatrix_matrix m1;
    bitmatrix_matrix m2;
    bitmatrix_matrix m3;
    bitmatrix_allocate(&m1,64,64,1);
    bitmatrix_allocate(&m2,64,64,1);
    bitmatrix_allocate(&m3,64,64,1);

    int i;
    for (i=0; i<m1.r; i++) {
        bitvector_canonical(&m1.rows[i][0],i);
        bitvector_canonical(&m2.rows[i][0],i);
    }

    bitvector_setBit(&m1.rows[0][0],3);
    bitmatrix_product(&m3,&m2,&m1);
    assert_int(bitvector_getBit(&m3.rows[0][0],3),1);
    assert_int(bitmatrix_weight(&m3),65);
    bitvector_clearVector(&m1.rows[0][0]);
    bitmatrix_product(&m3,&m2,&m1);
    assert_int(bitvector_getBit(&m3.rows[0][0],0),0);
    assert_int(bitvector_getBit(&m3.rows[0][0],3),0);
    assert_int(bitmatrix_weight(&m3),63);

    bitmatrix_free(&m1);
    bitmatrix_free(&m2);
    bitmatrix_free(&m3);
}

void bitmatrix_utest_power() {
    printf("bitmatrix : Executing power unit tests.\n");

    bitmatrix_matrix m1;
    bitmatrix_matrix m2;
    bitmatrix_allocate(&m1,64,64,1);
    bitmatrix_allocate(&m2,64,64,1);

    int i;
    for (i=0; i<m1.r; i++) {
        bitvector_canonical(&m1.rows[i][0],i);
    }
    bitvector_setBit(&m1.rows[0][0],3);

    bitmatrix_power(&m2,&m1,0);
    assert_int(bitvector_getBit(&m2.rows[0][0],3),0);
    assert_int(bitmatrix_weight(&m2),64);
    bitmatrix_power(&m2,&m1,1);
    assert_int(bitvector_getBit(&m2.rows[0][0],3),1);
    assert_int(bitmatrix_weight(&m2),65);
    bitmatrix_power(&m2,&m1,2);
    assert_int(bitvector_getBit(&m2.rows[0][0],3),0);
    assert_int(bitmatrix_weight(&m2),64);
    bitmatrix_power(&m2,&m1,-1);
    assert_int(bitvector_getBit(&m2.rows[0][0],3),1);
    assert_int(bitmatrix_weight(&m2),65);


    bitmatrix_free(&m1);
    bitmatrix_free(&m2);
}

void bitmatrix_utest_powerOfTwo() {
    printf("bitmatrix : Executing powerOfTwo unit tests.\n");

    bitmatrix_matrix m1;
    bitmatrix_matrix m2;
    bitmatrix_allocate(&m1,64,64,1);
    bitmatrix_allocate(&m2,64,64,1);

    int i;
    for (i=0; i<m1.r; i++) {
        bitvector_canonical(&m1.rows[i][0],i);
    }
    bitvector_setBit(&m1.rows[0][0],3);

    bitmatrix_powerOfTwo(&m2,&m1,0);
    assert_int(bitvector_getBit(&m2.rows[0][0],3),1);
    assert_int(bitmatrix_weight(&m2),65);
    bitmatrix_powerOfTwo(&m2,&m1,1);
    assert_int(bitvector_getBit(&m2.rows[0][0],3),0);
    assert_int(bitmatrix_weight(&m2),64);

    bitmatrix_free(&m1);
    bitmatrix_free(&m2);
}


void bitmatrix_utest_all() {
    printf("bitmatrix : Executing all unit tests.\n");

    bitmatrix_utest_copypart();
    bitmatrix_utest_copySpecial();
    bitmatrix_utest_transpose();
    bitmatrix_utest_exchangeRows();
    bitmatrix_utest_xorVect();
    bitmatrix_utest_diagonalize();
    bitmatrix_utest_gaussianElimination();
    bitmatrix_utest_specialGaussianElimination();
    bitmatrix_utest_completeElimination();
    bitmatrix_utest_inverse();
    bitmatrix_utest_productByVector();
    bitmatrix_utest_product();
    bitmatrix_utest_power();
    bitmatrix_utest_powerOfTwo();

    printf("bitmatrix : all unit tests succeeded.\n");
}

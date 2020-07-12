#include "gdef.h"
#include "util.h"
#include "mylib_utest.h"
#include "bitvector.h"
#include <stdio.h>
#include <string.h>

void bitvector_utest_copy() {
    printf("bitvector : Executing copy unit tests.\n");

    bitvector_vector v1;
    bitvector_vector v2;
    bitvector_allocate(&v1,64);
    bitvector_allocate(&v2,64);
    bitvector_setBit(&v2,0);
    bitvector_setBit(&v2,31);
    bitvector_setBit(&v2,63);

    bitvector_copy(&v1,&v2);
    assert_int(bitvector_getBit(&v1,0),1);
    assert_int(bitvector_getBit(&v1,31),1);
    assert_int(bitvector_getBit(&v1,63),1);
    assert_int(bitvector_hammingWeight(&v1),3);

    bitvector_free(&v1);
    bitvector_free(&v2);
}

void bitvector_utest_copyPart() {
    printf("bitvector : Executing copyPart unit tests.\n");

    bitvector_vector v1;
    bitvector_vector v2;
    bitvector_allocate(&v1,64);
    bitvector_allocate(&v2,64);
    bitvector_setBit(&v2,0);
    bitvector_setBit(&v2,31);
    bitvector_setBit(&v2,63);

    bitvector_copyPart(&v1,&v2,1);
    assert_int(bitvector_getBit(&v1,0),1);
    assert_int(bitvector_hammingWeight(&v1),1);
    bitvector_copyPart(&v1,&v2,32);
    assert_int(bitvector_getBit(&v1,0),1);
    assert_int(bitvector_getBit(&v1,31),1);
    assert_int(bitvector_hammingWeight(&v1),2);
    bitvector_copyPart(&v1,&v2,64);
    assert_int(bitvector_getBit(&v1,0),1);
    assert_int(bitvector_getBit(&v1,31),1);
    assert_int(bitvector_getBit(&v1,63),1);
    assert_int(bitvector_hammingWeight(&v1),3);

    bitvector_free(&v1);
    bitvector_free(&v2);
}

void bitvector_utest_clearVector() {
    printf("bitvector : Executing clearVector unit tests.\n");

    bitvector_vector v1;
    bitvector_allocate(&v1,64);
    bitvector_setBit(&v1,0);
    bitvector_setBit(&v1,31);
    bitvector_setBit(&v1,63);

    bitvector_clearVector(&v1);
    assert_int(bitvector_hammingWeight(&v1),0);

    bitvector_free(&v1);
}

void bitvector_utest_clearBit() {
    printf("bitvector : Executing clearBit unit tests.\n");

    bitvector_vector v1;
    bitvector_allocate(&v1,64);
    bitvector_setBit(&v1,0);
    bitvector_setBit(&v1,31);
    bitvector_setBit(&v1,63);

    bitvector_clearBit(&v1,0);
    bitvector_clearBit(&v1,31);
    bitvector_clearBit(&v1,63);
    assert_int(bitvector_getBit(&v1,0),0);
    assert_int(bitvector_getBit(&v1,31),0);
    assert_int(bitvector_getBit(&v1,63),0);
    assert_int(bitvector_hammingWeight(&v1),0);

    bitvector_free(&v1);
}

void bitvector_utest_canonical() {
    printf("bitvector : Executing canonical unit tests.\n");

    bitvector_vector v1;
    bitvector_allocate(&v1,64);

    bitvector_canonical(&v1,0);
    assert_int(bitvector_getBit(&v1,0),1);
    assert_int(bitvector_hammingWeight(&v1),1);
    bitvector_canonical(&v1,63);
    assert_int(bitvector_getBit(&v1,63),1);
    assert_int(bitvector_hammingWeight(&v1),1);

    bitvector_free(&v1);
}

void bitvector_utest_setAllOnes() {
    printf("bitvector : Executing setAllOnes unit tests.\n");

    bitvector_vector v1;
    bitvector_allocate(&v1,64);

    bitvector_setAllOnes(&v1);
    assert_int(bitvector_hammingWeight(&v1),64);

    bitvector_free(&v1);
}

void bitvector_utest_isZero() {
    printf("bitvector : Executing isZero unit tests.\n");

    bitvector_vector v1;
    bitvector_allocate(&v1,64);

    bitvector_setAllOnes(&v1);
    assert_int(bitvector_isZero(&v1),0);
    bitvector_clearVector(&v1);
    assert_int(bitvector_isZero(&v1),1);
    bitvector_setBit(&v1,31);
    assert_int(bitvector_isZero(&v1),0);

    bitvector_free(&v1);
}

void bitvector_utest_areEqual() {
    printf("bitvector : Executing areEqual unit tests.\n");

    bitvector_vector v1;
    bitvector_vector v2;
    bitvector_allocate(&v1,64);
    bitvector_allocate(&v2,64);

    bitvector_setBit(&v1,0);
    bitvector_setBit(&v1,31);
    bitvector_setBit(&v1,63);
    assert_int(bitvector_areEqual(&v1,&v2),0);

    bitvector_setBit(&v2,0);
    bitvector_setBit(&v2,31);
    bitvector_setBit(&v2,63);
    assert_int(bitvector_areEqual(&v1,&v2),1);

    bitvector_free(&v1);
    bitvector_free(&v2);
}

void bitvector_utest_haveCommonBit() {
    printf("bitvector : Executing haveCommonBit unit tests.\n");

    bitvector_vector v1;
    bitvector_vector v2;
    bitvector_allocate(&v1,64);
    bitvector_allocate(&v2,64);

    bitvector_setBit(&v1,0);
    bitvector_setBit(&v1,31);
    bitvector_setBit(&v1,63);
    assert_int(bitvector_haveCommonBit(&v1,&v2),0);

    bitvector_setBit(&v2,31);
    assert_int(bitvector_haveCommonBit(&v1,&v2),1);

    bitvector_free(&v1);
    bitvector_free(&v2);
}

void bitvector_utest_xor() {
    printf("bitvector : Executing xor unit tests.\n");

    bitvector_vector v1;
    bitvector_vector v2;
    bitvector_vector v3;
    bitvector_allocate(&v1,64);
    bitvector_allocate(&v2,64);
    bitvector_allocate(&v3,64);
    bitvector_setBit(&v3,0);
    bitvector_setBit(&v3,31);
    bitvector_setBit(&v3,63);
    bitvector_setBit(&v2,31);

    bitvector_xor(&v1,&v2,&v3);
    assert_int(bitvector_getBit(&v1,0),1);
    assert_int(bitvector_getBit(&v1,31),0)
    assert_int(bitvector_getBit(&v1,63),1)
    assert_int(bitvector_hammingWeight(&v1),2);

    bitvector_free(&v1);
    bitvector_free(&v2);
    bitvector_free(&v3);
}

void bitvector_utest_xor3() {
    printf("bitvector : Executing xor3 unit tests.\n");

    bitvector_vector v1;
    bitvector_vector v2;
    bitvector_vector v3;
    bitvector_vector v4;
    bitvector_allocate(&v1,64);
    bitvector_allocate(&v2,64);
    bitvector_allocate(&v3,64);
    bitvector_allocate(&v4,64);
    bitvector_setBit(&v4,63);
    bitvector_setBit(&v3,0);
    bitvector_setBit(&v3,31);
    bitvector_setBit(&v3,63);
    bitvector_setBit(&v2,31);

    bitvector_xor3(&v1,&v2,&v3,&v4);
    assert_int(bitvector_getBit(&v1,0),1);
    assert_int(bitvector_getBit(&v1,31),0)
    assert_int(bitvector_getBit(&v1,63),0)
    assert_int(bitvector_hammingWeight(&v1),1);

    bitvector_free(&v1);
    bitvector_free(&v2);
    bitvector_free(&v3);
    bitvector_free(&v4);
}

void bitvector_utest_xorSelf() {
    printf("bitvector : Executing xorSelf unit tests.\n");

    bitvector_vector v1;
    bitvector_vector v2;
    bitvector_allocate(&v1,64);
    bitvector_allocate(&v2,64);
    bitvector_setBit(&v2,0);
    bitvector_setBit(&v2,31);
    bitvector_setBit(&v2,63);
    bitvector_setBit(&v1,31);

    bitvector_xorSelf(&v1,&v2);
    assert_int(bitvector_getBit(&v1,0),1);
    assert_int(bitvector_getBit(&v1,31),0)
    assert_int(bitvector_getBit(&v1,63),1)
    assert_int(bitvector_hammingWeight(&v1),2);

    bitvector_free(&v1);
    bitvector_free(&v2);
}

void bitvector_utest_and() {
    printf("bitvector : Executing and unit tests.\n");

    bitvector_vector v1;
    bitvector_vector v2;
    bitvector_vector v3;
    bitvector_allocate(&v1,64);
    bitvector_allocate(&v2,64);
    bitvector_allocate(&v3,64);
    bitvector_setBit(&v3,0);
    bitvector_setBit(&v3,31);
    bitvector_setBit(&v3,63);
    bitvector_setBit(&v2,31);

    bitvector_and(&v1,&v2,&v3);
    assert_int(bitvector_getBit(&v1,0),0);
    assert_int(bitvector_getBit(&v1,31),1)
    assert_int(bitvector_getBit(&v1,63),0)
    assert_int(bitvector_hammingWeight(&v1),1);

    bitvector_free(&v1);
    bitvector_free(&v2);
    bitvector_free(&v3);
}

void bitvector_utest_andSelf() {
    printf("bitvector : Executing andSelf unit tests.\n");

    bitvector_vector v1;
    bitvector_vector v2;
    bitvector_allocate(&v1,64);
    bitvector_allocate(&v2,64);
    bitvector_setBit(&v2,0);
    bitvector_setBit(&v2,31);
    bitvector_setBit(&v2,63);
    bitvector_setBit(&v1,31);

    bitvector_andSelf(&v1,&v2);
    assert_int(bitvector_getBit(&v1,0),0);
    assert_int(bitvector_getBit(&v1,31),1)
    assert_int(bitvector_getBit(&v1,63),0)
    assert_int(bitvector_hammingWeight(&v1),1);

    bitvector_free(&v1);
    bitvector_free(&v2);
}

void bitvector_utest_andMaskLow() {
    printf("bitvector : Executing andMaskLow unit tests.\n");

    bitvector_vector v1;
    bitvector_vector v2;
    bitvector_allocate(&v1,64);
    bitvector_allocate(&v2,64);
    bitvector_setBit(&v2,0);
    bitvector_setBit(&v2,31);
    bitvector_setBit(&v2,63);

    bitvector_andMaskLow(&v1,&v2,32);
    assert_int(bitvector_getBit(&v1,0),1);
    assert_int(bitvector_getBit(&v1,31),1);
    assert_int(bitvector_hammingWeight(&v1),2);

    bitvector_andMaskLow(&v1,&v2,64);
    assert_int(bitvector_getBit(&v1,0),1);
    assert_int(bitvector_getBit(&v1,31),1)
    assert_int(bitvector_getBit(&v1,63),1)
    assert_int(bitvector_hammingWeight(&v1),3);

    bitvector_free(&v1);
    bitvector_free(&v2);
}

void bitvector_utest_andInvMaskLow() {
    printf("bitvector : Executing andInvMaskLow unit tests.\n");

    bitvector_vector v1;
    bitvector_vector v2;
    bitvector_allocate(&v1,64);
    bitvector_allocate(&v2,64);
    bitvector_setBit(&v2,0);
    bitvector_setBit(&v2,31);
    bitvector_setBit(&v2,63);

    bitvector_andInvMaskLow(&v1,&v2,32);
    assert_int(bitvector_getBit(&v1,0),0);
    assert_int(bitvector_getBit(&v1,31),0);
    assert_int(bitvector_getBit(&v1,63),1);
    assert_int(bitvector_hammingWeight(&v1),1);

    bitvector_andInvMaskLow(&v1,&v2,64);
    assert_int(bitvector_hammingWeight(&v1),0);

    bitvector_free(&v1);
    bitvector_free(&v2);
}

void bitvector_utest_leftShift() {
    printf("bitvector : Executing leftShift unit tests.\n");

    bitvector_vector v1;
    bitvector_vector v2;
    bitvector_allocate(&v1,64);
    bitvector_allocate(&v2,64);
    bitvector_setBit(&v2,0);
    bitvector_setBit(&v2,31);
    bitvector_setBit(&v2,63);

    bitvector_leftShift(&v1,&v2,31);
    assert_int(bitvector_getBit(&v1,0),1);
    assert_int(bitvector_getBit(&v1,32),1)
    assert_int(bitvector_getBit(&v1,63),0)
    assert_int(bitvector_hammingWeight(&v1),2);

    bitvector_free(&v1);
    bitvector_free(&v2);
}

void bitvector_utest_rightShift() {
    printf("bitvector : Executing rightShift unit tests.\n");

    bitvector_vector v1;
    bitvector_vector v2;
    bitvector_allocate(&v1,64);
    bitvector_allocate(&v2,64);
    bitvector_setBit(&v2,0);
    bitvector_setBit(&v2,31);
    bitvector_setBit(&v2,63);

    bitvector_rightShift(&v1,&v2,32);
    assert_int(bitvector_getBit(&v1,0),0);
    assert_int(bitvector_getBit(&v1,32),1)
    assert_int(bitvector_getBit(&v1,63),1)
    assert_int(bitvector_hammingWeight(&v1),2);

    bitvector_free(&v1);
    bitvector_free(&v2);
}


void bitvector_utest_leftShiftSelf() {
    printf("bitvector : Executing leftShiftSelf unit tests.\n");

    bitvector_vector v1;
    bitvector_allocate(&v1,64);
    bitvector_setBit(&v1,0);
    bitvector_setBit(&v1,31);
    bitvector_setBit(&v1,63);

    bitvector_leftShiftSelf(&v1,31);
    assert_int(bitvector_getBit(&v1,0),1);
    assert_int(bitvector_getBit(&v1,32),1)
    assert_int(bitvector_getBit(&v1,63),0)
    assert_int(bitvector_hammingWeight(&v1),2);

    bitvector_free(&v1);
}

void bitvector_utest_rightShiftSelf() {
    printf("bitvector : Executing rightShiftSelf unit tests.\n");

    bitvector_vector v1;
    bitvector_allocate(&v1,64);
    bitvector_setBit(&v1,0);
    bitvector_setBit(&v1,31);
    bitvector_setBit(&v1,63);

    bitvector_rightShiftSelf(&v1,32);
    assert_int(bitvector_getBit(&v1,0),0);
    assert_int(bitvector_getBit(&v1,32),1)
    assert_int(bitvector_getBit(&v1,63),1)
    assert_int(bitvector_hammingWeight(&v1),2);

    bitvector_free(&v1);
}

void bitvector_utest_flip() {
    printf("bitvector : Executing flip unit tests.\n");

    bitvector_vector v1;
    bitvector_allocate(&v1,64);
    bitvector_setBit(&v1,0);
    bitvector_setBit(&v1,31);
    bitvector_setBit(&v1,63);

    bitvector_flip(&v1);
    assert_int(bitvector_getBit(&v1,0),0);
    assert_int(bitvector_getBit(&v1,31),0);
    assert_int(bitvector_getBit(&v1,63),0);
    assert_int(bitvector_hammingWeight(&v1),61);

    bitvector_free(&v1);
}

void bitvector_utest_setMaskLow() {
    printf("bitvector : Executing setMaskLow unit tests.\n");

    bitvector_vector v1;
    bitvector_allocate(&v1,64);

    bitvector_setMaskLow(&v1,1);
    assert_int(bitvector_getBit(&v1,0),1);
    assert_int(bitvector_hammingWeight(&v1),1);
    bitvector_setMaskLow(&v1,32);
    assert_int(bitvector_getBit(&v1,31),1);
    assert_int(bitvector_hammingWeight(&v1),32);
    bitvector_setMaskLow(&v1,64);
    assert_int(bitvector_getBit(&v1,63),1);
    assert_int(bitvector_hammingWeight(&v1),64);

    bitvector_free(&v1);
}

void bitvector_utest_setInvMaskLow() {
    printf("bitvector : Executing setInvMaskLow unit tests.\n");

    bitvector_vector v1;
    bitvector_allocate(&v1,64);

    bitvector_setInvMaskLow(&v1,1);
    assert_int(bitvector_getBit(&v1,0),0);
    assert_int(bitvector_hammingWeight(&v1),63);
    bitvector_setInvMaskLow(&v1,32);
    assert_int(bitvector_getBit(&v1,31),0);
    assert_int(bitvector_hammingWeight(&v1),32);
    bitvector_setInvMaskLow(&v1,64);
    assert_int(bitvector_getBit(&v1,63),0);
    assert_int(bitvector_hammingWeight(&v1),0);

    bitvector_free(&v1);
}

void bitvector_utest_all() {
    printf("bitvector : Executing all unit tests.\n");

    bitvector_utest_copy();
    bitvector_utest_copyPart();
    bitvector_utest_clearVector();
    bitvector_utest_clearBit();
    bitvector_utest_canonical();
    bitvector_utest_setAllOnes();
    bitvector_utest_isZero();
    bitvector_utest_areEqual();
    bitvector_utest_haveCommonBit();
    bitvector_utest_xor();
    bitvector_utest_xor3();
    bitvector_utest_xorSelf();
    bitvector_utest_and();
    bitvector_utest_andSelf();
    bitvector_utest_andMaskLow();
    bitvector_utest_andInvMaskLow();
    bitvector_utest_leftShift();
    bitvector_utest_rightShift();
    bitvector_utest_leftShiftSelf();
    bitvector_utest_rightShiftSelf();
    bitvector_utest_flip();
    bitvector_utest_setMaskLow();
    bitvector_utest_setInvMaskLow();

    printf("bitvector : all unit tests succeeded.\n");
}

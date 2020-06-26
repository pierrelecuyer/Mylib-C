#include "gdef.h"
#include "util.h"
#include "unit.h"
#include "bitvector.h"
#include <stdio.h>
#include <string.h>

void bitvector_utest_copy() {
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

    printf("bitvector : copy unit tests succeeded.\n");
}

void bitvector_utest_copyPart() {
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

    printf("bitvector : copyPart unit tests succeeded.\n");
}

void bitvector_utest_clearVector() {
    bitvector_vector v1;
    bitvector_allocate(&v1,64);
    bitvector_setBit(&v1,0);
    bitvector_setBit(&v1,31);
    bitvector_setBit(&v1,63);

    bitvector_clearVector(&v1);
    assert_int(bitvector_hammingWeight(&v1),0);

    bitvector_free(&v1);

    printf("bitvector : clearVector unit tests succeeded.\n");
}

void bitvector_utest_clearBit() {
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

    printf("bitvector : clearBit unit tests succeeded.\n");
}

void bitvector_utest_canonical() {
    bitvector_vector v1;
    bitvector_allocate(&v1,64);

    bitvector_canonical(&v1,0);
    assert_int(bitvector_getBit(&v1,0),1);
    assert_int(bitvector_hammingWeight(&v1),1);
    bitvector_canonical(&v1,63);
    assert_int(bitvector_getBit(&v1,63),1);
    assert_int(bitvector_hammingWeight(&v1),1);

    bitvector_free(&v1);

    printf("bitvector : canonical unit tests succeeded.\n");
}

void bitvector_utest_setAllOnes() {
    bitvector_vector v1;
    bitvector_allocate(&v1,64);

    bitvector_setAllOnes(&v1);
    assert_int(bitvector_hammingWeight(&v1),64);

    bitvector_free(&v1);

    printf("bitvector : setAllOnes unit tests succeeded.\n");
}

void bitvector_utest_isZero() {
    bitvector_vector v1;
    bitvector_allocate(&v1,64);

    bitvector_setAllOnes(&v1);
    assert_int(bitvector_isZero(&v1),0);
    bitvector_clearVector(&v1);
    assert_int(bitvector_isZero(&v1),1);
    bitvector_setBit(&v1,31);
    assert_int(bitvector_isZero(&v1),0);

    bitvector_free(&v1);

    printf("bitvector : isZero unit tests succeeded.\n");
}

void bitvector_utest_areEqual() {
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

    printf("bitvector : areEqual unit tests succeeded.\n");
}

void bitvector_utest_haveCommonBit() {
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

    printf("bitvector : haveCommonBit unit tests succeeded.\n");
}

void bitvector_utest_xor() {
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

    printf("bitvector : xor unit tests succeeded.\n");
}

void bitvector_utest_xor3() {
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

    printf("bitvector : xor3 unit tests succeeded.\n");
}

void bitvector_utest_xorSelf() {
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

    printf("bitvector : xorSelf unit tests succeeded.\n");
}

void bitvector_utest_and() {
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

    printf("bitvector : and unit tests succeeded.\n");
}

void bitvector_utest_andSelf() {
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

    printf("bitvector : andSelf unit tests succeeded.\n");
}

void bitvector_utest_andMaskLow() {
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

    printf("bitvector : andMaskLow unit tests succeeded.\n");
}

void bitvector_utest_andInvMaskLow() {
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

    printf("bitvector : andInvMaskLow unit tests succeeded.\n");
}

void bitvector_utest_leftShift() {
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

    printf("bitvector : leftShift unit tests succeeded.\n");
}

void bitvector_utest_rightShift() {
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

    printf("bitvector : rightShift unit tests succeeded.\n");
}


void bitvector_utest_leftShiftSelf() {
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

    printf("bitvector : leftShiftSelf unit tests succeeded.\n");
}

void bitvector_utest_rightShiftSelf() {
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

    printf("bitvector : rightShiftSelf unit tests succeeded.\n");
}

void bitvector_utest_flip() {
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

    printf("bitvector : flip unit tests succeeded.\n");
}

void bitvector_utest_setMaskLow() {
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

    printf("bitvector : setMaskLow unit tests succeeded.\n");
}

void bitvector_utest_setInvMaskLow() {
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

    printf("bitvector : setInvMaskLow unit tests succeeded.\n");
}

void bitvector_utest_all() {
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


int main(void) {
    bitvector_utest_all();
    return 0;
}

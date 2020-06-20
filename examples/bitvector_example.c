#include "bitvector.h"
#include  <stdio.h>
int main(void) {
    bitvector_vector bv;
    bitvector_allocate(&bv, 64);

    bitvector_clearVector(&bv);
    bitvector_display(&bv,64);
    printf("\n");


    bitvector_setBit(&bv,0);
    bitvector_setBit(&bv,63);
    bitvector_display(&bv,64);
    printf("\n");


    bitvector_clearBit(&bv,63);
    bitvector_display(&bv,64);
    printf("\n");


    printf("%d\n",bitvector_getBit(&bv,1));

    bitvector_canonical(&bv,1);
    bitvector_display(&bv,64);
    printf("\n");


    bitvector_setAllOnes(&bv);
    bitvector_display(&bv,64);
    printf("\n");


    printf("%d\n",bitvector_isZero(&bv));
    bitvector_clearVector(&bv);
    printf("%d\n",bitvector_isZero(&bv));
    printf("\n");


    bitvector_free(&bv);

    bitvector_vector v1;
    bitvector_vector v2;
    bitvector_allocate(&v1,64);
    bitvector_allocate(&v2,64);

    bitvector_setBit(&v1,63);
    bitvector_clearVector(&v2);
    printf("%d\n",bitvector_areEqual(&v1,&v2));
    bitvector_setBit(&v2,63);
    printf("%d\n",bitvector_areEqual(&v1,&v2));
    printf("\n");


    bitvector_setBit(&v1,0);
    printf("%d\n",bitvector_haveCommonBit(&v1,&v2));
    bitvector_clearVector(&v1);
    printf("%d\n",bitvector_haveCommonBit(&v1,&v2));
    printf("\n");


    bitvector_vector v3;
    bitvector_allocate(&v3,64);

    bitvector_display(&v1,64);
    bitvector_display(&v2,64);
    bitvector_xor(&v3,&v2,&v1);
    bitvector_display(&v3,64);
    printf("\n");


    bitvector_vector v4;
    bitvector_allocate(&v4,64);

    bitvector_display(&v1,64);
    bitvector_display(&v2,64);
    bitvector_display(&v3,64);
    bitvector_xor3(&v4,&v3,&v2,&v1);
    bitvector_display(&v4,64);
    printf("\n");


    bitvector_display(&v1,64);
    bitvector_display(&v2,64);
    bitvector_xorSelf(&v1,&v2);
    bitvector_display(&v1,64);
    printf("\n");

    bitvector_setBit(&v1,0);
    bitvector_setBit(&v2,1);

    bitvector_display(&v1,64);
    bitvector_display(&v2,64);
    bitvector_and(&v3,&v2,&v1);
    bitvector_display(&v3,64);
    printf("\n");

    bitvector_display(&v1,64);
    bitvector_display(&v2,64);
    bitvector_andSelf(&v1,&v2);
    bitvector_display(&v1,64);
    printf("\n");


    bitvector_display(&v2,64);
    bitvector_andMaskLow(&v1,&v2,2);
    bitvector_display(&v1,64);
    printf("\n");

    bitvector_display(&v2,64);
    bitvector_andInvMaskLow(&v1,&v2,2);
    bitvector_display(&v1,64);
    printf("\n");

    bitvector_display(&v1,64);
    bitvector_leftShift(&v1,&v1,6);
    bitvector_display(&v1,64);
    printf("\n");

    bitvector_display(&v1,64);
    bitvector_rightShift(&v1,&v1,6);
    bitvector_display(&v1,64);
    printf("\n");

    bitvector_display(&v1,64);
    bitvector_leftShiftSelf(&v1,6);
    bitvector_display(&v1,64);
    printf("\n");

    bitvector_display(&v1,64);
    bitvector_leftShift1Self(&v1);
    bitvector_display(&v1,64);
    printf("\n");

    bitvector_display(&v1,64);
    bitvector_rightShiftSelf(&v1,7);
    bitvector_display(&v1,64);
    printf("\n");

    bitvector_setInvMaskLow(&v1,32);
    bitvector_display(&v1,64);
    bitvector_flip(&v1);
    bitvector_display(&v1,64);
    bitvector_setMaskLow(&v1,32);
    bitvector_display(&v1,64);
    printf("\n");

    bitvector_clearVector(&v2);

    bitvector_display(&v1,64);
    bitvector_copyPart(&v2,&v1,3);
    bitvector_display(&v2,64);

    bitvector_free(&v1);
    bitvector_free(&v2);
    bitvector_free(&v3);
    bitvector_free(&v4);

    return 0;
}

#include "gdef.h"
#include "util.h"
#include "mylib_utest.h"
#include "rngstream.h"
#include <stdio.h>
#include <string.h>

void rngstream_utest_RandU01() {
    rngstream g = rngstream_CreateStream();
    rngstream_RandU01(g);

    int i;
    double sum = 0;
    for (i=0; i<1000; i++) {
        sum += rngstream_RandU01(g);
    }

    assert_double(sum,490.925484);
    rngstream_DeleteStream(&g);
    printf("rngstream : RandU01 unit tests succeeded.\n");
}

void rngstream_utest_RandInt() {
    rngstream g = rngstream_CreateStream();
    rngstream_RandU01(g);

    int i;
    int sum = 0;
    for (i=0; i<1000; i++) {
        sum += rngstream_RandInt(g,0,10);
    }

    assert_int(sum,5052);
    rngstream_DeleteStream(&g);
    printf("rngstream : RandInt unit tests succeeded.\n");
}

void rngstream_utest_SetSeed() {
    rngstream g = rngstream_CreateStream();
    int64_t seed[6] = {12344, 12344, 12344, 12344, 12344, 12344};
    rngstream_SetSeed(g,seed);

    int i;
    for (i=0; i<6; i++) {
        assert_int64_t(g->Cg[i],12344);
    }
    rngstream_DeleteStream(&g);

    printf("rngstream : SetSeed unit tests succeeded.\n");
}

void rngstream_utest_SetPackageSeed() {
    int64_t seed[6] = {12346, 12346, 12346, 12346, 12346, 12346};
    rngstream_SetPackageSeed(seed);
    rngstream g = rngstream_CreateStream();

    int i;
    for (i=0; i<6; i++) {
        assert_int64_t(g->Cg[i],12346);
    }
    rngstream_DeleteStream(&g);

    printf("rngstream : SetPackageSeed unit tests succeeded.\n");
}

void rngstream_utest_all() {
    rngstream_utest_RandU01();
    rngstream_utest_RandInt();
    rngstream_utest_SetSeed();
    rngstream_utest_SetPackageSeed();

    printf("rngstream : all unit tests succeeded.\n");
}

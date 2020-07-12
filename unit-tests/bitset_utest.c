#include "gdef.h"
#include "util.h"
#include "mylib_utest.h"
#include "bitset.h"
#include <stdio.h>
#include <string.h>

void bitset_utest_ReverseOrderSimple() {
    assert_uint64_t(bitset_ReverseOrderSimple(1,64), 0x8000000000000000ULL);
    assert_uint64_t(bitset_ReverseOrderSimple(1,32), 0x80000000ULL);
    assert_uint64_t(bitset_ReverseOrderSimple(0x8000000000000000ULL,64), 1);
    assert_uint64_t(bitset_ReverseOrderSimple(0x80000000ULL,32), 1);
    assert_uint64_t(bitset_ReverseOrderSimple(0xAAAAAAAAAAAAAAAAULL,64), 0x5555555555555555ULL);
    assert_uint64_t(bitset_ReverseOrderSimple(0xAAAAAAAAULL,32), 0x55555555ULL);
    assert_uint64_t(bitset_ReverseOrderSimple(0x5555555555555555ULL,64), 0xAAAAAAAAAAAAAAAAULL);
    assert_uint64_t(bitset_ReverseOrderSimple(0x55555555ULL,32), 0xAAAAAAAAULL);
    assert_uint64_t(bitset_ReverseOrderSimple(6142,13),4093);
    assert_uint64_t(bitset_ReverseOrderSimple(4093,13),6142);
    assert_uint64_t(bitset_ReverseOrderSimple(39742763864745,46),41035504462089);
    assert_uint64_t(bitset_ReverseOrderSimple(41035504462089,46),39742763864745);

    printf("bitset : ReverseOrderSimple unit tests succeeded.\n");
}

void bitset_utest_ReverseOrder() {
    assert_uint64_t(bitset_ReverseOrder(1,64), 0x8000000000000000ULL);
    assert_uint64_t(bitset_ReverseOrder(1,32), 0x80000000ULL);
    assert_uint64_t(bitset_ReverseOrder(0x8000000000000000ULL,64), 1);
    assert_uint64_t(bitset_ReverseOrder(0x80000000ULL,32), 1);
    assert_uint64_t(bitset_ReverseOrder(0xAAAAAAAAAAAAAAAAULL,64), 0x5555555555555555ULL);
    assert_uint64_t(bitset_ReverseOrder(0xAAAAAAAAULL,32), 0x55555555ULL);
    assert_uint64_t(bitset_ReverseOrder(0x5555555555555555ULL,64), 0xAAAAAAAAAAAAAAAAULL);
    assert_uint64_t(bitset_ReverseOrder(0x55555555ULL,32), 0xAAAAAAAAULL);
    assert_uint64_t(bitset_ReverseOrder(6142,13),4093);
    assert_uint64_t(bitset_ReverseOrder(4093,13),6142);
    assert_uint64_t(bitset_ReverseOrder(39742763864745,46),41035504462089);
    assert_uint64_t(bitset_ReverseOrder(41035504462089,46),39742763864745);

    printf("bitset : ReverseOrder unit tests succeeded.\n");
}

void bitset_utest_all() {
    bitset_utest_ReverseOrderSimple();
    bitset_utest_ReverseOrder();

    printf("bitset : all unit tests succeeded.\n");
}

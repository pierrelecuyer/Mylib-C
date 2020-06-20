#include "gdef.h"
#include "util.h"
#include "unit.h"
#include "num.h"
#include <stdio.h>
#include <string.h>

void num_utest_Round64() {
    assert_int64_t(num_Round64(0.0005),0);
    assert_int64_t(num_Round64(0.5),1);
    assert_int64_t(num_Round64(10.3),10);

    printf("num : Round64 unit tests succeeded.\n");
}

void num_utest_RoundD() {
    assert_double(num_RoundD(0.0005),0);
    assert_double(num_RoundD(0.5),1);
    assert_double(num_RoundD(10.3),10);

    printf("num : RoundD unit tests succeeded.\n");
}

void num_utest_IsNumber() {
    assert_double(num_IsNumber("+ 2"),TRUE);
    assert_double(num_IsNumber("-+ 2"),FALSE);
    assert_double(num_IsNumber("4hello"),TRUE);
    assert_double(num_IsNumber("hello"),FALSE);

    printf("num : IsNumber unit tests succeeded.\n");
}

void num_utest_IntToStrBase() {
    char *S;
    num_IntToStrBase(40,2,S);
    assert_str(S,"101000");
    num_IntToStrBase(40,3,S);
    assert_str(S,"1111");
    num_IntToStrBase(150,9,S);
    assert_str(S,"176");

    printf("num : IntToStrBase unit tests succeeded.\n");
}

void num_utest_MultMod() {
    assert_int64_t(num_MultMod(32342234,333,32434,92842034),320412);
    assert_int64_t(num_MultMod(-23432423,4434,223,2432422344),694797433);
    assert_int64_t(num_MultMod(9223372036854775807,5,3,9223372036854775807),3);

    printf("num : MultMod unit tests succeeded.\n");
}

void num_utest_MultModDouble() {
    assert_double(num_MultModDouble(32342234,333,32434,92842034),320412);
    assert_double(num_MultModDouble(-23432423,4434,223,2432422344),694797433);
    assert_double(num_MultModDouble(1503599627370496,5,3,1503599627370496),3);

    printf("num : MultModDouble unit tests succeeded.\n");
}

void num_utest_InvEuclid() {
    assert_int64_t(num_InvEuclid(26,3),9);
    assert_int64_t(num_InvEuclid(1503599627370496,-23432423),154074406631721);
    assert_int64_t(num_InvEuclid(1503599627370496,34543543),1238010685519367);
    assert_int64_t(num_InvEuclid(10,2),0);

    printf("num : InvEuclid unit tests succeeded.\n");
}

void num_utest_InvExpon() {
    assert_int64_t(num_InvExpon(8,9),57);
    assert_int64_t(num_InvExpon(32,-32423423),3472014849);
    assert_int64_t(num_InvExpon(51,32423423),1849366495969791);
    assert_int64_t(num_InvExpon(3,6),0);

    printf("num : InvExpon unit tests succeeded.\n");
}

void num_utest_all() {
    num_utest_Round64();
    num_utest_RoundD();
    num_utest_IsNumber();
    num_utest_IntToStrBase();
    num_utest_MultMod();
    num_utest_MultModDouble();
    num_utest_InvEuclid();
    num_utest_InvExpon();
    printf("num : all unit tests succeeded.\n");
}

int main(void) {
    num_utest_all();
    return 0;
}

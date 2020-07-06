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
	char S[80];
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

void num_utest_MultModDirect() {
	assert_double(num_MultModDirect(32342234,333,32434,92842034),320412);
	assert_double(num_MultModDirect(-23432423,4434,223,2432422344),694797433);
	assert_double(num_MultModDirect(1503599627370496,5,3,1503599627370496),3);

	printf("num : MultModDirect unit tests succeeded.\n");
}

void num_utest_InvEuclid() {
	assert_int64_t(num_InvEuclid(26,3),9);
	assert_int64_t(num_InvEuclid(1503599627370496,-23432423),154074406631721);
	assert_int64_t(num_InvEuclid(1503599627370496,34543543),1238010685519367);

	printf("num : InvEuclid unit tests succeeded.\n");
}

void num_utest_InvEuclid32() {
	assert_int64_t(num_InvEuclid32(26,3),9);
	assert_int64_t(num_InvEuclid32(1503599627370496,-23432423),154074406631721);
	assert_int64_t(num_InvEuclid32(1503599627370496,34543543),1238010685519367);

	printf("num : InvEuclid32 unit tests succeeded.\n");
}

void num_utest_InvExpon() {
	assert_int64_t(num_InvExpon(8,9),57);
	assert_int64_t(num_InvExpon(32,-32423423),3472014849);
	assert_int64_t(num_InvExpon(51,32423423),1849366495969791);

	printf("num : InvExpon unit tests succeeded.\n");
}

void num_utest_InvExpon32() {
	assert_int64_t(num_InvExpon32(8,9),57);
	assert_int64_t(num_InvExpon32(32,-32423423),3472014849);
	assert_int64_t(num_InvExpon32(51,32423423),1849366495969791);

	printf("num : InvExpon32 unit tests succeeded.\n");
}

void num_utest_gcd() {
    assert_uint64_t(num_gcd(270,192),6);
    assert_uint64_t(num_gcd(68,119),17);
    assert_uint64_t(num_gcd(1785,546),21);

	printf("num : gcd unit tests succeeded.\n");
}

void num_utest_gcd32() {
    assert_uint64_t(num_gcd32(270,192),6);
    assert_uint64_t(num_gcd32(68,119),17);
    assert_uint64_t(num_gcd32(1785,546),21);

	printf("num : gcd32 unit tests succeeded.\n");
}

void num_utest_isMersennePrime() {
    assert_int(num_isMersennePrime(107),TRUE);
    assert_int(num_isMersennePrime(110503),TRUE);
    assert_int(num_isMersennePrime(64),FALSE);

	printf("num : isMersennePrime unit tests succeeded.\n");
}

void num_utest_all() {
	num_utest_Round64();
	num_utest_RoundD();
	num_utest_IsNumber();
	num_utest_IntToStrBase();
	num_utest_MultMod();
	num_utest_MultModDouble();
    num_utest_MultModDirect();
	num_utest_InvEuclid();
    num_utest_InvEuclid32();
	num_utest_InvExpon();
    num_utest_InvExpon32();
    num_utest_gcd();
    num_utest_gcd32();
    num_utest_isMersennePrime();

	printf("num : all unit tests succeeded.\n");
}

#include "gdef.h"
#include "util.h"
#include "mylib_utest.h"
#include "num.h"
#include <stdio.h>
#include <string.h>

void num_utest_Round64() {
	printf("num : Executing Round64 unit tests.\n");
	assert_int64_t(num_Round64(0.0005),0);
	assert_int64_t(num_Round64(0.5),1);
	assert_int64_t(num_Round64(10.3),10);
}

void num_utest_RoundD() {
	printf("num : Executing RoundD unit tests.\n");
	assert_double(num_RoundD(0.0005),0);
	assert_double(num_RoundD(0.5),1);
	assert_double(num_RoundD(10.3),10);
}

void num_utest_IsNumber() {
	printf("num : Executing IsNumber unit tests.\n");
	assert_double(num_IsNumber("+ 2"),TRUE);
	assert_double(num_IsNumber("-+ 2"),FALSE);
	assert_double(num_IsNumber("4hello"),TRUE);
	assert_double(num_IsNumber("hello"),FALSE);
}

void num_utest_IntToStrBase() {
	printf("num : Executing IntToStrBase unit tests.\n");
	char S[80];
	num_IntToStrBase(40,2,S);
	assert_str(S,"101000");
	num_IntToStrBase(40,3,S);
	assert_str(S,"1111");
	num_IntToStrBase(150,9,S);
	assert_str(S,"176");
}

void num_utest_MultMod() {
	printf("num : Executing MultMod unit tests.\n");
	assert_int64_t(num_MultMod(32342234,333,32434,92842034),320412);
	assert_int64_t(num_MultMod(-23432423,4434,223,2432422344),694797433);
	assert_int64_t(num_MultMod(9223372036854775807,5,3,9223372036854775807),3);
}

void num_utest_MultModDouble() {
	printf("num : Executing MultModDouble unit tests.\n");
	assert_double(num_MultModDouble(32342234,333,32434,92842034),320412);
	assert_double(num_MultModDouble(-23432423,4434,223,2432422344),694797433);
	assert_double(num_MultModDouble(1503599627370496,5,3,1503599627370496),3);
}

void num_utest_MultModDirect() {
	printf("num : Executing MultModDirect unit tests.\n");
	assert_double(num_MultModDirect(32342234,333,32434,92842034),320412);
	assert_double(num_MultModDirect(-23432423,4434,223,2432422344),694797433);
	assert_double(num_MultModDirect(1503599627370496,5,3,1503599627370496),3);
}

void num_utest_InvEuclid() {
	printf("num : Executing InvEuclid unit tests.\n");
	assert_int64_t(num_InvEuclid(26,3),9);
	assert_int64_t(num_InvEuclid(1503599627370496,-23432423),154074406631721);
	assert_int64_t(num_InvEuclid(1503599627370496,34543543),1238010685519367);
}

void num_utest_InvEuclid32() {
	printf("num : Executing InvEuclid32 unit tests.\n");
	assert_int64_t(num_InvEuclid32(26,3),9);
	assert_int64_t(num_InvEuclid32(1503599627370496,-23432423),154074406631721);
	assert_int64_t(num_InvEuclid32(1503599627370496,34543543),1238010685519367);
}

void num_utest_InvExpon() {
	printf("num : Executing InvExpon unit tests.\n");
	assert_int64_t(num_InvExpon(8,9),57);
	assert_int64_t(num_InvExpon(32,-32423423),3472014849);
	assert_int64_t(num_InvExpon(51,32423423),1849366495969791);
}

void num_utest_InvExpon32() {
	printf("num : Executing InvExpon32 unit tests.\n");
	assert_int64_t(num_InvExpon32(8,9),57);
	assert_int64_t(num_InvExpon32(32,-32423423),3472014849);
	assert_int64_t(num_InvExpon32(51,32423423),1849366495969791);
}

void num_utest_gcd() {
	printf("num : Executing gcd unit tests.\n");
	assert_uint64_t(num_gcd(270,192),6);
	assert_uint64_t(num_gcd(68,119),17);
	assert_uint64_t(num_gcd(1785,546),21);
}

void num_utest_gcd32() {
	printf("num : Executing gcd32 unit tests.\n");
	assert_uint64_t(num_gcd32(270,192),6);
	assert_uint64_t(num_gcd32(68,119),17);
	assert_uint64_t(num_gcd32(1785,546),21);
}

void num_utest_isMersennePrime() {
	printf("num : Executing isMersennePrime unit tests.\n");
	assert_int(num_isMersennePrime(107),TRUE);
	assert_int(num_isMersennePrime(110503),TRUE);
	assert_int(num_isMersennePrime(64),FALSE);
}

void num_utest_all() {
	printf("num : Executing all unit tests.\n");
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

#include "gdef.h"
#include "util.h"
#include "unit.h"
#include "num.h"
#include "num2.h"
#include <stdio.h>
#include <string.h>


void num2_utest_LnFactorial() {
    assert_double(num2_LnFactorial(85),295.76660135076);
    assert_double(num2_LnFactorial(100),363.73937555556);
    assert_double(num2_LnFactorial(113),424.47819341826);
    printf("num2 : LnFactorial unit tests succeeded.\n");

}

void num2_utest_LnGamma() {
    assert_double(num2_LnGamma(0.00005),9.903458693809000468393);
    assert_double(num2_LnGamma(0.5),0.5723649429247000870717);
    assert_double(num2_LnGamma(18),33.50507345013688888401);
    assert_double(num2_LnGamma(50),144.5657439463448860089);
    assert_double(num2_LnGamma(113),419.7508055995447340991);
    printf("num2 : LnGamma unit tests succeeded.\n");
}

void num2_utest_Combination() {
    assert_double(num2_Combination(0,0),1);
    assert_double(num2_Combination(10,0),1);
    assert_double(num2_Combination(24,12),2704156);
    assert_double(num2_Combination(74,60),456002537343216);
    printf("num2 : Combination unit tests succeeded.\n");
}

void num2_utest_log1p() {
    assert_double(num2_log1p(0),0);
    assert_double(num2_log1p(-0.5),0.6931471805599453);
    assert_double(num2_log1p(0.5),0.4054651081081644);
    assert_double(num2_log1p(100),4.61512051684126);
    printf("num2 : log1p unit tests succeeded.\n");
}

void num2_utest_CalcMatStirling() {
    double **M;
    num2_CalcMatStirling(&M, 9, 9);
    double matStirlingSum[] = {1,1,2,5,15,52,203,877,4140,21147};
    double matStirlingSum_utest[10];
    int i,j;
    double k;

    for (i=0; i<=9; i++) {
        k=0;
        for (j=0; j<=i; j++) {
            k=k+M[j][i];
        }
        matStirlingSum_utest[i]=k;
    }

    assert_double(matStirlingSum[0],matStirlingSum_utest[0]);
    assert_double(matStirlingSum[1],matStirlingSum_utest[1]);
    assert_double(matStirlingSum[2],matStirlingSum_utest[2]);
    assert_double(matStirlingSum[3],matStirlingSum_utest[3]);
    assert_double(matStirlingSum[4],matStirlingSum_utest[4]);
    assert_double(matStirlingSum[5],matStirlingSum_utest[5]);
    assert_double(matStirlingSum[6],matStirlingSum_utest[6]);
    assert_double(matStirlingSum[7],matStirlingSum_utest[7]);
    assert_double(matStirlingSum[8],matStirlingSum_utest[8]);
    assert_double(matStirlingSum[9],matStirlingSum_utest[9]);

    num2_FreeMatStirling(&M,9);

    printf("num2 : CalcMatStirling unit tests succeeded.\n");
}

void num2_utest_VolumeSphere() {
    assert_double(num2_VolumeSphere(2,3),4.188790204786390984);
    assert_double(num2_VolumeSphere(3,3),5.696583541509835167);
    assert_double(num2_VolumeSphere(1000,3),7.99996059844262270);
    assert_double(num2_VolumeSphere(2,10),2.550164039877345443);
    assert_double(num2_VolumeSphere(3,10),35.651609488062913386);
    assert_double(num2_VolumeSphere(1000,10),1023.924607665882446014);

    printf("num2 : VolumeSphere unit tests succeeded.\n");
}

void num2_utest_BesselK025() {
    assert_double(num2_BesselK025(1),0.4307397744485855246569);
    assert_double(num2_BesselK025(0.5),0.960316324931886022947);
    assert_double(num2_BesselK025(0.00005),25.463633449667459958);

    printf("num2 : BesselK025 unit tests succeeded.\n");
}

void num2_utest_Digamma() {
    assert_double(num2_Digamma(10),2.251752589066721107647);
    assert_double(num2_Digamma(2),0.4227843350984671393935);
    assert_double(num2_Digamma(0.3),-3.502524222200132988964);
    assert_double(num2_Digamma(0.0005),-2000.576393498247108909);

    printf("num2 : Digamma unit tests succeeded.\n");
}

void num2_utest_all() {
    num2_utest_LnFactorial();
    num2_utest_LnGamma();
    num2_utest_Combination();
    num2_utest_CalcMatStirling();
    num2_utest_VolumeSphere();
    num2_utest_BesselK025();
    num2_utest_Digamma();

    printf("num2 : all unit tests succeeded.\n");
}

int main(void) {
    num2_utest_all();
    return 0;
}

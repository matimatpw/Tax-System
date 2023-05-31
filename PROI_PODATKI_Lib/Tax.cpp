#include "Tax.h"


float Vat::calculate_tax(float income) {//23%

    return 1.23 * income;
}

float Pit::calculate_tax(float income)//Pierwszy próg podatkowy - do 85 528 zł.Do tej kwoty należny podatek PIT wynosi 17 % uszczuplony o kwotę zmniejszającą podatek;
//Drugi próg podatkowy - powyżej 85 528 zł, od nadwyżki ponad tę kwotę musimy zapłacić 32 % podatku dochodowego.
{
    if (income >= 85528) {
        return 1.17 * income;
    }
    return 1.32 * income;
}

float Cit::calculate_tax(float income)//19%
{
    return 1.19 * income;
}

float Pon::calculate_tax(float income)//1zl za m^2/ grunt -> 0.61 m^2
{
    return 4.0f;
}

float Zus::calculate_tax(float income)/*Ubezpieczenie emerytalne:
Składka emerytalna wynosi 19,52% podstawy wymiaru składki. W przypadku zarobków w wysokości 10 000 zł miesięcznie:

Składka emerytalna = 10 000 zł * 19,52% = 1 952 zł

Ubezpieczenie rentowe:
Składka rentowa wynosi 8% podstawy wymiaru składki. W przypadku zarobków w wysokości 10 000 zł miesięcznie:

Składka rentowa = 10 000 zł * 8% = 800 zł

Ubezpieczenie chorobowe:
Składka chorobowa wynosi 2,45% podstawy wymiaru składki. W przypadku zarobków w wysokości 10 000 zł miesięcznie:

Składka chorobowa = 10 000 zł * 2,45% = 245 zł*/
{
    return (1.1952 * income + 1.08 * income + 2.45 * income);
}
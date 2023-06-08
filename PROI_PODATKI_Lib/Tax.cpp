#include "Tax.h"

double Vat::operator()(double income) {

    return 1.23 * income;
}

double Pit::operator()(double income)
{
    if (income >= 85528) {
        return 1.17 * income;
    }
    return 1.32 * income;
}

double Cit::operator()(double income)//19%
{
    return 1.19 * income;
}

double Pon::operator()(double income)
{
    return 4.0f;
}

double Zus::operator()(double income)
{
    return (1.1952 * income + 1.08 * income + 2.45 * income);
}
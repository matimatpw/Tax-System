#include "Tax.h"

double Vat::operator()(double income) {

    return 0.23 * income;
}

double Pit::operator()(double income)
{
    if (income >= 85528) {
        return 0.17 * income;
    }
    return 0.32 * income;
}

double Cit::operator()(double income)//19%
{
    return 0.19 * income;
}

double Pon::operator()(double income)
{
    return 0.10f;
}

double Zus::operator()(double income)
{
    return (0.1952 * income + 0.08 * income + 0.45 * income);
}
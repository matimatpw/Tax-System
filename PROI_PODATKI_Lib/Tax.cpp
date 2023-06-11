#include "Tax.h"

double Vat::operator()(double income) {

    return 0.23 * income;
}

std::string Vat::getName()
{
    return std::string("Vat");
}

double Pit::operator()(double income)
{
    if (income >= 85528) {
        return 0.32 * income;
    }
    return 0.17 * income;
}

std::string Pit::getName()
{
    return std::string("Pit");
}

double Cit::operator()(double income)//19%
{
    return 0.19 * income;
}

std::string Cit::getName()
{
    return std::string("Cit");
}

double Pon::operator()(double income)
{
    return 0.10 * income;
}

std::string Pon::getName()
{
    return std::string("Pon");
}

double Zus::operator()(double income)
{
    return (0.1952 * income + 0.08 * income + 0.45 * income);
}

std::string Zus::getName()
{
    return std::string("Zus");
}


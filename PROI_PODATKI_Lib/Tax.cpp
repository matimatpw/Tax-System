#include "Tax.h"

double Vat::operator()(double income) const noexcept
{

    return 0.23 * income;
}

std::string Vat::getName() const noexcept
{
    return std::string("Vat");
}

double Pit::operator()(double income) const noexcept
{
    if (income >= 85528) {
        return 0.32 * income;
    }
    return 0.17 * income;
}

std::string Pit::getName() const noexcept
{
    return std::string("Pit");
}

double Cit::operator()(double income) const noexcept
{
    return 0.19 * income;
}

std::string Cit::getName() const noexcept
{
    return std::string("Cit");
}

double Pon::operator()(double income) const noexcept
{
    return 0.10 * income;
}

std::string Pon::getName() const noexcept
{
    return std::string("Pon");
}

double Zus::operator()(double income) const noexcept
{
    return (0.1952 * income + 0.08 * income + 0.45 * income);
}

std::string Zus::getName() const noexcept
{
    return std::string("Zus");
}


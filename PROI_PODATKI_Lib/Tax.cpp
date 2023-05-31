#include "Tax.h"

float Tax::calculate_tax() {
	return 0.0f;
}

float Vat::calculate_tax() {
	return 1.0f;
}

float Pit::calculate_tax()
{
	return 2.0f;
}

float Cit::calculate_tax()
{
	return 3.0f;
}

float Pon::calculate_tax()
{
	return 4.0f;
}

float Zus::calculate_tax()
{
	return 5.0f;
}

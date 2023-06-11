#pragma once
#include "Tax.h"

struct Income
{
	Income(double amount, Tax* tax, size_t id) : tax(tax), amount(amount), id(id), toPay((*tax)(amount)) {};

	double amount;
	Tax* tax;
	size_t id;
	double toPay;
	bool paid = false;
};

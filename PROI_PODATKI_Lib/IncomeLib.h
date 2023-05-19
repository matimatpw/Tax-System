#pragma once

template <typename Tax>
struct Income
{
	Income(int amount, Tax tax, size_t id) : tax(tax), amount(amount), id(id), toPay(tax(amount)) {};

	int amount;
	Tax tax;
	size_t id;
	int toPay;
};


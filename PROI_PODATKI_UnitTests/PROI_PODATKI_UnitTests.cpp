#include "CppUnitTest.h"
#include "../PROI_PODATKI_Lib/TaxSystemLib.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PROIPODATKIUnitTests
{
	TEST_CLASS(ClientUnitTests)
	{
	public:
		TEST_METHOD(PersonDefaultConstructorTest)
		{
			Person p1(21, "xyz");
			Assert::AreEqual(21, (int)p1.getID());
			Assert::AreEqual((std::string)"xyz", p1.getName());
		}

		TEST_METHOD(TryingToCreatePersonWithNoName)
		{
			Assert::ExpectException<std::runtime_error>([] {Person p1(21, ""); });
		}

		TEST_METHOD(TryingToCreatePersonWithNumName)
		{
			Assert::ExpectException<std::runtime_error>([] {Person p1(21, "ABc12D"); });
		}

		/*TEST_METHOD(TryingToCreateClientWithSameID)
		{
			// TODO this test should pass
				
			Person p1(21, "xyz");
			Person p2(214, "xsyz");
			Assert::ExpectException<std::runtime_error>([] {Person p3(21, "abc"); });
		}*/

		TEST_METHOD(CreatePersonAndAddIncome)
		{
			Person p1(21, "xyz");
			Income new_inc(5000, p1.getTaxes()[pit], 213);
			Assert::AreEqual(850, new_inc.toPay, 0.01);
			p1.addIncome(new_inc);

			Assert::AreEqual(850, p1.calculateTaxAmount(), 0.01);
		}

		TEST_METHOD(PersonWithMultipleIncomes)
		{
			Person p2(22, "lkkl");
			Income first_inc(5000, p2.getTaxes()[pit], 213);
			Income sec_inc(20000, p2.getTaxes()[pon], 214);
			std::vector<Income> all_person_incomes = {first_inc, sec_inc};
			Person p1(21, "xyz", all_person_incomes);
			Assert::AreEqual(850 + 2000, p1.calculateTaxAmount(), 0.01);
		}

		TEST_METHOD(CreateCompanyAndAddIncomes)
		{
			Company c1(21, "xyz");
			Income new_inc(5000, c1.getTaxes()[cit], 213);
			Assert::AreEqual(950, new_inc.toPay, 0.01);
			c1.addIncome(new_inc);
			Income sec_inc(25000, c1.getTaxes()[cit], 214);
			c1.addIncome(sec_inc);

			Assert::AreEqual(950 + 4750, c1.calculateTaxAmount(), 0.01);
		}

		TEST_METHOD(MarkIncomeAsPaid)
		{
			Company c1(21, "xyz");
			Income new_inc(5000, c1.getTaxes()[cit], 213);
			c1.addIncome(new_inc);

			Income before = c1.getIncomes()[0];

			Assert::IsFalse(before.paid);

			c1.markPaid(213);

			Income after_paid_tax = c1.getIncomes()[0];

			Assert::IsTrue(after_paid_tax.paid);
		}

		TEST_METHOD(CheckWhetherClientHasIncome)
		{
			Company c1(21, "xyz");
			Income new_inc(5000, c1.getTaxes()[cit], 213);

			Assert::IsFalse(c1.hasIncome(213));

			c1.addIncome(new_inc);
			
			Assert::IsTrue(c1.hasIncome(213));

		}
	};
	TEST_CLASS(PROIPODATKIUnitTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
		}
	};
	TEST_CLASS(PROITax)
	{
	public:

		TEST_METHOD(Vattest)
		{
			Vat tax;
			Assert::AreEqual(double(23), tax(100));
		}
		TEST_METHOD(Pittest)
		{
			Pit tax;
			Assert::AreEqual(double(17), tax(100));
		}
		TEST_METHOD(Pitovertest)
		{
			Pit tax;
			Assert::AreEqual(double(27368.96), tax(85528));
		}
		TEST_METHOD(Cittest)
		{
			Cit tax;
			Assert::AreEqual(double(19), tax(100));
		}
		TEST_METHOD(Pontest)
		{
			Pon tax;
			Assert::AreEqual(double(10), tax(100));
		}
		TEST_METHOD(Zustest)
		{
			Zus tax;
			Assert::AreEqual(double(72.52), tax(100));
		}
		TEST_METHOD(Taxtest)
		{
			Tax* tax_ptr = new Vat;
			Assert::AreEqual(double(27.6), tax_ptr->operator()(120));
			delete tax_ptr;
			
		}
	};
}

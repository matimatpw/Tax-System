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
			Income new_inc(5000, p1.getPersonTaxes()[pit], 213);
			Assert::AreEqual(850, new_inc.toPay, 0.01);
			p1.addIncome(new_inc);

			Assert::AreEqual(850, p1.calculateTaxAmount(), 0.01);
		}

		TEST_METHOD(PersonWithMultipleIncomes)
		{
			Person p2(22, "lkkl");
			Income first_inc(5000, p2.getPersonTaxes()[pit], 213);
			Income sec_inc(20000, p2.getPersonTaxes()[pon], 214);
			std::vector<Income> all_person_incomes = {first_inc, sec_inc};
			Person p1(21, "xyz", all_person_incomes);
			 // TODO change assert later (pon is not yet finished)
			Assert::AreEqual(850 + 4, p1.calculateTaxAmount(), 0.01);
		}

		TEST_METHOD(CreateCompanyAndAddIncomes)
		{
			Company p1(21, "xyz");
			Income new_inc(5000, p1.getCompanyTaxes()[cit], 213);
			Assert::AreEqual(950, new_inc.toPay, 0.01);
			p1.addIncome(new_inc);
			Income sec_inc(25000, p1.getCompanyTaxes()[cit], 214);
			p1.addIncome(sec_inc);

			Assert::AreEqual(950 + 4750, p1.calculateTaxAmount(), 0.01);
		}
	};
	TEST_CLASS(PROIPODATKIUnitTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
		}
	};
}

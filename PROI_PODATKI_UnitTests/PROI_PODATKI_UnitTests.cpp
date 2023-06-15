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
	TEST_CLASS(PROITaxSystem)
	{
	public:

		TEST_METHOD(InsertClientStandard)
		{
			TaxSystem system;
			Client* client = new Person(1, "TEST");
			system.addClient(client);

			Assert::AreEqual(std::string("TEST"), system.get_clients_base()[0]->getName());
		}
		TEST_METHOD(InsertClient_ID_AlreadyExists)
		{
			TaxSystem system;
			Client* client = new Person(1, "TEST");
			system.addClient(client);
			

			Assert::ExpectException<std::runtime_error>([&system] { Client* sameIDClient = new Person(1, "TEST2"); system.addClient(sameIDClient); });
		}
		TEST_METHOD(SearchAfterInit)
		{
			TaxSystem system;

			Assert::ExpectException<std::runtime_error>([&system] {system.searchByClientID(0); });
		}
		TEST_METHOD(InsertIncomeStandard)
		{
			TaxSystem system;
			Client* client = new Person(1, "Name");
			system.addClient(client);
			system.addIncome(1, 120, client->getTaxes()[zusOsoba]);

			Assert::AreEqual(client->getIncomes()[0].amount, double(120));
			Assert::AreEqual(client->getIncomes()[0].id, size_t(0));
		}
		TEST_METHOD(SearchIncomeNotExists)
		{
			TaxSystem system;
			Client* client = new Person(1, "Name");
			system.addClient(client);
			system.addIncome(1, 100, client->getTaxes()[zusOsoba]);

			Assert::ExpectException<std::runtime_error>([&system] {system.searchByIncome(1); });
		}
		TEST_METHOD(MarkIncomePaidStandard)
		{
			TaxSystem system;
			Client* client = new Person(1, "Name");
			system.addClient(client);
			system.addIncome(1, 100, client->getTaxes()[zusOsoba]);
			system.markPaid(0);

			Assert::AreEqual(client->getIncomes()[0].paid, true);
		}
		TEST_METHOD(MarkIncomeNotExists)
		{
			TaxSystem system;
			Client* client = new Person(1, "Name");
			system.addClient(client);
			system.addIncome(1, 100, client->getTaxes()[zusOsoba]);
			
			
			Assert::ExpectException<std::runtime_error>([&system] {system.markPaid(1); });
		}
		TEST_METHOD(MarkIncomeAlreadyPaid)
		{
			TaxSystem system;
			Client* client = new Person(1, "Name");
			system.addClient(client);
			system.addIncome(1, 100, client->getTaxes()[zusOsoba]);
			system.markPaid(0);

			Assert::ExpectException<std::runtime_error>([&system] {system.markPaid(0); });
		}
		TEST_METHOD(SearchClientByIDStandard)
		{
			TaxSystem system;
			Client* client = new Person(420, "TEST");
			system.addClient(client);

			Client* search = system.searchByClientID(420);

			Assert::AreEqual(client->getName(), search->getName());
		}
		TEST_METHOD(SearchClientByIDNotExists)
		{
			TaxSystem system;
			Client* client = new Person(21, "TEST");
			system.addClient(client);

			Assert::ExpectException<std::runtime_error>([&system] {system.searchByClientID(15); });
		}
		TEST_METHOD(SearchClientByIncomeIDStandard)
		{
			TaxSystem system;
			Client* client = new Person(1, "TEST");
			system.addClient(client);
			system.addIncome(1, 100, client->getTaxes()[zusOsoba]);
			
			Client* search = system.searchByIncome(0);

			Assert::AreEqual(client->getName(), search->getName());
		}
		TEST_METHOD(SearchClientByIncomeIDNotExists)
		{
			TaxSystem system;
			Client* client = new Person(1, "TEST");
			system.addClient(client);
			system.addIncome(1, 100, client->getTaxes()[zusOsoba]);

			Client* search = system.searchByIncome(0);

			Assert::ExpectException<std::runtime_error>([&system] {system.searchByIncome(15); });
		}
		TEST_METHOD(DeleteClientStandard)
		{
			TaxSystem system;
			Client* client = new Person(1, "TEST");
			system.addClient(client);

			system.deleteClientByID(1);
			Assert::AreEqual(size_t(0), system.get_clients_base().size());

		}
		TEST_METHOD(DeleteClientNoID)
		{
			TaxSystem system;
			Client* client = new Person(1, "TEST");
			system.addClient(client);

			Assert::ExpectException<std::runtime_error>([&system] {system.deleteClientByID(15); });
		}
		//  For tests to calc Taxes:
		//	Tax of Cit = 0.19 * income
		//  Tax of Pit 
		//  if (income >= 85528) 
		//		return 0.32 * income;
		//  else
		// 		return 0.17 * income;
		//  Tax of Pon = 0.1 * income
		//  Tax of Vat = 0.23 * income
		TEST_METHOD(CalcTaxesOneClientOneIncome)
		{
			TaxSystem system;
			Client* client = new Person(1, "TEST");
			system.addClient(client);
			system.addIncome(1, 100, client->getTaxes()[pit]);

			Assert::AreEqual(double(17), system.calculateAllTaxes());
		}
		TEST_METHOD(CalcTaxesOneClientOneIncomePaid)
		{
			TaxSystem system;
			Client* client = new Person(1, "TEST");
			system.addClient(client);
			system.addIncome(1, 100, client->getTaxes()[pit]);
			system.markPaid(0);

			Assert::AreEqual(double(0), system.calculateAllTaxes());
		}
		TEST_METHOD(CalcTaxesOneClientTwoIncomes)
		{
			TaxSystem system;
			Client* client = new Person(1, "TEST");
			system.addClient(client);
			system.addIncome(1, 100, client->getTaxes()[pit]);
			system.addIncome(1, 200, client->getTaxes()[pon]);

			Assert::AreEqual(double(37), system.calculateAllTaxes());
		}
		TEST_METHOD(CalcTaxesTwoClients)
		{
			TaxSystem system;
			Client* client = new Person(1, "TEST");
			Client* secondClient = new Company(2, "TEST2");
			system.addClient(client);
			system.addClient(secondClient);
			system.addIncome(1, 100, client->getTaxes()[pit]);
			system.addIncome(2, 100, secondClient->getTaxes()[vat]);

			Assert::AreEqual(double(40), system.calculateAllTaxes());
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
		TEST_METHOD(Vatgetnametest)
		{
			Vat tax;
			Assert::AreEqual(std::string("Vat"), tax.getName());
		}
		TEST_METHOD(Pitgetnametest)
		{
			Pit tax;
			Assert::AreEqual(std::string("Pit"), tax.getName());
		}
		TEST_METHOD(Citgetnametest)
		{
			Cit tax;
			Assert::AreEqual(std::string("Cit"), tax.getName());
		}
		TEST_METHOD(Pongetnametest)
		{
			Pon tax;
			Assert::AreEqual(std::string("Pon"), tax.getName());
		}
		TEST_METHOD(Zusgetnametest)
		{
			Zus tax;
			Assert::AreEqual(std::string("Zus"), tax.getName());
		}
		TEST_METHOD(Taxgetnametest)
		{
			Tax* tax_ptr = new Vat;
			Assert::AreEqual(std::string("Vat"), tax_ptr->getName());
			delete tax_ptr;

		}

	};
}

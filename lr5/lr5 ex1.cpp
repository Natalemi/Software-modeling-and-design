// lr5 ex1.cpp Декоратор — це структурний патерн проектування, що дає змогу динамічно додавати об’єктам нову функціональність, загортаючи їх у корисні «обгортки».
// Pеалізувати приклад з лекції (не забыть о функции стоимости).

#include <iostream>
#include <string>
using namespace std;

class Coffee
{
public:
	virtual double Get_Price() = 0;
	virtual double Operation() = 0;
	virtual ~Coffee() {}
};

class Espresso : public Coffee
{
	double price = 22.10;
public:
	double Operation() override {
		cout << "\tЭспрессо\n";
		return this->Get_Price();
	}

	double Get_Price() override	{ return  this->price; }
};

class Cappuccino : public Coffee
{
	double price = 35.20;
public:
	double Operation() override {
		cout << "\tКапучино\n";
		return this->Get_Price();
	}

	double Get_Price() override { return  this->price; }
};

class Americano : public Coffee
{
	double price = 14.50;
public:
	double Operation() override {
		cout << "\tАмерикано\n";
		return this->Get_Price();
	}

	double Get_Price() override { return  this->price; }
};

class Latte : public Coffee
{
	double price = 26.45;
public:
	double Operation() override {
		cout << "\tЛатте\n";
		return this->Get_Price();
	}

	double Get_Price() override { return  this->price; }
};

////////////////////////////////////

class Decorator : public Coffee
{
protected:
	Coffee* coffee;
public:
	Decorator(Coffee* _coffee_) : coffee(_coffee_) { }

	double Operation() override { return this->coffee->Operation(); }
};

class Milk : public Decorator
{
	double price = 5.50;
public:
	Milk(Coffee* coffee) : Decorator(coffee) { }

	double Operation() override {
		cout << "+ Молоко ";
		return this->Get_Price() + Decorator::Operation();
	}

	double Get_Price() override { return  this->price; }
};

class Sugar : public Decorator
{
	double price = 2.30;
public:
	Sugar(Coffee* coffee) : Decorator(coffee) {}

	double Operation() override {
		cout << "+ Сахар ";
		return this->Get_Price() + Decorator::Operation();
	}

	double Get_Price() override { return  this->price; }
};

class Cream : public Decorator
{
	double price = 8.25;
public:
	Cream(Coffee* coffee) : Decorator(coffee) {}

	double Operation() override {
		cout << "+ Сливки ";
		return this->Get_Price() + Decorator::Operation();
	}

	double Get_Price() override { return  this->price; }
};

class Chocolate : public Decorator
{
	double price = 4.35;
public:
	Chocolate(Coffee* coffee) : Decorator(coffee) {}

	double Operation() override {
		cout << "+ Шоколад ";
		return this->Get_Price() + Decorator::Operation();
	}

	double Get_Price() override { return  this->price; }
};

////////////////////////////////////

Coffee* Get_Milk(Coffee* coffee)
{
	string choise;
	cout << "Добавлять молоко в кофе?\n"; cin >> choise; cout << endl;

	if (choise == "yes") {
		coffee = new Milk(coffee);
		return coffee;
	}

	else { return coffee; }
}

Coffee* Get_Sugar(Coffee* coffee)
{
	string choise;
	cout << "Добавлять сахар в кофе?\n"; cin >> choise; cout << endl;

	if (choise == "yes") {
		coffee = new Sugar(coffee);
		return coffee;
	}

	else { return coffee; }
}

Coffee* Get_Cream(Coffee* coffee)
{
	string choise;
	cout << "Добавлять сливки в кофе?\n"; cin >> choise; cout << endl;

	if (choise == "yes") {
		coffee = new Cream(coffee);
		return coffee;
	}

	else { return coffee; }
}

Coffee* Get_Chocolate(Coffee* coffee)
{
	string choise;
	cout << "Добавлять шоколад в кофе?\n"; cin >> choise; cout << endl;

	if (choise == "yes") {
		coffee = new Chocolate(coffee);
		return coffee;
	}

	else { return coffee; }
}

////////////////////////////////////

void MakeCoffee()
{
	int choise = 0;
	cout << "\t\tДобро пожаловать!\n\n\tКакой кофе закажите?\n1. Эспрессо\n2. Капучино\n3. Американо\n4. Латте\n";
	cin >> choise; cout << endl;

	if (choise == 1) {
		Coffee* coffee = new Espresso();
		coffee = Get_Milk(coffee);
		coffee = Get_Sugar(coffee);
		coffee = Get_Cream(coffee);
		coffee = Get_Chocolate(coffee);
		cout << "\nЦена = " << coffee->Operation();
	}

	else if (choise == 2) {
		Coffee* coffee = new Cappuccino();
		coffee = Get_Milk(coffee);
		coffee = Get_Sugar(coffee);
		coffee = Get_Cream(coffee);
		coffee = Get_Chocolate(coffee);
		cout << "\nЦена = " << coffee->Operation();
	}

	else if (choise == 3) {
		Coffee* coffee = new Americano();
		coffee = Get_Milk(coffee);
		coffee = Get_Sugar(coffee);
		coffee = Get_Cream(coffee);
		coffee = Get_Chocolate(coffee);
		cout << "\nЦена = " << coffee->Operation();
	}

	else if (choise == 4) {
		Coffee* coffee = new Latte();
		coffee = Get_Milk(coffee);
		coffee = Get_Sugar(coffee);
		coffee = Get_Cream(coffee);
		coffee = Get_Chocolate(coffee);
		cout << "\nЦена = " << coffee->Operation();
	}
	
	else { cout << "Такого кофе нет\n"; }
	cout << endl;
}

////////////////////////////////////

int main()
{
	setlocale(LC_ALL, "Ru");

	MakeCoffee();

	system("pause");
	return 0;
}
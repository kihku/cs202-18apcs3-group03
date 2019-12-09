//.h file code:

#include <string>
#include <vector>
#include <iostream>
using namespace std;
class IPizza
{
public:
	virtual string doPizza() = 0;
};
class TomatoPizza : public IPizza
{

public:
	string doPizza() override
	{
		return "I am a Tomato Pizza";
	};
};
class ChickenPizza : public IPizza
{

public:
	string doPizza() override
	{
		return "I am a Chicken Pizza";
	};
};
class PizzaDecorator : public IPizza
{
	// Reference to component object
protected:
	IPizza* mPizza;

	// We initialize a Decorator with existing pizza we need decorate
public:
	
	PizzaDecorator(IPizza* pizza)
	{
		mPizza = pizza;
	}

	virtual IPizza* getPizza()
	{
		return mPizza;
	}

	virtual void setPizza(IPizza* mPizza)
	{
		this->mPizza = mPizza;
	}
};
class CheeseDecorator : public PizzaDecorator
{

public:
	CheeseDecorator(IPizza* pizza) : PizzaDecorator(pizza) {};

	string doPizza() override
	{
		string type = mPizza->doPizza();
		return type + addCheese();
	}

	// This is additional functionality
	// It adds cheese to an existing pizza
private:
	string addCheese()
	{
		return "+ Cheese";
	}
};
class PepperDecorator : public PizzaDecorator
{

public:
	PepperDecorator(IPizza* pizza) : PizzaDecorator(pizza) {};

	string doPizza() override
	{
		string type = mPizza->doPizza();
		return type + addPepper();
	}

	// This is our additional functionality
	// It add pepper to existing pizza at runtime
private:
	string addPepper()
	{
		return "+ Pepper";
	}
};



string TomatoPizza::doPizza()
{
	return "I am a Tomato Pizza";
}

string ChickenPizza::doPizza()
{
	return "I am a Chicken Pizza";
}

PizzaDecorator::PizzaDecorator(IPizza* pizza)
{
	mPizza = pizza;
}

IPizza* PizzaDecorator::getPizza()
{
	return mPizza;
}

void PizzaDecorator::setPizza(IPizza* mPizza)
{
	this->mPizza = mPizza;
}

CheeseDecorator::CheeseDecorator(IPizza* pizza) : PizzaDecorator(pizza)
{
}

string CheeseDecorator::doPizza()
{
	string type = mPizza->doPizza();
	return type + addCheese();
}

string CheeseDecorator::addCheese()
{
	return "+ Cheese";
}

PepperDecorator::PepperDecorator(IPizza* pizza) : PizzaDecorator(pizza)
{
}

string PepperDecorator::doPizza()
{
	string type = mPizza->doPizza();
	return type + addPepper();
}

string PepperDecorator::addPepper()
{
	return "+ Pepper";
}

void main()
{
	IPizza* tomato = new TomatoPizza();
	IPizza* chicken = new ChickenPizza();

	cout << tomato->doPizza() << endl;
	cout << chicken->doPizza() << endl;

	// Use Decorator pattern to extend existing pizza dynamically

	// Add pepper to tomato-pizza
	PepperDecorator* pepperDecorator = new PepperDecorator(tomato);
	cout << pepperDecorator->doPizza() << endl;

	// Add cheese to tomato-pizza
	CheeseDecorator* cheeseDecorator = new CheeseDecorator(tomato);
	cout << cheeseDecorator->doPizza() << endl;

	// Add cheese and pepper to tomato-pizza
	// We combine functionalities together easily.
	CheeseDecorator* cheeseDecorator2 = new CheeseDecorator(pepperDecorator);
	cout << cheeseDecorator2->doPizza() << endl;
	
}
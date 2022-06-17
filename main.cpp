#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Smoothy {
private:
	int price;
public:
	Smoothy(int price) : price{ price } {};

	virtual string descriere() = 0;

	virtual int getPret() {
		return price;
	}

	~Smoothy() = default;
};

class BasicSmoothy : public Smoothy {
private:
	string name;
public:
	BasicSmoothy(const string& name, int pret) : Smoothy{ pret }, name{ name }{};

	string descriere() override {
		return name;
	}

	~BasicSmoothy() = default;
};

class DecoratorSmoothy : public Smoothy {
private:
	Smoothy& s;
public:
	DecoratorSmoothy(Smoothy& s) : Smoothy{ s.getPret() }, s{ s } {};

	virtual string descriere() {
		return s.descriere();
	}

	virtual int getPret() {
		return s.getPret();
	}

	~DecoratorSmoothy() = default;
};

class SmoothyFrisca : public DecoratorSmoothy {
public:
	SmoothyFrisca(Smoothy& s) : DecoratorSmoothy{ s } {};

	string descriere() override {
		return DecoratorSmoothy::descriere() + " cu frisca";
	}

	int getPret() override {
		return DecoratorSmoothy::getPret() + 5;
	}

	~SmoothyFrisca() = default;
};

class SmoothyUmbreluta : public DecoratorSmoothy {
public:
	SmoothyUmbreluta(Smoothy& s) : DecoratorSmoothy{ s } {};

	string descriere() override {
		return DecoratorSmoothy::descriere() + " cu umbreluta ";
	}

	int getPret() override {
		return DecoratorSmoothy::getPret() + 3;
	}

	~SmoothyUmbreluta() = default;
};

vector<Smoothy*> fun() {
	vector<Smoothy*> order;

	BasicSmoothy* bs1 = new BasicSmoothy{ "kiwi", 15 };
	SmoothyFrisca* f1 = new SmoothyFrisca{ *bs1 };
	SmoothyUmbreluta* u1 = new SmoothyUmbreluta{ *f1 };
	order.push_back(u1);

	BasicSmoothy* bs2 = new BasicSmoothy{ "masline",20 };
	SmoothyUmbreluta* u2 = new SmoothyUmbreluta{ *bs2 };
	order.push_back(u2);

	BasicSmoothy* bs3 = new BasicSmoothy{ "kiwi", 15 };
	order.push_back(bs3);

	return order;
}

int main() {
	auto order = fun();
	sort(order.begin(), order.end(), [](Smoothy* s1, Smoothy* s2) {return s1->descriere() < s2->descriere(); });
	for (auto& ord : order) {
		cout << ord->descriere() << " " << ord->getPret() << '\n';
	}
	return 0;
}
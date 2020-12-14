#include <string>
#include "List.h"

class Monom
{
	double coef;
	int power;
public:
	double getCoef() { return coef; };
	void setCoef(double _coef) { coef = _coef; };
	int getPower() { return power; };
	void setPower(int _power) { power = _power; };
	Monom() { coef = 1; power = 1; };
	Monom(double _coef,  int _power);
	friend bool operator==(const Monom& m1, const Monom& m2);
	friend Monom operator+(const Monom& m1, const Monom& m2);
	friend Monom operator-(const Monom& m1, const Monom& m2);
	friend Monom operator*(const Monom& m1, const Monom& m2);
	friend std::ostream& operator<<(std::ostream &out, const Monom &m);
};

class Polynom
{
	int size;
public:
	List<Monom> monoms;
	Polynom() { size = 0; };
	Polynom(const Polynom& polynom);
	void printAll();
	void resize();
	void parse(std::string str);
	void normalize();
	Polynom operator+(Polynom& p2);
	Polynom operator-(Polynom& p2);
	friend Polynom operator*(const Polynom& p1, const Polynom& p2);
};


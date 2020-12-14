#include "monom.h"

Monom::Monom(int _coef, int x, int y, int z)// Конструктор монома
{
	setlocale(LC_ALL, "Russian");
	if ((x<0) || (y<0) || (z<0) || (x>19) || (y>19) || (z>19))
		throw "Некоректно введено";
	coef = _coef;
	power = x * 400 + y * 20 + z;
}

int Monom::GetCoef() const// Получаем коэфф
{
	return coef;
}

int Monom::GetX() const// Получаем x
{
	return (power / 400);
}

int Monom::GetY() const// Получаем y
{
	return ((power % 400) / 20);
}

int Monom::GetZ() const// Получаем z
{
	return (power % 20);
}

ostream& operator << (ostream& ostr, const Monom& m) // Вывод монома
{
	if ((m.GetCoef() == 0) || (m.GetPower() == 0))
		cout << m.GetCoef();
	else
		ostr << m.GetCoef() << "x^" << m.GetX() << "y^" << m.GetY() << "z^" << m.GetZ();
	return ostr;
}



int Monom::GetPower() const// Возвращаем степень
{
	return power;
}

void Monom::SetCoeff(int _coef) // Устанавливаем коэффициент
{
	coef = _coef;
}

Monom::Monom(int _coef, int _power) //Конструктор монома
	: coef(_coef), power(_power)
{
}

Monom Monom::operator*(const Monom& m)
{
	setlocale(LC_ALL, "Russian");
	Monom temp;
	temp.coef = this->coef * m.coef;
	int x = this->GetX() + m.GetX();
	int y = this->GetY() + m.GetY();
	int z = this->GetZ() + m.GetZ();
	if ((x>19) || (y>19) || (z>19))
		throw "Степень более 19";
	temp.power = x * 400 + y * 20 + z;
	return temp;
}

void Monom::SetPower(int x, int y, int z)// Установить степень
{
	power = x * 400 + y * 20 + z;
}
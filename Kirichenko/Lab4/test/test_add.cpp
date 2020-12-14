

#include <gtest.h>
#include "polinom.h"
#include "monom.h"
#include <sstream>


TEST(Monom, can_create_right_monom)
{
	ASSERT_NO_THROW(Monom m(2, 321));
}

TEST(Monom, coef_right_and_get_coef_right)
{
	Monom m(2, 321);
	EXPECT_EQ(2, m.GetCoef());
}

TEST(Monom, power_right_and_get_power_right)
{
	Monom m(2, 321);
	EXPECT_EQ(321, m.GetPower());
}

TEST(Monom, set_coef_right)
{
	Monom m(2, 321);
	m.SetCoeff(5);
	EXPECT_EQ(5, m.GetCoef());
}

TEST(Monom, set_power_right)
{
	Monom m(2, 521);
	m.SetPower(5, 6, 7);
	EXPECT_EQ(2127, m.GetPower());
}

TEST(Monom, multiply_right_coeff)
{
	Monom m(2, 521);
	Monom m1(4, 123);
	Monom m2 = m*m1;
	EXPECT_EQ(8, m2.GetCoef());
}

TEST(Monom, multiply_right_power)
{
	Monom m(2, 521);
	Monom m1(4, 123);
	Monom m2 = m*m1;
	EXPECT_EQ(644, m2.GetPower());
}
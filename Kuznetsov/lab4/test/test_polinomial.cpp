#include "gtest.h"
#include "polinomial.h"

TEST(TMonom, can_create_monomial)
{
	ASSERT_NO_THROW(TMonom M);
}

TEST(TMonom, can_create_monomial_with_positive_size)
{
	int mas[] = {5,7,3};

	ASSERT_NO_THROW(TMonom M(3, mas, 4));
}

TEST(TMonom, throws_when_create_monomial_with_negative_size)
{
	int mas[] = { 5, 7, 3};

	ASSERT_ANY_THROW(TMonom M(-3, mas, 2));
}

TEST(TMonom, can_copy_monomial)
{
	int mas[] = { 5, 7, 3 };
	TMonom M1(3,mas,2);
	ASSERT_NO_THROW(TMonom M(M1));
}

TEST(TMonom, can_set_power)
{
	int mas[] = { 5, 7, 3 };
	TMonom M;

	ASSERT_NO_THROW(M.SetPower(mas));
}

TEST(TMonom, can_get_power)
{
	int mas[] = { 5, 7, 3 };
	TMonom M(3, mas, 1);
	int nmas[] = {4, 2, 5};

	ASSERT_NO_THROW(M.SetPower(nmas));
	ASSERT_EQ(nmas[0], M.GetPower()[0]);
	ASSERT_EQ(nmas[1], M.GetPower()[1]);
	ASSERT_EQ(nmas[2], M.GetPower()[2]);
}

TEST(TMonom, can_set_size)
{
	int mas[] = { 5, 7, 3 };

	TMonom M(3, mas, 1);

	M.SetN(2);
	EXPECT_EQ(2, M.GetN());
}


TEST(TMonom, can_get_size)
{
	int mas[] = { 5, 7, 3 };

	TMonom M(3, mas, 1);

	EXPECT_EQ(3, M.GetN());
}

TEST(TMonom, can_set_coeff)
{
	TMonom M;

	ASSERT_NO_THROW(M.SetCoeff(2));
}

TEST(TMonom, can_get_coeff)
{
	TMonom M;

	M.SetCoeff(3);

	EXPECT_EQ(3, M.GetCoeff());
}

TEST(TMonom, can_set_next)
{
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 3, 4, 5 };

	TMonom M(3, mas, 3);
	TMonom M1(3, nmas, 3);

	ASSERT_NO_THROW(M.SetNext(&M1));
}

TEST(TMonom, can_get_next)
{
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 3, 4, 5 };

	TMonom M(3, mas, 2);
	TMonom M1(3, nmas, 2);

	M.SetNext(&M1);
	EXPECT_EQ(M.GetNext(), &M1);
}


TEST(TMonom, can_assign_monomials_with_equal_size)
{
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 7, 9, 4 };

	TMonom M(3, mas, 6);
	TMonom M1(3, nmas, 6);

	ASSERT_NO_THROW(M = M1);
}

TEST(TMonom, throws_when_assign_monomials_with_different_size)
{
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 7, 9, 4, 8};

	TMonom M(3, mas, 3);
	TMonom M1(4, nmas, 3);

	ASSERT_ANY_THROW(M = M1);
}

TEST(TMonom, can_add_monomials_with_equal_size)
{
	int mas[] = { 5, 7, 3 };

	TMonom M(3, mas, 2);
	TMonom M1(3, mas, 5);

	ASSERT_NO_THROW(M + M1);
}

TEST(TMonom, can_subtract_monomials_with_equal_size)
{
	int mas[] = { 5, 7, 3 };

	TMonom M(3, mas, 5);
	TMonom M1(3, mas, 2);

	ASSERT_NO_THROW(M - M1);
}

TEST(TMonom, throws_when_add_or_subtract_monomials_with_different_size)
{
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 1, 2, 3, 4, 5 };

	TMonom M(3, mas, 2);
	TMonom M1(5, nmas, 2);

	ASSERT_ANY_THROW(M + M1);
	ASSERT_ANY_THROW(M - M1);
}

TEST(TMonom, can_multiply_monomials)
{
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 1, 2, 3 };
	
	TMonom M(3, mas, 2);
	TMonom M1(3, nmas, 3);

	ASSERT_NO_THROW(M * M1);
}

TEST(TMonom, throws_when_multiply_different_monomials)
{
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 1, 2, 3, 7 };
	TMonom M(3,mas, 2);
	TMonom M1(4, nmas, 2);
	ASSERT_ANY_THROW(M * M1);
}

TEST(TMonom, can_compare_monomials_with_equal_size)
{
	int mas[] = { 1, 3, 3 };
	int nmas[] = { 2, 3, 4 };

	TMonom M(3, mas, 5);
	TMonom M1(3, nmas, 7);

	ASSERT_NO_THROW(M > M1);
	ASSERT_NO_THROW(M < M1);

	ASSERT_FALSE(M > M1);
	ASSERT_TRUE(M < M1);
}

TEST(TMonom, throws_when_compare_monomials_with_different_size)
{
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 5, 4, 3, 2};

	TMonom M(3, mas, 2);
	TMonom M1(4, nmas, 2);

	ASSERT_ANY_THROW(M > M1);
	ASSERT_ANY_THROW(M < M1);
}

TEST(TMonom, can_equivalence_monomials)
{
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 5, 4, 3};


	TMonom M(3, mas, 4);
	TMonom M1(3, mas, 4);
	TMonom M2(3, nmas, 4);
	ASSERT_TRUE(M == M1);
	ASSERT_FALSE(M == M2);
}

TEST(TMonom, throws_when_equivalence_monomials_with_different_size)
{
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 5, 4, 3, 8 };

	TMonom M(3, mas, 2);
	TMonom M1(4, nmas, 2);
	ASSERT_ANY_THROW(M == M1);
}

TEST(TPolynom, can_create_polynomial)
{
	ASSERT_NO_THROW(TPolynom P(2));
}

TEST(TPolynom, throws_when_create_polynomial_with_negative_size)
{
	ASSERT_ANY_THROW(TPolynom P(-2));
}

TEST(TPolynom, can_copy_polynomial)
{
	TPolynom P;
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 5, 4, 3 };
	TMonom M(3, mas, 4);
	TMonom M1(3, nmas, 4);
	P += M;
	P += M1;

	ASSERT_NO_THROW(TPolynom P1(P));
	TPolynom P1(P);
	ASSERT_TRUE(P1 == P);
}


TEST(TPolynom, can_get_n)
{
	TPolynom P(3);

	EXPECT_EQ(3, P.GetN());
}


TEST(TPolynom, can_get_size)
{
	TPolynom P;
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 5, 4, 3 };
	TMonom M(3, mas, 4);
	TMonom M1(3, nmas, 4);
	P += M;
	P += M1;

	ASSERT_EQ(P.GetSize(), 2);
}


TEST(TPolynom, can_add_polynomials)
{
	TPolynom P;
	TPolynom P1;
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 5, 4, 3 };
	int nnmas[] = { 1, 2, 3 };
	TMonom M(3, mas, 4);
	TMonom M1(3, nmas, 4);
	TMonom M2(3, nnmas, 4);
	P += M;
	P += M1;
	P1 += M;
	P1 += M2;

	ASSERT_NO_THROW(P1 + P);
}

TEST(TPolynom, can_subtract_polynomials)
{
	TPolynom P;
	TPolynom P1;
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 5, 4, 3 };
	int nnmas[] = { 1,2,3 };
	TMonom M(3, mas, 4);
	TMonom M1(3, nmas, 4);
	TMonom M2(3, nnmas, 4);
	P += M;
	P += M1;
	P1 += M;
	P1 += M2;

	ASSERT_NO_THROW(P1 - P);
}

TEST(TPolynom, operator_add_monomial)
{
	TPolynom P;
	int mas[] = { 5, 7, 3 };
	TMonom M(3, mas, 4);

	ASSERT_NO_THROW(P += M);
	EXPECT_EQ(1, P.GetSize());

}

TEST(TPolynom, operator_subtract_monomial)
{
	TPolynom P;;
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 5, 4, 3 };
	TMonom M(3, mas, 4);
	TMonom M1(3, nmas, 4);
	P += M;
	ASSERT_NO_THROW(P -= M1);
}

TEST(TPolynom, can_multiply_equal_polynomials)
{
	TPolynom P;
	TPolynom P1;
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 5, 4, 3 };
	int nnmas[] = { 1,2,3 };
	TMonom M(3, mas, 4);
	TMonom M1(3, nmas, 4);
	TMonom M2(3, nnmas, 4);
	P += M;
	P += M1;
	P1 += M;
	P1 += M2;

	ASSERT_NO_THROW(P1 * P);
}

TEST(TPolynom, can_assign_polynomials)
{
	TPolynom P;
	TPolynom P1;
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 5, 4, 3 };
	int nnmas[] = { 1,2,3 };
	TMonom M(3, mas, 4);
	TMonom M1(3, nmas, 4);
	TMonom M2(3, nnmas, 4);
	P += M;
	P += M1;
	P1 += M;
	P1 += M2;

	ASSERT_NO_THROW(P = P1);
}

TEST(TPolynom, can_equivalence_polynoms_now)
{
	TPolynom P;
	TPolynom P1;
	int mas[] = { 5, 7, 3 };
	int nmas[] = { 5, 4, 3 };
	int nnmas[] = { 1,2,3 };
	TMonom M(3, mas, 4);
	TMonom M1(3, nmas, 4);
	TMonom M2(3, nnmas, 4);
	P += M;
	P += M1;
	P1 += M;
	P1 += M2;
	ASSERT_FALSE(P == P1);
	P1 = P;
	ASSERT_TRUE(P == P1);

}
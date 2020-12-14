#pragma once

#include "TNode.h"

template<>
class TNode<int, float>
{
public:
	unsigned int key;
	float pData;
	TNode<int, float>* pNext;
	TNode() : key(0), pData(0), pNext(nullptr)
	{
	}
	TNode(int NewKey, float Data, TNode<int, float>* next = nullptr) :key(NewKey), pData(Data), pNext(next)
	{
	}
	TNode(const TNode& tmp) : key(tmp.key), pData(tmp.pData), pNext(nullptr)
	{
	}
	TNode(unsigned int deg_x, unsigned int deg_y, unsigned int deg_z, float coeff, TNode<int, float>* next = nullptr);
	~TNode()
	{
		pNext = nullptr;
	}
	TNode<int, float> operator*(const TNode<int, float>&);
	TNode<int, float> operator+(const TNode<int, float>&);
	TNode<int, float> operator-(const TNode<int, float>&);
	TNode<int, float>* operator-()const;
	bool operator <(const TNode<int, float>&)const;
	bool operator >(const TNode<int, float>&)const;
	bool operator !=(const TNode<int, float>&)const;
	bool operator ==(const TNode<int, float>&)const;
	const TNode<int, float>& operator= (const TNode<int, float>& monom);
};

TNode<int, float> ::TNode(unsigned int deg_x, unsigned int deg_y, unsigned int deg_z, float coeff, TNode<int, float>* next)
{
	if (deg_x > 9 || deg_x < 0 || deg_y > 9 || deg_y < 0 || deg_z > 9 || deg_z < 0)
		throw "invalid parameter";
	this->key = deg_x * 100 + deg_y * 10 + deg_z;
	this->pData = coeff;
	this->pNext = next;
}

bool TNode<int, float> ::operator <(const TNode& OtherMonom)const
{
	return(this->key < OtherMonom.key);
}

bool TNode<int, float> ::operator >(const TNode& OtherMonom)const
{
	return(this->key > OtherMonom.key);
}

bool TNode<int, float> ::operator ==(const TNode& OtherMonom)const
{
	return(this->key == OtherMonom.key && this->pData == OtherMonom.pData);
}

bool TNode<int, float> ::operator !=(const TNode& OtherMonom)const
{
	return(!(*this == OtherMonom));
}

const TNode<int, float>& TNode<int, float> :: operator=(const TNode<int, float>& monom)
{
	if (*this == monom)
		return *this;
	this->key = monom.key;
	this->pData = monom.pData;
	return *this;
}

TNode<int, float> TNode<int, float>::operator*(const TNode<int, float>& monom)
{
	int deg_x1 = this->key / 100;
	int deg_y1 = (this->key - deg_x1 * 100) / 10;
	int deg_z1 = this->key - deg_x1 * 100 - deg_y1 * 10;
	int deg_x2 = monom.key / 100;
	int deg_y2 = (monom.key - deg_x2 * 100) / 10;
	int deg_z2 = monom.key - deg_x2 * 100 - deg_y2 * 10;
	if (deg_z1 + deg_z2 > 9 || deg_y1 + deg_y2 > 9 || deg_x1 + deg_x2 > 9)
		throw "invalid parameter";
	TNode<int, float> product(this->key + monom.key, this->pData * monom.pData);
	/*product->key = this->key + monom.key;
	product->pData = this->pData * monom.pData;*/
	return product;
}

TNode<int, float> TNode<int, float>::operator+(const TNode<int, float>& monom)
{
	if (this->key != monom.key)
		throw "monoms have different degrees";
	return TNode<int, float>(monom.key, this->pData + monom.pData);
}

TNode<int, float> TNode<int, float>::operator-(const TNode<int, float>& monom)
{
	if (this->key != monom.key)
		throw "monoms have different degrees";
	return TNode<int, float>(monom.key, this->pData - monom.pData);
}
TNode<int, float>* TNode<int, float>::operator-() const
{
	TNode<int, float>* tmp = new TNode<int, float>(*this);
	tmp->pData = -1 * tmp->pData;
	return tmp;
}

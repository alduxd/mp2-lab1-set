// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = BitLen / (sizeof(TELEM) * 8) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else throw out_of_range("out of range"); 
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	
	BitLen = bf.BitLen; 
	MemLen = bf.MemLen; 
	pMem = new TELEM[MemLen]; 
	for (int i =0;i<MemLen; i++) 
		pMem[i] = bf.pMem[i]; 
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / (sizeof(TELEM) * 8));
	
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	
	if (n >= 0 && n <= BitLen)
	{
		pMem[GetMemIndex(n)] |= GetMemMask(n); 
	}
	else throw out_of_range("Out of range"); 
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n <= BitLen)
	{
		pMem[GetMemIndex(n)] &=~GetMemMask(n); 
	}
	else throw out_of_range("Out of range"); 
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= 0 && n <= BitLen)
	{
		int temp = pMem[GetMemIndex(n)];
		temp &= GetMemMask(n);
		if (temp != 0)
			return 1;
		else
			return 0;
	}
	else throw out_of_range("Out of range"); 
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		BitLen = bf.BitLen; 
		MemLen = bf.MemLen; 
		delete []pMem; 
		pMem = new TELEM[MemLen]; 
		for (int i=0; i<MemLen; i++) 
			pMem[i] = bf.pMem[i];
	}
	return *this; 
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int f=1; 
	if (BitLen == bf.BitLen) 
	{ 
		for (int i = 0;i < MemLen;i++) 
			if (pMem[i] != bf.pMem[i]) 
			{ 
				f = 0; 
				break; 
			} 
	} 
	else 
		f=0;
	return f; 
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf) return 0;
	else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int n = BitLen;
	if (n < bf.BitLen)
		n = bf.BitLen;
	TBitField tmp(n);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] |= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int n = BitLen;
	if (n < bf.BitLen)
		n = bf.BitLen;
	TBitField tmp(n);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] &= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{	
	TBitField tmp(*this);
	for (int i = 0; i < BitLen; i++)
	{
		if ((tmp).GetBit(i) == 1){
			tmp.ClrBit(i);
		}
		else
			tmp.SetBit(i);
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{ 
	int i = 0;
	while ((i >= 0) && (i < bf.BitLen))
	{
		bf.SetBit(i);
		istr >> i;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	return ostr;
}

// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	MemLen=len;
	pMem=new TELEM [MemLen];
	if(!pMem) exit(1);
	for(int i=0; i<MemLen; i++)
	pMem[i]=0;

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen= bf.BitLen;
	MemLen= bf.MemLen;
	pMem= new TELEM [bf.MemLen];
	if(!pMem) exit(1);
	for(int i=0; i< bf.MemLen; i++)
		pMem[i]=bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int Pos=n/32;
	return Pos;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1<<(n % 32);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if((n<0)||(n>=BitLen))
		return;
	else
	{
		pMem[GetMemIndex(n)]|=GetMemMask(n);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if((n<0) || (n>=BitLen))
		return;
	else
	{
		pMem[GetMemIndex(n)]&= ~GetMemMask(n);
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if((n<0) && (n>=BitLen))
		return 0;
	else
		return pMem[GetMemIndex(n)] & GetMemMask(n);


}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen= bf.BitLen;
	if(MemLen < bf.MemLen)
		delete[]pMem;
	pMem=new TELEM [bf.MemLen];
	MemLen = bf.MemLen;
	if(!pMem)
		exit(1);
	for(int i=0; i<bf.MemLen; i++)
		pMem[i]=bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{

  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	MemLen=bf.MemLen;
	TBitField ObpMem();

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
}

TBitField TBitField::operator~(void) // отрицание
{
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int len=bf.MemLen;
	for(int i=0; i<len; i++)
	{
		for(int j=0;j<32;j++)
		{
			if()



	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len=bf.MemLen;
	for(int i=0; i<len; i++)
	{
		for(int j=0; j<32; j++)
		{
		if((bf.pMem[i]&bf.GetMemMask(j))!=0)
			ostr<< '1';
		else
			ostr<< '0';
 		}
	}
	return ostr;
}

};
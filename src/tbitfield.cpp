// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
	{
		throw"error size";
	}
	else
	{
		BitLen = len;
		MemLen = (len + 31) >> 5;
		pMem = new TELEM[MemLen];
		if (!pMem) exit(1);
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}

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
	return n>>5;
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
	if ((n < 0) || (n >= BitLen))
		throw "error";
	else
	{
		pMem[GetMemIndex(n)]|=GetMemMask(n);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if((n<0) || (n>=BitLen))
		throw "error";
	else
	{
		pMem[GetMemIndex(n)]&= ~GetMemMask(n);
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if((n<0) || (n>=BitLen))
		throw "error";
	else
		return (pMem[GetMemIndex(n)] & GetMemMask(n));


}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		if (MemLen < bf.MemLen)
			delete[]pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[bf.MemLen];
		if (!pMem)
			exit(1);
		for (int i = 0; i < bf.MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{

	for(int i=0; i<MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i])
			return 0;
	}
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{

		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
				return 1;
		}
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = 0;
	if(BitLen<bf.BitLen)
	{
		 len=bf.BitLen;
	}
	else
		 len=BitLen;
	TBitField temp(len);
	for(int i=0; i<bf.MemLen; i++)
	{
		temp.pMem[i]=bf.pMem[i];
	}
	for(int i=0; i<MemLen; i++)
	{
		temp.pMem[i]|=pMem[i];
	}
	return temp;

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = 0;
	if (BitLen<bf.BitLen)
	{
		len = bf.BitLen;
	}
	else
		len = BitLen;
	TBitField temp(len);
	for(int i=0; i<bf.MemLen; i++)
	{
		temp.pMem[i]=bf.pMem[i];
	}
	for(int i=0; i<MemLen; i++)
	{
		temp.pMem[i]&=pMem[i];
	}
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(BitLen);
	for (int i = 0; i < MemLen-1; i++)
	{
		temp.pMem[i] = ~pMem[i];
	}
	for (int i = (MemLen - 1)*sizeof(TELEM); i < BitLen; i++)
	{
		if ((*this).GetBit(i) == 0)
	        temp.SetBit(i);
	}
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int len=bf.MemLen;
	char str;
	int i=0;
	while(str!=' ')
	{
		istr>>str;
		if(str=='1')
		{
			bf.SetBit(i++);
		}
		else

		if(str=='0')
		{
			bf.ClrBit(i++);
		}
		else
			break;
	}
	return istr;
}
	
ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.MemLen;
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if ((bf.pMem[i] & bf.GetMemMask(j)) != 0)
				ostr << '1';
			else
				ostr << '0';
		}
	}
	return ostr;
}


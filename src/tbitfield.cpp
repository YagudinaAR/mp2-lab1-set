// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen=len;
	MemLen=(len+31)>>5;
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
	int flag=1;
	for(int i=0; i<MemLen; i++)
	{
		if(pMem[i]!=bf.pMem[i])
			flag=0;
		break;
	}
	if(MemLen < bf.MemLen)
	{
		for(int i =MemLen; i<bf.MemLen; i++)
		{
			if(bf.pMem[i]!=0)
				flag=0;
			break;
		}
	}
	else
	{
		for(int i=bf.MemLen; i<MemLen; i++)
		{
			if(pMem[i]!=0)
			flag=0;
			break;
		}
	}
  return flag;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int flag=0;
	if(MemLen!=bf.MemLen)
		flag=1;
	else
	{
		for(int i=0; i<MemLen; i++)
		{
			if(pMem[i]!=bf.pMem[i])
				flag=1;
			break;
		}
	}
  return flag;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len;
	TBitField temp(len);
	if(BitLen<bf.BitLen)
	{
		len=bf.BitLen;
	}
	else
		len=BitLen;
	for(int i=0; i<len; i++)
	{
		temp.pMem[i]=bf.pMem[i];
	}
	int min= MemLen;
	for(int i=0; i<min; i++)
	{
		temp.pMem[i]|=pMem[i];
	}
	return temp;

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len;
	TBitField temp(len);
	if(BitLen<bf.BitLen)
	{
		len=bf.BitLen;
	}
	else
	{
		len=BitLen;
	}
	for(int i=0; i<len; i++)
	{
		temp.pMem[i]=bf.pMem[i];
	}
	int min=bf.MemLen;
	for(int i=0; i<min; i++)
	{
		temp.pMem[i]&=pMem[i];
	}
	for(int i=min; i<temp.MemLen; i++)
	{
		temp.pMem[i]=0;
	}
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int len;
	TBitField temp(len);
	len=BitLen;
	for(int i=0; i<len; i++)
	{
		temp.pMem[i]=~pMem[i];
	}
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int len=bf.MemLen;
	for(int i=0; i<len; i++)
	{
		for(int j=0;j<32;j++)
		{
			if();



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
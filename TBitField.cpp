// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tbitfield.cpp - Copyright (c) ������� �.�. 07.05.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (19.04.2015)
//
// ������� ����

#include "TBitField.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 0) throw - 1;

    BitLen = len;
    MemLen = (BitLen - 1) * (sizeof(TELEM) * 8) + 1;
    pMem = new TELEM(MemLen);

    for (size_t i = 0; i < BitLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField& bf) // ����������� �����������
{
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    this->pMem = new TELEM(MemLen);

    for (size_t i = 0; i < BitLen; i++) {
        this->pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // ������ ��� ��� ���� n
{
    if (n > BitLen) throw out_of_range("Out of range!");
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // ������� ����� ��� ���� n
{
    if (n > BitLen) throw out_of_range("Out of range!");
    return pow(2, n % 8);
}

// ������ � ����� �������� ����

int TBitField::GetLength(void) const // �������� ����� (�-�� �����)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // ���������� ���
{
    if (n > BitLen) throw out_of_range("Out of range!");
    pMem[n] = 1;
}

void TBitField::ClrBit(const int n) // �������� ���
{
    if (n > BitLen) throw out_of_range("Out of range!");
    pMem[n] = 0;
}

int TBitField::GetBit(const int n) const // �������� �������� ����
{
    if (n > BitLen) throw out_of_range("Out of range!");
    return pMem[n];
}

// ������� ��������

TBitField& TBitField::operator=(const TBitField& bf) // ������������
{
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    this->pMem = new TELEM(MemLen);

    for (size_t i = 0; i < BitLen; i++) {
        this->pMem[i] = bf.pMem[i];
    }

    return *this;
}

int TBitField::operator==(const TBitField& bf) const // ���������
{

    if (this->BitLen != bf.BitLen) return 0;

    for (size_t i = 0; i < BitLen; i++) {
        if (this->pMem[i] != bf.pMem[i]) return 0;
    }

    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // ���������
{
    if (this->BitLen != bf.BitLen) return 1;

    for (size_t i = 0; i < BitLen; i++) {
        if (this->pMem[i] != bf.pMem[i]) return 1;
    }

    return 0;
}

TBitField TBitField::operator|(const TBitField& bf) // �������� "���"
{
    if (this->BitLen != bf.BitLen) throw -1;

    TBitField res(bf);

    for (size_t i = 0; i < bf.BitLen; i++) {
        res.pMem[i] = (res.pMem[i] + this->pMem[i]) % 2;
    }

    return res;

}

TBitField TBitField::operator&(const TBitField& bf) // �������� "�"
{
    if (this->BitLen != bf.BitLen) throw -1;

    TBitField res(bf);

    for (size_t i = 0; i < bf.BitLen; i++) {
        res.pMem[i] = res.pMem[i] * this->pMem[i];
    }

    return res;
}

TBitField TBitField::operator~(void) // ���������
{
    TBitField res(*this);

    for (size_t i = 0; i < res.BitLen; i++) {
        res.pMem[i] = !res.pMem[i];
    }

    return res;
}

// ����/�����

istream& operator>>(istream& istr, TBitField& bf) // ����
{
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // �����
{
    return ostr;
}
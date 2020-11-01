#include <string>
#include <iostream>
#include <cstdlib>
#include <string>
#include <regex>
#include "LinkedList.h"
#include "ExceptionClass.h"
using namespace std;





class BigInteger
{
	string data;
	bool sign;
	friend BigInteger Add(const BigInteger &, int);
	friend BigInteger Add(const BigInteger &, const BigInteger &);
	friend BigInteger Subtract(const BigInteger &, int);
	friend BigInteger Subtract(int, const BigInteger &);
	friend BigInteger Subtract(const BigInteger &, const BigInteger &);
	friend BigInteger Multiply(const BigInteger &, int);
	friend BigInteger Multiply(const BigInteger &, const BigInteger &);
	friend BigInteger Divide(const BigInteger &, int);
	friend BigInteger Divide(const BigInteger &, const BigInteger &);
	bool LessThan(int) const;
	bool LessThan(const BigInteger &) const;
	bool GreaterThan(int) const;
	bool GreaterThan(const BigInteger &) const;
	bool EqualWith(int) const;
	bool EqualWith(const BigInteger &) const;

	
public:
	BigInteger();
	BigInteger(int);
	BigInteger(const BigInteger &); // 변경되지 않을 레퍼런스들은 반드시 const 하자
	BigInteger(string str);
	~BigInteger();
	void operator=(int);
	void operator=(const BigInteger &); // const가 너무 중요했다..
	void operator=(string);
	BigInteger operator+(int) const;
	BigInteger operator+(const BigInteger &) const;
	BigInteger operator+(string) const;
	BigInteger operator-(int) const;
	BigInteger operator-(const BigInteger &) const;
	BigInteger operator-(string) const;
	BigInteger operator*(int) const;
	BigInteger operator*(const BigInteger &) const;
	BigInteger operator*(string) const;
	BigInteger operator/(int) const;
	BigInteger operator/(const BigInteger &) const;
	BigInteger operator/(string)const;

	bool operator<(int) const; // this를 const -> 멤버변수 전체를 const
	bool operator<(const BigInteger &) const;
	bool operator<(string) const;
	bool operator>(int) const;
	bool operator>(const BigInteger &) const;
	bool operator>(string) const;
	bool operator<=(int) const;
	bool operator<=(const BigInteger &) const;
	bool operator<=(string) const;
	bool operator>=(int) const;
	bool operator>=(const BigInteger &) const;
	bool operator>=(string) const;
	bool operator==(int) const;
	bool operator==(const BigInteger &) const;
	bool operator==(string) const;
	bool operator!=(int) const;
	bool operator!=(const BigInteger &) const;
	bool operator!=(string) const;

	bool GetSign() const { return this->sign; } 
	void Negative() { this->sign = (this->sign)?false:true; }

	friend ostream & operator <<(ostream &, BigInteger &);

	friend BigInteger operator+(int, const BigInteger &);
	friend BigInteger operator-(int, const BigInteger &);
	friend BigInteger operator*(int, const BigInteger &);
	friend BigInteger operator/(int, const BigInteger &);
	friend void operator>(int, const BigInteger &);
	friend void operator>=(int, const BigInteger &);
	friend void operator<(int, const BigInteger &);
	friend void operator<=(int, const BigInteger &);
	friend void operator==(int, const BigInteger &);
	friend void operator!=(int, const BigInteger &);

};

ostream & operator<<(ostream &os, BigInteger &b)
{
	if (b.sign)
		os << b.data;
	else
		os <<"-"<< b.data;
	return os;
}

BigInteger::BigInteger()
{
	this->data = "";
	this->sign = true;
}


BigInteger::BigInteger(int data)
{
	if (data >= 0)
	{
		this->data = to_string(data);
		this->sign = true;
	}
	else
	{
		this->data = to_string(-data);
		this->sign = false;
	}
}
BigInteger::BigInteger(string str)
{

	if (str[0] == '-')
	{
		str.erase(str.begin());
		data = str;
		this->sign = false;
	}
	else
	{
		data = str;
		this->sign = true;
	}
}
BigInteger::BigInteger(const BigInteger &b)
{
	data = string(b.data);
	this->sign = b.sign;
}

BigInteger::~BigInteger()
{

}


BigInteger Add(const BigInteger &bdata, int data)
{
	BigInteger arg_data = BigInteger(data);
	BigInteger btemp = Add(bdata,arg_data);


	return  btemp;
}
BigInteger Add(const BigInteger &bdata1, const BigInteger &bdata2)
{
	BigInteger btemp;
	int carry = 0;

	auto longer = (bdata1.data.length() < bdata2.data.length()) ? bdata2.data.rbegin() : bdata1.data.rbegin();
	auto shorter = (bdata1.data.length() < bdata2.data.length()) ? bdata1.data.rbegin() : bdata2.data.rbegin();
	auto longer_end = (bdata1.data.length() < bdata2.data.length()) ? bdata2.data.rend() : bdata1.data.rend();
	auto shorter_end = (bdata1.data.length() < bdata2.data.length()) ? bdata1.data.rend() : bdata2.data.rend();
	btemp.sign = bdata1.sign;

	int res = 0;

	for (; carry != 0 || longer != longer_end;)
	{
		int byte = 0;

		if (longer != longer_end)
		{
			byte = *longer - 48;
			longer++;
		}
		if (shorter != shorter_end)
		{
			int temp = byte + carry + *shorter - 48;
			carry = temp / 10;
			btemp.data.insert(btemp.data.begin(), (const char)(temp % 10 + 48));
			shorter++;
		}
		else
		{
			int temp = byte + carry;
			carry = temp / 10;
			btemp.data.insert(btemp.data.begin(), (const char)(temp % 10 + 48));
		}
	}
	return  btemp;
}
BigInteger Subtract(const BigInteger &bdata, int data)
{
	BigInteger btemp(""), bdata1(bdata), bdata2(data);


	if (bdata < -data)
		btemp.sign = false;
	else
		btemp.sign = true;

	auto longer = (bdata1.data.length() < bdata2.data.length()) ? bdata2.data.rbegin() : bdata1.data.rbegin();
	auto shorter = (bdata1.data.length() < bdata2.data.length()) ? bdata1.data.rbegin() : bdata2.data.rbegin();
	auto longer_end = (bdata1.data.length() < bdata2.data.length()) ? bdata2.data.rend() : bdata1.data.rend();
	auto shorter_end = (bdata1.data.length() < bdata2.data.length()) ? bdata1.data.rend() : bdata2.data.rend();


	int res = 0, carry = 0;

	for (; carry != 0 || longer != longer_end;)
	{
		int byte = 0;

		byte = *longer - 48;
		longer++;
		

		if (shorter != shorter_end)
		{
			int temp = byte - *shorter + 48 - carry;
			carry = (temp < 0) ? 1 : 0;
			temp = (temp < 0) ? 10+temp : temp;
			btemp.data.insert(btemp.data.begin(), (const char)(temp % 10 + 48));
			shorter++;
		}
		else
		{
			int temp = byte  - carry;
			carry = (temp < 0) ? 1 : 0;
			temp = (temp < 0) ? 10+temp : temp;
			btemp.data.insert(btemp.data.begin(), (const char)(temp % 10 + 48));
		}
	}
	if (btemp.data.at(0) == '0' && btemp.data.length() != 1)
		btemp.data.erase(btemp.data.begin());
	return  btemp;
}
BigInteger Subtract( int data, const BigInteger &bdata)
{
	BigInteger btemp(""), bdata1(data), bdata2(bdata),forabs(bdata);

	forabs.Negative();
	if (forabs > data)
		btemp.sign = false;
	else
		btemp.sign = true;

	auto longer = (bdata1.data.length() < bdata2.data.length()) ? bdata2.data.rbegin() : bdata1.data.rbegin();
	auto shorter = (bdata1.data.length() < bdata2.data.length()) ? bdata1.data.rbegin() : bdata2.data.rbegin();
	auto longer_end = (bdata1.data.length() < bdata2.data.length()) ? bdata2.data.rend() : bdata1.data.rend();
	auto shorter_end = (bdata1.data.length() < bdata2.data.length()) ? bdata1.data.rend() : bdata2.data.rend();


	int res = 0, carry = 0;

	for (; carry != 0 || longer != longer_end;)
	{
		int byte = 0;

		byte = *longer - 48;
		longer++;

		if (shorter != shorter_end)
		{
			int temp = byte - *shorter + 48 - carry;
			carry = (temp < 0) ? 1 : 0;
			temp = (temp < 0) ? 10+temp : temp;
			btemp.data.insert(btemp.data.begin(), (const char)(temp % 10 + 48));
			shorter++;
		}
		else
		{
			int temp = byte  - carry;
			carry = (temp < 0) ? 1 : 0;
			temp = (temp < 0) ? 10+temp : temp;
			btemp.data.insert(btemp.data.begin(), (const char)(temp % 10 + 48));
		}
	}
	if (btemp.data.at(0) == '0' && btemp.data.length() != 1)
		btemp.data.erase(btemp.data.begin());
	return  btemp;
}
BigInteger Subtract(const BigInteger &bdata1, const BigInteger &bdata2)
{
	BigInteger btemp(""), temp1(bdata1), temp2(bdata2);

	temp1.sign = true;
	temp2.sign = true;

	if (temp1 < temp2)
		btemp.sign = false;
	else
		btemp.sign = true;

	auto longer = (bdata1.data.length() < bdata2.data.length()) ? bdata2.data.rbegin() : bdata1.data.rbegin();
	auto shorter = (bdata1.data.length() < bdata2.data.length()) ? bdata1.data.rbegin() : bdata2.data.rbegin();
	auto longer_end = (bdata1.data.length() < bdata2.data.length()) ? bdata2.data.rend() : bdata1.data.rend();
	auto shorter_end = (bdata1.data.length() < bdata2.data.length()) ? bdata1.data.rend() : bdata2.data.rend();


	int res = 0, carry = 0;

	for (; carry != 0 || longer != longer_end;)
	{
		int byte = 0;

		byte = *longer - 48;
		longer++;

		if (shorter != shorter_end)
		{
			int temp = byte - *shorter + 48 - carry;
			carry = (temp < 0) ? 1 : 0;
			temp = (temp < 0) ? 10 + temp : temp;
			btemp.data.insert(btemp.data.begin(), (const char)(temp % 10 + 48));
			shorter++;
		}
		else
		{
			int temp = byte - carry;
			carry = (temp < 0) ? 1 : 0;
			temp = (temp < 0) ? 10 + temp : temp;
			btemp.data.insert(btemp.data.begin(), (const char)(temp % 10 + 48));
		}
	}
	if (btemp.data.at(0) == '0' && btemp.data.length() != 1)
		btemp.data.erase(btemp.data.begin());
	return  btemp;
}
BigInteger Multiply(const BigInteger &bdata, int data)
{
	BigInteger temp(0);
	bool datasign = true;
	if (data < 0)
	{
		data = -data;
		datasign = false;
	}


	for (int i = 1; i <= data; i++)
		temp = temp + bdata;


	temp.sign = !((!bdata.sign && datasign) || (bdata.sign && !datasign));
	return  temp;
}
BigInteger Multiply(const BigInteger &bdata1, const BigInteger &bdata2)
{
	BigInteger res(0), temp1 = bdata1, temp2 = bdata2;

	temp1.sign = true;
	temp2.sign = true;


	while(temp2 > 0)
	{
		res = res + bdata1;
		temp2 = temp2 - 1;
	}

	res.sign = !((!bdata1.sign && bdata2.sign) || (bdata1.sign && !bdata2.sign));
	return res;
}
BigInteger Divide(const BigInteger &bdata,int data)
{
	BigInteger res(0);
	BigInteger temp = bdata;
	bool datasign = true;
	if (data < 0)
	{
		data = -data;
		datasign = false;
	}

	temp.sign = true;

	for (res = 0; temp >= data ; res = res + 1)
		temp = temp - data;


	res.sign = !((!bdata.sign && datasign) || (bdata.sign && !datasign));
	res.sign = (res.data == "0") ? true : res.sign;
	return  res;
}
BigInteger Divide(const BigInteger &bdata1, const BigInteger &bdata2) 
{
	BigInteger res(0), temp1 = bdata1, temp2 = bdata2;

	temp1.sign = true;
	temp2.sign = true;

	for (res = 0; temp1 >= temp2; res = res + 1)
		temp1 = temp1 - temp2;

	res.sign = !((!bdata1.sign && bdata2.sign) || (bdata1.sign && !bdata2.sign));
	res.sign = (res.data == "0") ? true : res.sign;
	return res;
}


bool BigInteger::LessThan(int data) const
{
	BigInteger temp = data;

	if (this->sign == true && temp.sign == true)
	{
		if (this->data.length() == temp.data.length())
		{
			return this->data < temp.data;
		}
		else if (this->data.length() < temp.data.length())
			return true;
		else
			return false;
	}
	if (this->sign == false && temp.sign == false)
	{
		if (this->data.length() == temp.data.length())
		{
			return this->data > temp.data;
		}
		else if (this->data.length() > temp.data.length())
			return true;
		else
			return false;
	}
	if (this->sign == true && temp.sign == false)
		return false;
	if (this->sign == false && temp.sign == true)
		return true;

	throw BigIntegerException(1,"asdf","asdf");
}
bool BigInteger::LessThan(const BigInteger &bdata) const
{
	if (this->sign == true && bdata.sign == true)
	{
		if (this->data.length() == bdata.data.length())
		{
			return this->data < bdata.data;
		}
		else if (this->data.length() < bdata.data.length())
			return true;
		else
			return false;
	}
	if (this->sign == false && bdata.sign == false)
	{
		if (this->data.length() == bdata.data.length())
		{
			return this->data > bdata.data;
		}
		else if (this->data.length() > bdata.data.length())
			return true;
		else
			return false;
	}
	if (this->sign == true && bdata.sign == false)
		return false;
	if (this->sign == false && bdata.sign == true)
		return true;
	throw BigIntegerException(1,"asdf","asdf");
}
bool BigInteger::GreaterThan(int data) const
{
	BigInteger temp = data;

	if (this->sign == true && temp.sign == true)
	{
		if (this->data.length() == temp.data.length())
		{
			return this->data > temp.data;
		}
		else if (this->data.length() > temp.data.length())
			return true;
		else
			return false;
	}
	if (this->sign == false && temp.sign == false)
	{
		if (this->data.length() == temp.data.length())
		{
			return this->data < temp.data;
		}
		else if (this->data.length() < temp.data.length())
			return true;
		else
			return false;
	}
	if (this->sign == true && temp.sign == false)
		return true;
	if (this->sign == false && temp.sign == true)
		return false;
	throw BigIntegerException();
}
bool BigInteger::GreaterThan(const BigInteger &bdata) const
{
	if (this->sign == true && bdata.sign == true)
	{
		if (this->data.length() == bdata.data.length())
		{
			return this->data > bdata.data;
		}
		else if (this->data.length() > bdata.data.length())
			return true;
		else
			return false;
	}
	if (this->sign == false && bdata.sign == false)
	{
		if (this->data.length() == bdata.data.length())
		{
			return this->data < bdata.data;
		}
		else if (this->data.length() < bdata.data.length())
			return true;
		else
			return false;
	}
	if (this->sign == true && bdata.sign == false)
		return true;
	if (this->sign == false && bdata.sign == true)
		return false;
	throw BigIntegerException();
}
bool BigInteger::EqualWith(int data) const
{
	BigInteger temp = data;

	if (this->sign != temp.sign)
		return false;
	else
		return this->data == temp.data;
}
bool BigInteger::EqualWith(const BigInteger &bdata) const
{
	if (this->sign != bdata.sign)
		return false;
	else
		return this->data == bdata.data;
}

void BigInteger::operator=(int data)
{
	if (data >= 0)
	{
		this->data = to_string(data);
		this->sign = true;
	}
	else
	{
		this->data = to_string(-data);
		this->sign = false;
	}
}

void BigInteger::operator=(const BigInteger &b)
{
	this->data = string(b.data);
	this->sign = b.sign;
}

void BigInteger::operator=(string str)
{
	if (str[0] == '-')
	{
		str.erase(str.begin());
		data = str;
		this->sign = false;
	}
	else
	{
		data = str;
		this->sign = true;
	}
}


BigInteger BigInteger::operator+(int data) const
{
	if (this->sign == true && data >= 0)
		return  Add(*this, data);
	else if (this->sign == false && data >= 0)
		return Subtract(data, *this);
	else if (this->sign == true && data < 0)
		return Subtract(*this, data);
	else if (this->sign == false && data < 0)
		return Add(*this, data);
	else
		throw BigIntegerException();
}

BigInteger BigInteger::operator+(const BigInteger &bdata) const
{

	if (this->sign == true && bdata.sign == true)
		return Add(*this, bdata);
	else if (this->sign == false && bdata.sign == true)
		return Subtract(bdata, *this);
	else if (this->sign == true && bdata.sign == false)
		return Subtract(*this, bdata);
	else if (this->sign == false && bdata.sign == false)
		return Add(*this, bdata);
	else
		throw BigIntegerException();
}

BigInteger BigInteger::operator+(string str) const
{
	BigInteger bdata = str;

	if (this->sign == true && bdata.sign == true)
		return Add(*this, bdata);
	else if (this->sign == false && bdata.sign == true)
		return Subtract(bdata, *this);
	else if (this->sign == true && bdata.sign == false)
		return Subtract(*this, bdata);
	else if (this->sign == false && bdata.sign == false)
		return Add(*this, bdata);
	else
		throw BigIntegerException();
}

BigInteger BigInteger::operator-(int data) const
{
	if (this->sign == true && data >= 0)
		return  Subtract(*this, data);
	else if (this->sign == false && data >= 0)
		return Add(*this, data);
	else if (this->sign == true && data < 0)
		return Add(*this, data);
	else if (this->sign == false && data < 0)
		return Subtract(data, *this);
	else
		throw BigIntegerException();
}


BigInteger BigInteger::operator-(const BigInteger &bdata) const
{
	if (this->sign == true && bdata.sign == true)
		return  Subtract(*this, bdata);
	else if (this->sign == false && bdata.sign == true)
		return Add(*this, bdata);
	else if (this->sign == true && bdata.sign == false)
		return Add(*this, bdata);
	else if (this->sign == false && bdata.sign == false)
		return Subtract(bdata, *this);
	else
		throw BigIntegerException();
}

BigInteger BigInteger::operator-(string str) const
{
	BigInteger bdata = str;

	if (this->sign == true && bdata.sign == true)
		return  Subtract(*this, bdata);
	else if (this->sign == false && bdata.sign == true)
		return Add(*this, bdata);
	else if (this->sign == true && bdata.sign == false)
		return Add(*this, bdata);
	else if (this->sign == false && bdata.sign == false)
		return Subtract(bdata, *this);
	else
		throw BigIntegerException();
}

bool BigInteger::operator<(int data) const
{
	return this->LessThan(data);
}
bool BigInteger::operator<(const BigInteger &bdata) const
{
	return this->LessThan(bdata);
}
bool BigInteger::operator<(string str) const
{
	return this->LessThan(BigInteger(str));
}
bool BigInteger::operator>(int data) const
{
	return this->GreaterThan(data);
}
bool BigInteger::operator>(const BigInteger &bdata) const
{
	return this->GreaterThan(bdata);
}

bool BigInteger::operator>(string str) const
{
	return this->GreaterThan(BigInteger(str));
}

bool BigInteger::operator<=(int data) const
{
	return this->LessThan(data) || this->EqualWith(data);
}
bool BigInteger::operator<=(const BigInteger &bdata) const
{
	return this->LessThan(data) || this->EqualWith(bdata);
}
bool BigInteger::operator<=(string str) const
{
	return this->LessThan(data) || this->EqualWith(BigInteger(str));
}

bool BigInteger::operator>=(int data) const
{
	return this->GreaterThan(data) || this->EqualWith(data);
}
bool BigInteger::operator>=(const BigInteger &bdata) const
{
	return this->GreaterThan(bdata) || this->EqualWith(bdata);
}
bool BigInteger::operator>=(string str) const
{
	return this->GreaterThan(string(str)) || this->EqualWith(string(str));
}
bool BigInteger::operator==(int data) const
{
	return this->EqualWith(data);
}
bool BigInteger::operator==(const BigInteger &bdata) const
{
	return this->EqualWith(bdata);
}
bool BigInteger::operator==(string str) const
{
	return this->EqualWith(BigInteger(str));
}
bool BigInteger::operator!=(int data) const
{
	return !this->EqualWith(data);
}

bool BigInteger::operator!=(const BigInteger &bdata) const
{
	return ! this->EqualWith(bdata);
}
bool BigInteger::operator!=(string str) const
{
	return !this->EqualWith(BigInteger(str));
}



BigInteger BigInteger::operator*(int data) const
{
	return Multiply(*this,data);
}
BigInteger BigInteger::operator*(const BigInteger &bdata) const
{
	return Multiply(*this, bdata);
}
BigInteger BigInteger::operator*(string str) const
{
	BigInteger bdata = str;
	return Multiply(*this, bdata);
}

BigInteger BigInteger::operator/(int data) const
{
	return Divide(*this,data);
}
BigInteger BigInteger::operator/(const BigInteger &bdata) const
{
	return Divide(*this, bdata);
}
BigInteger BigInteger::operator/(string str) const
{
	BigInteger bdata = str;
	return Divide(*this, bdata);
}



BigInteger operator+(int data, const BigInteger &bdata) 
{
	BigInteger b = bdata;
	return b + data;
}
BigInteger operator-(int data, const BigInteger &bdata) 
{
	BigInteger b = data;
	return b - bdata;
}
BigInteger operator*(int data, const BigInteger &bdata) 
{
	BigInteger b = data;
	return b * bdata;
}
BigInteger operator/(int data, const BigInteger &bdata) 
{
	BigInteger b = data;
	return b / bdata;
}
void operator>(int data, const BigInteger &bdata) {}
void operator>=(int data, const BigInteger &bdata) {}
void operator<(int data, const BigInteger &bdata) {}
void operator<=(int data, const BigInteger &bdata) {}
void operator==(int data, const BigInteger &bdata) {}
void operator!=(int data, const BigInteger &bdata) {}

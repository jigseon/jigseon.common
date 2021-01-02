#include <string>
#include <iostream>
#include <cstdlib>
#include <string>
#include <regex>
#include "llist.h"
#include "ExceptionClass.h"


namespace jigseon
{



	class BigInteger
	{
		std::string _data;
		bool _sign;
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
		BigInteger(std::string str);
		~BigInteger();
		void operator=(int);
		void operator=(const BigInteger &); // const가 너무 중요했다..
		void operator=(std::string);
		BigInteger operator+(int) const;
		BigInteger operator+(const BigInteger &) const;
		BigInteger operator+(std::string) const;
		BigInteger operator-(int) const;
		BigInteger operator-(const BigInteger &) const;
		BigInteger operator-(std::string) const;
		BigInteger operator*(int) const;
		BigInteger operator*(const BigInteger &) const;
		BigInteger operator*(std::string) const;
		BigInteger operator/(int) const;
		BigInteger operator/(const BigInteger &) const;
		BigInteger operator/(std::string)const;

		bool operator<(int) const; // this를 const -> 멤버변수 전체를 const
		bool operator<(const BigInteger &) const;
		bool operator<(std::string) const;
		bool operator>(int) const;
		bool operator>(const BigInteger &) const;
		bool operator>(std::string) const;
		bool operator<=(int) const;
		bool operator<=(const BigInteger &) const;
		bool operator<=(std::string) const;
		bool operator>=(int) const;
		bool operator>=(const BigInteger &) const;
		bool operator>=(std::string) const;
		bool operator==(int) const;
		bool operator==(const BigInteger &) const;
		bool operator==(std::string) const;
		bool operator!=(int) const;
		bool operator!=(const BigInteger &) const;
		bool operator!=(std::string) const;

		bool GetSign() const { return this->_sign; }
		void Negative() { this->_sign = (this->_sign)?false:true; }

		friend std::ostream & operator <<(std::ostream &, BigInteger &);

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

	std::ostream & operator<<(std::ostream &os, BigInteger &b)
	{
		if (b._sign)
			os << b._data;
		else
			os <<"-"<< b._data;
		return os;
	}

	BigInteger::BigInteger()
	{
		this->_data = "";
		this->_sign = true;
	}


	BigInteger::BigInteger(int data)
	{
		if (data >= 0)
		{
			this->_data = std::to_string(data);
			this->_sign = true;
		}
		else
		{
			this->_data = std::to_string(-data);
			this->_sign = false;
		}
	}
	BigInteger::BigInteger(std::string str)
	{

		if (str[0] == '-')
		{
			str.erase(str.begin());
			this->_data = str;
			this->_sign = false;
		}
		else
		{
			this->_data = str;
			this->_sign = true;
		}
	}
	BigInteger::BigInteger(const BigInteger &b)
	{
		this->_data = std::string(b._data);
		this->_sign = b._sign;
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

		auto longer = (bdata1._data.length() < bdata2._data.length()) ? bdata2._data.rbegin() : bdata1._data.rbegin();
		auto shorter = (bdata1._data.length() < bdata2._data.length()) ? bdata1._data.rbegin() : bdata2._data.rbegin();
		auto longer_end = (bdata1._data.length() < bdata2._data.length()) ? bdata2._data.rend() : bdata1._data.rend();
		auto shorter_end = (bdata1._data.length() < bdata2._data.length()) ? bdata1._data.rend() : bdata2._data.rend();
		btemp._sign = bdata1._sign;

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
				btemp._data.insert(btemp._data.begin(), (const char)(temp % 10 + 48));
				shorter++;
			}
			else
			{
				int temp = byte + carry;
				carry = temp / 10;
				btemp._data.insert(btemp._data.begin(), (const char)(temp % 10 + 48));
			}
		}
		return  btemp;
	}
	BigInteger Subtract(const BigInteger &bdata, int data)
	{
		BigInteger btemp(""), bdata1(bdata), bdata2(data);


		if (bdata < -data)
			btemp._sign = false;
		else
			btemp._sign = true;

		auto longer = (bdata1._data.length() < bdata2._data.length()) ? bdata2._data.rbegin() : bdata1._data.rbegin();
		auto shorter = (bdata1._data.length() < bdata2._data.length()) ? bdata1._data.rbegin() : bdata2._data.rbegin();
		auto longer_end = (bdata1._data.length() < bdata2._data.length()) ? bdata2._data.rend() : bdata1._data.rend();
		auto shorter_end = (bdata1._data.length() < bdata2._data.length()) ? bdata1._data.rend() : bdata2._data.rend();


		int carry = 0;

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
				btemp._data.insert(btemp._data.begin(), (const char)(temp % 10 + 48));
				shorter++;
			}
			else
			{
				int temp = byte  - carry;
				carry = (temp < 0) ? 1 : 0;
				temp = (temp < 0) ? 10+temp : temp;
				btemp._data.insert(btemp._data.begin(), (const char)(temp % 10 + 48));
			}
		}
		if (btemp._data.at(0) == '0' && btemp._data.length() != 1)
			btemp._data.erase(btemp._data.begin());
		return  btemp;
	}
	BigInteger Subtract( int data, const BigInteger &bdata)
	{
		BigInteger btemp(""), bdata1(data), bdata2(bdata),forabs(bdata);

		forabs.Negative();
		if (forabs > data)
			btemp._sign = false;
		else
			btemp._sign = true;

		auto longer = (bdata1._data.length() < bdata2._data.length()) ? bdata2._data.rbegin() : bdata1._data.rbegin();
		auto shorter = (bdata1._data.length() < bdata2._data.length()) ? bdata1._data.rbegin() : bdata2._data.rbegin();
		auto longer_end = (bdata1._data.length() < bdata2._data.length()) ? bdata2._data.rend() : bdata1._data.rend();
		auto shorter_end = (bdata1._data.length() < bdata2._data.length()) ? bdata1._data.rend() : bdata2._data.rend();


		int carry = 0;

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
				btemp._data.insert(btemp._data.begin(), (const char)(temp % 10 + 48));
				shorter++;
			}
			else
			{
				int temp = byte  - carry;
				carry = (temp < 0) ? 1 : 0;
				temp = (temp < 0) ? 10+temp : temp;
				btemp._data.insert(btemp._data.begin(), (const char)(temp % 10 + 48));
			}
		}
		if (btemp._data.at(0) == '0' && btemp._data.length() != 1)
			btemp._data.erase(btemp._data.begin());
		return  btemp;
	}
	BigInteger Subtract(const BigInteger &bdata1, const BigInteger &bdata2)
	{
		BigInteger btemp(""), temp1(bdata1), temp2(bdata2);

		temp1._sign = true;
		temp2._sign = true;

		if (temp1 < temp2)
			btemp._sign = false;
		else
			btemp._sign = true;

		auto longer = (bdata1._data.length() < bdata2._data.length()) ? bdata2._data.rbegin() : bdata1._data.rbegin();
		auto shorter = (bdata1._data.length() < bdata2._data.length()) ? bdata1._data.rbegin() : bdata2._data.rbegin();
		auto longer_end = (bdata1._data.length() < bdata2._data.length()) ? bdata2._data.rend() : bdata1._data.rend();
		auto shorter_end = (bdata1._data.length() < bdata2._data.length()) ? bdata1._data.rend() : bdata2._data.rend();


		int carry = 0;

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
				btemp._data.insert(btemp._data.begin(), (const char)(temp % 10 + 48));
				shorter++;
			}
			else
			{
				int temp = byte - carry;
				carry = (temp < 0) ? 1 : 0;
				temp = (temp < 0) ? 10 + temp : temp;
				btemp._data.insert(btemp._data.begin(), (const char)(temp % 10 + 48));
			}
		}
		while (btemp._data.at(0) == '0' && btemp._data.length() != 1)
			btemp._data.erase(btemp._data.begin());
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


		temp._sign = !((!bdata._sign && datasign) || (bdata._sign && !datasign));
		return  temp;
	}
	BigInteger Multiply(const BigInteger &bdata1, const BigInteger &bdata2)
	{
		BigInteger res(0), temp1 = bdata1, temp2 = bdata2;

		temp1._sign = true;
		temp2._sign = true;


		while(temp2 > 0)
		{
			res = res + bdata1;
			temp2 = temp2 - 1;
		}

		res._sign = !((!bdata1._sign && bdata2._sign) || (bdata1._sign && !bdata2._sign));
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

		temp._sign = true;

		for (res = 0; temp >= data ; res = res + 1)
			temp = temp - data;


		res._sign = !((!bdata._sign && datasign) || (bdata._sign && !datasign));
		res._sign = (res._data == "0") ? true : res._sign;
		return  res;
	}
	BigInteger Divide(const BigInteger &bdata1, const BigInteger &bdata2) 
	{
		BigInteger res(0), temp1 = bdata1, temp2 = bdata2;

		temp1._sign = true;
		temp2._sign = true;

		for (res = 0; temp1 >= temp2; res = res + 1)
			temp1 = temp1 - temp2;

		res._sign = !((!bdata1._sign && bdata2._sign) || (bdata1._sign && !bdata2._sign));
		res._sign = (res._data == "0") ? true : res._sign;
		return res;
	}


	bool BigInteger::LessThan(int data) const
	{
		BigInteger temp = data;

		if (this->_sign == true && temp._sign == true)
		{
			if (this->_data.length() == temp._data.length())
			{
				return this->_data < temp._data;
			}
			else if (this->_data.length() < temp._data.length())
				return true;
			else
				return false;
		}
		if (this->_sign == false && temp._sign == false)
		{
			if (this->_data.length() == temp._data.length())
			{
				return this->_data > temp._data;
			}
			else if (this->_data.length() > temp._data.length())
				return true;
			else
				return false;
		}
		if (this->_sign == true && temp._sign == false)
			return false;
		if (this->_sign == false && temp._sign == true)
			return true;

		throw BIGINTEGER;
	}
	bool BigInteger::LessThan(const BigInteger &bdata) const
	{
		if (this->_sign == true && bdata._sign == true)
		{
			if (this->_data.length() == bdata._data.length())
			{
				return this->_data < bdata._data;
			}
			else if (this->_data.length() < bdata._data.length())
				return true;
			else
				return false;
		}
		if (this->_sign == false && bdata._sign == false)
		{
			if (this->_data.length() == bdata._data.length())
			{
				return this->_data > bdata._data;
			}
			else if (this->_data.length() > bdata._data.length())
				return true;
			else
				return false;
		}
		if (this->_sign == true && bdata._sign == false)
			return false;
		if (this->_sign == false && bdata._sign == true)
			return true;
		throw BIGINTEGER;
	}
	bool BigInteger::GreaterThan(int data) const
	{
		BigInteger temp = data;

		if (this->_sign == true && temp._sign == true)
		{
			if (this->_data.length() == temp._data.length())
			{
				return this->_data > temp._data;
			}
			else if (this->_data.length() > temp._data.length())
				return true;
			else
				return false;
		}
		if (this->_sign == false && temp._sign == false)
		{
			if (this->_data.length() == temp._data.length())
			{
				return this->_data < temp._data;
			}
			else if (this->_data.length() < temp._data.length())
				return true;
			else
				return false;
		}
		if (this->_sign == true && temp._sign == false)
			return true;
		if (this->_sign == false && temp._sign == true)
			return false;
		throw BIGINTEGER;
	}
	bool BigInteger::GreaterThan(const BigInteger &bdata) const
	{
		if (this->_sign == true && bdata._sign == true)
		{
			if (this->_data.length() == bdata._data.length())
			{
				return this->_data > bdata._data;
			}
			else if (this->_data.length() > bdata._data.length())
				return true;
			else
				return false;
		}
		if (this->_sign == false && bdata._sign == false)
		{
			if (this->_data.length() == bdata._data.length())
			{
				return this->_data < bdata._data;
			}
			else if (this->_data.length() < bdata._data.length())
				return true;
			else
				return false;
		}
		if (this->_sign == true && bdata._sign == false)
			return true;
		if (this->_sign == false && bdata._sign == true)
			return false;
		throw BIGINTEGER;
	}
	bool BigInteger::EqualWith(int data) const
	{
		BigInteger temp = data;

		if (this->_sign != temp._sign)
			return false;
		else
			return this->_data == temp._data;
	}
	bool BigInteger::EqualWith(const BigInteger &bdata) const
	{
		if (this->_sign != bdata._sign)
			return false;
		else
			return this->_data == bdata._data;
	}

	void BigInteger::operator=(int data)
	{
		if (data >= 0)
		{
			this->_data = std::to_string(data);
			this->_sign = true;
		}
		else
		{
			this->_data = std::to_string(-data);
			this->_sign = false;
		}
	}

	void BigInteger::operator=(const BigInteger &b)
	{
		this->_data = std::string(b._data);
		this->_sign = b._sign;
	}

	void BigInteger::operator=(std::string str)
	{
		if (str[0] == '-')
		{
			str.erase(str.begin());
			this->_data = str;
			this->_sign = false;
		}
		else
		{
			this->_data = str;
			this->_sign = true;
		}
	}


	BigInteger BigInteger::operator+(int data) const
	{
		if (this->_sign == true && data >= 0)
			return  Add(*this, data);
		else if (this->_sign == false && data >= 0)
			return Subtract(data, *this);
		else if (this->_sign == true && data < 0)
			return Subtract(*this, data);
		else if (this->_sign == false && data < 0)
			return Add(*this, data);
		else
			throw BIGINTEGER;
	}

	BigInteger BigInteger::operator+(const BigInteger &bdata) const
	{

		if (this->_sign == true && bdata._sign == true)
			return Add(*this, bdata);
		else if (this->_sign == false && bdata._sign == true)
			return Subtract(bdata, *this);
		else if (this->_sign == true && bdata._sign == false)
			return Subtract(*this, bdata);
		else if (this->_sign == false && bdata._sign == false)
			return Add(*this, bdata);
		else
			throw BIGINTEGER;
	}

	BigInteger BigInteger::operator+(std::string str) const
	{
		BigInteger bdata = str;

		if (this->_sign == true && bdata._sign == true)
			return Add(*this, bdata);
		else if (this->_sign == false && bdata._sign == true)
			return Subtract(bdata, *this);
		else if (this->_sign == true && bdata._sign == false)
			return Subtract(*this, bdata);
		else if (this->_sign == false && bdata._sign == false)
			return Add(*this, bdata);
		else
			throw BIGINTEGER;
	}

	BigInteger BigInteger::operator-(int data) const
	{
		if (this->_sign == true && data >= 0)
			return  Subtract(*this, data);
		else if (this->_sign == false && data >= 0)
			return Add(*this, data);
		else if (this->_sign == true && data < 0)
			return Add(*this, data);
		else if (this->_sign == false && data < 0)
			return Subtract(data, *this);
		else
			throw BIGINTEGER;
	}


	BigInteger BigInteger::operator-(const BigInteger &bdata) const
	{
		if (this->_sign == true && bdata._sign == true)
			return  Subtract(*this, bdata);
		else if (this->_sign == false && bdata._sign == true)
			return Add(*this, bdata);
		else if (this->_sign == true && bdata._sign == false)
			return Add(*this, bdata);
		else if (this->_sign == false && bdata._sign == false)
			return Subtract(bdata, *this);
		else
			throw BIGINTEGER;
	}

	BigInteger BigInteger::operator-(std::string str) const
	{
		BigInteger bdata = str;

		if (this->_sign == true && bdata._sign == true)
			return  Subtract(*this, bdata);
		else if (this->_sign == false && bdata._sign == true)
			return Add(*this, bdata);
		else if (this->_sign == true && bdata._sign == false)
			return Add(*this, bdata);
		else if (this->_sign == false && bdata._sign == false)
			return Subtract(bdata, *this);
		else
			throw BIGINTEGER;
	}

	bool BigInteger::operator<(int data) const
	{
		return this->LessThan(data);
	}
	bool BigInteger::operator<(const BigInteger &bdata) const
	{
		return this->LessThan(bdata);
	}
	bool BigInteger::operator<(std::string str) const
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

	bool BigInteger::operator>(std::string str) const
	{
		return this->GreaterThan(BigInteger(str));
	}

	bool BigInteger::operator<=(int data) const
	{
		return this->LessThan(data) || this->EqualWith(data);
	}
	bool BigInteger::operator<=(const BigInteger &bdata) const
	{
		return this->LessThan(bdata) || this->EqualWith(bdata);
	}
	bool BigInteger::operator<=(std::string str) const
	{
		return this->LessThan(BigInteger(str)) || this->EqualWith(BigInteger(str));
	}

	bool BigInteger::operator>=(int data) const
	{
		return this->GreaterThan(data) || this->EqualWith(data);
	}
	bool BigInteger::operator>=(const BigInteger &bdata) const
	{
		return this->GreaterThan(bdata) || this->EqualWith(bdata);
	}
	bool BigInteger::operator>=(std::string str) const
	{
		return this->GreaterThan(std::string(str)) || this->EqualWith(std::string(str));
	}
	bool BigInteger::operator==(int data) const
	{
		return this->EqualWith(data);
	}
	bool BigInteger::operator==(const BigInteger &bdata) const
	{
		return this->EqualWith(bdata);
	}
	bool BigInteger::operator==(std::string str) const
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
	bool BigInteger::operator!=(std::string str) const
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
	BigInteger BigInteger::operator*(std::string str) const
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
	BigInteger BigInteger::operator/(std::string str) const
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
	/*
	void operator>(int data, const BigInteger &bdata) {}
	void operator>=(int data, const BigInteger &bdata) {}
	void operator<(int data, const BigInteger &bdata) {}
	void operator<=(int data, const BigInteger &bdata) {}
	void operator==(int data, const BigInteger &bdata) {}
	void operator!=(int data, const BigInteger &bdata) {}
	*/
}
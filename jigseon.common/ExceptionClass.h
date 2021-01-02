#pragma once
#include <iostream>
#include <string>

#define ASSERT(x) x;

#define INVALIDINPUT	InvalidInputException(__LINE__, __FUNCTION__, __FILE__)
#define ZERODEVIDE		ZeroDevideException(__LINE__, __FUNCTION__, __FILE__)
#define BIGINTEGER		BigIntegerException(__LINE__, __FUNCTION__, __FILE__)
#define INVALIDINDEX	InvalidIndexException(__LINE__, __FUNCTION__, __FILE__)
#define NULLPOINT		NullPointException(__LINE__, __FUNCTION__, __FILE__)
#define BADALLOC		BadAllocException(__LINE__, __FUNCTION__, __FILE__)
#define TEST(test_id)	TestException(__LINE__, __FUNCTION__, __FILE__,test_id)

namespace jigseon
{
	class ExceptionBase
	{
	protected:
		int _line;
		std::string  _function, _file, _type;
	public:
		ExceptionBase(int line, std::string function, std::string file, std::string type)
		{
			this->_line = line;
			this->_function = function;
			this->_file = file;
			this->_type = type;
		}
		void print() { std::cout << _type << " : " << _function << "in " << _file << "(line:" << _line << ")" << std::endl; }
	};

	class InvalidInputException : public ExceptionBase
	{
	public:
		InvalidInputException(int line, std::string function, std::string file, std::string type = "InvalidInputException") : ExceptionBase(line, function, file, type) {}
	};
	class ZeroDevideException : public ExceptionBase
	{
	public:
		ZeroDevideException(int line, std::string function, std::string file, std::string type = "ZeroDevideException") : ExceptionBase(line, function, file, type) {}
	};
	class BigIntegerException : public ExceptionBase
	{
	public:
		BigIntegerException(int line = -1, std::string function = "temp", std::string file = "temp", std::string type = "BigIntegerException") : ExceptionBase(line, function, file, type) {}
	};

	class InvalidIndexException : public ExceptionBase
	{
	public:
		InvalidIndexException(int line, std::string function, std::string file, std::string type = "InvalidIndexException") : ExceptionBase(line, function, file, type) {}
	};

	class NullPointException : public ExceptionBase
	{
	public:
		NullPointException(int line, std::string function, std::string file, std::string type = "NullPointException") : ExceptionBase(line, function, file, type) {}
	};

	class BadAllocException : public ExceptionBase
	{
	public:
		BadAllocException(int line, std::string function, std::string file, std::string type = "BadAllocException") : ExceptionBase(line, function, file, type) {}
	};

	class TestException : public ExceptionBase
	{
		std::string _test_id;
	public:
		TestException(int line, std::string function, std::string file, std::string test_id, std::string type = "TestException") : ExceptionBase(line, function, file, type) { _test_id = test_id; }
		void print() { std::cout << _type << " : " << _function << "in " << _file << "(line:" << _line << ")" << std::endl; }
	};
}
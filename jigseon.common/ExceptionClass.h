#pragma once
#include <iostream>
#include <string>

using namespace std;

#define ASSERT(x) x;


#define INVALIDINPUT	InvalidInputException(__LINE__, __FUNCTION__, __FILE__)
#define ZERODEVIDE		ZeroDevideException(__LINE__, __FUNCTION__, __FILE__)
#define BIGINTEGER		BigIntegerException(__LINE__, __FUNCTION__, __FILE__)
#define INVALIDINDEX	InvalidIndexException(__LINE__, __FUNCTION__, __FILE__)
#define NULLPOINT		NullPointException(__LINE__, __FUNCTION__, __FILE__)
#define BADALLOC		BadAllocException(__LINE__, __FUNCTION__, __FILE__)

class ExceptionBase
{
	int line;
	string  function, file, type;
public:
	ExceptionBase(int line, string function, string file, string type)
	{
		this->line = line;
		this->function = function;
		this->file = file;
		this->type = type;
	}
	void print() { cout << type << " : " << function << "in " << file << "(line:" << line << ")" << endl; }
};

class InvalidInputException : public ExceptionBase
{
public:
	InvalidInputException(int line, string function, string file, string type = "InvalidInputException") : ExceptionBase(line, function, file, type) {}
};
class ZeroDevideException : public ExceptionBase
{
public:
	ZeroDevideException(int line, string function, string file, string type = "ZeroDevideException") : ExceptionBase(line, function, file, type) {}
};
class BigIntegerException : public ExceptionBase
{
public:
	BigIntegerException(int line = -1, string function = "temp", string file = "temp", string type = "BigIntegerException") : ExceptionBase(line, function, file, type) {}
};

class InvalidIndexException : public ExceptionBase
{
public:
	InvalidIndexException(int line, string function, string file, string type = "InvalidIndexException") : ExceptionBase(line, function, file, type) {}
};

class NullPointException : public ExceptionBase
{
public:
	NullPointException(int line, string function, string file, string type = "NullPointException") : ExceptionBase(line, function, file, type) {}
};

class BadAllocException : public ExceptionBase
{
public:
	BadAllocException(int line, string function, string file, string type = "BadAllocException") : ExceptionBase(line, function, file, type) {}
};
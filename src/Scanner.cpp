#include "Scanner.h"

namespace json {
	Scanner::Scanner(const std::string& source)
		: _source(source), ptr(0), value_number(0.0f), value_string("")
	{
	}

	Scanner::Scanner()
		: _source(""), ptr(0), value_number(0.0f), value_string("")
	{
	}

	Scanner::JsonTokenType Scanner::Scan()
	{
		if (this->AtEnd())
		{
			return JsonTokenType::END_OF_SOURCE;
		}

		char c = this->Advance();
		switch (c)
		{
		case '\"':
			this->ScanString();
			return JsonTokenType::VAlUE_STRING;
		case '-':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			this->ScanNumber();
			return JsonTokenType::VALUE_NUMBER;
		case '{':
			return JsonTokenType::BEGIN_OBJECT;
		case '}':
			return JsonTokenType::END_OBJECT;
		case '[':
			return JsonTokenType::BEGIN_ARRAY;
		case ']':
			return JsonTokenType::END_ARRAY;
		case ':':
			return JsonTokenType::SEP_COLON;
		case ',':
			return JsonTokenType::SEP_COMMA;
		case 't':
			this->ScanTrue();
			return JsonTokenType::LITERAL_TRUE;
		case 'f':
			this->ScanFalse();
			return JsonTokenType::LITERAL_FALSE;
		case 'n':
			this->Scannull();
			return JsonTokenType::LITERAL_NULL;
		default:
			break;
		}
		return JsonTokenType();
	}
	std::string Scanner::getstring() const
	{
		return this->value_string;
	}
	float Scanner::getnumber() const
	{
		return this->value_number;
	}
	bool Scanner::AtEnd()
	{
		if (ptr >= _source.length())
		{
			return true;
		}
		return false;
	}

	char Scanner::Advance()
	{
		if (ptr >= _source.length())
		{
			throw new std::logic_error("at end of source.");
		}
		return _source[ptr++];
	}

	char Scanner::Peek()
	{
		if (ptr >= _source.length())
		{
			throw new std::logic_error("at end of source.");
		}
		return _source[ptr];
	}

	char Scanner::Peeknext()
	{
		if (this->AtEnd())
		{
			return '\0';
		}
		return _source[ptr + 1];
	}

	void Scanner::ScanNumber()
	{
		size_t pos = this->ptr - 1;
		while (IsDigit(Peek()))
		{
			Advance();
		}
		if (Peek() == '.' && this->IsDigit(this->Peeknext()))
		{
			Advance();
			while (this->IsDigit(Peek()))
			{
				Advance();
			}
		}

		value_number = std::atof(_source.substr(pos, ptr - pos).c_str());
	}

	void Scanner::ScanString()
	{
		size_t pos = this->ptr;

		while (Peek() != '\"' && !AtEnd())
		{
			this->Advance();
		}
		if (this->AtEnd())
		{
			throw new std::logic_error("at end of source. Maybe has error.");
		}
		this->value_string = _source.substr(pos, ptr - pos);
		Advance();
	}

	void Scanner::ScanTrue()
	{
		if (_source.compare(ptr, 3, "rue") == 0)
		{
			ptr += 3;
		}
		else
		{
			throw new std::logic_error("read true error.");
		}
	}

	void Scanner::ScanFalse()
	{
		if (_source.compare(ptr, 3, "alse") == 0)
		{
			ptr += 4;
		}
		else
		{
			throw new std::logic_error("read flase error.");
		}
	}

	void Scanner::Scannull()
	{
		if (_source.compare(ptr, 3, "ull") == 0)
		{
			ptr += 3;
		}
		else
		{
			throw new std::logic_error("read null error.");
		}
	}

	bool Scanner::IsDigit(char c)
	{
		return ('0' <= c && c <= '9') || c == 'e' || c == 'E';
	}
}

#include <iostream>
#include "Scanner.h"

int main() {
	const char* c = "  {\"name\": 1.2e10, \"age\": 12}";
	json::Scanner scan(c);
	json::Scanner::JsonTokenType type;
	while ((type = scan.Scan()) != json::Scanner::JsonTokenType::END_OF_SOURCE)
	{
		switch (type)
		{
		case json::Scanner::JsonTokenType::BEGIN_OBJECT:
			break;
		case json::Scanner::JsonTokenType::END_OBJECT:
			break;
		case json::Scanner::JsonTokenType::BEGIN_ARRAY:
			break;
		case json::Scanner::JsonTokenType::END_ARRAY:
			break;
		case json::Scanner::JsonTokenType::VALUE_NUMBER:
			std::cout << scan.getnumber() << std::endl;
			break;
		case json::Scanner::JsonTokenType::VAlUE_STRING:
			std::cout << scan.getstring() << std::endl;
			break;
		case json::Scanner::JsonTokenType::LITERAL_TRUE:
			break;
		case json::Scanner::JsonTokenType::LITERAL_FALSE:
			break;
		case json::Scanner::JsonTokenType::LITERAL_NULL:
			break;
		case json::Scanner::JsonTokenType::SEP_COLON:
			break;
		case json::Scanner::JsonTokenType::SEP_COMMA:
			break;
		case json::Scanner::JsonTokenType::END_OF_SOURCE:
			break;
		default:
			break;
		}
	}
	return 0;
}
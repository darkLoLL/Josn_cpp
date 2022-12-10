#ifndef _SCANNER_H
#define _SCANNER_H

#include <string>
#include <stdexcept>

namespace json {

	class Scanner
	{
	public:
		enum class JsonTokenType {
			///< char {
			BEGIN_OBJECT,
			///< char }
			END_OBJECT, 

			///< char [
			BEGIN_ARRAY,
			///< char ]
			END_ARRAY,

			///< number
			VALUE_NUMBER,
			///< string
			VAlUE_STRING,
			
			///< true
			LITERAL_TRUE,
			//< false
			LITERAL_FALSE,
			///< null
			LITERAL_NULL,

			///< char :
			SEP_COLON,
			///< char ,
			SEP_COMMA,
			///< EOF
			END_OF_SOURCE 
		};

		Scanner(const std::string& source);
		Scanner();

		JsonTokenType Scan();

		std::string getstring() const;
		float getnumber() const;
	private:
		std::string _source;
		size_t ptr;

		std::string value_string;
		float value_number;
	private:
		bool AtEnd();
		char Advance();
		char Peek();
		char Peeknext();

		void ScanNumber();
		void ScanString();
		void ScanTrue();
		void ScanFalse();
		void Scannull();
		bool IsDigit(char c);
	};
}

#endif // !_SCANNER_H
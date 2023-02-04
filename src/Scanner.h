#ifndef _SCANNER_H
#define _SCANNER_H

namespace json {

	class Scanner
	{
	public:
		enum class JsonTokenType {
			BEGIN_OBJECT, //< char {
			END_OBJECT, //< char }

			BEGIN_ARRAY, //< char [
			END_ARRAY, //< char ]

			VALUE_NUMBER, //< number
			VAlUE_STRING, //< string
			
			LITERAL_TRUE, //< true
			LITERAL_FALSE, //< false
			LITERAL_NULL, //< null

			SEP_COLON, //< char :
			SEP_COMMA, //< char ,
			
			END_OF_SOURCE //< EOF
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
#ifndef _JSONELEMENT_H
#define _JSONELEMENT_H

namespace json {
class JsonElement;
	using JsonArray = std::vector<JsonElement>;
	using JsonObject = std::map<std::string, JsonElement>;
	
	class JsonElement
	{
	public:
		enum class JsonType
		{
			JSON_NULL, //< object NULL
			JSON_BOOL, //< object bool
			JSON_NUMBER, //< object number
			JSON_STRING, //< json string
			JSON_ARRAY, //< json array
			JSON_OBJECT //< json object
		};

		union Value
		{
			bool _boolean;
			float _number;
			std::string* _string;
			JsonArray* _array;
			JsonObject* _object;
		};
	public:
		JsonElement();
		JsonElement(const bool value);
		JsonElement(const float value);
		JsonElement(const std::string& value);
		JsonElement(const JsonElement& other);
		JsonElement& operator=(JsonElement& other);
		
		operator std::string();
		operator bool();
		operator float();

		~JsonElement();
	private:
		JsonType _type;
		Value _value;
	private:
		void clear();
	};
}
#endif // !_JSONELEMENT_H
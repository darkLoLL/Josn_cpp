#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include "JsonElement.h"

namespace json {
	JsonElement::JsonElement(): _type(JsonType::JSON_NULL) {
	}

	JsonElement::JsonElement(const bool value)
		: _type(JsonType::JSON_BOOL)
	{
		_value._boolean = value;
	}

	JsonElement::JsonElement(const float value)
		: _type(JsonType::JSON_NUMBER)
	{
		_value._number = value;
	}

	JsonElement::JsonElement(const std::string& value)
		: _type(JsonType::JSON_STRING)
	{
		_value._string = new std::string(value);
	}

	JsonElement::JsonElement(const JsonElement& other)
		: _type(other._type)
	{
		switch (_type)
		{
		case json::JsonElement::JsonType::JSON_NULL:
			break;
		case json::JsonElement::JsonType::JSON_BOOL:
			this->_value._boolean = other._value._boolean;
			break;
		case json::JsonElement::JsonType::JSON_NUMBER:
			this->_value._number = other._value._number;
			break;
		case json::JsonElement::JsonType::JSON_STRING:
			this->_value._string = new std::string(*other._value._string);
			break;
		case json::JsonElement::JsonType::JSON_ARRAY:
			this->_value._array = new JsonArray(other._value._array->begin(), other._value._array->end());
			break;
		case json::JsonElement::JsonType::JSON_OBJECT:
			this->_value._object = new JsonObject(other._value._object->begin(), other._value._object->end());
			break;
		default:
			break;
		}
	}

	JsonElement& JsonElement::operator=(JsonElement& other)
	{
		this->clear();
		this->_type = other._type;
		switch (_type)
		{
		case json::JsonElement::JsonType::JSON_NULL:
			break;
		case json::JsonElement::JsonType::JSON_BOOL:
			this->_value._boolean = other._value._boolean;
			break;
		case json::JsonElement::JsonType::JSON_NUMBER:
			this->_value._number = other._value._number;
			break;
		case json::JsonElement::JsonType::JSON_STRING:
			this->_value._string = new std::string(*other._value._string);
			break;
		case json::JsonElement::JsonType::JSON_ARRAY:
			this->_value._array = new JsonArray(other._value._array->begin(), other._value._array->end());
			break;
		case json::JsonElement::JsonType::JSON_OBJECT:
			this->_value._object = new JsonObject(other._value._object->begin(), other._value._object->end());
			break;
		default:
			break;
		}
		return *this;
	}

	JsonElement::operator std::string()
	{
		return *(this->_value._string);
	}

	JsonElement::operator bool()
	{
		return this->_value._boolean;
	}

	JsonElement::operator float()
	{
		return this->_value._number;
	}

	JsonElement::~JsonElement()
	{
		this->clear();
	}

	void JsonElement::clear()
	{
		switch (_type)
		{
		case json::JsonElement::JsonType::JSON_NULL:
			break;
		case json::JsonElement::JsonType::JSON_BOOL:
			this->_value._boolean = false;
			break;
		case json::JsonElement::JsonType::JSON_NUMBER:
			this->_value._number = 0.0f;
			break;
		case json::JsonElement::JsonType::JSON_STRING:
			delete this->_value._string;
			break;
		case json::JsonElement::JsonType::JSON_ARRAY:
			delete this->_value._array;
			break;
		case json::JsonElement::JsonType::JSON_OBJECT:
			delete this->_value._object;
			break;
		default:
			break;
		}
		this->_type = JsonType::JSON_NULL;
	}
}
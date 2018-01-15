#pragma once

#include <map>
#include <vector>
#include <memory>

#include <eggs/variant.hpp>




template<typename T, typename S>
void Serialize(T Serializer, S v)
{
	v.Serialize(Serializer);
}



class JsonValue;
class JsonObject
{
public:
	JsonObject() = default;

	template<typename T>
	JsonObject(T value)
	{
		JsonSerializer serializer;
		Serialize(serializer, value);
		*this = serializer.object;
	}

	template<typename T>
	T Get()
	{
		T res;
		JsonDeserializer serializer;


	}

	std::map<std::string, JsonValue> values;
};


class JsonDeserializer;


class JsonSerializer
{
public:
	template<typename T>
	void operator()(std::string name, T value)
	{
		object.values[name] = value;
	}

	template<typename T>
	void operator()(std::string name, std::unordered_set<T> &value, std::function<JsonObject(T)> onSave, std::function<T(JsonDeserializer)> onLoad)
	{
		//object.values[name] = value;
	}

	JsonObject object;
};


class JsonDeserializer
{
public:
	template<typename T>
	void operator()(std::string name, T value)
	{
		//object.values[name] = value;
	}

#if 0
	template<typename T>
	void operator()(std::string name, T value, std::function<void()> onSave, std::function<void()> onLoad)
	{
		//object.values[name] = value;
	}
#endif


	template<typename T>
	void operator()(std::string name, std::unordered_set<T> &value, std::function<JsonObject(T)>onSave, std::function<T(JsonDeserializer)> onLoad)
	{
		//object.values[name] = value;
	}
};


using JsonValueTypeSet = eggs::variant<
	nullptr_t,
	bool,
	int32_t,
	double,
	std::string,
	JsonObject,
	std::vector<JsonValue>
>;


class JsonValue : public JsonValueTypeSet
{
public:
	JsonValue()
		: JsonValueTypeSet()
	{
	}

	template<typename T>
	JsonValue(std::unordered_set<T> values)
		: JsonValueTypeSet()
	{
		std::vector<JsonValue> json_array;
		for (const auto &value : values)
		{
			json_array.push_back(value);
		}
		*this = json_array;
	}

	template<typename T>
	JsonValue(std::shared_ptr<T> value_ptr)
		: JsonValueTypeSet()
	{
		*(this) = *value_ptr;
	}

	template<typename T>
	JsonValue(T value)
		: JsonValueTypeSet(value)
	{
	}
};


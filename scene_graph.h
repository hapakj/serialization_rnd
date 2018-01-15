#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>
#include <memory>
#include <functional>

#include<glm/glm.hpp>

#include"json_object.h"



struct Color
{
	Color() = default;
	Color(float r, float g, float b)
		: r(r)
		, g(g)
		, b(b)
	{}

	float r{ 0.0f };
	float g{ 0.0f };
	float b{ 0.0f };
	float a{ 0.0f };
};


class Object
{
public:
	Object(std::string name)
		: m_name(name)
	{
	}

	std::string m_name;
	uint64_t m_guid;

};


class Node : public Object
{
public:
	Node(std::string name)
		: Object(name)
	{
	}

	std::weak_ptr<Node> m_parent;
	std::unordered_set<std::shared_ptr<Node>> m_children;

	glm::mat4x4 m_local_transform;

#if 1
	void Serialize(JsonSerializer &json)
	{
		//json.values["name"] = m_name;
		//json.values["children"] = m_children;
	}
#endif
};


class LightNode : public Node
{
public:
	Color m_color;
};


class MeshNode : public Node
{
public:
	std::string m_meshname;
};


class Actor : public Node
{
public:
	Actor(std::string name)
		: Node(name)
	{
	}
};



class World : public Object
{
public:
	World(std::string name)
		: Object(name)
	{
	}

	std::unordered_set<std::shared_ptr<Actor>> m_actors;


	template<typename T>
	void Serialize(T Serializer)
	{
		std::function<std::shared_ptr<Actor>(JsonDeserializer)> OnActorLoad = [](JsonDeserializer Deserializer) -> std::shared_ptr<Actor>
		{
			std::string name;
			Deserializer("name", name);

			std::shared_ptr<Actor> actor = std::make_shared<Actor>(name);
			//actor->Serialize(Deserializer);

			return actor;
		};

		Serializer("name", m_name);
		Serializer("actors", m_actors, std::function<JsonObject(std::shared_ptr<Actor>)>(), OnActorLoad);
	}
};


#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>
#include <memory>

#include<glm/glm.hpp>

#ifdef USE_CEREAL
#include<cereal/types/memory.hpp>
#include<cereal/types/unordered_set.hpp>
#endif


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

#ifdef USE_CEREAL
	template<class Archive>
	void load(Archive &ar)
	{
		ar(cereal::make_nvp("name", m_name));
	}

	template<class Archive>
	void save(Archive &ar) const
	{
		ar(cereal::make_nvp("name", m_name));
	}
#endif
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

#ifdef USE_CEREAL
	template<class Archive>
	void load(Archive &ar)
	{
		ar(cereal::base_class<Object>(this));
	}

	template<class Archive>
	void save(Archive &ar) const
	{
		ar(cereal::base_class<Object>(this));
	}
#endif
};



class World : public Object
{
public:
	World(std::string name)
		: Object(name)
	{
	}

	std::unordered_set<std::shared_ptr<Actor>> m_actors;

#ifdef USE_CEREAL
	template<class Archive>
	void save(Archive &ar) const
	{
		ar(cereal::make_nvp("object", cereal::base_class<Object>(this)));

		for (auto actor : m_actors)
		{
			ar(*actor);
		}
	}

	template<class Archive>
	void load(Archive &ar)
	{
	}
#endif
};


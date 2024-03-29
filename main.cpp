#include "scene_graph.h"

#include <iostream>
#include <fstream>

#ifdef USE_CEREAL
#include <cereal\cereal.hpp>
#include <cereal\archives\json.hpp>
#endif


#ifdef USE_CEREAL
//
//	Test Cereal 1 color
//

template<class Archive>
void serialize(Archive &ar, Color &c)
{
	ar(cereal::make_nvp("r", c.r),
		cereal::make_nvp("g", c.g),
		cereal::make_nvp("b", c.b));
}

void test1_cereal()
{
	std::ofstream os("test1.json");
	cereal::JSONOutputArchive ar(os);

	Color color;

	ar(cereal::make_nvp("color", color));
}




//
//	Test 2 World
//

std::unique_ptr<World> CreateTestWorld()
{
	std::unique_ptr<World> world = std::unique_ptr<World>(new World("teszt_vilag"));

	world->m_actors.insert(std::make_shared<Actor>("actor1"));
	world->m_actors.insert(std::make_shared<Actor>("actor2"));

	return world;
}



void test2_cereal()
{
	std::ofstream os("test2.json");
	cereal::JSONOutputArchive ar(os);

	auto world = CreateTestWorld();

	ar(cereal::make_nvp("world", *world));
}
#endif


int main(int /*argc*/, char** /*argv*/)
{
#ifdef USE_CEREAL
	test1_cereal();
	test2_cereal();
#endif
}


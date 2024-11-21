//scene.cpp

#include "scene.h"
#include <iostream>

std::vector<std::shared_ptr<Entity>>&Scene::getEnts() {
	return _ents.list;
}

void Scene::render() { 
	//std::cout << "scene.render.start\n";
	_ents.render(); 
	//std::cout << "scene.render.end\n";
}

void Scene::update(double dt) {
	_ents.update(dt);
}
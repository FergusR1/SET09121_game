//scene.cpp

#include "scene.h"
#include <iostream>

std::vector<std::shared_ptr<Entity>>&Scene::getEnts() {
	return _ents.list;
}

void Scene::render() { 
	_ents.render(); 
}

void Scene::update(double dt) {
	_ents.update(dt);
}
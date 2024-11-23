//LevelSystem.cpp
#include "../lib_tile_level_loader/LevelSystem.h"
#include "LevelSystem.h"
#include <fstream>

#define ls LevelSystem

using namespace std;
using namespace sf;

map<ls::TILE, Color> ls::_colours = {
    { ls::WALL, Color::White },
    { ls::START, Color::Cyan },
    { ls::END, Color::Green },
    { ls::EMPTY, Color::Black },
    { ls::WAYPOINT, Color::Blue },
    { ls::ENEMY, Color::Red }
};

size_t ls::_width = 0;
size_t ls::_height = 0;
Vector2f ls::_offset = {0,0};
float ls::_tileSize = 0;
unique_ptr < ls::TILE[] > ls::_tiles = nullptr;
vector<unique_ptr<RectangleShape>> ls::_sprites;


//void ls::loadLevelFile(const std::string& path, float tileSize) {
void LevelSystem::loadLevelFile(const std::string & path, float tileSize) {
  _tileSize = tileSize;
  size_t w = 0, h = 0;
  string buffer;

  // Load in file to buffer
  ifstream f(path);
  if (f.good()) {
    f.seekg(0, std::ios::end);
    buffer.resize(f.tellg());
    f.seekg(0);
    f.read(&buffer[0], buffer.size());
    f.close();
  } else {
    //std::cout << "Loading level file: " << path << std::endl;
    throw string("Couldn't open level file: ") + path;
  }

  std::vector<TILE> temp_tiles;
  for (int i = 0; i < buffer.size(); ++i) {
    const char c = buffer[i];
    cout << c;
    switch (c) {
    case 'w':
      temp_tiles.push_back(WALL);
      break;
    case 's':
      temp_tiles.push_back(START);
      break;
    case 'e':
      temp_tiles.push_back(END);
      break;
    case ' ':
      temp_tiles.push_back(EMPTY);
      break;
    case '+':
      temp_tiles.push_back(WAYPOINT);
      break;
    case 'n':
      temp_tiles.push_back(ENEMY);
      break;
    case '\n':      // end of line
      if (w == 0) { // if we haven't written width yet
        w = i;      // set width
      }
      h++; // increment height
      break;
    default:
      cout << c << endl; // Don't know what this tile type is
    }
  }
  if (temp_tiles.size() != (w * h)) {
    throw string("Can't parse level file") + path;
  }
  _tiles = std::make_unique<TILE[]>(w * h);
  _width = w; //set static class vars
  _height = h;
  std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
  cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;
  buildSprites();
}

void LevelSystem::buildSprites() {
  _sprites.clear();
  for (size_t y = 0; y < LevelSystem::getHeight(); ++y) {
    for (size_t x = 0; x < LevelSystem::getWidth(); ++x) {
      auto s = make_unique<RectangleShape>();
      s->setPosition(getTilePosition({x, y}));
      s->setSize(Vector2f(_tileSize, _tileSize));
      s->setFillColor(getColor(getTile({x, y})));
      _sprites.push_back(move(s));
    }
  }
}

Vector2f LevelSystem::getTilePosition(Vector2ul p) {
  return (Vector2f(p.x, p.y) * _tileSize);
}

LevelSystem::TILE LevelSystem::getTile(Vector2ul p) {
  if (p.x > _width || p.y > _height) {
    throw string("Tile out of range: ") + to_string(p.x) + "," + to_string(p.y) + ")";
  }
  return _tiles[(p.y * _width) + p.x];
}


LevelSystem::TILE LevelSystem::getTileAt(Vector2f v) {
  auto a = v - _offset;
  if (a.x < 0 || a.y < 0) {
    throw string("Tile out of range ");
  }
  return getTile(Vector2ul((v - _offset) / (_tileSize)));
}

std::vector<sf::Vector2ul> LevelSystem::findTiles(TILE tile) {
    std::vector<sf::Vector2ul> foundTiles;
    for (int i = 0; i < _width * _height; i++) {
        if (_tiles[i] == tile) {
            int w = i % _width;
            int h = i / _width;  // Corrected here
            foundTiles.push_back(sf::Vector2ul(w, h));
        }
    }
    std::cout << "Found " << foundTiles.size() << " tiles of type " << tile << ".\n";
    return foundTiles;
}


size_t ls::getWidth() {
    return(_width);
}

size_t ls::getHeight() {
    return(_height);
}

Color ls::getColor(TILE t) {
    // Return the color associated with the tile type
    auto it = _colours.find(t);
    if (it != _colours.end()) {
        return it->second;
    }
    // Return a default color if not found
    return Color::Transparent;
}

float LevelSystem::getTileSize() {
    return _tileSize;
}

void LevelSystem::Render(RenderWindow &window) {
  for (size_t i = 0; i < _width * _height; ++i) {
    window.draw(*_sprites[i]);
  }
}
/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Map
*/

#include "../include/Map.hpp"
#include "../include/Blocks/Box.hpp"
#include "../include/Blocks/Wall.hpp"
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <iostream>

b_map::Map::Map(int size, irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver)
: _dev(device), _smgr(smgr), _dri(driver), _size(size), _last_explo_stat({{-1, -1}, -1, -1})
{
    std::vector<std::vector<Block>> map(size);
    for ( int i = 0 ; i < size; i++ )
        map[i].resize(size);
    _map = map;
    generate_map(size);

    if(!_music.openFromFile("../assets/sounds/game_music.ogg"))
        std::cout << "FAILED TO LOAD MAP MUSIC\n";
    _music.setVolume(3.f);
    _music.play();
}

b_map::Map::~Map()
{
    for (auto b : _blocks) {
        delete b;
    }
    _blocks.clear();
    for (auto it : _map) {
        it.clear();
    }
    _map.clear();
}


int b_map::Map::to_correct(int x, int y)
{
    if (_map[x][y] == b_map::Block::WALL) {
        if (_map[x + 1][y] == b_map::Block::EMPTY || _map[x - 1][y] == b_map::Block::EMPTY ||
           _map[x][y - 1] == b_map::Block::EMPTY || _map[x][y + 1] == b_map::Block::EMPTY)
        {
            _map[x][y] = b_map::Block::BOX;
        }
    }
    if (_map[x][y] == b_map::Block::WALL || _map[x][y] == b_map::Block::BOX) {
        if (_map[x + 1][y] == b_map::Block::WALL && _map[x - 1][y] == b_map::Block::WALL &&
            _map[x][y - 1] == b_map::Block::WALL && _map[x][y + 1] == b_map::Block::WALL)
        {
            if (_size - 2 != y)
                _map[x][y + 1] = b_map::Block::BOX;
            else
                _map[x][y - 1] = b_map::Block::BOX;

            if (_map[x][y] == b_map::Block::WALL)
                _map[x][y] = b_map::Block::BOX;
        }
    }
    return 1;
}


void b_map::Map::generate_map(int size)
{
    
    //EXTERIOR WALLS
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == 0 || i == size - 1 || j == 0 || j == size - 1)
                _map[i][j] = b_map::Block::WALL; //Indestructible walls
            else
                _map[i][j] = b_map::Block::EMPTY; // Empty space
        }   
    }


    //INTERIOR WALLS
    for (int i = 1; i < size - 1; i++) {
        for (int j = 1; j < size - 1; j++) {
            int random = rand();
            if (random % 10 == 0)
                _map[i][j] = b_map::Block::WALL; // Indestructible
            else  
                _map[i][j] = b_map::Block::BOX; // Destructible
        }   
    }

    //Space For The players at the corners
    _map[1][1] = b_map::Block::EMPTY;
    _map[2][1] = b_map::Block::EMPTY;
    _map[1][2] = b_map::Block::EMPTY;

    _map[size - 2][1] = b_map::Block::EMPTY;
    _map[size - 3][1] = b_map::Block::EMPTY;
    _map[size - 2][2] = b_map::Block::EMPTY;

    _map[1][size - 2] = b_map::Block::EMPTY;
    _map[2][size - 2] = b_map::Block::EMPTY;
    _map[1][size - 3] = b_map::Block::EMPTY;

    _map[size - 2][size - 2] = b_map::Block::EMPTY;
    _map[size - 3][size - 2] = b_map::Block::EMPTY;
    _map[size - 2][size - 3] = b_map::Block::EMPTY;


    for (int i = 1; i < size - 1; i++) {
        for (int j = 1; j < size - 1; j++) {
            to_correct(i, j);
        }
    }
}

void b_map::Map::display_map()
{
    std::vector<b_map::IBlock*> blocks = {};

    for (size_t x = 0; x < _map.size(); x++)
    {
        for (size_t y = 0; y < _map[x].size(); y++)
        {
            IBlock* block;
            switch (_map[x][y])
            {
            case Block::WALL:
                block = new Wall(x, y);
                break;
            case Block::BOX:
                block = new Box(x, y);
                break;
            default:
                block = NULL;
            }

            if (block) {
                block->display(_dev, _smgr, _dri);
                blocks.push_back(block);
            }
        }
    }
    _blocks = blocks;
}

b_map::Powerup_type b_map::Map::zfind_powerup(int x, int y)
{
    auto pow = std::find_if(_blocks.begin(), _blocks.end(),
                    [&x, &y](IBlock* block) { return (block->getX() == x && block->getY() == y); }
        );
    b_map::Powerup *tmp = static_cast<b_map::Powerup*>(*pow);
    _map[x][y] = b_map::Block::EMPTY;
    return (*tmp).getType();
}

bool b_map::Map::destroy_block(const int x, const int y)
{
    if (_map[x][y] == b_map::Block::BOX)
    {
        if (rand() % 8 == 0) {
            _map[x][y] = b_map::Block::POWERUP;
            b_map::IBlock *newp = new Powerup(x, y, (b_map::Powerup_type)(rand() % 4));
            newp->display(_dev, _smgr, _dri);
            b_map::Powerup* tmp = static_cast<Powerup *>(newp);
            _powerups.push_back(*tmp);
        }
        else
            _map[x][y] = b_map::Block::EMPTY;

        auto box = std::find_if(_blocks.begin(), _blocks.end(),
                    [&x, &y](IBlock* block) { return (block->getX() == x && block->getY() == y); }
        );
        Box* tmp = static_cast<Box*>(*box);
        _blocks.erase(box);
        tmp->destroy();
        return true;
    }
    if (_map[x][y] == b_map::Block::BOMB)
    {
        auto block = std::find_if(_blocks.begin(), _blocks.end(),
                    [&x, &y](IBlock* block) { return (block->getX() == x && block->getY() == y); }
        );
        static_cast<Bomb *>(*block)->force_detonate();
        return true;
    }
    return false;
}

void b_map::Map::place_bomb(Bomb* new_bomb)
{
    _map[new_bomb->getX()][new_bomb->getY()] = b_map::Block::BOMB;
    new_bomb->display(_dev, _smgr, _dri);
    _blocks.push_back(new_bomb);
    int b_x = new_bomb->getX();
    int b_y = new_bomb->getY();
    for (int i = 1; i < new_bomb->getPower() + 1; i++)
    {
        if ( b_x + i <= _size - 1 &&  b_y + i <= _size - 1 && b_x - i >= 0 &&  b_y - i >= 0) {
            if (_map[b_x + i][b_y] == b_map::Block::EMPTY)
                _map[b_x + i][b_y] = b_map::Block::EMPTY_NOT_SAFE;
            if (_map[b_x - i][b_y] == b_map::Block::EMPTY)
                _map[b_x - i][b_y] = b_map::Block::EMPTY_NOT_SAFE;
            if (_map[b_x][b_y + i] == b_map::Block::EMPTY)
                _map[b_x][b_y + i] = b_map::Block::EMPTY_NOT_SAFE;
            if (_map[b_x][b_y - i] == b_map::Block::EMPTY)
                _map[b_x][b_y - i] = b_map::Block::EMPTY_NOT_SAFE;
        }
    }
}

void b_map::Map::delete_bomb(const int x, const int y)
{
    if (_map[x][y] != b_map::Block::BOMB) return;

    if (!buffer.loadFromFile("../assets/sounds/bomb_goes_boom.wav"))
        std::cout << "FAILED TO LOAD BOMB DESTROY SOUND\n";
    _sound.setVolume(10.f);
    _sound.setBuffer(buffer);
    _sound.play();

    _map[x][y] = b_map::Block::EMPTY;
    auto bomb = std::find_if(_blocks.begin(), _blocks.end(),
                [&x, &y](IBlock* block) { return (block->getX() == x && block->getY() == y); }
    );
    Bomb* tmp = static_cast<Bomb*>(*bomb);
    _last_explo_stat.pos = {x, y};
    _last_explo_stat.pow = tmp->getPower();
    _last_explo_stat.id = tmp->getOwner();
    _blocks.erase(bomb);
    tmp->detonate();
}

void b_map::Map::update_bombs()
{
    _last_explo_stat.id = -1;
    for (size_t x = 0; x < _map.size(); x++) {
        for (size_t y = 0; y < _map[x].size(); y++) {
            if (_map[x][y] == b_map::Block::BOMB) {
                auto tmp = std::find_if(_blocks.begin(), _blocks.end(),
                    [&x, &y](IBlock* block) { return (block->getX() == x && block->getY() == y); }
                );
                Bomb* bomb = static_cast<Bomb*>(*tmp);
                if ((float)(clock() - bomb->getClock()) / CLOCKS_PER_SEC >= BOMB_TIMER) {
                    detonate_bomb(1, 0, bomb);
                    detonate_bomb(0, 1, bomb);
                    detonate_bomb(-1, 0, bomb);
                    detonate_bomb(0, -1, bomb);
                    delete_bomb(bomb->getX(), bomb->getY());
                    return;
                }
            }
        }
    }
}

void b_map::Map::detonate_bomb(const int x, const int y, const Bomb *bomb, const int power)
{
    if (power >= bomb->getPower()) return;

    if (x == 0) {
        if (destroy_block(bomb->getX(), bomb->getY() + y * (power + 1))) {
            detonate_bomb(x, y, bomb, power + 1);
        }
    }
    if (y == 0) {
        if (destroy_block(bomb->getX() + x * (power + 1), bomb->getY())) {
            detonate_bomb(x, y, bomb, power + 1);
        }
    }
}

// void b_map::Map::place_powerup(int x, int y, b_map::Powerup_type type)
// {
//     _map[x][y] = b_map::Block::POWERUP;
//     b_map::IBlock *block = new Powerup(x, y, type);
//     //block->display(device, smgr, driver);
//     _blocks.push_back(block);
// }

const std::vector<std::vector<b_map::Block>> &b_map::Map::getmap() const { return _map; }

const b_map::LastExplosion &b_map::Map::getLastExplosion() const { return _last_explo_stat; }


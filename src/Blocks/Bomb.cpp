/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#include "../../include/Blocks/Bomb.hpp"
#include <time.h>

#include <iostream>

b_map::Bomb::Bomb(int x, int y, int power, int owner)
: _position({x, y}), _power(power), _clock(clock()), _owner(owner)
{
    if (!buffer.loadFromFile("../assets/sounds/bomb_appear.wav"))
        std::cout << "FAILED TO LOAD BOMB APPEARING SOUND\n";
    _sound.setBuffer(buffer);
    _sound.play();  
}

b_map::Bomb::~Bomb()
{
    _node->remove();
}

void b_map::Bomb::force_detonate() { _clock = clock() - (BOMB_TIMER + 1); }

void b_map::Bomb::detonate() const
{
    delete this;
}

void b_map::Bomb::display(irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver)
{
    irr::scene::IAnimatedMesh* mesh = smgr->getMesh("../assets/bomb/Bomb.obj");
    if (!mesh)
    {
        device->drop();
        exit(84);
    }

    _node = smgr->addMeshSceneNode(mesh, 0, -1, irr::core::vector3df(getX(), 0, getY()), irr::core::vector3df(0, 0, 0), irr::core::vector3df(0.2f, 0.2f, 0.2f));
    if (_node)
    {
        _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _node->setMaterialTexture(0, driver->getTexture("../assets/bomb/Bomb_thumb.png"));
    }
}

const int b_map::Bomb::getX() const {return _position.x;}

const int b_map::Bomb::getY() const {return _position.y;}

irr::scene::IMeshSceneNode* b_map::Bomb::getNode() const {return _node;}

irr::scene::IMesh* b_map::Bomb::getMesh() const {return _node->getMesh();}

const int b_map::Bomb::getPower() const {return _power;}

const int b_map::Bomb::getClock() const {return _clock;}

const int b_map::Bomb::getOwner() const {return _owner;}
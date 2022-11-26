/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Powerup
*/

#include "../../include/Blocks/Powerup.hpp"

b_map::Powerup::Powerup(int x, int y, b_map::Powerup_type type) : _position({x, y})
{
    _type = type;
}

b_map::Powerup::~Powerup()
{
}

void b_map::Powerup::display(irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver)
{
    irr::scene::IAnimatedMesh* mesh = smgr->getMesh("../assets/cubes/cube.obj");
    if (!mesh)
    {
        device->drop();
        exit(84);
    }

    _node = smgr->addMeshSceneNode(mesh, 0, -1, irr::core::vector3df(getX(), 0, getY()), irr::core::vector3df(0, 0, 0), irr::core::vector3df(0.7f, 0.7f, 0.7f));
    if (_node)
    {
        _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        if (_type == b_map::Powerup_type::BOMB_COUNT)
            _node->setMaterialTexture(0, driver->getTexture("../assets/powerups/bomb_capacity.png"));
        if (_type == b_map::Powerup_type::BOMB_POWER)
            _node->setMaterialTexture(0, driver->getTexture("../assets/powerups/bomb_power.png"));
        if (_type == b_map::Powerup_type::SPEEDUP)
            _node->setMaterialTexture(0, driver->getTexture("../assets/powerups/speed.png"));
        if (_type == b_map::Powerup_type::WALL_PASS)
            _node->setMaterialTexture(0, driver->getTexture("../assets/powerups/wall_pass.png"));
    }
}

const int b_map::Powerup::getX() const {return _position.x;}

const int b_map::Powerup::getY() const {return _position.y;}

b_map::Powerup_type b_map::Powerup::getType() const { return _type;}

irr::scene::IMeshSceneNode* b_map::Powerup::getNode() const {return _node;}

irr::scene::IMesh* b_map::Powerup::getMesh() const {return _node->getMesh();}
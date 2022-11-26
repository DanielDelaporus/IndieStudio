/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Wall
*/

#include "../../include/Blocks/Wall.hpp"

b_map::Wall::Wall(int x, int y) : _position({x, y})
{
}

b_map::Wall::~Wall()
{
}

void b_map::Wall::display(irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver)
{
    irr::scene::IAnimatedMesh* mesh = smgr->getMesh("../assets/cubes/cube.obj");
    if (!mesh)
    {
        device->drop();
        exit(84);
    }

    _node = smgr->addMeshSceneNode(mesh, 0, -1, irr::core::vector3df(getX(), 0, getY()));
    if (_node)
    {
        _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _node->setMaterialTexture(0, driver->getTexture("../assets/cubes/wall.png"));
    }
}

const int b_map::Wall::getX() const {return _position.x;}

const int b_map::Wall::getY() const {return _position.y;}

irr::scene::IMeshSceneNode* b_map::Wall::getNode() const {return _node;}

irr::scene::IMesh* b_map::Wall::getMesh() const {return _node->getMesh();}
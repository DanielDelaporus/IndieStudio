/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Box
*/

#include "../../include/Blocks/Box.hpp"

b_map::Box::Box(int x, int y) : _position({x, y})
{
}

b_map::Box::~Box()
{
    _node->remove();
}

void b_map::Box::display(irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver)
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
        _node->setMaterialTexture(0, driver->getTexture("../assets/cubes/box.png"));
    }
}

void b_map::Box::destroy() const { delete this; }

const int b_map::Box::getX() const {return _position.x;}

const int b_map::Box::getY() const {return _position.y;}

irr::scene::IMeshSceneNode* b_map::Box::getNode() const {return _node;}

irr::scene::IMesh* b_map::Box::getMesh() const {return _node->getMesh();}
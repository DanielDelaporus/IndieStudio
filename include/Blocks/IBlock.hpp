/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IBlock
*/

#ifndef IBLOCK_HPP_
#define IBLOCK_HPP_

#include <irrlicht.h>

struct Position { int x; int y; };

namespace b_map
{
    class IBlock {
    public:
        virtual void display(irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver) = 0;

        virtual const int getX() const = 0;
        virtual const int getY() const = 0;
        virtual irr::scene::IMeshSceneNode* getNode() const = 0;
        virtual irr::scene::IMesh* getMesh() const = 0;
    };
} // namespace b_map

#endif /* !IBLOCK_HPP_ */

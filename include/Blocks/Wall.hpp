/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Wall
*/

#ifndef WALL_HPP_
#define WALL_HPP_

#include "IBlock.hpp"

namespace b_map
{
    class Wall : public IBlock {
    public:
        Wall(int x, int y);
        ~Wall();

        void display(irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver);

        const int getX() const;
        const int getY() const;

        irr::scene::IMeshSceneNode* getNode() const;
        irr::scene::IMesh* getMesh() const;

    private:
        const Position _position;
        irr::scene::IMeshSceneNode* _node;
    };
} // namespace b_map

#endif /* !WALL_HPP_ */

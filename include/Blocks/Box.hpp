/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Box
*/

#ifndef BOX_HPP_
#define BOX_HPP_

#include "IBlock.hpp"

namespace b_map
{
    class Box : public IBlock {
    public:
        Box(int x, int y);
        ~Box();

        void display(irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver);

        void destroy() const;

        const int getX() const;
        const int getY() const;

        irr::scene::IMeshSceneNode* getNode() const;
        irr::scene::IMesh* getMesh() const;

    private:
        const Position _position;
        irr::scene::IMeshSceneNode*     _node;
    };
} // namespace b_map

#endif /* !BOX_HPP_ */

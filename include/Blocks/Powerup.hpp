/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** powerup
*/

#ifndef POWERUP_HPP_
#define POWERUP_HPP_

#include "IBlock.hpp"

namespace b_map
{
    enum Powerup_type
    {
        SPEEDUP,
        BOMB_COUNT,
        BOMB_POWER,
        WALL_PASS,
    };

    class Powerup : public IBlock {
    public:
        Powerup(int x, int y, b_map::Powerup_type type);
        ~Powerup();

        void display(irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver);

        const int getX() const;
        const int getY() const;

        b_map::Powerup_type getType() const;

        irr::scene::IMeshSceneNode* getNode() const;
        irr::scene::IMesh* getMesh() const;

    private:
        const Position _position;
        irr::scene::IMeshSceneNode* _node;
        b_map::Powerup_type _type;
    };
} // namespace b_map

#endif /* !powerup_HPP_ */

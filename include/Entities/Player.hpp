/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "../Map.hpp"
#include "../EventReceiver.hpp"

namespace entity
{
    class Player
    {
    public:
        Player(int x, int y, int id);
        virtual ~Player();

        virtual void display(irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver);

        virtual void reduceBombCount();

        virtual bool isInDeadZone(const Position &bomb_pos, const int power) const;

        virtual void move(EventReceiver &receiver, irr::f32 deltaTime, b_map::Map &map, std::vector<std::unique_ptr<Player>> &players);

        virtual const irr::core::vector3df getPosition() const;
        virtual const int getId() const;

        virtual const int getSpeed() const;
        virtual const int getBombCapacity() const;
        virtual const int getBombBlast() const;
        virtual const bool getWallPass() const;

        virtual irr::scene::IAnimatedMeshSceneNode* getNode() const;

    protected:
        virtual void translate(int x, int y, b_map::Map &map, irr::f32 deltaTime);
        virtual void putBomb(b_map::Map &map);

        std::pair<int, int> _spawn;
        int     _id;
        int     _speed;
        int     _bomb_capacity;
        int     _bomb_blast;
        bool    _wall_pass;
        int     _bomb_count;
        irr::scene::IAnimatedMeshSceneNode* _node;
    };
} // namespace entity

#endif /* !PLAYER_HPP_ */

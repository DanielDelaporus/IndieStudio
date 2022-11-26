/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "IBlock.hpp"
#include <SFML/Audio.hpp>

#define BOMB_TIMER 2

namespace b_map
{
    class Bomb : public IBlock
    {
        public:
            Bomb(int x, int y, int power, int owner);
            ~Bomb();

            void force_detonate();
            void detonate() const;

            void display(irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver);
            const int getX() const;
            const int getY() const;

            irr::scene::IMeshSceneNode* getNode() const;
            irr::scene::IMesh* getMesh() const;

            const int getPower() const;
            const int getClock() const;
            const int getOwner() const;

        private:
            sf::Sound _sound;
            sf::SoundBuffer buffer;
            const Position _position;
            const int _power;
            int _clock;
            const int _owner;
            irr::scene::IMeshSceneNode* _node;
    };
}

#endif /* !BOMB_HPP_ */

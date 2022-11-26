/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <irrlicht.h>
#include "Blocks/IBlock.hpp"
#include "Blocks/Bomb.hpp"
#include "Blocks/Powerup.hpp"

namespace b_map
{
    enum Block {
        WALL,
        BOX,
        BOMB,
        EMPTY,
        POWERUP,
        EMPTY_NOT_SAFE,
    };

    struct LastExplosion
    {
        Position    pos;
        int         pow;
        int         id;
    };

    class Map
    {
        public:
            // init map, gen;
            Map(int size, irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver);
            ~Map();

            void generate_map(int size);
            void display_map();

            bool destroy_block(const int x, const int y);

            const std::vector<std::vector<Block>> &getmap() const;
            b_map::Powerup_type find_powerup(int x, int y);
            const LastExplosion &getLastExplosion() const;
            

            void place_bomb(Bomb* new_bomb);
            void update_bombs();

        private:
            int to_correct(int x, int y);

            void delete_bomb(const int x, const int y);
            void detonate_bomb(const int x, const int y, const Bomb *bomb, const int power = 0);

        private:
            int _size;
            irr::IrrlichtDevice* _dev;
            sf::Music _music;
            sf::Sound _sound;
            sf::SoundBuffer buffer;
            irr::scene::ISceneManager* _smgr;
            irr::video::IVideoDriver* _dri;
            std::vector<std::vector<Block>> _map;
            std::vector<IBlock*>            _blocks;
            std::vector<b_map::Powerup> _powerups;
            LastExplosion _last_explo_stat;
            
    };
} 

#endif /* !MAP_HPP_ */
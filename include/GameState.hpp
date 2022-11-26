/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameState
*/

#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include "EventReceiver.hpp"
#include "Map.hpp"
#include "Entities/Player.hpp"
#include "Entities/Bot.hpp"
#include <memory>

#define PLAYER_MAX 4

const Position g_spawns[4] = {{1, 13}, {1, 1}, {13, 1}, {13, 13}};

class GameState
{
    public:
        GameState(EventReceiver &receiver);
        ~GameState();

        void start(irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, const int nb_player_total, const int nb_human);
        void update(irr::f32 deltaTime);
        void reset(irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, const int nb_player_total, const int nb_human);

    private:
        EventReceiver& _receiver;
        b_map::Map* _map;
        std::vector<std::unique_ptr<entity::Player>> _players;
};

#endif /* !GAMESTATE_HPP_ */

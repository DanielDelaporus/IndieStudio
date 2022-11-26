/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bot
*/

#include "../../include/Entities/Bot.hpp"

entity::Bot::Bot(int x, int y, int id) : Player(x, y, id), _ai(new AI_nm::AI())
{
}

entity::Bot::~Bot()
{
    delete _ai;
}

void entity::Bot::move(EventReceiver &receiver, irr::f32 deltaTime, b_map::Map &map, std::vector<std::unique_ptr<Player>> &players)
{
    _ai->set_map(map.getmap());
    _ai->set_ia_position(static_cast<int>(round(getPosition().X)), static_cast<int>(round(getPosition().Z)));
    std::vector<std::pair<int, int>> enemies_pos = {};
    for (auto enemy = players.begin(); enemy != players.end(); enemy++)
    {
        enemies_pos.push_back(std::make_pair((*enemy)->getPosition().X, (*enemy)->getPosition().Z));
    }
    _ai->set_ennemy_position(enemies_pos);

    switch (_ai->run())
    {
    case AI_nm::MOVE_UP:
        translate(0, 1, map, deltaTime);
        break;
    
    case AI_nm::MOVE_DOWN:
        translate(0, -1, map, deltaTime);
        break;
    
    case AI_nm::MOVE_LEFT:
        translate(-1, 0, map, deltaTime);
        break;
    
    case AI_nm::MOVE_RIGHT:
        translate(1, 0, map, deltaTime);
        break;
    
    case AI_nm::BOMB:
        putBomb(map);
        break;
    
    default:
        break;
    }
}

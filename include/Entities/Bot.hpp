/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bot
*/

#ifndef BOT_HPP_
#define BOT_HPP_

#include "Player.hpp"
#include "../AI/AI.hpp"

namespace entity
{
    class Bot : public Player
    {
    public:
        Bot(int x, int y, int id);
        virtual ~Bot() final;

        virtual void move(EventReceiver &receiver, irr::f32 deltaTime, b_map::Map &map, std::vector<std::unique_ptr<Player>> &players) final;

    private:
        AI_nm::AI* _ai;
    };
} // namespace entity

#endif /* !BOT_HPP_ */

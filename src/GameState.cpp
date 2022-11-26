/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameState
*/

#include "../include/GameState.hpp"
#include <ctime>
#include <algorithm>

GameState::GameState(EventReceiver &receiver)
: _receiver(receiver), _map(NULL)
{
    std::srand(std::time(0));
}

GameState::~GameState()
{
    _players.clear();
    if (_map) { delete _map; }
}

void GameState::start(irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver,
    const int nb_player_total, const int nb_human)
{
    _map = new b_map::Map(15, device, smgr, driver);
    _map->display_map();

    const int max = (nb_player_total > PLAYER_MAX) ? PLAYER_MAX : nb_player_total;
    for (size_t id = 0; id < max; id++)
    {
        if (id < nb_human)
        {
            std::unique_ptr<entity::Player> p_ptr(new entity::Player(g_spawns[id].x, g_spawns[id].y, id));
            _players.push_back(std::move(p_ptr));
        }
        else
        {
            std::unique_ptr<entity::Bot> b_ptr(new entity::Bot(g_spawns[id].x, g_spawns[id].y, id));
            _players.push_back(std::move(b_ptr));
        }
    }
    for (auto player = _players.begin(); player != _players.end(); player++) {
        (*player)->display(device, smgr, driver);
    }
}

void GameState::update(irr::f32 deltaTime)
{
    if (_players.size() < 2)
    {
        return;
    }
    
    for (auto player = _players.begin(); player != _players.end(); player++)
    {
        (*player)->move(_receiver, deltaTime, *_map, _players);
    }
    _map->update_bombs();
    const b_map::LastExplosion bomb_stat = _map->getLastExplosion();
    if (bomb_stat.id >= 0)
    {
        auto player = std::find_if(_players.begin(), _players.end(), [bomb_stat](auto const& p) {return p->getId() == bomb_stat.id; });
        if (player != _players.end()) {
            (*player)->reduceBombCount();
        }
        _players.erase(std::remove_if(_players.begin(), _players.end(),
            [bomb_stat](auto const& p){ return p->isInDeadZone(bomb_stat.pos, bomb_stat.pow); }
            ), _players.end());
        _players.shrink_to_fit();
    }
}

void GameState::reset(irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver,
    const int nb_player_total, const int nb_human)
{
    if (_map) {
        delete _map;
    }
    _players.clear();
    _players.shrink_to_fit();

    start(device, smgr, driver, nb_player_total, nb_human);
}

/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Player
*/

#include "../../include/Entities/Player.hpp"

entity::Player::Player(int x, int y, int id)
: _spawn(x, y), _id(id), _speed(0), _bomb_capacity(1), _bomb_blast(1), _wall_pass(false), _bomb_count(0)
{
}

entity::Player::~Player()
{
    _node->remove();
}

void entity::Player::display(irr::IrrlichtDevice* device, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver)
{
    irr::scene::IAnimatedMesh* mesh = smgr->getMesh("../assets/players/Peon.obj");
    if (!mesh)
    {
        device->drop();
        exit(84);
    }

    _node = smgr->addAnimatedMeshSceneNode(mesh, 0, -1, irr::core::vector3df(_spawn.first, 0, _spawn.second), irr::core::vector3df(0, 0, 0), irr::core::vector3df(0.2f, 0.2f, 0.2f));
    if (_node)
    {
        _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        if (_id == 0)
            _node->setMaterialTexture(0, driver->getTexture("../assets/players/player1.png"));
        if (_id == 1)
            _node->setMaterialTexture(0, driver->getTexture("../assets/players/player2.png"));
        if (_id == 2)
            _node->setMaterialTexture(0, driver->getTexture("../assets/players/player3.png"));
        if (_id == 3)
            _node->setMaterialTexture(0, driver->getTexture("../assets/players/player4.png"));
    }
}

void entity::Player::putBomb(b_map::Map &map)
{
    if (_bomb_count < _bomb_capacity)
    {
        _bomb_count++;
        b_map::Bomb* bomb = new b_map::Bomb(round(getPosition().X), round(getPosition().Z), _bomb_blast, _id);
        map.place_bomb(bomb);
    }
}

void entity::Player::reduceBombCount()
{
    if (_bomb_count > 0)
        _bomb_count--;
}

void entity::Player::move(EventReceiver &receiver, irr::f32 deltaTime, b_map::Map &map, std::vector<std::unique_ptr<Player>> &players)
{
    if (receiver.IsKeyDown(controls::g_put_bomb[_id])) putBomb(map);

    if (receiver.IsKeyDown(controls::g_move_right[_id])) {
        translate(1, 0, map, deltaTime);
    } else if (receiver.IsKeyDown(controls::g_move_left[_id])) {
        translate(-1, 0, map, deltaTime);
    } else if (receiver.IsKeyDown(controls::g_move_up[_id])) {
        translate(0, 1, map, deltaTime);
    } else if (receiver.IsKeyDown(controls::g_move_down[_id])) {
        translate(0, -1, map, deltaTime);
    }
}

void entity::Player::translate(int x, int y, b_map::Map &map, irr::f32 deltaTime)
{
    irr::core::vector3df position = getPosition();

    float centerX = round(position.X);
    float centerY = round(position.Z);

    if (x == 0 && y != 0)
    {
        if (y > 0)
        {
            if (map.getmap()[centerX][y + centerY] < 3 && floor(position.Z) == centerY) {
                position.Z = centerY;
            } else {
                position.Z += y * (2 + 0.5 * _speed) * deltaTime;
            }
        }
        else
        {
            if (map.getmap()[centerX][y + centerY] < 3 && ceil(position.Z) == centerY) {
                position.Z = centerY;
            } else {
                position.Z += y * (2 + 0.5 * _speed) * deltaTime;
            }
        }
        position.X = centerX;
    }
    if (y == 0 && x != 0)
    {
        if (x > 0)
        {
            if (map.getmap()[x + centerX][centerY] < 3 && floor(position.X) == centerX) {
                position.X = centerX;
            } else {
                position.X += x * (2 + 0.5 * _speed) * deltaTime;
            }
        }
        else
        {
            if (map.getmap()[x + centerX][centerY] < 3 && ceil(position.X) == centerX) {
                position.X = centerX;
            } else {
                position.X += x * (2 + 0.5 * _speed) * deltaTime;
            }
        }
        position.Z = centerY;
    }
    _node->setPosition(position);
    if (map.getmap()[centerX][centerY] == b_map::Block::POWERUP) {
        b_map::Powerup_type power_type = map.find_powerup(centerX, centerY);
        if (power_type == b_map::Powerup_type::BOMB_COUNT)
            _bomb_capacity++;
        if (power_type == b_map::Powerup_type::BOMB_POWER)
            _bomb_blast++;
        if (power_type == b_map::Powerup_type::SPEEDUP)
            _speed++;
        if (power_type == b_map::Powerup_type::WALL_PASS)
            _wall_pass = true;
    }
}



bool entity::Player::isInDeadZone(const Position &bomb_pos, const int power) const
{
    const float x = round(getPosition().X);
    const float y = round(getPosition().Z);

    if (x == bomb_pos.x && (y <= bomb_pos.y + power && y >= bomb_pos.y - power))
    {
        return true;
    }
    if ((x <= bomb_pos.x + power && x >= bomb_pos.x - power) && y == bomb_pos.y)
    {
        return true;
    }
    return false;
}

const irr::core::vector3df entity::Player::getPosition() const {return _node->getPosition();}

const int entity::Player::getId() const {return _id;}

const int entity::Player::getSpeed() const {return _speed;}

const int entity::Player::getBombCapacity() const {return _bomb_capacity;}

const int entity::Player::getBombBlast() const {return _bomb_blast;}

const bool entity::Player::getWallPass() const {return _wall_pass;}

irr::scene::IAnimatedMeshSceneNode* entity::Player::getNode() const {return _node;}

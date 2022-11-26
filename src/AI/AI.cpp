/*
** EPITECH PROJECT, 2020
** vince52 [WSL: Debian]
** File description:
** AI
*/

#include "../../include/AI/AI.hpp"

using namespace std;

AI_nm::AI::AI()
{
}

AI_nm::AI::~AI()
{

}

AI_nm::move_enum AI_nm::AI::run()
{
    djikstra_compute();
    if (is_bomb_on_map()) {
        if (are_you_safe() == true)
            return wait_bomb_to_explode();
        else
            return go_to_safe_place();
    } else {
        int item = is_there_item_on_map();
        if (item != -1) {
            return go_and_take_item(item);
        } else {
            int enemy_coord = are_enemies_alive();
            if (enemy_coord != -1) {
                return go_and_kill_emeny(enemy_coord);
            }
        }
    }
    return STAY;
}

void AI_nm::AI::set_ia_position(int x, int y)
{
    player_x= x;
    player_y = y;
}

void AI_nm::AI::set_ennemy_position(std::vector<std::pair<int, int>> ennemy_position)
{
    _ennemy_position = ennemy_position;
}

void AI_nm::AI::set_map(std::vector<std::vector<b_map::Block>> test2)
{
    test = test2;
}

// BOMB ON MAP:

AI_nm::move_enum AI_nm::AI::go_to_safe_place()
{
    size_t coord_to_go = 0;
    size_t coord_player = player_x * test[0].size() + player_y;
    for (int i = 0; i < d.size(); i++) {
        if ((i != coord_player) && (d[coord_to_go] > d[i]) && (d[i] % 100 != 0))
            coord_to_go = i;
    }
    if (coord_to_go == 0)
        return STAY;
    while (p[coord_to_go] != coord_player) {
        coord_to_go = p[coord_to_go];
    }
    if (coord_player - 1 == coord_to_go && (coord_player + 1) % test[0].size() != 0)
        return MOVE_DOWN;
    if (coord_player + 1 == coord_to_go && (coord_player + 1) % test[0].size() != 0)
        return MOVE_UP;
    if (coord_player + test[0].size() == coord_to_go)
        return MOVE_RIGHT;
    if (coord_player - test[0].size() == coord_to_go)
        return MOVE_LEFT;
    return STAY;
}

AI_nm::move_enum AI_nm::AI::wait_bomb_to_explode()
{
    return STAY;
}

bool AI_nm::AI::is_bomb_on_map() {
    for(int i = 0; i < test.size(); i++ )
        for(int j = 0; j < test[i].size(); j++)
            if (test[i][j] == b_map::Block::BOMB)
                return true;
    return false;
}

bool AI_nm::AI::are_you_safe()
{
    if (test[player_x][player_y] == b_map::Block::EMPTY_NOT_SAFE || test[player_x][player_y] == b_map::Block::BOMB)
        return false;
    return true;
}

// END BOMB ON MAP

// ITEM

int AI_nm::AI::is_there_item_on_map()
{
    for (int i = 0; i < test.size(); i++)
        for (int j = 0; j < test[i].size(); j++)
            if (test[i][j] == b_map::Block::POWERUP)
                return (i * test[i].size() + j);
    return -1;
}

AI_nm::move_enum AI_nm::AI::go_and_take_item(int coord_to_go)
{
    size_t coord_player = player_x * test[0].size() + player_y;
    while (p[coord_to_go] != coord_player) {
        coord_to_go = p[coord_to_go];
    }
    if (d[coord_to_go] == 10000)
        return BOMB;
    if (coord_player - 1 == coord_to_go && (coord_player + 1) % test[0].size() != 0)
        return MOVE_DOWN;
    if (coord_player + 1 == coord_to_go && (coord_player + 1) % test[0].size() != 0)
        return MOVE_UP;
    if (coord_player + test[0].size() == coord_to_go)
        return MOVE_RIGHT;
    if (coord_player - test[0].size() == coord_to_go)
        return MOVE_LEFT;
    return STAY;
}

// END ITEM

int AI_nm::AI::are_enemies_alive()
{
    int near = -1;
    size_t coord_player = player_x * test[0].size() + player_y;
    for (int i = 0; i < _ennemy_position.size(); i++) {
        int enemy = _ennemy_position[i].first * test[i].size() + _ennemy_position[i].second;
        if ((near == -1 || (d[enemy] < d[near])) && d[enemy] != 0)
            near = enemy;
    }
    return near;
}

AI_nm::move_enum AI_nm::AI::go_and_kill_emeny(int enemy)
{
    // TO DO: BOMB LEVEL UP
    size_t coord_player = player_x * test[0].size() + player_y;

    if (coord_player - 1 == enemy && (coord_player + 1) % test[0].size() != 0)
        return BOMB;
    if (coord_player + 1 == enemy && (coord_player + 1) % test[0].size() != 0)
        return BOMB;
    if (coord_player + test[0].size() == enemy)
        return BOMB;
    if (coord_player - test[0].size() == enemy)
        return BOMB;
    
    // Going near the enemy
    while (p[enemy] != coord_player) {
        enemy = p[enemy];
    }
    if (d[enemy] == 100000)
        return BOMB;
    if (coord_player - 1 == enemy && (coord_player + 1) % test[0].size() != 0)
        return MOVE_DOWN;
    if (coord_player + 1 == enemy && (coord_player + 1) % test[0].size() != 0)
        return MOVE_UP;
    if (coord_player + test[0].size() == enemy)
        return MOVE_RIGHT;
    if (coord_player - test[0].size() == enemy)
        return MOVE_LEFT;
    return STAY;
}

size_t AI_nm::AI::djikstra_compute_block_handle(size_t x, size_t y)
{
    if (test[x][y] == b_map::Block::BOX)
        return 1000;
    if (test[x][y] == b_map::Block::EMPTY_NOT_SAFE || test[x][y] == b_map::Block::BOMB)
        return 100;
    for (int i = 0; i < _ennemy_position.size(); i++) {
        if (_ennemy_position[i].first == x && _ennemy_position[i].second == y && _ennemy_position[i].first != player_x && _ennemy_position[i].second != player_y)
            return 100000;
    }
    return 1;
}

void AI_nm::AI::djikstra_compute()
{
    int size = 0;
    for (int i = 0; i < test.size() ; i++) {
        size += test[i].size();
    }

    graph_t g(size);
    WeightMap weightmap = get(edge_weight, g);

    for (std::size_t i = 0; i < test.size(); i++) {

        edge_descriptor e; 
        bool inserted;

        for (std::size_t j = 0; j < test[i].size(); j++) {
            if (test[i][j] != b_map::Block::WALL) {
                if (j != test[i].size() - 1) {
                    tie(e, inserted) = add_edge(i * test[i].size() + j, i * test[i].size() + j  + 1, g);
                    weightmap[e] = djikstra_compute_block_handle(i, j + 1);
                    tie(e, inserted) = add_edge(i * test[i].size() + j  + 1, i * test[i].size() + j, g);
                    weightmap[e] = djikstra_compute_block_handle(i, j);
                }
                if (i < test.size() - 1) {
                    tie(e, inserted) = add_edge(i * test[i].size() + j, (i+1) * test[i].size() + j, g);
                    weightmap[e] = djikstra_compute_block_handle(i + 1, j);
                    tie(e, inserted) = add_edge((i+1) * test[i].size() + j, i * test[i].size() + j, g);
                    weightmap[e] = djikstra_compute_block_handle(i, j);
                }
            }
        }
    }

    size_t player_pos = player_x * test[0].size() + player_y;

    p = std::vector<graph_t::vertex_descriptor> (num_vertices(g));
    d = std::vector<int> (num_vertices(g));
    vertex_descriptor s = vertex(player_pos, g);
    dijkstra_shortest_paths(g, s, predecessor_map(&p[0]).distance_map(&d[0]));
}
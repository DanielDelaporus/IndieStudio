/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AI
*/

#ifndef AI_HPP_
#define AI_HPP_

#include <iostream>
#include <vector>
#include <utility>

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include "../../include/Map.hpp"

using namespace boost;

typedef adjacency_list < listS, vecS, directedS,
      no_property, property < edge_weight_t, int > > graph_t;
typedef property_map<graph_t, edge_weight_t>::type WeightMap;
typedef graph_t::vertex_descriptor vertex_descriptor;
typedef graph_t::edge_descriptor edge_descriptor;
typedef std::pair<int, int> edge;
namespace AI_nm
{
    enum move_enum
    {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        STAY,
        BOMB
    };
    class AI {
        
        public:
        
            AI();
            ~AI();
            move_enum run();
            void set_ia_position(int x, int y);
            void set_ennemy_position(std::vector<std::pair<int, int>>);
            void set_map(std::vector<std::vector<b_map::Block>>);

        private:

            // BOMB
            bool is_bomb_on_map();
            bool are_you_safe();
            move_enum wait_bomb_to_explode();
            move_enum go_to_safe_place();

            int is_there_item_on_map();
            move_enum go_and_take_item(int coord_to_go);

            int are_enemies_alive();
            move_enum go_and_kill_emeny(int enemy);

            void djikstra_compute();
            size_t djikstra_compute_block_handle(size_t x, size_t y);

            std::vector<std::vector<b_map::Block>> test;
            int player_x;
            int player_y;
            std::vector<std::pair<int, int>> _ennemy_position;
            std::vector<graph_t::vertex_descriptor> p;
            std::vector<int> d;

        protected:
            
    };
}

#endif /* !AI_HPP_ */

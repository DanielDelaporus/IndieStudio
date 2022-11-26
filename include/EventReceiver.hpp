/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EventReceiver
*/

#ifndef EVENTRECEIVER_HPP_
#define EVENTRECEIVER_HPP_

#include <irrlicht.h>

namespace controls
{
    const irr::EKEY_CODE g_move_up[4]    = {irr::KEY_KEY_W, irr::KEY_KEY_T, irr::KEY_KEY_I, irr::KEY_UP};
    const irr::EKEY_CODE g_move_left[4]  = {irr::KEY_KEY_A, irr::KEY_KEY_F, irr::KEY_KEY_J, irr::KEY_LEFT};
    const irr::EKEY_CODE g_move_down[4]  = {irr::KEY_KEY_S, irr::KEY_KEY_G, irr::KEY_KEY_K, irr::KEY_DOWN};
    const irr::EKEY_CODE g_move_right[4] = {irr::KEY_KEY_D, irr::KEY_KEY_H, irr::KEY_KEY_L, irr::KEY_RIGHT};
    const irr::EKEY_CODE g_put_bomb[4]   = {irr::KEY_KEY_E, irr::KEY_KEY_Y, irr::KEY_KEY_O, irr::KEY_RCONTROL};
} // namespace controls

class EventReceiver : public irr::IEventReceiver
{
public:
    EventReceiver();

    virtual bool OnEvent(const irr::SEvent &event);
    virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;

private:
    bool _key_is_down[irr::KEY_KEY_CODES_COUNT];
};

#endif /* !EVENTRECEIVER_HPP_ */

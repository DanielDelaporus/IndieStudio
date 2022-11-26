/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EventReceiver
*/

#include "../include/EventReceiver.hpp"
#include <iostream>

EventReceiver::EventReceiver()
{
    for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
    {
        _key_is_down[i] = false;
    }
}

bool EventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
        _key_is_down[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }
    return false;
}

bool EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
    return _key_is_down[keyCode];
}

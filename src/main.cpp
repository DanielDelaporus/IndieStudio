/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/

#include <ctime>
#include <irrlicht.h>
#include <iostream>
#include "../include/GameState.hpp"

int main(int argc, char const *argv[])
{
    EventReceiver receiver;

    irr::IrrlichtDevice *device = createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1280, 720), 16, false, false, false, &receiver);

    if (!device) {
        std::cerr << "Failed to create device." << std::endl;
        return 1;
    }
    device->setWindowCaption(L"Irrlicht - Bomberman");
    irr::video::IVideoDriver* driver = device->getVideoDriver();
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

    irr::scene::ICameraSceneNode* cam = smgr->addCameraSceneNode(0, irr::core::vector3df(7, 14, 7));
    cam->bindTargetAndRotation(true);
    cam->setRotation(irr::core::vector3df(89.9, 0, 0));

    GameState* gameState = new GameState(receiver);
    gameState->start(device, smgr, driver, 4, 3);

    irr::u32 then = device->getTimer()->getTime();
    while (device->run())
    {
        const irr::u32 now = device->getTimer()->getTime();
        const irr::f32 deltaTime = (irr::f32)(now - then) / 1000.f;
        then = now;

        gameState->update(deltaTime);

        driver->beginScene(true, true, irr::video::SColor(255, 100, 100, 100));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }

    delete gameState;

    device->drop();

    return 0;
}
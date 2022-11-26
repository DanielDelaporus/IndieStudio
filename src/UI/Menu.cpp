/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Menu class cpp file
*/

#include <irrlicht/irrlicht.h>
#include "../../include/UI/Menu.hpp"
#include <iostream>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

class MyEventReceiver : public IEventReceiver
{
public:
    MyEventReceiver(UI::SAppContext & context) : Context(context) { }

    virtual bool OnEvent(const SEvent& event)
    {
        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();

            switch(event.GUIEvent.EventType) {
                case EGET_BUTTON_CLICKED:
                    switch(id) {
                    case UI::GUI_ID_NEW_GAME_BUTTON:
                        std::cout << "NEW GAME PRESSED" << std::endl;
                        return true;
                    case UI::GUI_ID_OPTIONS_BUTTON:
                        std::cout << "OPTIONS PRESSED" << std::endl;
                        return true;
                    case UI::GUI_ID_QUIT_BUTTON:
                        Context.device->closeDevice();
                        return true;
                    case UI::GUI_ID_MENU_BUTTON:
                        std::cout << "RETURN TO MENU PRESSED" << std::endl;
                        return true;
                    case UI::GUI_ID_BTN_P1:
                        std::cout << "P1 TOGGLED" << std::endl;
                        return true;
                    case UI::GUI_ID_BTN_P2:
                        std::cout << "P2 TOGGLED" << std::endl;
                        return true;
                    case UI::GUI_ID_BTN_P3:
                        std::cout << "P3 TOGGLED" << std::endl;
                        return true;
                    case UI::GUI_ID_BTN_P4:
                        std::cout << "P4 TOGGLED" << std::endl;
                        return true;
                    default:
                        return false;
                    }
                    break;
            default:
                break;
            }
        }

        return false;
    }
private:
    UI::SAppContext & Context;
};

UI::Menu::Menu(IrrlichtDevice *device) : _device(device), _env(device->getGUIEnvironment())
{
    _device->setWindowCaption(L"Bomberman Indie - Menu");
    _device->setResizable(true);

    video::IVideoDriver* driver = _device->getVideoDriver();

    IGUISkin* skin = _env->getSkin();
    IGUIFont* font = _env->getFont("../../assets/UI_elements/BOMBERMAN_font.bmp");
    _env->addFont("../../assets/UI_elements/BOMBERMAN_font.bmp", font);
    if (font)
        skin->setFont(font);
    
    ITexture* image = driver->getTexture("../../assets/UI_elements/Bomberman_wallpaper_2_scaled.jpg");

    _background_image = _env->addImage(rect<s32>(0, 0, 1280, 720), 0, 0, 0);

    _background_image->setImage(image); 

    _btn_new = _env->addButton(rect<s32>(640 - 60, 310 - 20, 640 + 60, 310 + 20), 0, UI::GUI_ID_NEW_GAME_BUTTON, L"New Game", L"Launch a new game");
    _btn_options = _env->addButton(rect<s32>(640 - 60, 360 - 20, 640 + 60, 360 + 20), 0, UI::GUI_ID_OPTIONS_BUTTON, L"Options", L"Opens options window");
    _btn_quit = _env->addButton(rect<s32>(640 - 60, 410 - 20, 640 + 60, 410 + 20), 0, UI::GUI_ID_QUIT_BUTTON, L"Quit", L"Quits the game");

    _btn_p1 = _env->addButton(rect<s32>(710, 290, 770, 310), 0, UI::GUI_ID_BTN_P1, L"Player 1", L"Toggle player 1 type");
    _btn_p2 = _env->addButton(rect<s32>(710, 310, 770, 330), 0, UI::GUI_ID_BTN_P2, L"Player 2", L"Toggle player 2 type");
    _btn_p3 = _env->addButton(rect<s32>(710, 330, 770, 350), 0, UI::GUI_ID_BTN_P3, L"Player 3", L"Toggle player 3 type");
    _btn_p4 = _env->addButton(rect<s32>(710, 350, 770, 370), 0, UI::GUI_ID_BTN_P4, L"Player 4", L"Toggle player 4 type");

    _txt_p1 = _env->addStaticText(L"N/A", rect<s32>(770, 290, 790, 310));
    _txt_p2 = _env->addStaticText(L"N/A", rect<s32>(770, 310, 790, 330));
    _txt_p3 = _env->addStaticText(L"N/A", rect<s32>(770, 330, 790, 350));
    _txt_p4 = _env->addStaticText(L"N/A", rect<s32>(770, 350, 790, 390));

    if(!_music.openFromFile("../assets/sounds/menu_music.ogg"))
        std::cout << "FAILED TO LOAD MAP MUSIC\n";
    _music.setVolume(3.f);
    _music.play();

    UI::SAppContext context;
    context.device = _device;
    context.counter = 0;

    MyEventReceiver receiver(context);
    _device->setEventReceiver(&receiver);

    _logo = _env->addImage(driver->getTexture("../../assets/UI_elements/Bomberman_logo.png"), position2d<int>(265,10));
    /*
    while(_device->run() && driver)
        if (_device->isWindowActive())
        {
            driver->beginScene(true, true, SColor(0,200,200,200));

            _env->drawAll();
        
            driver->endScene();
        }
    _device->drop();
    */
}

UI::Menu::~Menu() {}

UI::GameOverScreen::GameOverScreen(IrrlichtDevice *device) : _device(device), _env(device->getGUIEnvironment())
{
    _device->setWindowCaption(L"Bomberman Indie - Game Over");
    _device->setResizable(true);

    video::IVideoDriver* driver = _device->getVideoDriver();

    IGUISkin* skin = _env->getSkin();
    IGUIFont* font = _env->getFont("../../assets/UI_elements/BOMBERMAN_font.bmp");
    _env->addFont("../../assets/UI_elements/BOMBERMAN_font.bmp", font);
    if (font)
        skin->setFont(font);
    
    ITexture* image = driver->getTexture("../../assets/UI_elements/Bomberman_wallpaper_2_scaled.jpg");

    _background_image = _env->addImage(rect<s32>(0, 0, 1280, 720), 0, 0, 0);

    _background_image->setImage(image); 
    
    _btn_menu = _env->addButton(rect<s32>(640 - 60, 310 - 20, 640 + 60, 310 + 20), 0, UI::GUI_ID_MENU_BUTTON, L"Return to Menu", L"Returns you to main menu screen");
    _btn_quit = _env->addButton(rect<s32>(640 - 60, 360 - 20, 640 + 60, 360 + 20), 0, UI::GUI_ID_QUIT_BUTTON, L"Quit", L"Quits the game");

    UI::SAppContext context;
    context.device = _device;
    context.counter = 0;

    MyEventReceiver receiver(context);
    _device->setEventReceiver(&receiver);

    _logo = _env->addImage(driver->getTexture("../../assets/UI_elements/game_over_scaled.png"), position2d<int>(300,10));

    while(_device->run() && driver)
        if (_device->isWindowActive())
        {
            driver->beginScene(true, true, SColor(0,200,200,200));

            _env->drawAll();
        
            driver->endScene();
        }

    _device->drop();
}

UI::GameOverScreen::~GameOverScreen() {}
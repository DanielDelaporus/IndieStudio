/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Menu class hpp file
*/

#include <irrlicht/irrlicht.h>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace UI
{
    struct SAppContext
    {
        IrrlichtDevice *device;
        s32             counter;
        IGUIListBox*    listbox;
    };

    enum
    {
        GUI_ID_NEW_GAME_BUTTON,
        GUI_ID_OPTIONS_BUTTON,
        GUI_ID_QUIT_BUTTON = 101,
        GUI_ID_MENU_BUTTON,
        GUI_ID_BTN_P1,
        GUI_ID_BTN_P2,
        GUI_ID_BTN_P3,
        GUI_ID_BTN_P4
    };

    class Menu
    {
        public:
            Menu(IrrlichtDevice *);
            ~Menu();
            void clear();
        private:
            IrrlichtDevice *_device;
            IGUIEnvironment *_env;
            sf::Music _music;

            IGUIImage *_background_image;
            IGUIImage *_logo;
            IGUIButton *_btn_new;
            IGUIButton *_btn_options;
            IGUIButton *_btn_quit;

            IGUIButton *_btn_p1;
            IGUIButton *_btn_p2;
            IGUIButton *_btn_p3;
            IGUIButton *_btn_p4;

            IGUIStaticText *_txt_p1;
            IGUIStaticText *_txt_p2;
            IGUIStaticText *_txt_p3;
            IGUIStaticText *_txt_p4;
    };

    class GameOverScreen
    {
        public:
            GameOverScreen(IrrlichtDevice *);
            ~GameOverScreen();
            void clear();
        private:
            IrrlichtDevice *_device;
            IGUIEnvironment *_env;
            //sf::Music _music;

            IGUIImage *_background_image;
            IGUIImage *_logo;
            IGUIButton *_btn_menu;
            IGUIButton *_btn_quit;
    };

    class EventReceiver : public IEventReceiver
    {
        public:
            EventReceiver(SAppContext&);
            ~EventReceiver();
            virtual bool onEvent(const SEvent&);
        private:
            SAppContext& Context;
    };
};
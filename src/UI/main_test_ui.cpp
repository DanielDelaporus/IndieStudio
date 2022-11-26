#include <irrlicht/irrlicht.h>
#include "../../include/UI/Menu.hpp"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{
    IrrlichtDevice * device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(1280, 720));

    if (device == 0)
        return 1;
    
    UI::GameOverScreen GameOver(device);
    //UI::Menu Menu(device);
}
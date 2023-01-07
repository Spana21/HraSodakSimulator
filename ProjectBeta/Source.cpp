
#include "Game.h"
using namespace sf;

int main()
{
    RenderWindow window(sf::VideoMode(1920, 1080), "Project Beta!", Style::Fullscreen);
   
 
    bool gamePause;

    Game game(&window);


    while (window.isOpen())
    {
       // death.close();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                window.close();

        }
       game.Update();
       
       game.Draw();
    }
   
    return 0;
}
//
// Created by Quill on 1/17/2021.
//

#ifndef TESTPROJ_GAME_HPP
#define TESTPROJ_GAME_HPP


#include <string>
#include <SFML/Graphics.hpp>
#include "Rendering/Renderer.hpp"

using namespace std;
using namespace sf;

class Game {
public:

    RenderWindow *window = new RenderWindow(); // window to be rendering to
    Clock *clock = new Clock(); //clock for getting delta time

    Renderer *renderer = new Renderer(); //game renderer

    /**
     * Constructor for new game windows
     * @param width of the game window
     * @param height of the game window
     * @param name of the window
     */
    Game(int width, int height, const std::string& name)
    {
        //create the window
        this->window->create(VideoMode(width, height), name);
        this->window->setFramerateLimit(300);
    }

    /**
     * Method to start running the game
     */
    void run() const{
        //Loop while the window is open
        while (window->isOpen()){

            Event event{}; //event var for storing a polled event

            //poll the window for events
            while(window->pollEvent(event))
            {

                //if we get a closed event, close the game
                if(event.type == Event::Closed)
                {
                    window->close(); //close the game window
                }

            }

            renderer->render(window); //render any changes to the game window
        }
    }
};
#endif //DEMO_GAME_HPP

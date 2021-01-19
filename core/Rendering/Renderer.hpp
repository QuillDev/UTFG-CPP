//
// Created by Quill on 1/17/2021.
//

#ifndef TESTPROJ_RENDERER_HPP
#define TESTPROJ_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "AssetLoader.hpp"

class Renderer {

private:
    AssetLoader *assetLoader = new AssetLoader();
    Sprite sprite;
public:
    Renderer(){
        sprite = assetLoader->get_sprite("grass.png");
    }
    //The window to render to
    void render(sf::RenderWindow *window)
    {

        //Rendering loop
        window->clear(sf::Color(120, 0, 120)); //clear the window using the given color

        window->draw(sprite);
        window->display(); //display the window with updates
    }
};
#endif //DEMO_RENDERER_HPP

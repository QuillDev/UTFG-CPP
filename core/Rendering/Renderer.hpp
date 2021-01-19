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
    Sprite *sprite;
    Sprite *sprite2;
    Sprite *sprite3;

public:
    Renderer(){
        sprite = assetLoader->get_sprite("grass.png");
        sprite2 = assetLoader->get_sprite("grass.png", Vector2<float>(32.0f, 0.0f));
        sprite3 = assetLoader->get_sprite("fakesprite.png", Vector2<float>(64.0f, 0.0f));
    }
    //The window to render to
    void render(sf::RenderWindow *window)
    {

        //Rendering loop
        window->clear(sf::Color(100, 149, 237)); //clear the window using the given color
        window->draw(*sprite);
        window->draw(*sprite2);
        window->draw(*sprite3);
        window->display(); //display the window with updates
    }
};
#endif //DEMO_RENDERER_HPP

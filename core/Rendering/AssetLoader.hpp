//
// Created by robert on 1/18/21.
//

#ifndef TESTPROJ_ASSETLOADER_HPP
#define TESTPROJ_ASSETLOADER_HPP

#include <iostream>
#include <utility>
#include <boost/filesystem.hpp>
#include <boost/fusion/container/map.hpp>
#include <string>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

using namespace boost::filesystem;

class AssetLoader {

private:
    std::map<std::string, sf::Texture> *textureMap = new std::map<std::string, sf::Texture>;

    sf::Texture *debug_texture = new sf::Texture();
public:
    AssetLoader()
    {
        debug_texture->loadFromFile("./Assets/debug_texture.png");
        this->load("./Assets"); //start loading in the assets directory
    }

    /**
     * Get the sprite with the given key
     * @param query to find the texture with
     * @return the sprite if it exists
     */
    sf::Sprite * get_sprite(const std::string& query)
    {
        return get_sprite(query, sf::Vector2<float>(0.0f,0.0f));
    }

    /**
     * Get the sprite with the given key
     * @param query to find the texture with
     * @return the sprite if it exists
     */
    sf::Sprite * get_sprite(const std::string& query, sf::Vector2<float> position)
    {

        auto *sprite = new sf::Sprite(); //create the sprite

        //try to set the image of the sprite
        try {

            //try to set the sprites image
            sprite->setTexture(textureMap->at(query));

        }
        catch (const std::exception& e)
        {
            sprite->setTexture(*debug_texture); //if the texture fails to be retrieved, use the debug texture
        }

        sprite->setPosition(position); //set the position of the sprite

        return sprite;
    }

    /**
     * try to load the given map
     * @param map to load
     * @param query to check for
     */
    void load_map(tmx::Map *map, const std::string& query)
    {
        if(!map->load("./Assets/Maps/" + query))
        {
            std::cout << "Failed to load the requested map " << query << std::endl;
        }
    }
private:
    /**
     * Loads sprites dynamically going down the file tree automatically
     * For example in the given structure
     *
     * EXAMPLE STRUCTURE
     * __________________
     * ASSETS/ - MAPS/
     * |         |
     * |         - map1.tmx
     * |         - map2.tmx
     * - texture1.png
     * - texture2.png
     *
     * The code would go down path 1 and call load(string path) on any subdirectories it finds, filling the tree
     * and finding all available texture files in the assets directory (including all subdirectories)
     */
    void load(std::string pathString) const
    {

        std::cout << "Loading Path @ " << pathString << std::endl; //log we started loading the given path

        //Get the working directory
        path directory (pathString);
        directory_iterator end_iterator;

        //iterate in the given directory
        for(directory_iterator itr(directory); itr != end_iterator; itr++)
        {

            //get the path from the iterator
            auto curPath= itr->path();

            //if the file is a regular file, let us know
            if(is_regular_file(curPath))
            {
                //Get details about the file
                path filePath = itr->path(); // Get the path
                std::string extension = filePath.extension().string(); // Get the file extension as a string

                if(extension == ".png")
                {
                    load_texture(filePath);
                    continue;
                }

                //if we did not find an appropriate loader
                else
                {
                    std::cout << "Did not find a loader for type " << extension << std::endl;
                }

            }
            else if(is_directory(curPath))
            {
                load(curPath.string());
            }
        }
    }

    /**
     * Load the texture at the given path
     * @param filePath to load the texture from
     */
    void load_texture(const path& filePath) const
    {
        // Setup texture stuff for adding to the map
        auto *texture = new sf::Texture(); // Create the texture to load the sprite into
        auto fileName = filePath.filename().string(); // Get the file name from the path

        //if we failed to load the texture, log it and continue
        if(!texture->loadFromFile(filePath.string()))
        {
            std::cout << "Failed to load file: " << filePath << std::endl;
            return;
        }

        //Add the texture to the map and log it
        textureMap->insert(make_pair(fileName, *texture));
        std::cout << "Loaded Sprite: KEY=" << fileName << std::endl; //log that we loaded the sprite
    }
};
#endif //TESTPROJ_ASSETLOADER_HPP

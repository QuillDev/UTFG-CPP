//
// Created by robert on 1/18/21.
//

#ifndef TESTPROJ_ASSETLOADER_HPP
#define TESTPROJ_ASSETLOADER_HPP

#include <iostream>
#include "boost/filesystem.hpp"

using namespace std;
using namespace sf;
using namespace boost::filesystem;

class AssetLoader {

private:
    map<string, Texture> *textureMap = new map<string, Texture>;
    Texture *debug_texture = new Texture();
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
    Sprite * get_sprite(string query)
    {
        return get_sprite(query, Vector2<float>(0.0f,0.0f));
    }

    /**
     * Get the sprite with the given key
     * @param query to find the texture with
     * @return the sprite if it exists
     */
    Sprite * get_sprite(string query, Vector2<float> position)
    {

        Sprite *sprite = new Sprite(); //create the sprite

        //try to set the image of the sprite
        try {

            //try to set the sprites image
            sprite->setTexture(textureMap->at(query));

        }
        catch (out_of_range ignored)
        {
            sprite->setTexture(*debug_texture); //if the texture fails to be retrieved, use the debug texture
        }

        sprite->setPosition(position); //set the position of the sprite

        return sprite;
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
    void load(string pathString) const
    {

        cout << "Loading Path @ " << pathString << endl; //log we started loading the given path

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
                string extension = filePath.extension().string(); // Get the file extension as a string

                //if the file extension is not a png, skip it
                if(extension == ".png")
                {
                    // Setup texture stuff for adding to the map
                    Texture *texture = new Texture(); // Create the texture to load the sprite into
                    string fileName = filePath.filename().string(); // Get the file name from the path

                    //if we failed to load the texture, log it and continue
                    if(!texture->loadFromFile(filePath.string()))
                    {
                        cout << "Failed to load file: " << filePath << endl;
                        continue;
                    }

                    //Add the texture to the map and log it
                    textureMap->insert(make_pair(fileName, *texture));
                    cout << "Loaded sprite with key: " << fileName << endl; //log that we loaded the sprite
                    continue;
                }


            }
            else if(is_directory(curPath))
            {
                load(curPath.string());
            }
        }
    }
};
#endif //TESTPROJ_ASSETLOADER_HPP

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
    map<string, Sprite> *textureMap = new map<string, Sprite>;
public:
    AssetLoader()
    {
        this->load();
    }

    /**
     * Get the sprite with the given key
     * @param query to find the texture with
     * @return the sprite if it exists
     */
    Sprite get_sprite(string query)
    {
        return textureMap->at(query);
    }

private:
    /**
     * Load any sprites into the map in the asset loader
     */
    void load() const
    {
        //Get the working directory
        path directory ("./Assets");
        directory_iterator end_iterator;

        //iterate in the given directory
        for(directory_iterator itr(directory); itr != end_iterator; itr++)
        {

            //if the file is a regular file, let us know
            if(is_regular_file(itr->path()))
            {

                //Get details about the file
                path filePath = itr->path(); // Get the path
                string extension = filePath.extension().string(); // Get the file extension as a string

                //if the file extension is not a png, skip it
                if(extension != ".png")
                {
                    cout << "Found non-image file in assets: " << filePath << endl;
                    continue;
                }

                // Setup texture stuff for adding to the map
                Texture *texture = new Texture(); // Create the texture to load the sprite into
                string fileName = filePath.filename().string(); // Get the file name from the path

                //if we failed to load the texture, log it and continue
                if(!texture->loadFromFile(filePath.string()))
                {
                    cout << "Failed to load file: " << filePath << endl;
                    continue;
                }

                //create a sprite using the texture
                Sprite *sprite = new Sprite();
                sprite->setTexture(*texture);

                //Add the texture to the map and log it
                textureMap->insert(make_pair(fileName, *sprite)); //put the sprite into the texture map
                cout << "Loaded sprite with key: " << fileName << endl; //log that we loaded the sprite
            }
        }
    }
};
#endif //TESTPROJ_ASSETLOADER_HPP

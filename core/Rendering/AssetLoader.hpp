//
// Created by robert on 1/18/21.
//

#ifndef TESTPROJ_ASSETLOADER_HPP
#define TESTPROJ_ASSETLOADER_HPP

#include <iostream>
#include "boost/filesystem.hpp"

using namespace std;
using namespace boost::filesystem;

class AssetLoader {
public:
    AssetLoader()
    {
        this->load();
    }

private:
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

                //get the current file and it's extension
                string current_file = itr->path().string();
                string extension = itr->path().extension().string();

                //if the file extension is not a png, skip it
                if(extension != ".png")
                {
                    cout << "Found non-image file in assets: " << current_file << endl;
                    continue;
                }

                //Log the current file if it's good!
                cout << current_file << " | " << extension << endl;
            }
        }
    }
};
#endif //TESTPROJ_ASSETLOADER_HPP

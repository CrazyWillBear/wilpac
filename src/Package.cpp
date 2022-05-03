// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "Package.h"

Package::Package() { }

std::string Package::pkgExists(std::string query) {
    const char* PATH = "/etc/wilpac-buckets";
    DIR *dir = opendir(PATH);
    FILE *file;

    struct dirent *entry = readdir(dir);

    while (entry != NULL)
    {
        if (entry->d_type == DT_DIR) {
            std::string curfile = "/etc/wilpac-buckets/" + std::string(entry->d_name) + "/pkgs/" + query;

            if ((file = fopen(curfile.c_str(), "r"))) {
                return "/etc/wilpac-buckets/" + std::string(entry->d_name) + "/pkgs/" + query;
            }
        }
        entry = readdir(dir);
    }

    closedir(dir);

    return "0";
}

void Package::installPkg(std::string file) {
    // assign path variable
    std::string path = pkgExists(file);
    std::ifstream pkgFile(path, std::ios::in);

    // return nothing if file cannot be read
    if (!pkgFile.is_open()) {
        std::cerr << BLD R "()Unable to read package file" RS "\n";
        return;
    }

    // initiate start of file
    std::string cur;
    pkgFile >> cur;

    // read through entire file
    do{
        std::cout << cur << std::endl;
        pkgFile >> cur;
    } while (!pkgFile.eof());

    pkgFile.close();
}

Package::~Package() { }
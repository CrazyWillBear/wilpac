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
            std::string curfile = "/etc/wilpac-buckets/" + std::string(entry->d_name) + "/" + query;

            if ((file = fopen(curfile.c_str(), "r"))) {
                return "/etc/wilpac-buckets/" + std::string(entry->d_name) + "/" + query;
            }
        }
        entry = readdir(dir);
    }

    closedir(dir);

    return "0";
}

void Package::installPkg(std::string path) {
    std::string line;
    std::ifstream pkgFile(path);\

    if (!pkgFile.is_open()) {
        std::cerr << BLD R "()Unable to read package file" RS "\n";
        return;
    }

    std::string x;
    std::string file;
    while (pkgFile >> x) {
        file += " " + x;
    }
    pkgFile.close();

    jsonxx::Object json;
    jsonxx::assert(json.parse(file));
    std::cout << json.json() << "\n";
}

Package::~Package() { }
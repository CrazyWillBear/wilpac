// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PACKAGE_H
#define PACKAGE_H

#include <dirent.h>
#include <fstream>
#include <iostream>
#include <string>

#include "Colors.h"

class Package {
public:
    Package();

    // returns "0" if false, returns path if true
    static std::string pkgExists(std::string);

    // parses package
    static void installPkg(std::string);

    ~Package();
};

#endif
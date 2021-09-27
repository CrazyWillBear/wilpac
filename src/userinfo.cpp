// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "userinfo.h"

std::string userinfo::getUID() {
    char text[255];
    FILE *name;
    name = popen("id -u", "r");
    return fgets(text, sizeof(text), name);
}

std::string userinfo::getUsername() {
    char text[255];
    FILE *name;
    name = popen("whoami", "r");
    return fgets(text, sizeof(text), name);
}
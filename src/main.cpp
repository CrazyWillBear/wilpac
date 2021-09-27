// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "runtime.h"
#include "userinfo.h"

int main(int argc, char **argv) {
    // check to see if user is admin, if not operations won't work so exit
    if (userinfo().getUID() != "0\n") {
        std::cerr << "\033[1;31m()Please run as root\n\033[0m";
        return 1;
    }

    runtime();
    std::string username = userinfo().getUsername();

    return 0;
}
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include "Commands.h"


Commands::Commands() { }

cmds Commands::getLongOption(std::string input) {
    if (input.compare("--help") == 0) { return cmds::help; }
    if (input.compare("--fetch") == 0) { return cmds::fetch; }
    else { return cmds::invalid; }
}

cmds Commands::getShortOption(char input) {
    if (input == 'h') { return cmds::help; }
    if (input == 'f') { return cmds::fetch; }
    else { return cmds::invalid; }
}

Commands::~Commands() { }
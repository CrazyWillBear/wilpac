// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>

enum cmds {
    help,
    fetch,
    install,
    invalid
};

class Commands {
public:
    Commands();

    // takes input, returns corresponding cmds value for options with '--'
    cmds getLongOption(std::string);
    // same thing but for options with '-', so by character
    cmds getShortOption(char);

    // takes input, returns corresponding mods value for options with '--'
    void getLongModifier(std::string);
    // same thing but for options with '-', so by character
    void getShortModifier(char);
    
    // modifiers
    bool all;

    ~Commands();
};
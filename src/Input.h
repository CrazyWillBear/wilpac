// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>

enum cmds {
    // commands
    help,
    fetch,
    install,
    uninstall,
    update_all,

    // options
    silent,
    alldeps,

    // nothing
    invalid
};

class Input {
public:
    Input() { all = false; }

    // takes input, returns corresponding cmds value for options with '--'
    cmds getLongOption(std::string);
    // same thing but for options with '-', so by character
    cmds getShortOption(char);

    // takes input, returns corresponding mods value for options with '--'
    void getLongModifier(std::string);
    // same thing but for options with '-', so by character
    void getShortModifier(char);

    // get input
    static std::string getInput(std::string);
    // confirm option
    static bool confOpt(std::string, bool yesDominant = true);
    
    // modifiers
    bool all;

    ~Input() = default;
};

#endif
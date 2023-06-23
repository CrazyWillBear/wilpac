// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "Input.h"


cmds Input::getLongOption(std::string input) {
    if (input.compare("--help") == 0) { return cmds::help; }
    else if (input.compare("--fetch") == 0) { return cmds::fetch; }
    else if (input.compare("--install") == 0) { return cmds::install; }
    else if (input.compare("--remove") == 0) { return cmds::uninstall; }
    else if (input.compare("--updateall") == 0) { return cmds::update_all; }
    else if (input.compare("--silent") == 0) { return cmds::silent; }
    else if (input.compare("--all-deps") == 0) { return cmds::alldeps; }
    else { return cmds::invalid; }
}

cmds Input::getShortOption(char input) {
    if (input == 'h') { return cmds::help; }
    else if (input == 'F') { return cmds::fetch; }
    else if (input == 'I') { return cmds::install; }
    else if (input == 'R') { return cmds::uninstall; }
    else if (input == 'U') { return cmds::update_all; }
    else if (input == 's') { return cmds::silent; }
    else if (input == 'a') { return cmds::alldeps; }
    else { return cmds::invalid; }
}

void Input::getLongModifier(std::string input) {
    if (input.compare("--all") == 0) { all = true; }
    else { return; }
}

void Input::getShortModifier(char input) {
    if (input == 'a') { all = true; }
    else { return; }
}

std::string Input::getInput(std::string text) {
    std::string returnS;
    std::cout << text << "  >>  ";
    getline(std::cin, returnS);
    return returnS;
}

bool Input::confOpt(std::string text, bool yesDominant) {
    std::string input;
    std::cout << text << (yesDominant ? " (Y/n)" : " (y/N)") << "  >>  ";
    std::getline(std::cin, input);

    if (input != "Y" && input != "y" != 0 && !input.empty()) { return false; }
    return true;
}
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>

enum cmds{
    help,
    fetch,
    invalid
};

class Commands {
public:
    Commands();

    // takes input, returns corresponding enum value
    static cmds getLongOption(std::string);
    static cmds getShortOption(char);

    ~Commands();
};
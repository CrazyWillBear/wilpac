// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>

#include "Colors.h"
#include "Package.h"

class Parser {
private:
    Package pkg;

public:
    Parser(std::string);

    Package getPkg() { return this->pkg; }
    void rewriteCompleted(std::string);

    ~Parser() = default;
};

#endif
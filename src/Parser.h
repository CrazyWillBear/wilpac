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
#include "PackageStat.h"

class Parser {
private:
    Package pkg;

public:
    Parser() = default;
    Parser(std::string);

    // parses JSON package info and returns a Package
    Package getPkg() { return this->pkg; }
    // rewrites the package's JSON file to be marked as completed
    void markCompleted(std::string);

    // parses JSON package stat and returns PackageStat
    PackageStat getPkgStat(std::string);

    ~Parser() = default;
};

#endif
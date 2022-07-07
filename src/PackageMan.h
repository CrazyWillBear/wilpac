// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PACKAGEMAN_H
#define PACKAGEMAN_H

#include <dirent.h>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#include "Colors.h"
#include "Input.h"
#include "Output.h"
#include "Parser.h"
#include "PackageStat.h"

// returns "0" if false, returns path if true
std::string pkgExists(std::string);
// returns whether or not package is installed
bool pkgInstalled(std::string);

// installs package
void installPkg(std::string, bool, bool = false);
// updates all installed packages
void updateAll(bool);

// removes/uninstalled a package
void removePkg(std::string, bool, bool = false);

// gets checksum
std::string getChkSum(std::string);

#endif
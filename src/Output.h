// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <string>

#include "Colors.h"

// introduce task to be overwritten in green by outroTask()
static void introTask(std::string task) { std::cout << REG RED << task << RS; }
// overwrite introTask() in green to signify completion of task
static void outroTask(std::string task) { std::cout << "\r" REG GRE << task << RS << std::endl; }

#endif

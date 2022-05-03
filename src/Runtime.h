// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RUNTIME_H
#define RUNTIME_H

#include <fstream>
#include <iostream>
#include <string>

#include "Bucket.h"
#include "Colors.h"

class Runtime {
public:
    Runtime();
    // fills the bucketlist with the default repo
    void fillDefaultFetchScript();
    ~Runtime();
};

#endif
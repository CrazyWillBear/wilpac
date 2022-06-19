// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BUCKETS_H
#define BUCKETS_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Colors.h"

// gets the buckets the user has in their bucketlist file
static void getBuckets() {
    std::cout << REG GRE "()Buckets:" RS "\n";
    std::system("cd /etc/wilpac-buckets; ls -d */ | sed 's/^/\t/g'");
}

// pulls the latest bucket repositories
static void fetchBuckets() {
    std::cout << REG GRE "()Updating buckets..." RS "\n";
    std::system("cd /etc/wilpac-buckets; $SHELL /etc/wilpac-buckets/fetch.sh |& sed 's/^/\t/g'");
}

#endif
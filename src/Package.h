// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BUCKET_H
#define BUCKET_H

#include <string>
#include <vector>

struct Package {
    std::string name;
    std::string zipURL;
    std::string version;
    std::string sha256sum;
    std::vector<std::string> files;
    bool installed;
};

#endif
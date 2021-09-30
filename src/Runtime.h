// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <fstream>
#include <iostream>
#include <string>

class Runtime {
private:
    // if bucketlist exists, return true.
    bool bucketlistExists;
public:
    Runtime();
    // fills the bucketlist with the default repo.
    void fillBucketlist();
    ~Runtime();
};

// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <unistd.h>

#include "Bucket.h"
#include "Runtime.h"

int main(int argc, char **argv) {
    
    // check if user is root
    if (geteuid() != 0) 
    {
        std::cerr << "\033[1;31m()Please run as root\n\033[0m";
        return 1;
    }

    // if the user is admin, then runtime functions/tasks can be completed.
    Runtime();
    std::cout << Bucket().getBuckets() << "\n";

    return 0;
}

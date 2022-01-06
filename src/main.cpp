// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "Bucket.h"
#include "Colors.h"
#include "Runtime.h"
#include "UserInfo.h"

int main(int argc, char **argv) {
    // check to see if user is admin, if not operations won't work so exit.
    if (UserInfo().getUID() != "0\n") {
        std::cerr << BLD << R "()Please run as root\n" << RS;
        return 1;
    }

    // if the user is admin, then runtime functions/tasks can be completed.
    Runtime();
    Bucket::fetchBuckets();
    Bucket::getBuckets();

    return 0;
}
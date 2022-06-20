// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <vector>

#include "Bucket.h"
#include "Colors.h"
#include "Commands.h"
#include "Runtime.h"
#include "UserInfo.h"

int main(int argc, char *argv[]) {
    // check to see if user is admin, if not operations won't work so exit
    if (UserInfo().getUID() != "0\n") {
        std::cerr << BLD << R "()Please run as root\n" << RS;
        return 1;
    }

    // runtime functions/tasks can be completed
    Runtime();

    // create list of operations to be performed and new arglist (args without '-' or '--')
    std::vector<cmds> operations;
    std::vector<std::string> args;

    // create operations list
    for (int i = 0; i < argc; i ++) {
        if (argv[i][0] == '-' && argv[i][1] == '-') {
            operations.push_back(Commands::getLongOption(argv[i]));
        } if (argv[i][0] == '-') {
            for (int j = 1; j < std::string(argv[i]).length(); j++) {
                operations.push_back(Commands::getShortOption(argv[i][j]));
            }
        } else { args.push_back(argv[i]); }
    }

    // execute operations
    for (int i = 0; i <operations.size(); i++) {
        if (operations[i] == cmds::help) { std::cout << "help is on da way\n"; }
        if (operations[i] == cmds::fetch) {
            Bucket::fetchBuckets();
            Bucket::getBuckets();
        }
    }

    return 0;
}
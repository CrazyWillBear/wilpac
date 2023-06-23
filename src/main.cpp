// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <unistd.h>
#include <vector>

#include "Buckets.h"
#include "Input.h"
#include "PackageMan.h"
#include "Runtime.h"

// help menu / usage function
void usage() {
    std::cout << REG GRE <<
    "()Usage: `wilpac <OPTIONS> <modifiers> <args>\n" <<
    "\t()OPTIONS:\n" <<
    "\t-I, --install; install package\n" <<
    "\t-F, --fetch; fetch buckets\n" <<
    "\t-U, --updateall; update all packages\n" <<
    "\t-R, --remove; remove a package\n\n" <<
    "\t()MODIFIERS:\n" <<
    "\t-a, --all-deps; remove all dependencies alongside a package\n" <<
    "\t-s, --silent; disable verbosity\n" <<
    "\t-h, --help; display help and exit\n\n" <<
    "\t()EXAMPLES:\n" <<
    "\t-FU; full system update\n" <<
    "\t-Ra <package>; fully remove package\n" <<
    "\t-I <package>; install package" << std::endl;
}

int main(int argc, char *argv[]) {
    // check to see if user is admin, if not operations won't work so exit
    if (geteuid() != 0) {
        std::cerr << BLD RED "()Please run as root" RS << std::endl;
        return 1;
    }

    // check to see if args have been provided, if not exit with error
    if (argc <= 1) {
        std::cerr << BLD RED "()Not enough arguments provided (-h or --help for help)" RS << std::endl;
        return 2;
    }

    // runtime functions/tasks can be completed
    Runtime();

    // create Commands object
    Input input;

    // create list of operations to be performed and new arglist (args without '-' or '--')
    std::vector<cmds> operations;
    std::vector<std::string> args;

    // create operations list
    for (int i = 0; i < argc; i ++) {
        // if the option starts with '--' then parse it accordingly, if it's just '-' parse accordingly,
        // otherwise add it as a program argument (helps with organization to have separate args variable)
        if (argv[i][0] == '-' && argv[i][1] == '-') {
            operations.push_back(input.getLongOption(argv[i]));
            input.getLongModifier(argv[i]);
        } if (argv[i][0] == '-') {
            for (int j = 1; j < std::string(argv[i]).length(); j++) {
                operations.push_back(input.getShortOption(argv[i][j]));
                input.getShortModifier(argv[i][j]);
            }
        } else { args.push_back(argv[i]); }
    }

    // set paramaters
    bool silent = false;
    bool alldeps = false;

    for (int i = 0; i < operations.size(); i++) {
        if (operations[i] == cmds::silent) { silent = true; }
        else if (operations[i] == cmds::alldeps) { alldeps = true; }
    }

    // execute operations
    for (int i = 0; i < operations.size(); i++) {
        if (operations[i] == cmds::help) { usage(); }
        else if (operations[i] == cmds::fetch) {
            fetchBuckets();
            getBuckets();
        } else if (operations[i] == cmds::install) {
            if (args.size() <= 1) {
                std::cerr << BLD RED "()Not enough arguments provided for install (-h or --help for help)" RS << std::endl;
            }
            else if (pkgExists(std::string(args[1] + ".json")) == "0") {
                std::cerr << BLD RED "()Package not found, is the package's bucket installed?" RS << std::endl;
                return 3;
            } else {
                installPkg(pkgExists(std::string(args[1] + ".json")), (silent ? false : true));
            }
        } else if (operations[i] == cmds::uninstall) {
            if (!pkgInstalled(std::string(args[1] + ".json"))) {
                std::cerr << BLD RED "()Package not found, is it installed?" RS << std::endl;
                return 4;
            }
            removePkg(std::string(args[1] + ".json"), (silent ? false : true), alldeps);
        } else if (operations[i] == cmds::update_all) {
            if (!silent) std::cout << "()Verbose update (silent tag not detected)" << std::endl;
            updateAll(!silent);
        }
    }

    return 0;
}
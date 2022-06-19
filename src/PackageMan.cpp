// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "PackageMan.h"

std::string pkgExists(std::string query) {
    const char* PATH = "/etc/wilpac-buckets";
    DIR *dir = opendir(PATH);

    struct dirent *entry = readdir(dir);

    while (entry != NULL)
    {
        if (entry->d_type == DT_DIR) {
            std::string curfile = "/etc/wilpac-buckets/" + std::string(entry->d_name) + "/pkgs/" + query;

            if (std::filesystem::exists(curfile)) {
                return "/etc/wilpac-buckets/" + std::string(entry->d_name) + "/pkgs/" + query;
            }
        }
        entry = readdir(dir);
    }

    closedir(dir);

    return "0";
}

void installPkg(std::string pkgFile) {
    // assign path variable
    std::string path = pkgExists(pkgFile);

    // install package
    Parser parser(path);
    Package pkg = parser.getPkg();

    // check to see if package is installed
    std::cout << "()Checking to see if package is installed..." << std::endl;
    if (pkg.installed) {
        std::string input;
        std::cout << "()Package is already installed, would you like to reinstall? (Y/N)  >>  ";
        std::getline(std::cin, input);
        if (!std::strcmp(input.c_str(), "Y") && !std::strcmp(input.c_str(), "y") && !input.empty()) {
            std::cerr << BLD RED "()Cancelling install..." RS << std::endl;
            return;
        }
    }

    // download zip file if necessary
    bool skipDl = false;
    if (std::filesystem::exists(std::string("/var/cache/wilpac/" + pkg.name + ".zip").c_str())) {
        std::cout << "()File exists, checking to see if old version..." << std::endl;
        char *output;
        FILE *fd = popen(std::string("sha256sum /var/cache/wilpac/" + pkg.name + ".zip").c_str(), "w");
        fgets(output, 1024, fd);
        if (std::strcmp(std::string(pkg.sha256sum + "  /var/cache/wilpac/" + pkg.name + ".zip").c_str(), output)) {
            skipDl = true;
            std::cout << "()Current file up-to-date, skipping download..." << std::endl;
        }
    }
    if (!skipDl) {
        std::cout << "()Downloading file..." << std::endl;
        std::system(std::string("sudo curl -L " + pkg.zipURL + " -o /var/cache/wilpac/" + pkg.name + ".zip").c_str());
        std::cout << "()Verifying download..." << std::endl;
        char *output;
        FILE *fd = popen(std::string("sha256sum /var/cache/wilpac/" + pkg.name + ".zip").c_str(), "w");
        fgets(output, 1024, fd);
        if (!std::strcmp(std::string(pkg.sha256sum + "  /var/cache/wilpac/" + pkg.name + ".zip").c_str(), output)) {
            std::cerr << BLD RED "()Verification failed, exiting..." RS << std::endl;
            return;
        }
    }

    // unzip zip file
    std::cout << "()Extracting contents..." << std::endl;
    std::system(std::string("sudo unzip /var/cache/wilpac/" + pkg.name + ".zip").c_str());

    // use gigachad to install
    std::cout << "()Installing with gigachad..." << std::endl;
    std::system(std::string("cd /var/cache/wilpac/" + pkg.name + "; gigachad install").c_str());

    // rewrite json as install completed
    std::cout << "()Marking as complete..." << std::endl;
    parser.rewriteCompleted(path);

    // delete directory, keep zip
    std::cout << "()Cleaning cache..." << std::endl;
    std::system(std::string("sudo rm -rf /var/cache/wilpac/" + pkg.name).c_str());
}
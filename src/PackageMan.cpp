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
    std::cout << REG RED "()Checking to see if package is installed..." RS;
    if (pkg.installed) {
        std::cout << REG GRE "\r()Checking to see if package is installed..." RS << std::endl;

        std::string input;
        std::cout << "()Package is already installed, would you like to reinstall? (Y/N)  >>  ";
        std::getline(std::cin, input);

        if (std::strcmp(input.c_str(), "Y") != 0 && std::strcmp(input.c_str(), "y") != 0 && !input.empty()) {
            std::cerr << BLD RED "()Cancelling install..." RS << std::endl;
            return;
        }
    } else { std::cout << REG GRE "\r()Checking to see if package is installed..." RS << std::endl; }

    // download zip file if necessary
    bool skipDl = false;
    if (std::filesystem::exists(std::string("/var/cache/wilpac/" + pkg.name + ".zip").c_str())) {
        std::cout << REG RED "()File exists, checking to see if old version..." RS;

        std::string hash = getChkSum(std::string("/var/cache/wilpac/" + pkg.name + ".zip"));

        std::cout << REG GRE "\r()File exists, checking to see if old version..." RS << std::endl;
        std::cout << "\t- Local file hash: " << hash;
        std::cout << "\t- Source file hash: " << pkg.sha256sum << " /var/cache/wilpac/" << pkg.name << ".zip" << std::endl;

        if (std::strcmp(std::string(pkg.sha256sum + "  /var/cache/wilpac/" + pkg.name + ".zip\n").c_str(), hash.c_str()) == 0) {
            std::cout << REG GRE "()Current file up-to-date, skipping download..." RS << std::endl;
            skipDl = true;
        }
    }

    if (!skipDl) {
        // download file
        std::cout << REG RED "()Downloading file..." RS;
        std::system(std::string("sudo curl -L " + pkg.zipURL + " -o /var/cache/wilpac/" + pkg.name + ".zip").c_str());
        std::cout << REG GRE "\r()Downloading file..." RS << std::endl;

        // verify download
        std::cout << REG RED "()Verifying download..." RS;

        std::string hash = getChkSum(std::string("/var/cache/wilpac/" + pkg.name + ".zip"));

        std::cout << REG GRE "\r()Verifying download..." RS << std::endl;

        if (!std::strcmp(std::string(pkg.sha256sum + "  /var/cache/wilpac/" + pkg.name + ".zip\n").c_str(), hash.c_str())) {
            std::cerr << BLD RED "()Verification failed, exiting..." RS << std::endl;
            return;
        }
    }

    // unzip zip file
    std::cout << REG RED "()Extracting contents..." RS;
    std::system(std::string("sudo unzip -u /var/cache/wilpac/" + pkg.name + ".zip > /dev/null").c_str());
    std::cout << REG GRE "\r()Extracting contents..." RS << std::endl;

    // use gigachad to install
    std::cout << REG RED "()Installing with gigachad..." RS << std::endl;
    if (std::system(std::string("cd /var/cache/wilpac/" + pkg.name + " 2&> /dev/null; gigachad install").c_str()) == 0) { std::cout << REG GRE "\r()Installing with gigachad..." RS << std::endl; }
    else {
        std::cerr << BLD RED "()Failed to install with gigachad, is it installed? Exiting..." RS << std::endl;
        return;
    }

    // rewrite json as install completed
    std::cout << REG RED "()Marking as complete..." RS;
    parser.rewriteCompleted(path);
    std::cout << REG GRE "\r()Marking as complete..." RS << std::endl;

    // delete directory, keep zip
    std::cout << REG RED "()Cleaning cache..." RS;
    std::system(std::string("sudo rm -rf /var/cache/wilpac/" + pkg.name).c_str());
    std::cout << REG GRE "\r()Cleaning cache..." RS << std::endl;
}

std::string getChkSum(std::string file) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(std::string("sha256sum " + file).c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}
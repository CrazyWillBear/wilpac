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
            if (std::filesystem::exists("/etc/wilpac-buckets/" + std::string(entry->d_name) + "/pkgs/" + query)) {
                return "/etc/wilpac-buckets/" + std::string(entry->d_name) + "/pkgs/" + query;
            }
        }
        entry = readdir(dir);
    }

    closedir(dir);

    return "0";
}

void installPkg(std::string path, bool verbose, bool updating) {
    // parse package
    Parser parser(path);
    Package pkg = parser.getPkg();

    // confirm options
    if (!updating) {
        if (!Input::confOpt("()Would you like to install " + pkg.name + "?")) {
            std::cerr << BLD RED "()Cancelling install..." RS << std::endl;
            return;
        }
    }

    // introduce package
    std::cout << "()Installing " << pkg.name << "..." << std::endl;

    // check to see if package is installed
    if (verbose) introTask("()Checking to see if package is installed...");
    if (pkg.installed) {
        if (verbose) outroTask("()Checking to see if package is installed...");

        if (!updating) {
            if (!Input::confOpt("()Package is already installed, would you like to reinstall?")) {
                std::cerr << BLD RED "()Cancelling install..." RS << std::endl;
                return;
            }
        }
    } else if (verbose) { outroTask("()Checking to see if package is installed..."); }

    // download zip file if necessary
    bool skipDl = false;
    if (std::filesystem::exists(std::string("/var/cache/wilpac/" + pkg.name + ".zip").c_str())) {
        if (verbose) introTask("()File exists, checking to see if old version...");

        std::string hash = getChkSum(std::string("/var/cache/wilpac/" + pkg.name + ".zip"));

        if (verbose) outroTask("()File exists, checking to see if old version...");
        if (verbose) std::cout << "\t- Local file hash: " << hash;
        if (verbose) std::cout << "\t- Source file hash: " << pkg.sha256sum << " /var/cache/wilpac/" << pkg.name << ".zip" << std::endl;

        if (std::strcmp(std::string(pkg.sha256sum + "  /var/cache/wilpac/" + pkg.name + ".zip\n").c_str(), hash.c_str()) == 0) {
            if (verbose) outroTask("()Current file up-to-date, skipping download..."); // write this out in green
            skipDl = true;
        }
    }

    if (!skipDl) {
        // download file
        if (verbose) introTask("()Downloading file...");
        std::system(std::string("curl -L " + pkg.zipURL + " -o /var/cache/wilpac/" + pkg.name + ".zip").c_str());
        if (verbose) outroTask("()Downloading file...");

        // verify download
        if (verbose) introTask("()Verifying download...");

        std::string hash = getChkSum(std::string("/var/cache/wilpac/" + pkg.name + ".zip"));

        if (verbose) outroTask("()Verifying download...");

        if (!std::strcmp(std::string(pkg.sha256sum + "  /var/cache/wilpac/" + pkg.name + ".zip\n").c_str(), hash.c_str())) {
            std::cerr << BLD RED "()Verification failed, exiting..." RS << std::endl;
            return;
        }
    }

    // unzip zip file
    if (verbose) introTask("()Extracting contents...");
    std::system(std::string("unzip -u /var/cache/wilpac/" + pkg.name + ".zip > /dev/null").c_str());
    if (verbose) outroTask("()Extracting contents...");

    // use gigachad to install
    if (verbose) introTask("()Installing with gigachad...");
    if (std::system(std::string("cd /var/cache/wilpac/" + pkg.name + " 2&> /dev/null; gigachad install").c_str()) == 0) { if (verbose) outroTask("()Installing with gigachad..."); }
    else {
        std::cerr << BLD RED "\n()Failed to install with gigachad, is it installed? Exiting..." RS << std::endl;
        return;
    }

    // rewrite json as install completed
    if (verbose) introTask("()Marking as complete...");
    parser.rewriteCompleted(path);
    if (verbose) outroTask("()Marking as complete...");

    // delete directory, keep zip
    if (verbose) introTask("()Cleaning cache...");
    std::system(("rm -rf /var/cache/wilpac/" + pkg.name).c_str());
    if (verbose) outroTask("()Cleaning cache...");
}

void updateAll(bool verbose) {
    std::vector<std::string> installedPkgs;
    std::string listPkgs;

    const char* PATH = "/etc/wilpac-buckets";
    DIR *dir = opendir(PATH);

    struct dirent *entry = readdir(dir);

    while (entry != NULL)
    {
        if (entry->d_type == DT_DIR) {
            if (std::filesystem::exists("/etc/wilpac-buckets/" + std::string(entry->d_name) + "/pkgs")) {
                DIR *curDir = opendir(("/etc/wilpac-buckets/" + std::string(entry->d_name) + "/pkgs").c_str());
                struct dirent *curEntry;
                while ((curEntry = readdir(curDir)) != NULL) {
                    try {
                        Parser parser("/etc/wilpac-buckets/" + std::string(entry->d_name) + "/pkgs/" + curEntry->d_name);
                        Package pkg = parser.getPkg();
                        if (pkg.installed == true) {
                            installedPkgs.push_back("/etc/wilpac-buckets/" + std::string(entry->d_name) + "/pkgs/" + curEntry->d_name);
                            std::string pkgName = std::string(curEntry->d_name) ;
                            listPkgs += "\n\t- '" + pkgName.replace(pkgName.end() - 5, pkgName.end(), "") + "'";
                        }
                    } catch (std::exception ex) { }
                }
            }
        }
        entry = readdir(dir);
    }

    if (!Input::confOpt("()Would you like to update all the following packages? " + listPkgs + "\n")) {
        std::cerr << BLD RED "()Cancelling update all..." RS << std::endl;
        return;
    }
    for (std::string pkg : installedPkgs) { installPkg(pkg, verbose, true); }

    closedir(dir);
}

std::string getChkSum(std::string file) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(("sha256sum " + file).c_str(), "r");
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
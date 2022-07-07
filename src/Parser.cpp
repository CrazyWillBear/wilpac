// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "Parser.h"

Parser::Parser(std::string jsonFile) {
    std::ifstream file(jsonFile, std::ios::in);
    nlohmann::json json;
    file >> json;
    try {
        this->pkg.name = json["name"];
        this->pkg.zipURL = json["zipURL"];
        this->pkg.version = json["version"];
        this->pkg.sha256sum = json["sha256sum"];

        nlohmann::json files = json["files"];
        for (auto file = files.begin(); file != files.end(); file++) { this->pkg.files.push_back(file.value()); }
    } catch (std::exception &ex) {
        std::cerr << BLD RED "()Error with package json file" RS << std::endl;
    }
    try {
        nlohmann::json deps = json["deps"];
        for (auto dep = deps.begin(); dep != deps.end(); dep++) { this->pkg.files.push_back(dep.value()); }
    } catch (std::exception &ex) { }
}

void Parser::markCompleted(std::string jsonFile) {
    std::ifstream file(jsonFile, std::ios::in);
    nlohmann::json jsonIn;
    nlohmann::json jsonOut;
    file >> jsonIn;
    jsonOut["name"] = jsonIn["name"];
    jsonOut["pkgPath"] = jsonFile;
    jsonOut["version"] = jsonIn["version"];

    std::string newFile = "/etc/wilpac-buckets/installed/" + std::string(jsonIn["name"]) + ".json";
    std::ofstream newFileStream(newFile, std::ios::out);
    newFileStream << jsonOut.dump();
}

PackageStat Parser::getPkgStat(std::string jsonFile) {
    PackageStat r;

    std::ifstream file(jsonFile, std::ios::in);
    nlohmann::json json;
    file >> json;

    r.name = json["name"];
    r.pkgPath = json["pkgPath"];
    r.version = json["version"];

    return r;
}
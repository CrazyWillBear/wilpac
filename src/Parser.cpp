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
        this->pkg.installed = json["installed"];
        this->pkg.sha256sum = json["sha256sum"];

        nlohmann::json files = json["files"];
        for (auto file = files.begin(); file != files.end(); file++) { this->pkg.files.push_back(file.value()); }
    } catch (std::exception &ex) {
        std::cerr << BLD RED "()Error with package json file" RS << std::endl;
    }
}

void Parser::rewriteCompleted(std::string jsonFile) {
    std::ifstream file(jsonFile, std::ios::in);
    nlohmann::json json;
    file >> json;
    json["installed"] = true;
    std::ofstream newFile(jsonFile, std::ios::out);
    newFile << json.dump();
}
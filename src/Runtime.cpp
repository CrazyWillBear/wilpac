// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "Runtime.h"

Runtime::Runtime() {
    FILE *file;

    if ((file = fopen("/etc/wilpac-buckets", "r"))) { fclose(file); } else { std::system("mkdir -p /etc/wilpac-buckets"); }

    if ((file = fopen("/etc/wilpac-buckets/fetch.sh", "r"))) { fclose(file); } else { fillBucketlist(); }
}

void Runtime::fillBucketlist() {
    std::cout << "()Filling bucketlist\n";
    std::string text = "if cd wilpac-main; then git pull; else git clone https://github.com/CrazyWillBear/wilpac-main --progress; fi";
    std::fstream file;

    file.open("/etc/wilpac-buckets/fetch.sh", std::ios::out);

    if (!file) { std::cerr << "()Failed to write new buckletlist\n"; } else {
        file.write(text.data(), text.size());
        std::cout << "()Wrote default bucketlist to fetch script\n";
    }

    file.close();
}

Runtime::~Runtime() { }
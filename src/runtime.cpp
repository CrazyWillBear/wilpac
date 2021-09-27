// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "runtime.h"

runtime::runtime() {
    FILE *file;
    if ((file = fopen("/etc/wilpac-bucketlist", "r"))) { fclose(file); } else { this->fillBucketlist(); }

    if ((file = fopen("/etc/wilpac-buckets", "r"))) { fclose(file); } else { std::system("mkdir -p /etc/wilpac-buckets"); }
}

void runtime::fillBucketlist() {
    std::string text = "https://github.com/CrazyWillBear/winpac-main";
    std::fstream file;

    file.open("/etc/wilpac-bucketlist", std::ios::out);

    if (!file) { std::cerr << "()Failed to write new buckletlist\n"; } else {
        file.write(text.data(), text.size());
        std::cout << "()Wrote default bucketlist\n";
    }

    file.close();
}

runtime::~runtime() { }
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "Runtime.h"

Runtime::Runtime() {
    FILE *file;

    if ((file = fopen("/etc/wilpac-buckets", "r"))) { fclose(file); } else { std::system("mkdir -p /etc/wilpac-buckets"); }

    if ((file = fopen("/etc/wilpac-buckets/fetch.sh", "r"))) { fclose(file); } else { fillDefaultFetchScript(); }
}

void Runtime::fillDefaultFetchScript() {
    std::cout << REG G "()Filling bucketlist..." RS;
    std::string text = "# This is the default fetch script. This was generated by wilpac.\n\necho \"- wilpac-main:\"; if cd wilpac-main 2>/dev/null; then git pull --progress |& sed 's/^/\t/g'; else git clone https://github.com/CrazyWillBear/wilpac-main |& sed 's/^/\t/g'; echo \"\tCloned into 'wilpac-main'\"; fi\n";
    std::fstream file;

    file.open("/etc/wilpac-buckets/fetch.sh", std::ios::out);

    if (!file) { std::cerr << REG R "()Failed to write new buckletlist" RS "\n"; } else {
        file.write(text.data(), text.size());
        std::cout << REG G "\r()Wrote default bucketlist to fetch script" RS "\n";
        Bucket::getBuckets();
    }

    file.close();
}

Runtime::~Runtime() { }
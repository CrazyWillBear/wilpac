// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "Bucket.h"

Bucket::Bucket() { }

void Bucket::getBuckets() {
    std::cout << REG G "()Buckets:" RS "\n";
    std::system("cd /etc/wilpac-buckets; ls -d */ | sed 's/^/\t/g'");
}

void Bucket::fetchBuckets() {
    std::cout << REG G "()Updating buckets..." RS "\n";
    std::system("cd /etc/wilpac-buckets; sh /etc/wilpac-buckets/fetch.sh |& sed 's/^/\t/g'");
}

Bucket::~Bucket() { }
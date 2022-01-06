// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "Bucket.h"

Bucket::Bucket() { }

void Bucket::getBuckets() {
    std::cout << "()Buckets:\n";
    std::system("cd /etc/wilpac-buckets; ls -d */");
}

void Bucket::fetchBuckets() {
    std::system("cd /etc/wilpac-buckets; bash /etc/wilpac-buckets/fetch.sh");
}

Bucket::~Bucket() { }
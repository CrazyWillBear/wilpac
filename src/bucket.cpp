// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "bucket.h"

bucket::bucket() {

}

void bucket::fetchBuckets() {
    std::system("pushd /etc/wilpac-buckets; find . -type d -depth 1 -exec echo git --git-dir={}/.git --work-tree=$PWD/{} status \\; popd");
    std::cout << this->getBuckets() << "\n";
}

std::string* bucket::getBuckets() {
    std::fstream bucketlist;
    bucketlist.open("/etc/wilpac-bucketlist");

    std::string str;
    bucketlist >> str;

}

bucket::~bucket() { }
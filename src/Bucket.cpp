// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "Bucket.h"

Bucket::Bucket() { }

void Bucket::fetchBuckets() {
    std::system("pushd /etc/wilpac-buckets; find . -type d -depth 1 -exec echo git --git-dir={}/.git --work-tree=$PWD/{} status \\; popd");
    std::cout << this->getBuckets() << "\n";
}

std::string Bucket::getBuckets() {
    std::fstream bucketlist;
    bucketlist.open("/etc/wilpac-bucketlist");

    std::string str;
    bucketlist >> str;

    // I've gotten this far: I'm trying to split this string, idk
    // what to do from here.
    std::string token = str.substr(0, str.find("\n"));

    // this is here for testing reasons, ignore:
    return str;
}

Bucket::~Bucket() { }
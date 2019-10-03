// Copyright © 2017-2019 Trust.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "HexCoding.h"
#include "Filecoin/Address.h"
#include "PublicKey.h"
#include "PrivateKey.h"
#include <gtest/gtest.h>
#include <vector>

using namespace TW;
using namespace TW::Filecoin;

TEST(FilecoinAddress, Validation) {
    // empty address
    ASSERT_FALSE(Address::isValid(""));
    // invalid checksum
//    ASSERT_FALSE(Address::isValid("t15ihq5ibzwki2b4ep2f46avlkrqzhpqgtga7pppp"));
    // wrong length
//    ASSERT_FALSE(Address::isValid("t15ihq5ibzwki2b4ep2f46avlkrqzhpqgtga7pdrq "));
    // Stellar address
//    ASSERT_FALSE(Address::isValid("t15ihq5ibzwki2b4ep2f46avlkrqzhpqgtga7p"));

    ASSERT_TRUE(Address::isValid("f17uoq6tp427uzv7fztkbsnn64iwotfrristwpryy"));
}

TEST(FilecoinAddress, FromPrivateKey) {
    auto privateKey = PrivateKey(parse_hex("526d96fffdbfe787b2f00586298538f9a019e97f6587964dc61aae9ad1d7fa23"));
    auto address = Address(privateKey.getPublicKey(TWPublicKeyTypeSECP256k1));
    ASSERT_EQ(address.string(), "t15ihq5ibzwki2b4ep2f46avlkrqzhpqgtga7pdrq");
}

TEST(FilecoinAddress, FromPublicKey) {
    auto publicKey = PublicKey(parse_hex("c2b423afa8b0095e5ae105668b91b2132db4dadbf38acfc64908d3476a00191f"), TWPublicKeyTypeSECP256k1);
    auto address = Address(publicKey);
    ASSERT_EQ(address.string(), "t15ihq5ibzwki2b4ep2f46avlkrqzhpqgtga7pdrq");
}

TEST(FilecoinAddress, FromString) {
    auto address = Address("t15ihq5ibzwki2b4ep2f46avlkrqzhpqgtga7pdrq");
    ASSERT_EQ(address.string(), "t15ihq5ibzwki2b4ep2f46avlkrqzhpqgtga7pdrq");
}

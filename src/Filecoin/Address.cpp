// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "../HexCoding.h"
#include "../Hash.h"
#include "Address.h"

#include <TrezorCrypto/base32.h>

#include <array>
#include <iostream>

using namespace TW;
using namespace TW::Filecoin;

bool Address::isValid(const std::string& string) {
    if (string.size() != encodedSize) {
        return false;
    }
    const size_t payloadSize = 20;
    const size_t dataSize = payloadSize + checksumSize;
    std::array<byte, dataSize> decoded;
    // base32 decode
    if (base32_decode(string.data()+2, string.size()-2, decoded.data(), dataSize, BASE32_ALPHABET_RFC4648) == nullptr) {
        return false;
    }
    std::array<byte, payloadSize+1> check;
//    std::copy(string.data()+1, string.data()+2, check.data());
    std::copy(decoded.data(), decoded.data()+payloadSize, check.data()+1);
    check[0] = 1;
    // compute checksum
    auto hash = TW::Hash::blake2b(check.data(), check.data()+payloadSize+1, 4);
    // last 4 bytes are checksum
//    std::array<byte, checksumSize> checksum;
//    std::copy(hash.data(), hash.data()+checksumSize, checksum.data());
//    printf("%s", checksum);
//    std::cout << "checksum";
    // compare checksum
    if (!std::equal(decoded.end() - checksumSize, decoded.end(), hash.begin())) {
        return false;
    }
    return true;
}

Address::Address(const std::string& string) {
    if (!isValid(string)) {
        throw std::invalid_argument("Invalid address string");
    }

    const size_t dataSize = 20 + checksumSize;
    std::array<byte, dataSize> decoded;
    base32_decode(string.data(), string.size(), decoded.data(), dataSize, BASE32_ALPHABET_RFC4648);
    std::copy(decoded.begin(), decoded.begin() + PublicKey::secp256k1Size, bytes.begin());
}

Address::Address(const PublicKey& publicKey) {
    if (publicKey.type != TWPublicKeyTypeSECP256k1) {
        throw std::invalid_argument("Invalid public key type");
    }
    std::copy(publicKey.bytes.begin(), publicKey.bytes.end(), bytes.data());
}

std::string Address::string() const {
    auto hash = Hash::sha512_256(bytes);
    const size_t dataSize = PublicKey::secp256k1Size + checksumSize;
    std::array<byte, dataSize> data;
    std::vector<char> encoded;
    encoded.resize(64);

    // base32_encode(publickey + checksum)
    std::copy(bytes.begin(), bytes.end(), data.data());
    std::copy(hash.end() - checksumSize, hash.end(), data.data() + PublicKey::secp256k1Size);
    base32_encode(data.data(), dataSize, encoded.data(), encoded.size(), BASE32_ALPHABET_RFC4648);
    return std::string(encoded.begin(), encoded.begin() + encodedSize);
}

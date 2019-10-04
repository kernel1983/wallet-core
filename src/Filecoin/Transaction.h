// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Address.h"
#include "../Data.h"
#include "../proto/Filecoin.pb.h"

namespace TW::Filecoin {

class Transaction {
  public:
    Address from;
    Address to;
    // uint64_t fee;
    // uint64_t amount;
    // uint64_t firstRound;
    // uint64_t lastRound;
    // Data note;
    // std::string type;

    uint64_t nonce;
    uint64_t value;
    uint64_t gasPrice;
    uint64_t gasLimit;
    uint64_t method;
    // Public key hash (Address.bytes)
    // Data to;
    // uint256_t amount;
    // Data payload;

    // std::string genesisId;
    // Data genesisHash;

    Transaction(Address &from, Address &to, uint64_t value, uint64_t gasPrice, uint64_t gasLimit)//, uint64_t firstRound,
                // uint64_t lastRound, Data &note, std::string type, std::string &genesisIdg, Data &genesisHash)
        : from(from) , to(to)
        , value(value)//, amount(amount)
        // , firstRound(firstRound), lastRound(lastRound)
        // , note(note), type(type)
        , gasPrice(gasPrice), gasLimit(gasLimit) {}

  public:
    Data serialize() const;
    Data serialize(Data &signature) const;
};

} // namespace TW::Filecoin

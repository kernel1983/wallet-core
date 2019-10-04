// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Transaction.h"

#include "../Data.h"
#include "../PrivateKey.h"

namespace TW::Filecoin {

/// Helper class that performs Filecoin transaction signing.
class Signer {
  public:
    Signer() = delete;

    /// Signs a Proto::SigningInput transaction
    static Proto::SigningOutput sign(const Proto::SigningInput& input) noexcept;

    /// Signs the given transaction.
    static Data sign(const PrivateKey& privateKey, Transaction& transaction) noexcept;
};

} // namespace TW::Filecoin

/// Wrapper for C interface.
struct TWFilecoinSigner {
    TW::Filecoin::Signer impl;
};

// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2018 The Bitcoin SV developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_SCRIPT_INTERPRETER_H
#define BITCOIN_SCRIPT_INTERPRETER_H

#include <satoshi_sv/src/primitives/transaction.h>
#include <satoshi_sv/src/script/script_flags.h>
#include <satoshi_sv/src/script/script_error.h>
#include <satoshi_sv/src/script/sighashtype.h>

#include <cstdint>
#include <string>
#include <vector>

namespace sv {

class CPubKey;
class CScript;
class CTransaction;
class uint256;

bool CheckSignatureEncoding(const std::vector<uint8_t> &vchSig, uint32_t flags,
                            ScriptError *serror);

uint256 SignatureHash(const CScript &scriptCode, const CTransaction &txTo,
                      unsigned int nIn, SigHashType sigHashType,
                      const Amount amount,
                      const PrecomputedTransactionData *cache = nullptr,
                      uint32_t flags = SCRIPT_ENABLE_SIGHASH_FORKID);

class BaseSignatureChecker {
public:
    virtual bool CheckSig(const std::vector<uint8_t> &scriptSig,
                          const std::vector<uint8_t> &vchPubKey,
                          const CScript &scriptCode, uint32_t flags) const {
        return false;
    }

    virtual bool CheckLockTime(const CScriptNum &nLockTime) const {
        return false;
    }

    virtual bool CheckSequence(const CScriptNum &nSequence) const {
        return false;
    }

    virtual ~BaseSignatureChecker() {}
};

class TransactionSignatureChecker : public BaseSignatureChecker {
private:
    const CTransaction *txTo;
    unsigned int nIn;
    const Amount amount;
    const PrecomputedTransactionData *txdata;

protected:
    virtual bool VerifySignature(const std::vector<uint8_t> &vchSig,
                                 const CPubKey &vchPubKey,
                                 const uint256 &sighash) const;

public:
    TransactionSignatureChecker(const CTransaction *txToIn, unsigned int nInIn,
                                const Amount amountIn)
        : txTo(txToIn), nIn(nInIn), amount(amountIn), txdata(nullptr) {}
    TransactionSignatureChecker(const CTransaction *txToIn, unsigned int nInIn,
                                const Amount amountIn,
                                const PrecomputedTransactionData &txdataIn)
        : txTo(txToIn), nIn(nInIn), amount(amountIn), txdata(&txdataIn) {}
    bool CheckSig(const std::vector<uint8_t> &scriptSig,
                  const std::vector<uint8_t> &vchPubKey,
                  const CScript &scriptCode, uint32_t flags) const override;
    bool CheckLockTime(const CScriptNum &nLockTime) const override;
    bool CheckSequence(const CScriptNum &nSequence) const override;
};

class MutableTransactionSignatureChecker : public TransactionSignatureChecker {
private:
    const CTransaction txTo;

public:
    MutableTransactionSignatureChecker(const CMutableTransaction *txToIn,
                                       unsigned int nInIn, const Amount amount)
        : TransactionSignatureChecker(&txTo, nInIn, amount), txTo(*txToIn) {}
};

bool EvalScript(std::vector<std::vector<uint8_t>> &stack, const CScript &script,
                uint32_t flags, const BaseSignatureChecker &checker,
                ScriptError *error = nullptr);
bool VerifyScript(const CScript &scriptSig, const CScript &scriptPubKey,
                  uint32_t flags, const BaseSignatureChecker &checker,
                  ScriptError *serror = nullptr);

}

#endif // BITCOIN_SCRIPT_INTERPRETER_H

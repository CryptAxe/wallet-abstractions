// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2019 Bitcoin Association
// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef BITCOIN_PRIMITIVES_BLOCK_H
#define BITCOIN_PRIMITIVES_BLOCK_H

#include <satoshi_sv/src/primitives/transaction.h>
#include <satoshi_sv/src/serialize.h>
#include <satoshi_sv/src/uint256.h>

namespace sv { 

/**
 * Nodes collect new transactions into a block, hash them into a hash tree, and
 * scan through nonce values to make the block's hash satisfy proof-of-work
 * requirements. When they solve the proof-of-work, they broadcast the block to
 * everyone and the block is added to the block chain. The first transaction in
 * the block is a special one that creates a new coin owned by the creator of
 * the block.
 */
class CBlockHeader {
public:
    // header
    int32_t nVersion;
    uint256 hashPrevBlock;
    uint256 hashMerkleRoot;
    uint32_t nTime;
    uint32_t nBits;
    uint32_t nNonce;

    CBlockHeader() { SetNull(); }

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream &s, Operation ser_action) {
        READWRITE(this->nVersion);
        READWRITE(hashPrevBlock);
        READWRITE(hashMerkleRoot);
        READWRITE(nTime);
        READWRITE(nBits);
        READWRITE(nNonce);
    }

    void SetNull() {
        nVersion = 0;
        hashPrevBlock.SetNull();
        hashMerkleRoot.SetNull();
        nTime = 0;
        nBits = 0;
        nNonce = 0;
    }

    bool IsNull() const { return (nBits == 0); }

    uint256 GetHash() const;

    int64_t GetBlockTime() const { return (int64_t)nTime; }
};

class CBlock : public CBlockHeader {
public:
    // network and disk
    std::vector<CTransactionRef> vtx;

    // memory only
    mutable bool fChecked;

    CBlock() { SetNull(); }

    CBlock(const CBlockHeader &header) {
        SetNull();
        *((CBlockHeader *)this) = header;
    }

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream &s, Operation ser_action) {
        READWRITE(*(CBlockHeader *)this);
        READWRITE(vtx);
    }

    uint64_t GetHeightFromCoinbase() const // Returns the block's height as specified in its coinbase transaction
    {
        const CScript &sig = vtx[0]->vin[0].scriptSig;

        // Get length of height number
        if(sig.empty())
            throw std::runtime_error("Empty coinbase scriptSig");
        uint8_t numlen = sig[0];
        if(sig.size() - 1 < numlen)
            throw std::runtime_error("Badly formated hight in coinbase");

        // Parse height as CScriptNum
        if (numlen == OP_0)
            return 0;
        if ((numlen >= OP_1) && (numlen <= OP_16))
            return numlen - OP_1 + 1;
        std::vector<unsigned char> heightScript(numlen);
        copy(sig.begin() + 1, sig.begin() + 1 + numlen, heightScript.begin());
        CScriptNum coinbaseHeight(heightScript, false, numlen);
        return coinbaseHeight.getint();
    }

    void SetNull() {
        CBlockHeader::SetNull();
        vtx.clear();
        fChecked = false;
    }

    CBlockHeader GetBlockHeader() const {
        CBlockHeader block;
        block.nVersion = nVersion;
        block.hashPrevBlock = hashPrevBlock;
        block.hashMerkleRoot = hashMerkleRoot;
        block.nTime = nTime;
        block.nBits = nBits;
        block.nNonce = nNonce;
        return block;
    }

    std::string ToString() const;
};

typedef std::shared_ptr<CBlock> CBlockRef;

/**
 * Describes a place in the block chain to another node such that if the other
 * node doesn't have the same branch, it can find a recent common trunk.  The
 * further back it is, the further before the fork it may be.
 */
struct CBlockLocator {
    std::vector<uint256> vHave;

    CBlockLocator() {}

    CBlockLocator(const std::vector<uint256> &vHaveIn) { vHave = vHaveIn; }

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream &s, Operation ser_action) {
        int nVersion = s.GetVersion();
        if (!(s.GetType() & SER_GETHASH)) READWRITE(nVersion);
        READWRITE(vHave);
    }

    void SetNull() { vHave.clear(); }

    bool IsNull() const { return vHave.empty(); }
};

}

#endif // BITCOIN_PRIMITIVES_BLOCK_H

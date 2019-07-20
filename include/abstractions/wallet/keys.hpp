// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_KEYS
#define ABSTRACTIONS_WALLET_KEYS

#include <data/crypto/secp256k1.hpp>
#include <abstractions/crypto/hash/sha256.hpp>
#include <abstractions/crypto/hash/ripemd160.hpp>
#include "tag.hpp"
#include "hash.hpp"
#include "address.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        struct pubkey;
        
        using signature = data::secp256k1::signature;
        
        struct secret : public data::secp256k1::secret {
            using parent = data::secp256k1::secret;
            using parent::secret;
            
            pubkey to_public() const;
            
            secret operator+(const secret&) const;
            secret operator*(const secret&) const;
            
            secret& operator=(const secret& s);
            
            signature sign(const sha256::digest&) const;
            
            explicit secret(string wif);
        };
        
        struct pubkey : public data::secp256k1::pubkey, public tag {
            using parent = data::secp256k1::pubkey;
            using parent::pubkey;
            
            pubkey operator+(const pubkey&) const;
            pubkey operator*(const secret&) const;
            
            pubkey& operator=(const pubkey& p);
            
            bool verify(const sha256::digest&, const signature&) const;
            
            explicit pubkey(string wif);
        };
        
        constexpr data::math::module<pubkey, secret> is_module{};
        constexpr data::crypto::signature_scheme<secret, pubkey, const sha256::digest, signature> is_signature_scheme{};
    
        namespace wif {
            bool read(string&, secret&);
            string write(secret&);
            void write(secret&, stringstream&);
        }
        
        namespace wif_compressed {
            bool read(string&, secret&);
            string write(secret&);
            void write(secret&, stringstream&);
        }
        
        inline address hash(pubkey& b) {
            return ripemd160::hash<data::secp256k1::pubkey_size>(static_cast<std::array<byte, data::secp256k1::pubkey_size>&>(b));
        }
            
        inline pubkey secret::to_public() const {
            throw 0;
        }
            
        inline secret secret::operator+(const secret&) const {
            throw 0;
        }
        
        inline secret secret::operator*(const secret&) const {
            throw 0;
        }
            
        inline secret& secret::operator=(const secret& s) {
            throw 0;
        }
            
        inline signature secret::sign(const sha256::digest&) const {
            throw 0;
        }
            
        inline pubkey pubkey::operator+(const pubkey&) const {
            throw 0;
        }
        
        inline pubkey pubkey::operator*(const secret&) const {
            throw 0;
        }
            
        inline pubkey& pubkey::operator=(const pubkey& p) {
            throw 0;
        }
            
        inline bool pubkey::verify(const sha256::digest&, const signature&) const {
            throw 0;
        }
        
    }
    
} 

#endif


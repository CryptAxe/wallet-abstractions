// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_KEYS
#define ABSTRACTIONS_WALLET_KEYS

#include <abstractions/crypto/secp256k1.hpp>
#include <abstractions/crypto/hash/sha256.hpp>
#include <abstractions/crypto/hash/ripemd160.hpp>
#include "tag.hpp"
#include "hash.hpp"
#include "address.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        struct pubkey;
        
        using signature = secp256k1::signature;
        
        struct secret : public secp256k1::compressed_secret {
            using parent = secp256k1::compressed_secret;
            using parent::secret;
            using pubkey = bitcoin::pubkey;
            
            pubkey to_public() const;
            
            secret operator+(const secret&) const;
            secret operator*(const secret&) const;
            
            secret& operator=(const secret& s);
            
            explicit secret(string wif);
            
            bitcoin::address address() const;
            string write();
        };
        
        struct pubkey : public secp256k1::compressed_pubkey, public tag {
            using parent = secp256k1::compressed_pubkey;
            using parent::pubkey;
            using secret = bitcoin::secret;
            
            pubkey operator+(const pubkey&) const;
            pubkey operator*(const secret&) const;
            
            pubkey& operator=(const pubkey& p);
            
            explicit pubkey(string hex);
            
            bitcoin::address address() const;
            string write();
        };
        
        constexpr data::math::module<pubkey, secret> is_module{};
        constexpr data::crypto::signature_scheme<secret, pubkey, const sha256::digest, signature> is_signature_scheme{};
    
        namespace wif {
            // 52 characters base58, starts with a 'K' or 'L'
            bool read(const string&, secret&);
            string write(secret&);
        }
        
        inline pubkey secret::to_public() const {
            return secret::parent::to_public();
        }
        
        inline secret secret::operator+(const secret& s) const {
            return parent::operator+(static_cast<const parent&>(s));
        }
        
        inline secret secret::operator*(const secret& s) const {
            return parent::operator+(static_cast<const parent&>(s));
        }
        
        inline secret& secret::operator=(const secret& s) {
            parent::operator=(static_cast<const parent&>(s));
            return *this;
        }
        
        inline pubkey pubkey::operator+(const pubkey& p) const {
            return parent::operator+(static_cast<const parent&>(p));
        }
        
        inline pubkey pubkey::operator*(const secret& s) const {
            return parent::operator*(static_cast<const secret::parent&>(s));
        }
        
        inline pubkey& pubkey::operator=(const pubkey& p) {
            parent::operator=(static_cast<const parent&>(p));
            return *this;
        }
        
        inline bitcoin::address pubkey::address() const {
            return secp256k1::address(*this);
        };
        
        inline bitcoin::address secret::address() const {
            return secp256k1::address(*this);
        };
        
    }
    
} 

#endif


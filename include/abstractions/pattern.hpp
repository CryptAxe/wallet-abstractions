// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_PATTERN
#define ABSTRACTIONS_PATTERN

#include <data/crypto/keypair.hpp>
#include <abstractions/transaction.hpp>

namespace abstractions {
    
    namespace pattern {
        
        namespace abstract {
        
            template <
                typename Key,
                typename Script, 
                typename Tx>
            struct redeemer {
                
                // make a script signature.
                virtual Script redeem(satoshi, Script, Tx, index, Key) const = 0;
                
            };
        
            template <
                typename Key,
                typename Script, 
                typename Tx>
            struct pattern : public redeemer<Key, Script, Tx> {
                
                // make a script pubkey. 
                virtual Script pay(Key) const = 0;
                
                template <typename Machine>
                void pattern_definition(Key k, Tx t, Machine i) const {
                    assert(i.run(pay(k), redeem(k, t), t));
                }
            };
        
            template <typename Key, typename Tag> struct tagged {
                virtual Tag tag(Key) const = 0;
            };
        
            template <
                typename Key,
                typename Script, 
                typename Tag, 
                typename Tx>
            struct recognizable : 
                public virtual pattern<Key, Script, Tx>, 
                public virtual tagged<Key, Tag> {
                
                virtual list<Tag> recognize(Script) const = 0;
                
                void recognizable_pattern_definition(Key k) const {
                    if (tagged<Key, Tag>::tag(k) != recognize(pattern<Key, Script, Tx>::pay(k))) throw 0;
                }
                
            };
        
            template <
                typename Key,
                typename Script, 
                typename Tag, 
                typename Tx>
            struct addressable : 
                public virtual pattern<Key, Script, Tx>, 
                public virtual tagged<Key, Tag> {
                
                virtual Script pay(Tag) const = 0;
                
                Script pay(Key k) const final override {
                    return pay(tagged<Key, Tag>::tag(k));
                }
                
            };
            
            template <
                typename Sk,
                typename Pk, 
                typename Script, 
                typename Tag, 
                typename Tx>
            struct standard : 
                public virtual data::crypto::keypair<Sk, Pk>, 
                public virtual recognizable<Sk, Script, Tag, Tx>, 
                public virtual addressable<Sk, Script, Tag, Tx> {
                    
                virtual Tag tag(Pk) const = 0;
                
                Tag tag(Sk k) const final override {
                    return tag(data::crypto::to_public<Sk, Pk>{}(k));
                };
                
                Script pay(Pk k) const {
                    return pay(tag(k));
                }
                
            };
            
        }
        
    }
    
} 

#endif

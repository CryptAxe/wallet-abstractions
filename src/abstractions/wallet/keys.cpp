// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/wallet/keys.hpp>

namespace abstractions {
    
    namespace bitcoin {
    
        namespace wif {
            bool read(const string&, secret&) {
                throw 0;
            }
            
            string write(secret&) {
                throw 0;
            }
            
            bool read(const string&, pubkey&) {
                throw 0;
            }
            
            string write(pubkey&) {
                throw 0;
            }
        }
        
        namespace wif_compressed {
            bool read(const string&, secret&) {
                throw 0;
            }
            
            string write(secret&) {
                throw 0;
            }
            bool read(const string&, pubkey&) {
                throw 0;
            }
            
            string write(pubkey&) {
                throw 0;
            }
        }
        
    }
    
} 


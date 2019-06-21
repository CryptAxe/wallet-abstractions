// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_ACCOUNT_OUTPUT
#define ABSTRACTIONS_ACCOUNT_OUTPUT

#include <abstractions/transaction.hpp>
#include "input.hpp"
#include "output.hpp"

namespace abstractions {
    
    namespace account {
        
        template <typename scriptPubkey, typename scriptSig>
        using transaction = abstractions::transaction<input<scriptSig>, output<scriptPubkey>>;
        
    }
    
} 

#endif

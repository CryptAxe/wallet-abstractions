// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2018 The Bitcoin SV developers
// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_SCRIPT
#define ABSTRACTIONS_SCRIPT_SCRIPT

#include <abstractions/abstractions.hpp>
#include <data/fold.hpp>

namespace abstractions::script {
    struct program {
        virtual N length() const = 0;
        virtual void write(ostream&) const = 0;
        bytes compile() const;

        operator bytes() const {
            return compile();
        }

        enum op : byte {
            // OP_0 and OP_FALSE push the bytes 0x00 onto the stack
            OP_0 = 0x00,
            OP_FALSE = OP_0,

            OP_PUSHSIZE1 = 0x01,
            OP_PUSHSIZE2 = 0x02,
            OP_PUSHSIZE3 = 0x03,
            OP_PUSHSIZE4 = 0x04,
            OP_PUSHSIZE5 = 0x05,
            OP_PUSHSIZE6 = 0x06,
            OP_PUSHSIZE7 = 0x07,
            OP_PUSHSIZE8 = 0x08,
            OP_PUSHSIZE9 = 0x09,

            OP_PUSHSIZE10 = 0x0a,
            OP_PUSHSIZE11 = 0x0b,
            OP_PUSHSIZE12 = 0x0c,
            OP_PUSHSIZE13 = 0x0d,
            OP_PUSHSIZE14 = 0x0e,
            OP_PUSHSIZE15 = 0x0f,
            OP_PUSHSIZE16 = 0x10,
            OP_PUSHSIZE17 = 0x11,
            OP_PUSHSIZE18 = 0x12,
            OP_PUSHSIZE19 = 0x13,

            OP_PUSHSIZE20 = 0x14,
            OP_PUSHSIZE21 = 0x15,
            OP_PUSHSIZE22 = 0x16,
            OP_PUSHSIZE23 = 0x17,
            OP_PUSHSIZE24 = 0x18,
            OP_PUSHSIZE25 = 0x19,
            OP_PUSHSIZE26 = 0x1a,
            OP_PUSHSIZE27 = 0x1b,
            OP_PUSHSIZE28 = 0x1c,
            OP_PUSHSIZE29 = 0x1d,

            OP_PUSHSIZE30 = 0x1e,
            OP_PUSHSIZE31 = 0x1f,
            OP_PUSHSIZE32 = 0x20,
            OP_PUSHSIZE33 = 0x21,
            OP_PUSHSIZE34 = 0x22,
            OP_PUSHSIZE35 = 0x23,
            OP_PUSHSIZE36 = 0x24,
            OP_PUSHSIZE37 = 0x25,
            OP_PUSHSIZE38 = 0x26,
            OP_PUSHSIZE39 = 0x27,

            OP_PUSHSIZE40 = 0x28,
            OP_PUSHSIZE41 = 0x29,
            OP_PUSHSIZE42 = 0x2a,
            OP_PUSHSIZE43 = 0x2b,
            OP_PUSHSIZE44 = 0x2c,
            OP_PUSHSIZE45 = 0x2d,
            OP_PUSHSIZE46 = 0x2e,
            OP_PUSHSIZE47 = 0x2f,
            OP_PUSHSIZE48 = 0x30,
            OP_PUSHSIZE49 = 0x31,

            OP_PUSHSIZE50 = 0x32,
            OP_PUSHSIZE51 = 0x33,
            OP_PUSHSIZE52 = 0x34,
            OP_PUSHSIZE53 = 0x35,
            OP_PUSHSIZE54 = 0x36,
            OP_PUSHSIZE55 = 0x37,
            OP_PUSHSIZE56 = 0x38,
            OP_PUSHSIZE57 = 0x39,
            OP_PUSHSIZE58 = 0x3a,
            OP_PUSHSIZE59 = 0x3b,

            OP_PUSHSIZE60 = 0x3c,
            OP_PUSHSIZE61 = 0x3d,
            OP_PUSHSIZE62 = 0x3e,
            OP_PUSHSIZE63 = 0x3f,
            OP_PUSHSIZE64 = 0x40,
            OP_PUSHSIZE65 = 0x41,
            OP_PUSHSIZE66 = 0x42,
            OP_PUSHSIZE67 = 0x43,
            OP_PUSHSIZE68 = 0x44,
            OP_PUSHSIZE69 = 0x45,

            OP_PUSHSIZE70 = 0x46,
            OP_PUSHSIZE71 = 0x47,
            OP_PUSHSIZE72 = 0x48,
            OP_PUSHSIZE73 = 0x49,
            OP_PUSHSIZE74 = 0x4a,
            OP_PUSHSIZE75 = 0x4b,

            // The next byte is the number of following bytes to push
            OP_PUSHDATA1 = 0x4c,
            // The next 2 bytes are the number of following bytes to push
            OP_PUSHDATA2 = 0x4d,
            // The next 4 bytes are the number of following bytes to push
            OP_PUSHDATA4 = 0x4e,
            // The number -1 is pushed to the stack
            OP_1NEGATE = 0x4f,
            // Unassigned word which will mark script as invalid if executed
            OP_RESERVED = 0x50,
            // For OP_1 and OP_TRUE, the number 1 is pushed to the stack.
            OP_1 = 0x51,
            OP_TRUE = OP_1,
            // The number 2 is pushed to the stack
            OP_2 = 0x52,
            // The number 3 is pushed to the stack
            OP_3 = 0x53,
            // The number 4 is pushed to the stack
            OP_4 = 0x54,
            // The number 5 is pushed to the stack
            OP_5 = 0x55,
            // The number 6 is pushed to the stack
            OP_6 = 0x56,
            // The number 7 is pushed to the stack
            OP_7 = 0x57,
            // The number 8 is pushed to the stack
            OP_8 = 0x58,
            // The number 9 is pushed to the stack
            OP_9 = 0x59,
            // The number 10 is pushed to the stack
            OP_10 = 0x5a,
            // The number 11 is pushed to the stack
            OP_11 = 0x5b,
            // The number 12 is pushed to the stack
            OP_12 = 0x5c,
            // The number 13 is pushed to the stack
            OP_13 = 0x5d,
            // The number 14 is pushed to the stack
            OP_14 = 0x5e,
            // The number 15 is pushed to the stack
            OP_15 = 0x5f,
            // The number 16 is pushed to the stack
            OP_16 = 0x60,

            // control
            // Does nothing
            OP_NOP = 0x61,
            // Unassigned word which will mark script as invalid if executed
            OP_VER = 0x62,
            // Clear top stack item, if true execute statements until OP_ENDIF
            OP_IF = 0x63,
            // Clear top stack item, if false execute statements until OP_ENDIF
            OP_NOTIF = 0x64,
            // Unassigned word which will mark script as invalid if executed
            OP_VERIF = 0x65,
            // Unassigned word which will mark script as invalid if executed
            OP_VERNOTIF = 0x66,
            // Execute until OP_ENDIF when previous IF / NOTIF not executed
            OP_ELSE = 0x67,
            // End of IF statement required for valid script
            OP_ENDIF = 0x68,
            // Clears the top stack value and marks script invalid if false
            OP_VERIFY = 0x69,
            // Ends script interpretation and marks script invalid
            OP_RETURN = 0x6a,

            // stack ops
            // Moves the current main stack top to alt stack
            OP_TOALTSTACK = 0x6b,
            // Moves the current alt stack top to main stack
            OP_FROMALTSTACK = 0x6c,
            // Removes the top two stack items
            OP_2DROP = 0x6d,
            // Copy the top two stack items and place copies on stack
            OP_2DUP = 0x6e,
            // Copy the top three stack items and place copies on stack
            OP_3DUP = 0x6f,
            // Copy stack top - 2 & stack top - 3 to the top of the stack
            OP_2OVER = 0x70,
            // Stack top - 4 & stack top - 5 are moved to the top of the stack
            OP_2ROT = 0x71,
            // Swaps the top two stack values with the two values below them
            OP_2SWAP = 0x72,
            // Duplicate the top stack value if it is non-zero / true
            OP_IFDUP = 0x73,
            // Push the current number of stack values to the stack
            OP_DEPTH = 0x74,
            // Remove the top stack item
            OP_DROP = 0x75,
            // Duplicate the top stack item
            OP_DUP = 0x76,
            // Remove stack top - 1
            OP_NIP = 0x77,
            // Copy stack top - 1 to stack
            OP_OVER = 0x78,
            // Copy stack top - N to the top where N is the current stack top
            OP_PICK = 0x79,
            // Move stack top - N to the top where N is the current stack top
            OP_ROLL = 0x7a,
            // Performs two swaps to rotate the top 3 stack values (123 -> 231)
            OP_ROT = 0x7b,
            // Swap the top two stack items with eachother
            OP_SWAP = 0x7c,
            // Copy top stack item to stack top - 1
            OP_TUCK = 0x7d,

            // splice ops
            OP_CAT = 0x7e,
            OP_SPLIT = 0x7f,   // after monolith upgrade (May 2018)
            OP_NUM2BIN = 0x80, // after monolith upgrade (May 2018)
            OP_BIN2NUM = 0x81, // after monolith upgrade (May 2018)
            OP_SIZE = 0x82,

            // bit logic
            OP_INVERT = 0x83,
            OP_AND = 0x84,
            OP_OR = 0x85,
            OP_XOR = 0x86,
            OP_EQUAL = 0x87,
            OP_EQUALVERIFY = 0x88,
            OP_RESERVED1 = 0x89,
            OP_RESERVED2 = 0x8a,

            // numeric
            OP_1ADD = 0x8b,
            OP_1SUB = 0x8c,
            OP_2MUL = 0x8d,
            OP_2DIV = 0x8e,
            OP_NEGATE = 0x8f,
            OP_ABS = 0x90,
            OP_NOT = 0x91,
            OP_0NOTEQUAL = 0x92,

            OP_ADD = 0x93,
            OP_SUB = 0x94,
            OP_MUL = 0x95,
            OP_DIV = 0x96,
            OP_MOD = 0x97,
            OP_LSHIFT = 0x98,
            OP_RSHIFT = 0x99,

            OP_BOOLAND = 0x9a,
            OP_BOOLOR = 0x9b,
            OP_NUMEQUAL = 0x9c,
            OP_NUMEQUALVERIFY = 0x9d,
            OP_NUMNOTEQUAL = 0x9e,
            OP_LESSTHAN = 0x9f,
            OP_GREATERTHAN = 0xa0,
            OP_LESSTHANOREQUAL = 0xa1,
            OP_GREATERTHANOREQUAL = 0xa2,
            OP_MIN = 0xa3,
            OP_MAX = 0xa4,

            OP_WITHIN = 0xa5,

            // crypto
            OP_RIPEMD160 = 0xa6,
            OP_SHA1 = 0xa7,
            OP_SHA256 = 0xa8,
            OP_HASH160 = 0xa9,
            OP_HASH256 = 0xaa,
            OP_CODESEPARATOR = 0xab,
            OP_CHECKSIG = 0xac,
            OP_CHECKSIGVERIFY = 0xad,
            OP_CHECKMULTISIG = 0xae,
            OP_CHECKMULTISIGVERIFY = 0xaf,

            // expansion
            OP_NOP1 = 0xb0,
            OP_CHECKLOCKTIMEVERIFY = 0xb1,
            OP_NOP2 = OP_CHECKLOCKTIMEVERIFY,
            OP_CHECKSEQUENCEVERIFY = 0xb2,
            OP_NOP3 = OP_CHECKSEQUENCEVERIFY,
            OP_NOP4 = 0xb3,
            OP_NOP5 = 0xb4,
            OP_NOP6 = 0xb5,
            OP_NOP7 = 0xb6,
            OP_NOP8 = 0xb7,
            OP_NOP9 = 0xb8,
            OP_NOP10 = 0xb9,

            // The first op_code value after all defined opcodes
            FIRST_UNDEFINED_OP_VALUE,

            // template matching params
            OP_SMALLINTEGER = 0xfa,
            OP_PUBKEYS = 0xfb,
            OP_PUBKEYHASH = 0xfd,
            OP_PUBKEY = 0xfe,

            OP_INVALIDOPCODE = 0xff,
        };

        struct noop;
        struct push;
        struct op_code;
        struct sequence;
        struct string;
        struct repeated;

    };

    struct program::noop : public program {
        void write(ostream&) const final override {}

        N length() const final override {
            return 0;
        }

        noop() {}
    };

    struct program::push : public program {
        bytes Data;

        void write(ostream& o) const final override {
            N size = Data.size();
            if (size == 0 || (size == 1 && Data[0] == 0)) {
                o << program::OP_0;
                return;
            }

            if (size == 1 && Data[0] <= 16) {
                o << Data[0] + 0x50;
                return;
            }

            if (size > 0xffff) {
                o << program::OP_PUSHDATA4;
                o << uint32(size);
            } else if (size > 0xff) {
                o << program::OP_PUSHDATA2;
                o << uint16_t(size);
            } else if (size > 75) {
                o << program::OP_PUSHDATA1;
                o << byte(size);
            } else {
                o << byte(size);
            }

            o << Data;
        }

        N length() const final override {
            N size = Data.size();
            if (size == 0 || (size == 1 && Data[0] <= 16)) return 1;
            if (size > 0xffff) return size + 5;
            if (size > 0xff) return size + 3;
            if (size > 75) return size + 2;
            return size + 1;
        }

        push(bytes data) : Data{data} {}
    };

    struct program::op_code : public program {
        op OpCode;
        void write(ostream& o) const final override {
            o << byte(OpCode);
        }

        N length() const final override {
            return 1;
        }

        op_code(op o) : OpCode{o} {}
    };

    struct program::string : public program {
        std::vector<op> String;
        void write(ostream& o) const final override {
            for (op code: String) o << byte(code);
        }

        N length() const final override {
            return String.size();
        }

        string(std::vector<op>& s) : String{s} {}
    };

    struct program::sequence : public list<pointer<program>>, public program {
        using list<pointer<program>>::list;
        void write(ostream& o) const final override {
            for (pointer<program> p : *this) p->write(o);
        }

        N length() const final override {
            return data::fold([](uint len, pointer<program> p)->uint{return len + p->length();}, 0, *this);
        }
    };

    struct program::repeated : public program {
        N Repetitions;
        pointer<program> Repeated;
        void write(ostream& o) const final override {
            for (int i = 0; i < Repetitions; i++) Repeated->write(o);
        }

        N length() const final override {
            return Repetitions * Repeated->length();
        }

        repeated(N n, pointer<program> r) : Repetitions{n}, Repeated{r} {}
    };

}

#endif

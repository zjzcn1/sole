#pragma once

#include <string>
#include <stdint.h>
#include <iostream>

namespace sole
{
    // 128-bit basic UUID type that allows comparison and sorting.
    // Use .str() for printing and .pretty() for pretty printing.
    struct uuid
    {
        union {
            struct {
                uint64_t low : 32;
                uint64_t mid : 16;
                uint64_t hiv : 16;
            };
            uint64_t ab;
        };

        union {
            struct {
                uint64_t seq : 16;
                uint64_t mac : 48;
            };
            uint64_t cd;
        };

        bool operator==( const uuid &other ) const;
        bool operator!=( const uuid &other ) const;
        bool operator <( const uuid &other ) const;

        std::string pretty() const;
        std::string str() const;
    };

    // Generators
    uuid uuid0(); // UUID v0, pro: unique; cons: MAC revealed, pid revealed, predictable.
    uuid uuid1(); // UUID v1, pro: unique; cons: MAC revealed, predictable.
    uuid uuid4(); // UUID v4, pros: anonymous, fast; con: uuids "can clash"

    // Rebuilders
    uuid rebuild( uint64_t ab, uint64_t cd );
    uuid rebuild( const std::string &uustr );
}

// ostream friendly
std::ostream &operator<<( std::ostream &os, const sole::uuid &u );

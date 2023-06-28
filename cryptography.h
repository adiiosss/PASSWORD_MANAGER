/**
 * @file cryptography.cpp
 * @brief This file contains functions useful for cryptography.
 */

#ifndef PASSWORDMANAGER_CRYPTOGRAPHY_H
#define PASSWORDMANAGER_CRYPTOGRAPHY_H

#include <string>
#include <math.h>

namespace pm {
    /**
     * @brief Applies xor cypher to a given base using a given key
     * @param base Base to encrypt
     * @param xorString Key for encryption
     */
    std::string apply_xor_cypher(const std::string& base, const std::string& xorString) {
        std::string result;
        for (size_t i = 0; i < base.length(); ++i) {
            result += base[i] ^ xorString[i % xorString.length()];
        }
        return result;
    }

    /**
     * @brief Generates a hash given a key
     * @param password Base to generate a hash
     */

    std::string generate_hash_from_password(const std::string& password) {
        std::string hash = "";
        int i = 1;
        for(auto b : password)
        {
            hash.append(std::to_string(pow(b*31, i)));
            hash = apply_xor_cypher(hash, password);
            i++;
        }
        size_t pos = hash.find('\n');
        while (pos != std::string::npos) {  //brak wystapienia danego podciagu
            hash.replace(pos, 1, "");
            pos = hash.find("\n", pos + 1);
        }
        hash = hash + "\n";
        return hash;
    }
}

#endif

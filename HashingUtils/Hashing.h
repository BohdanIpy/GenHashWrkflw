//
// Created by geth on 6/7/25.
//

#ifndef HASHING_H
#define HASHING_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <utility>
#include <optional>

#include <openssl/sha.h>
#include <openssl/evp.h>

#define BUFFER_SIZE 1024

namespace fs = std::filesystem;

namespace Hashing {
    inline auto getHashOfFile(const fs::path& pathToFile) -> std::pair<std::optional<std::string>, std::optional<std::vector<unsigned char>>> {
        std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> context(EVP_MD_CTX_new(), EVP_MD_CTX_free);

        if (EVP_DigestInit_ex(context.get(), EVP_blake2b512(), nullptr) != 1) {
            return {"EVP_DigestInit_ex failed", std::nullopt};
        }

        if (!fs::exists(pathToFile)) {
            std::cerr << "" << std::endl;
            return {"File does not exist", std::nullopt};
        }

        auto file = std::ifstream(pathToFile, std::ios::binary);
        if (!file.is_open()) {
            return {"Failed to open file", std::nullopt};
        }
        auto buffer = std::vector<unsigned char>(BUFFER_SIZE, 0);
        long bytes_read = 0;
        do {
            bytes_read = file.readsome(reinterpret_cast<char *>(buffer.data()), BUFFER_SIZE);
            EVP_DigestUpdate(context.get(), &buffer[0], bytes_read);
        } while (bytes_read != 0);

        unsigned int size = 0;
        auto result = std::vector<unsigned char>(64,0);
        if (EVP_DigestFinal_ex(context.get(), result.data(), &size) != 1) {
            return {"EVP_DigestFinal_ex failed", std::nullopt};
        }
        auto opt = std::optional<std::vector<unsigned char>>(result);
        return {std::nullopt, std::move(result)};
    }
}

#endif //HASHING_H

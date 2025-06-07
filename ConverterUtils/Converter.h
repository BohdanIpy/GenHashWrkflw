//
// Created by geth on 6/7/25.
//

#ifndef CONVERTER_H
#define CONVERTER_H

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

namespace fs = std::filesystem;

namespace ConverterUtils {
    inline auto convertArrayIntoString(const std::vector<unsigned char>& array) -> std::string {
        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        for (auto it : array) {
            ss << std::setw(2) << static_cast<int>(it);
        }
        return ss.str();
    }
}

#endif //CONVERTER_H
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <utility>
#include <optional>

#include "version.h"
#include "Hashing.h"
#include "Converter.h"

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {

    std::cout << "Hasher version: " << hashing_major_version << "." << hashing_minor_version << "." << hashing_patch_version << std::endl;
    std::cout << "Base workflow" << std::endl;
    if (argc != 2) {
        std::cerr << "Usage: ./program path_to_file\n";
        return EXIT_FAILURE;
    }

    auto filePath = fs::absolute(fs::path(argv[1]));
    auto [errStr, arrayRes] = Hashing::getHashOfFile(filePath);
    if(errStr.has_value()) {
        std::cerr << errStr.value() << std::endl;
        return EXIT_FAILURE;
    }
    auto res = ConverterUtils::convertArrayIntoString(arrayRes.value());

    std::cout << res << std::endl;
    return 0;
}

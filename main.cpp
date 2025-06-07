#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <filesystem>
#include <fstream>

#include <openssl/sha.h>
#include <openssl/evp.h>
#include <vector>

namespace fs = std::filesystem;

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./program path_to_file\n";
        return EXIT_FAILURE;
    }

    std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> context(EVP_MD_CTX_new(), EVP_MD_CTX_free);

    if (EVP_DigestInit_ex(context.get(), EVP_blake2b512(), nullptr) != 1) {
        std::cerr << "EVP_DigestInit_ex failed" << std::endl;
        return EXIT_FAILURE;
    }

    auto path_to_file = fs::absolute(fs::path(argv[1]));

    if (!fs::exists(path_to_file)) {
        std::cerr << "File does not exist" << std::endl;
        return EXIT_FAILURE;
    }

    auto file = std::ifstream(path_to_file.string(), std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return EXIT_FAILURE;
    }
    auto buffer = std::vector<unsigned char>(BUFFER_SIZE, 0);
    long bytes_read = 0;
    do {
        bytes_read = file.readsome(reinterpret_cast<char *>(buffer.data()), BUFFER_SIZE);
        EVP_DigestUpdate(context.get(), &buffer[0], bytes_read);
    } while (bytes_read != 0);

    unsigned int size = 0;
    auto result = std::vector<unsigned char>(64, size);
    if (EVP_DigestFinal_ex(context.get(), &result[0], &size) != 1) {
    }

    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (unsigned char & it : result) {
        oss << std::setw(2) << static_cast<int>(it);
    }
    std::string StrRes = oss.str();

    std::cout << "Result: " << StrRes << std::endl;

    return 0;
}

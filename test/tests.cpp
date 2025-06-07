//
// Created by geth on 6/7/25.
//
#include "gtest/gtest.h"
#include "Converter.h"
#include "Hashing.h"

#include <fstream>


TEST(Hashing, Blacke2b512) {
    //"52ae8c4cdb2f0bbe0efa267afb66c97b876cb97b9deb77c11398ee459092160c96634243d6bb4c24396dfc92d198e07413a7769388c163d860bf84b189c143b3"
    auto [msg, out] = Hashing::getHashOfFile(fs::absolute(fs::path("hash.txt")));
    ASSERT_EQ(msg.has_value(), true);
}

TEST (Hashing, properBlacke2b512) {
    std::cout << "Working directory: " << std::filesystem::current_path() << '\n';
    auto [msg, out] = Hashing::getHashOfFile(fs::absolute(fs::path("../src/main.cpp")));
    ASSERT_EQ(msg.has_value(), false);
    const auto rs = ConverterUtils::convertArrayIntoString(out.value());
    ASSERT_EQ(rs, "52ae8c4cdb2f0bbe0efa267afb66c97b876cb97b9deb77c11398ee459092160c96634243d6bb4c24396dfc92d198e07413a7769388c163d860bf84b189c143b3");
}
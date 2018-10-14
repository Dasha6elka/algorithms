#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include "../utils/utils.h"
#include "calculator/calculator.h"

const std::string SAMPLE_TEXT_1 = "2+2";
const std::string SAMPLE_TEXT_2 = "-16/8";
const std::string SAMPLE_TEXT_3 = "120-20";
const std::string SAMPLE_TEXT_4 = "13*2";
const std::string SAMPLE_TEXT_5 = "test 2-1";
const std::string SAMPLE_TEXT_6 = "3+2 test";
const std::string SAMPLE_TEXT_7 = "6 + 8";
const std::string SAMPLE_TEXT_8 = "4 / 2 test 8+2";
const std::string SAMPLE_TEXT_9 = "120-20\n"
                                  "55+555";
const std::string SAMPLE_TEXT_10 = "-test -5 + 2";
const std::string SAMPLE_TEXT_11 = "\n"
                                   "5*5";
const std::string SAMPLE_TEXT_12 = "1111111111-111111111";
const std::string SAMPLE_TEXT_13= "32 + 32 + 32";
const std::string SAMPLE_TEXT_14 = "8 4+4";
const std::string SAMPLE_TEXT_15 = "9 4 + 4";

TEST_CASE ("sample 1")
{
    std::string path = "test_text.txt";
    create_file(path, SAMPLE_TEXT_1);
    auto text = read_file(path);
    auto result = text_15(text);
            CHECK(result == "2+2\n4");
    std::remove(path.data());
}

TEST_CASE ("sample 2")
{
    std::string path = "test_text.txt";
    create_file(path, SAMPLE_TEXT_2);
    auto text = read_file(path);
    auto result = text_15(text);
            CHECK(result == "-16/8\n-2");
    std::remove(path.data());
}

TEST_CASE ("sample 3")
{
    std::string path = "test_text.txt";
    create_file(path, SAMPLE_TEXT_3);
    auto text = read_file(path);
    auto result = text_15(text);
            CHECK(result == "120-20\n100");
    std::remove(path.data());
}

TEST_CASE ("sample 4")
{
    std::string path = "test_text.txt";
    create_file(path, SAMPLE_TEXT_4);
    auto text = read_file(path);
    auto result = text_15(text);
            CHECK(result == "13*2\n26");
    std::remove(path.data());
}

TEST_CASE ("sample 5")
{
    std::string path = "test_text.txt";
    create_file(path, SAMPLE_TEXT_5);
    auto text = read_file(path);
    auto result = text_15(text);
            CHECK(result == "test 2-1\n1");
    std::remove(path.data());
}

TEST_CASE ("sample 6")
{
    std::string path = "test_text.txt";
    create_file(path, SAMPLE_TEXT_6);
    auto text = read_file(path);
    auto result = text_15(text);
            CHECK(result == "3+2 test\n5");
    std::remove(path.data());
}

TEST_CASE ("sample 7")
{
    std::string path = "test_text.txt";
    create_file(path, SAMPLE_TEXT_7);
    auto text = read_file(path);
    auto result = text_15(text);
            CHECK(result == "6 + 8\n14");
    std::remove(path.data());
}

TEST_CASE ("sample 8")
{
    std::string path = "test_text.txt";
    create_file(path, SAMPLE_TEXT_8);
    auto text = read_file(path);
    auto result = text_15(text);
            CHECK(result == "4 / 2 test 8+2\n10");
    std::remove(path.data());
}

TEST_CASE ("sample 9")
{
    std::string path = "test_text.txt";
    create_file(path, SAMPLE_TEXT_9);
    auto text = read_file(path);
    auto result = text_15(text);
            CHECK(result == "55+555\n610");
    std::remove(path.data());
}

TEST_CASE ("sample 10")
{
    std::string path = "test_text.txt";
    create_file(path, SAMPLE_TEXT_10);
    auto text = read_file(path);
    auto result = text_15(text);
            CHECK(result == "-test -5 + 2\n-3");
    std::remove(path.data());
}

TEST_CASE ("sample 11")
{
    std::string path = "test_text.txt";
    create_file(path, SAMPLE_TEXT_11);
    auto text = read_file(path);
    auto result = text_15(text);
            CHECK(result == "5*5\n25");
    std::remove(path.data());
}

TEST_CASE ("sample 12")
{
    std::string path = "test_text.txt";
    create_file(path, SAMPLE_TEXT_12);
    auto text = read_file(path);
    auto result = text_15(text);
            CHECK(result == "1111111111-111111111\n1000000000");
    std::remove(path.data());
}

TEST_CASE ("sample 13")
{
    std::string path = "test_text.txt";
    create_file(path, SAMPLE_TEXT_13);
    auto text = read_file(path);
    auto result = text_15(text);
            CHECK(result == "32 + 32 + 32\n64");
    std::remove(path.data());
}

TEST_CASE ("sample 14")
{
    std::string path = "test_text.txt";
    create_file(path, SAMPLE_TEXT_14);
    auto text = read_file(path);
    auto result = text_15(text);
            CHECK(result == "8 4+4\n8");
    std::remove(path.data());
}

TEST_CASE ("sample 15")
{
    std::string path = "test_text.txt";
    create_file(path, SAMPLE_TEXT_15);
    auto text = read_file(path);
    auto result = text_15(text);
            CHECK(result == "9 4 + 4\n8");
    std::remove(path.data());
}
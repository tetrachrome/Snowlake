/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2018 William Li

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************/
#include <gtest/gtest.h>

#include "ArgumentParser.h"

#include <vector>

// -----------------------------------------------------------------------------

class ArgumentParserTests : public ::testing::Test
{
};

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests, TestDefaultInitialization)
{
  ArgumentParser argparser;
  ASSERT_TRUE(argparser.positional_args().empty());
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests, TestParseStringOption)
{
  ArgumentParser argparser;
  std::string dst;
  const char* default_val = "DefaltName";
  argparser.add_string_parameter("name", 'n', "Name of character", true, &dst,
                                 default_val);

  const std::vector<char*> args{"MyProgram", "--name", "HelloWorld"};

  bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_TRUE(res);

  ASSERT_STREQ("HelloWorld", dst.c_str());
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests, TestParseStringAndUInt32Options)
{
  ArgumentParser argparser;
  std::string name_dst;
  uint32_t age_dst;
  argparser.add_string_parameter("name", 'n', "Name of character", true,
                                 &name_dst, "DefaltName");
  argparser.add_uint32_parameter("age", 'a', "Age of character", true, &age_dst,
                                 20);

  const std::vector<char*> args{"MyProgram", "--name", "NoName", "--age", "18"};

  bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_TRUE(res);

  ASSERT_STREQ("NoName", name_dst.c_str());
  ASSERT_EQ(18, age_dst);
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests, TestParseWithMissingRequiredOption)
{
  ArgumentParser argparser;
  std::string dst;
  const char* default_val = "DefaltName";
  argparser.add_string_parameter("name", 'n', "Name of character", true, &dst,
                                 default_val);

  const std::vector<char*> args{
      "MyProgram",
  };

  bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_FALSE(res);
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests, TestParseWithMissingNonRequiredOption)
{
  ArgumentParser argparser;
  std::string dst;
  const char* default_val = "DefaltName";
  argparser.add_string_parameter("name", 'n', "Name of character", false, &dst,
                                 default_val);

  const std::vector<char*> args{
      "MyProgram",
  };

  const bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_TRUE(res);

  ASSERT_STREQ(default_val, dst.c_str());
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests, TestParseWithAllOptionTypes)
{
  ArgumentParser argparser;
  std::string str_dst;
  uint32_t uint32_dst = 0;
  uint64_t uint64_dst = 0;
  bool bool_dst = false;
  float float_dst = 0.0f;
  double double_dst = 0.0;
  argparser.add_string_parameter("str", 's', "String value", true, &str_dst);
  argparser.add_uint32_parameter("uint32", 'u', "UInt32 value", true,
                                 &uint32_dst);
  argparser.add_uint64_parameter("uint64", 'n', "UInt64 value", true,
                                 &uint64_dst);
  argparser.add_boolean_parameter("bool", 'b', "Boolean value", true,
                                  &bool_dst);
  argparser.add_float_parameter("float", 'f', "Float value", true, &float_dst);
  argparser.add_double_parameter("double", 'd', "Double value", true,
                                 &double_dst);

  const std::vector<char*> args{"MyProgram", "--str",    "MyStringValue",
                                "--uint32",  "32",       "--uint64",
                                "64",        "--bool",   "--float",
                                "3.14",      "--double", "2.71828"};

  bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_TRUE(res);

  ASSERT_STREQ("MyStringValue", str_dst.c_str());
  ASSERT_EQ(32, uint32_dst);
  ASSERT_EQ(64, uint64_dst);
  ASSERT_EQ(true, bool_dst);
  ASSERT_DOUBLE_EQ(3.14f, float_dst);
  ASSERT_DOUBLE_EQ(2.71828, double_dst);
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests, TestParseWithAllOptionTypesAndDefaultValues)
{
  ArgumentParser argparser;
  std::string str_dst;
  uint32_t uint32_dst = 0;
  uint64_t uint64_dst = 0;
  bool bool_dst = false;
  float float_dst = 0.0f;
  double double_dst = 0.0;

  const char* str_dst_default = "DefaultStringValue";
  const uint32_t uint32_dst_default = 32;
  const uint64_t uint64_dst_default = 64;
  const bool bool_dst_default = false;
  const float float_dst_default = 3.14f;
  const double double_dst_default = 2.71828;

  argparser.add_string_parameter("str", 's', "String value", false, &str_dst,
                                 str_dst_default);
  argparser.add_uint32_parameter("uint32", 'u', "UInt32 value", false,
                                 &uint32_dst, uint32_dst_default);
  argparser.add_uint64_parameter("uint64", 'n', "UInt64 value", false,
                                 &uint64_dst, uint64_dst_default);
  argparser.add_boolean_parameter("bool", 'b', "Boolean value", false,
                                  &bool_dst, bool_dst_default);
  argparser.add_float_parameter("float", 'f', "Float value", false, &float_dst,
                                float_dst_default);
  argparser.add_double_parameter("double", 'd', "Double value", false,
                                 &double_dst, double_dst_default);

  const std::vector<char*> args{
      "MyProgram",
  };

  bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_TRUE(res);

  ASSERT_STREQ(str_dst_default, str_dst.c_str());
  ASSERT_EQ(uint32_dst_default, uint32_dst);
  ASSERT_EQ(uint64_dst_default, uint64_dst);
  ASSERT_EQ(bool_dst_default, bool_dst);
  ASSERT_DOUBLE_EQ(float_dst_default, float_dst);
  ASSERT_DOUBLE_EQ(double_dst_default, double_dst);
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests, TestParseWithAllOptionlAndPositionalArguments)
{
  ArgumentParser argparser;
  std::string str_dst;
  uint32_t uint32_dst = 0;
  uint64_t uint64_dst = 0;
  bool bool_dst = false;
  float float_dst = 0.0f;
  double double_dst = 0.0;
  const char* input_path = "/tmp/hellworld";

  argparser.add_string_parameter("str", 's', "String value", true, &str_dst);
  argparser.add_uint32_parameter("uint32", 'u', "UInt32 value", true,
                                 &uint32_dst);
  argparser.add_uint64_parameter("uint64", 'n', "UInt64 value", true,
                                 &uint64_dst);
  argparser.add_boolean_parameter("bool", 'b', "Boolean value", true,
                                  &bool_dst);
  argparser.add_float_parameter("float", 'f', "Float value", true, &float_dst);
  argparser.add_double_parameter("double", 'd', "Double value", true,
                                 &double_dst);

  const std::vector<char*> args{"MyProgram",
                                "--str",
                                "MyStringValue",
                                "--uint32",
                                "32",
                                "--uint64",
                                "64",
                                "--bool",
                                "--float",
                                "3.14",
                                "--double",
                                "2.71828",
                                const_cast<char*>(input_path)};

  bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_TRUE(res);

  ASSERT_STREQ("MyStringValue", str_dst.c_str());
  ASSERT_EQ(32, uint32_dst);
  ASSERT_EQ(64, uint64_dst);
  ASSERT_EQ(true, bool_dst);
  ASSERT_DOUBLE_EQ(3.14f, float_dst);
  ASSERT_DOUBLE_EQ(2.71828, double_dst);

  // Check positional argument.
  const auto& positional_args = argparser.positional_args();
  ASSERT_FALSE(positional_args.empty());
  ASSERT_EQ(1, positional_args.size());
  ASSERT_STREQ(input_path, positional_args.front().c_str());
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests,
       TestParseWithAllOptionlInShorthandFormAndPositionalArguments)
{
  ArgumentParser argparser;
  std::string str_dst;
  uint32_t uint32_dst = 0;
  uint64_t uint64_dst = 0;
  bool bool_dst = false;
  float float_dst = 0.0f;
  double double_dst = 0.0;
  const char* input_path = "/tmp/hellworld";

  argparser.add_string_parameter("str", 's', "String value", true, &str_dst);
  argparser.add_uint32_parameter("uint32", 'u', "UInt32 value", true,
                                 &uint32_dst);
  argparser.add_uint64_parameter("uint64", 'n', "UInt64 value", true,
                                 &uint64_dst);
  argparser.add_boolean_parameter("bool", 'b', "Boolean value", true,
                                  &bool_dst);
  argparser.add_float_parameter("float", 'f', "Float value", true, &float_dst);
  argparser.add_double_parameter("double", 'd', "Double value", true,
                                 &double_dst);

  const std::vector<char*> args{"MyProgram",
                                "-s",
                                "MyStringValue",
                                "-u",
                                "32",
                                "-n",
                                "64",
                                "-b",
                                "-f",
                                "3.14",
                                "-d",
                                "2.71828",
                                const_cast<char*>(input_path)};

  bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_TRUE(res);

  ASSERT_STREQ("MyStringValue", str_dst.c_str());
  ASSERT_EQ(32, uint32_dst);
  ASSERT_EQ(64, uint64_dst);
  ASSERT_EQ(true, bool_dst);
  ASSERT_DOUBLE_EQ(3.14f, float_dst);
  ASSERT_DOUBLE_EQ(2.71828, double_dst);

  // Check positional argument.
  const auto& positional_args = argparser.positional_args();
  ASSERT_FALSE(positional_args.empty());
  ASSERT_EQ(1, positional_args.size());
  ASSERT_STREQ(input_path, positional_args.front().c_str());
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests,
       TestParseWithAllOptionlInBothFormsFormAndPositionalArguments)
{
  ArgumentParser argparser;
  std::string str_dst;
  uint32_t uint32_dst = 0;
  uint64_t uint64_dst = 0;
  bool bool_dst = false;
  float float_dst = 0.0f;
  double double_dst = 0.0;
  const char* input_path = "/tmp/hellworld";

  argparser.add_string_parameter("str", 's', "String value", true, &str_dst);
  argparser.add_uint32_parameter("uint32", 'u', "UInt32 value", true,
                                 &uint32_dst);
  argparser.add_uint64_parameter("uint64", 'n', "UInt64 value", true,
                                 &uint64_dst);
  argparser.add_boolean_parameter("bool", 'b', "Boolean value", true,
                                  &bool_dst);
  argparser.add_float_parameter("float", 'f', "Float value", true, &float_dst);
  argparser.add_double_parameter("double", 'd', "Double value", true,
                                 &double_dst);

  const std::vector<char*> args{"MyProgram",
                                "--str",
                                "MyStringValue",
                                "-u",
                                "32",
                                "--uint64",
                                "64",
                                "-b",
                                "--float",
                                "3.14",
                                "-d",
                                "2.71828",
                                const_cast<char*>(input_path)};

  bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_TRUE(res);

  ASSERT_STREQ("MyStringValue", str_dst.c_str());
  ASSERT_EQ(32, uint32_dst);
  ASSERT_EQ(64, uint64_dst);
  ASSERT_EQ(true, bool_dst);
  ASSERT_DOUBLE_EQ(3.14f, float_dst);
  ASSERT_DOUBLE_EQ(2.71828, double_dst);

  // Check positional argument.
  const auto& positional_args = argparser.positional_args();
  ASSERT_FALSE(positional_args.empty());
  ASSERT_EQ(1, positional_args.size());
  ASSERT_STREQ(input_path, positional_args.front().c_str());
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests,
       TestParseWithSelectOptionsInBothFormsFormAndPositionalArguments)
{
  ArgumentParser argparser;
  std::string str_dst;
  uint32_t uint32_dst = 0;
  uint64_t uint64_dst = 0;
  bool bool_dst = false;
  float float_dst = 0.0f;
  double double_dst = 0.0;
  const const char* str_default_value = "Hello";
  const uint64_t uint64_default_value = 64;
  const bool boolean_default_value = true;
  const double double_default_value = 2.71828;
  const char* input_path = "/tmp/hellworld";

  argparser.add_string_parameter("str", 's', "String value", false, &str_dst,
                                /* default_val */ str_default_value);
  argparser.add_uint32_parameter("uint32", 'u', "UInt32 value", true,
                                 &uint32_dst);
  argparser.add_uint64_parameter("uint64", 'n', "UInt64 value", false,
                                 &uint64_dst, /* default_val */ uint64_default_value);
  argparser.add_boolean_parameter("bool", 'b', "Boolean value", false,
                                  &bool_dst, /* default_val */ boolean_default_value);
  argparser.add_float_parameter("float", 'f', "Float value", true, &float_dst);
  argparser.add_double_parameter("double", 'd', "Double value", false,
                                 &double_dst, /* default_val */ double_default_value);

  const std::vector<char*> args{"MyProgram",
                                "-u",
                                "32",
                                "--float",
                                "3.14",
                                const_cast<char*>(input_path)};

  bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_TRUE(res);

  ASSERT_STREQ(str_default_value, str_dst.c_str());
  ASSERT_EQ(32, uint32_dst);
  ASSERT_EQ(uint64_default_value, uint64_dst);
  ASSERT_EQ(boolean_default_value, bool_dst);
  ASSERT_DOUBLE_EQ(3.14f, float_dst);
  ASSERT_DOUBLE_EQ(double_default_value, double_dst);

  // Check positional argument.
  const auto& positional_args = argparser.positional_args();
  ASSERT_FALSE(positional_args.empty());
  ASSERT_EQ(1, positional_args.size());
  ASSERT_STREQ(input_path, positional_args.front().c_str());
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests, TestWithDuplicateShorthandlCmdlOptions)
{
  ArgumentParser argparser("My Program", "1.0.0", "This is a test program.");

  std::string str_dst;
  uint32_t uint32_dst = 0;
  uint64_t uint64_dst = 0;
  bool bool_dst = false;
  float float_dst = 0.0f;
  double double_dst = 0.0;

  argparser.add_string_parameter("str", 's', "String value", true, &str_dst);
  argparser.add_uint32_parameter("uint32", 'u', "UInt32 value", true,
                                 &uint32_dst);
  argparser.add_uint64_parameter("uint64", 'n', "UInt64 value", true,
                                 &uint64_dst);
  argparser.add_boolean_parameter("bool", 'b', "Boolean value", true,
                                  &bool_dst);
  argparser.add_float_parameter("float", 'f', "Float value", true, &float_dst);
  argparser.add_double_parameter("double", 's', "Double value", true,
                                 &double_dst);

  const std::vector<char*> args{
      "MyProgram", "-s", "MyStringValue", "-u", "32",     "-n", "64",
      "-b",        "-f", "3.14",          "-d", "2.71828"};

  bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_FALSE(res);
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests, TestParseWithUnrecognizedShorthandlCmdlOptions)
{
  ArgumentParser argparser("My Program", "1.0.0", "This is a test program.");

  std::string str_dst;
  uint32_t uint32_dst = 0;
  uint64_t uint64_dst = 0;
  bool bool_dst = false;
  float float_dst = 0.0f;
  double double_dst = 0.0;

  argparser.add_string_parameter("str", 's', "String value", true, &str_dst);
  argparser.add_uint32_parameter("uint32", 'u', "UInt32 value", true,
                                 &uint32_dst);
  argparser.add_uint64_parameter("uint64", 'n', "UInt64 value", true,
                                 &uint64_dst);
  argparser.add_boolean_parameter("bool", 'b', "Boolean value", true,
                                  &bool_dst);
  argparser.add_float_parameter("float", 'f', "Float value", true, &float_dst);
  argparser.add_double_parameter("double", 's', "Double value", true,
                                 &double_dst);

  const std::vector<char*> args{
      "MyProgram", "-s", "MyStringValue", "-u", "32",     "-n", "64",
      "-b",        "-f", "3.14",          "-x", "2.71828"};

  bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_FALSE(res);
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests, TestParseWithIllFormedShorthandlCmdlOptions)
{
  ArgumentParser argparser("My Program", "1.0.0", "This is a test program.");

  std::string str_dst;
  uint32_t uint32_dst = 0;
  uint64_t uint64_dst = 0;
  bool bool_dst = false;
  float float_dst = 0.0f;
  double double_dst = 0.0;

  argparser.add_string_parameter("str", 's', "String value", true, &str_dst);
  argparser.add_uint32_parameter("uint32", 'u', "UInt32 value", true,
                                 &uint32_dst);
  argparser.add_uint64_parameter("uint64", 'n', "UInt64 value", true,
                                 &uint64_dst);
  argparser.add_boolean_parameter("bool", 'b', "Boolean value", true,
                                  &bool_dst);
  argparser.add_float_parameter("float", 'f', "Float value", true, &float_dst);
  argparser.add_double_parameter("double", 's', "Double value", true,
                                 &double_dst);

  const std::vector<char*> args{
      "MyProgram", "-s", "MyStringValue", "-u",      "32",     "-n", "64",
      "-b",        "-f", "3.14",          "-double", "2.71828"};

  bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_FALSE(res);
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests, TestParseWithMissingShorthandlCmdlOptions)
{
  ArgumentParser argparser("My Program", "1.0.0", "This is a test program.");

  std::string str_dst;
  uint32_t uint32_dst = 0;
  uint64_t uint64_dst = 0;
  bool bool_dst = false;
  float float_dst = 0.0f;
  double double_dst = 0.0;

  argparser.add_string_parameter("str", 's', "String value", true, &str_dst);
  argparser.add_uint32_parameter("uint32", 'u', "UInt32 value", true,
                                 &uint32_dst);
  argparser.add_uint64_parameter("uint64", 'n', "UInt64 value", true,
                                 &uint64_dst);
  argparser.add_boolean_parameter("bool", 'b', "Boolean value", true,
                                  &bool_dst);
  argparser.add_float_parameter("float", 'f', "Float value", true, &float_dst);
  argparser.add_double_parameter("double", 's', "Double value", true,
                                 &double_dst);

  const std::vector<char*> args{
      "MyProgram", "-s", "MyStringValue", "-u",     "32", "-n", "64",
      "-b",        "-f", "3.14",          "2.71828"};

  bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_FALSE(res);
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests, TestWithSufficientNumberOfPositionalArguments)
{
  ArgumentParser argparser;
  argparser.set_minimum_positional_args_required(3);

  const std::vector<char*> args{"MyProgram", "1", "2", "3"};

  const bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_TRUE(res);
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests, TestWithInsufficientNumberOfPositionalArguments)
{
  ArgumentParser argparser;
  argparser.set_minimum_positional_args_required(3);

  const std::vector<char*> args{"MyProgram", "1", "2"};

  const bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_FALSE(res);
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests, TestPrintHelpMessage)
{
  ArgumentParser argparser("My Program", "1.0.0", "This is a test program.");
  std::string str_dst;
  uint32_t uint32_dst = 0;
  uint64_t uint64_dst = 0;
  bool bool_dst = false;
  float float_dst = 0.0f;
  double double_dst = 0.0;

  argparser.add_string_parameter("str", 's', "String value", true, &str_dst);
  argparser.add_uint32_parameter("uint32", 'u', "UInt32 value", true,
                                 &uint32_dst);
  argparser.add_uint64_parameter("uint64", 'n', "UInt64 value", true,
                                 &uint64_dst);
  argparser.add_boolean_parameter("bool", 'b', "Boolean value", true,
                                  &bool_dst);
  argparser.add_float_parameter("float", 'f', "Float value", true, &float_dst);
  argparser.add_double_parameter("double", 'd', "Double value", true,
                                 &double_dst);

  // Get help message.
  argparser.print_help();
}

// -----------------------------------------------------------------------------

TEST_F(ArgumentParserTests, TestsWithInvalidNumberOfPositionalArguments)
{
  ArgumentParser argparser;
  argparser.set_minimum_positional_args_required(1);

  const std::vector<char*> args{"MyProgram"};

  const bool res = argparser.parse_args(args.size(), (char**)args.data());
  ASSERT_FALSE(res);
}

// -----------------------------------------------------------------------------

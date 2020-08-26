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

#pragma once

#include "variant.h"
#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

class ArgumentParser
{
public:
  ArgumentParser();

  explicit ArgumentParser(const char* name);

  ArgumentParser(const char* name, const char* version);

  ArgumentParser(const char* name, const char* version,
                 const char* description);

  ArgumentParser(const char* name, const char* version, const char* description,
                 const char* long_description);

  void addStringParameter(const char* name, const char short_hand,
                          const char* description, bool required,
                          std::string* res, const char* default_val = "");

  void addUint32Parameter(const char* name, const char short_hand,
                          const char* description, bool required,
                          uint32_t* res, uint32_t default_val = 0);

  void addUint64Parameter(const char* name, const char short_hand,
                            const char* description, bool required,
                            uint64_t* res, uint64_t default_val = 0);

  void addFloatParameter(const char* name, const char short_hand,
                           const char* description, bool required, float* res,
                           float default_val = 0.0f);

  void addDoubleParameter(const char* name, const char short_hand,
                            const char* description, bool required, double* res,
                            double default_val = 0.0);

  void addBooleanParameter(const char* name, const char short_hand,
                             const char* description, bool required, bool* res,
                             bool default_val = false);

  void setMinimumPositionalArgsRequired(size_t n);

  bool optionProvided(const char* name) const;

  bool parseArgs(int argc, char** argv);

  using PositionalArgumentList = std::vector<std::string>;

  const PositionalArgumentList& positionalArgs() const;

  void setUsageString(const char*);

  std::string help() const;

  void printHelp() const;

public:
  using value_type = sl::variant::variant<std::string, uint32_t, uint64_t, bool,
                                          float, double>;

private:
  bool __definedBooleanOption(const std::string&) const;

  void __updateOptionValue(const std::string&, const std::string&);

  bool __parseArgs(int argc, char** argv);

  bool __registerCmdlOption(const std::string& key, int& argc, char**& argv);

  bool __checkParameters() const;

  void __assignValues();

  void __addPositionalParameter(std::string&& arg);

  template <typename Stream>
  void __printHelp(Stream&) const;

  template <typename T>
  void addParameter(const char* name, const char short_hand,
                     const char* description, bool required, T* res,
                     T default_val);

  struct CmdlOptionValue
  {
    using value_type = ArgumentParser::value_type;
    value_type value;
  };

  struct CmdlOption
  {
    char short_hand;
    std::string description;
    bool required;
    CmdlOptionValue default_value;
    CmdlOptionValue value;
    void* dst;

    void assignValueToDst();

    void updateValue(const std::string&);
  };

  using CmdlOptionMap = std::unordered_map<std::string, CmdlOption>;
  using ShortHandMap = std::unordered_map<char, std::string>;

  std::string m_name;
  std::string m_version;
  std::string m_desc;
  std::string m_long_desc;
  std::string m_usage;
  CmdlOptionMap m_opts;
  ShortHandMap m_shorthand_map;
  PositionalArgumentList m_positionalArgs;
  size_t m_min_positionalArgs_required;
};

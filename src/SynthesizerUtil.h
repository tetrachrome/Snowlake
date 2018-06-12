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

#define FORWARD_SLASH '/'
#define HEADER_FILE_EXT ".h"
#define CPP_FILE_EXT ".cpp"
#define CPP_PRAGMA_ONCE "#pragma once"
#define CPP_CLASS_KEYWORD "class"
#define CPP_OPEN_BRACE '{'
#define CPP_CLOSE_BRACE '}'
#define CPP_OPEN_PAREN '('
#define CPP_CLOSE_PAREN ')'
#define CPP_OPEN_BRACKET '['
#define CPP_CLOSE_BRACKET ']'
#define CPP_SEMICOLON ';'
#define CPP_COLON ':'
#define CPP_PUBLIC_KEYWORD "public"
#define CPP_PROTECTED_KEYWORD "protected"
#define CPP_PRIVATE_KEYWORD "private"
#define CPP_INDENTATION "    "
#define CPP_SPACE ' '
#define CPP_CONST_KEYWORD "const"
#define CPP_AMPERSAND '&'
#define CPP_COMA ','
#define CPP_ASSIGN '='
#define CPP_DOT '.'
#define CPP_STAR '*'
#define CPP_IF "if"
#define CPP_RETURN_KEYWORD "return"
#define CPP_FOR_KEYWORD "for"
#define CPP_SIZE_T "size_t"
#define CPP_LESS_THAN "<"
#define CPP_DOT_SIZE ".size()"
#define CPP_INCREMENT_OPERATOR "++"
#define CPP_INCLUDE_DIRECTIVE "#include"
#define CPP_INCLUDE_DIRECTIVE_PREFIX "#include <"
#define CPP_DOUBLE_QUOTE '"'
#define CPP_STD_ERROR_CODE "std::error_code"
#define CPP_NEGATION '!'

#define SYNTHESIZED_PREFIX_COMMENT                                             \
  "/**\n"                                                                      \
  " * Auto-generated by Snowlake compiler.\n"                                  \
  " */"

// TODO: Refine implementation of `InferenceErrorCategory`.
// [SNOWLAKE-17] Optimize and refine code synthesis pipeline

#define SYNTHESIZED_CUSTOM_ERROR_CATEGORY_DEFINITION                           \
  "class InferenceErrorCategory : public std::error_category\n"                \
  "{\n"                                                                        \
  "    virtual const char* name() const except override {\n"                   \
  "        return \"Inference error\";\n"                                      \
  "    }\n"                                                                    \
  "\n"                                                                         \
  "    virtual std::string message(int condition) const override {\n"          \
  "        return \"Inference failed\";\n"                                     \
  "    }\n"                                                                    \
  "};\n"                                                                       \
  "\n"                                                                         \
  "const InferenceErrorCategory inference_error_category {};\n"                \
  ""

#define SYNTHESIZED_ERROR_CATEGORY_CLASS_NAME "InferenceErrorCategory"

#define SYNTHESIZED_GLOBAL_ERROR_CATEGORY_INSTANCE_NAME                        \
  "inference_error_category"

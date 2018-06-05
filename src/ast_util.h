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

#include "ast_fwd.h"
#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string, const ASTDeductionTarget*> TargetTable;

std::string canonicalize_ASTIdentifiable(const ASTIdentifiable&);

bool are_targets_compatible(const ASTDeductionTarget&,
                            const ASTDeductionTarget&);

bool are_targets_compatible(const ASTDeductionTargetSingular&,
                            const ASTDeductionTargetSingular&);

bool are_targets_compatible(const ASTDeductionTargetArray&,
                            const ASTDeductionTargetArray&);

const std::string& get_root_of_ASTIdentifiable(const ASTIdentifiable&);

void add_target_to_table(const ASTDeductionTarget&, TargetTable*);

bool has_compatible_target_in_table(const ASTDeductionTarget&,
                                    const TargetTable&);

bool has_incompatible_target_in_table(const ASTDeductionTarget&,
                                      const TargetTable&);
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
#include "variant.h"
#include "optional.h"

#include <cstdlib>
#include <vector>
#include <string>

typedef std::string StringType;
typedef uint64_t IntegerType;

enum class EqualityOperator : uint8_t
{
  OPERATOR_EQ,
  OPERATOR_NEQ,
  OPERATOR_LT,
  OPERATOR_LTE
};

class ASTNode
{
};

typedef std::vector<ASTIdentifier> ASTIdentifierList;
typedef std::vector<ASTDeductionTarget> ASTDeductionTargetList;
typedef std::vector<ASTPremiseDefn> ASTPremiseDefnList;
typedef std::vector<ASTInferenceArgument> ASTInferenceArgumentList;
typedef std::vector<ASTGlobalDecl> ASTGlobalDeclList;
typedef std::vector<ASTEnvironmentDefn> ASTEnvironmentDefnList;
typedef std::vector<ASTInferenceDefn> ASTInferenceDefnList;



class ASTIdentifier 
{
public:
  ASTIdentifier(StringType&& value) :
    m_value(value) {}

private:
  StringType m_value;
};

class ASTIdentifiable
{
public:
  ASTIdentifiable(ASTIdentifierList&& identifiers) :
  m_identifiers(identifiers) {}

private:
  ASTIdentifierList m_identifiers;
};

class ASTDeductionTargetSingular
{
public:
  explicit ASTDeductionTargetSingular(StringType&& name) :
    m_name(name) {}

private:
  StringType m_name;
};

class ASTDeductionTargetArray
{
public:
  explicit ASTDeductionTargetArray(StringType&& name)
    :
    m_name(name), m_array_size() {}

  explicit ASTDeductionTargetArray(StringType&& name, IntegerType array_size)
    :
    m_name(name), m_array_size(array_size) {}

private:
  StringType m_name;
  sl::optional<IntegerType> m_array_size;
};

class ASTDeductionTargetComputed
{
public:
  ASTDeductionTargetComputed(StringType&& name, ASTDeductionTargetList&& arguments)
  :
  m_name(name), m_arguments(arguments) {}

private:
  StringType m_name;
  ASTDeductionTargetList m_arguments;
};

class ASTDeductionTarget : public ASTNode
{
public:
  ASTDeductionTarget(ASTDeductionTargetSingular&& value):
    m_value(value) {}

  ASTDeductionTarget(ASTDeductionTargetArray&& value):
  m_value(value) {}

  ASTDeductionTarget(ASTDeductionTargetComputed&& value):
  m_value(value) {}

private:
  sl::variant::variant<ASTDeductionTargetSingular, ASTDeductionTargetArray,
    ASTDeductionTargetComputed> m_value;
};

class ASTPropositionDefn
{
public:
  ASTPropositionDefn(ASTDeductionTarget&& target) :
    m_target(target) {}

private:
  ASTDeductionTarget m_target;
};

class ASTRangeClause : public ASTNode
{
public:
  ASTRangeClause(IntegerType lhs_idx,
    IntegerType rhs_idx,
    ASTDeductionTarget&& deduction_target)
    :
    m_lhs_idx(lhs_idx),
    m_rhs_idx(rhs_idx),
    m_deduction_target(deduction_target) {}

private:
  IntegerType m_lhs_idx;
  IntegerType m_rhs_idx;
  ASTDeductionTarget m_deduction_target;
};

class ASTInferenceEqualityDefn
{
public:
  ASTInferenceEqualityDefn(ASTDeductionTarget&& lhs,
    ASTDeductionTarget&& rhs)
    :
    m_lhs(lhs), m_rhs(rhs)
    {
    }

  ASTInferenceEqualityDefn(ASTDeductionTarget&& lhs,
    ASTDeductionTarget&& rhs,
    ASTRangeClause&& range_clause)
    :
    m_lhs(lhs), m_rhs(rhs), m_range_clause(range_clause)
    {
    }

private:
  ASTDeductionTarget m_lhs;
  ASTDeductionTarget m_rhs;
  sl::optional<ASTRangeClause> m_range_clause;
};

class ASTWhileClause : public ASTNode
{
public:
  explicit ASTWhileClause(ASTPremiseDefnList&& premise_defns) :
    m_premise_defns(premise_defns) {}

  const ASTPremiseDefnList& premise_defns() const {
    return m_premise_defns;
  }

private:
  ASTPremiseDefnList m_premise_defns;
};

class ASTInferencePremiseDefn
{
public:
  ASTInferencePremiseDefn(ASTIdentifiable&& source,
    ASTDeductionTarget&& deduction_target):
    m_source(source), m_deduction_target(deduction_target), m_while_clause()
  {
  }

  ASTInferencePremiseDefn(ASTIdentifiable&& source,
    ASTDeductionTarget&& deduction_target,
    ASTWhileClause&& while_clause):
    m_source(source), m_deduction_target(deduction_target), m_while_clause(while_clause)
  {
  }

  const ASTIdentifiable& source() const {
    return m_source;
  }

  const ASTDeductionTarget& deduction_target() const {
    return m_deduction_target;
  }

  bool has_while_clause() const {
    return m_while_clause.has_value();
  }

  const ASTWhileClause& while_clause() const {
    return m_while_clause.value();
  }

private:
  ASTIdentifiable m_source;
  ASTDeductionTarget m_deduction_target;
  sl::optional<ASTWhileClause> m_while_clause;
};

class ASTPremiseDefn : public ASTNode
{
public:
  ASTPremiseDefn(ASTInferencePremiseDefn&& defn) :
    m_value(defn) {}

  ASTPremiseDefn(ASTInferenceEqualityDefn&& defn) :
    m_value(defn) {}

  template<class U>
  bool is_type() const {
    return m_value.template is<U>();
  }

private:
  sl::variant::variant<ASTInferencePremiseDefn, ASTInferenceEqualityDefn> m_value;
};

class ASTInferenceArgument : public ASTNode
{
public:
  ASTInferenceArgument(StringType&& name, StringType&& type_name) :
    m_name(name), m_type_name(type_name) {}

  const StringType& name() const {
    return m_name;
  }

  const StringType& type_name() const {
    return m_type_name;
  }

private:
  StringType m_name;
  StringType m_type_name;
};

class ASTGlobalDecl : public ASTNode
{
public:
  explicit ASTGlobalDecl(StringType&& name) :
    m_name(name) {}

  const StringType& name() const {
    return m_name;
  }

private:
  StringType m_name;
};

class ASTInferenceDefn : public ASTNode
{
public:
  ASTInferenceDefn(ASTGlobalDeclList&& global_decls,
    ASTInferenceArgumentList&& arguments,
    ASTPremiseDefnList&& premise_defns, ASTPropositionDefn&& proposition_defn) :
    m_global_decls(global_decls),
    m_arguments(arguments),
    m_premise_defns(premise_defns),
    m_proposition_defn(proposition_defn)
  {
  }

  const ASTGlobalDeclList& global_decls() const {
    return m_global_decls;
  }

  const ASTInferenceArgumentList& arguments() const {
    return m_arguments;
  }

  const ASTPremiseDefnList& premise_defns() const {
    return m_premise_defns;
  }

  const ASTPropositionDefn& proposition_defn() const {
    return m_proposition_defn;
  }

private:
  ASTGlobalDeclList m_global_decls;
  ASTInferenceArgumentList m_arguments;
  ASTPremiseDefnList m_premise_defns;
  ASTPropositionDefn m_proposition_defn;
};

class ASTEnvironmentDefn : public ASTNode
{
public:
  ASTEnvironmentDefn(StringType&& field, StringType& value) :
    m_field(field), m_value(value) {}

  const StringType& field() const {
    return m_field;
  }

  const StringType& value() const {
    return m_value;
  }

private:
  StringType m_field;
  StringType m_value;
};

class ASTInferenceGroup : public ASTNode
{
public:
  ASTInferenceGroup(ASTEnvironmentDefnList&& environment_defns,
    ASTInferenceDefnList&& inference_defns)
    :
    m_environment_defns(environment_defns),
    m_inference_defns(inference_defns)
  {
  }

  const ASTEnvironmentDefnList& environment_defns() const {
    return m_environment_defns;
  }

  const ASTInferenceDefnList& inference_defns() const {
    return m_inference_defns;
  }

private:
  ASTEnvironmentDefnList m_environment_defns;
  ASTInferenceDefnList m_inference_defns;
};

typedef std::vector<ASTInferenceGroup> ASTInferenceGroupList;

class ASTModule : public ASTNode
{
public:
  explicit ASTModule(ASTInferenceGroupList&& inference_groups)
    : m_inference_groups(inference_groups) {}

  const ASTInferenceGroupList& inference_groups() const {
    return m_inference_groups;
  }

  ASTInferenceGroupList& inference_groups() {
    return m_inference_groups;
  }

private:
  ASTInferenceGroupList m_inference_groups;
};

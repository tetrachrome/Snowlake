.. Copyright William Li. All rights reserved.

********
Tutorial
********

Snowlake joins Flex and Bison (formerly known as Lex and Yacc) as a new
member in the family of compiler-compilers in empowering programming language
designers, authors, and engineers to be more efficient and productive.
As Flex and Bison focuses on enabling the authoring of language lexers and
parsers, Snowlake focuses on the next major step in language compiler
construction: static type inference as part of semantic analysis.

Snowlake is a declarative language for expressing the static type inference
rules expressed in programming language semantics. The Snowlake declarative
language is designed to be language agnostic, and is based on syntax and
semantics derived from existing languages in order to reduce the learning
curve in mastering it.

We demonstrate the features, syntax and semantics of the Snowlake language
by going through a brief example of defining the semantics and static type
inference rules of a trivial reference language. Here we intentionally omit
the introduction of the syntax of this reference language, and solely focus
on its semantics and static type inference rules, because the language syntax
is irrelevant in this context. The various features of the Snowlake language
are illustrated in detail as we progress in defining and expressing the
inference rules of our example language.


Inference Groups
################

The top-level abstraction in the Snowlake language is **inference group**,
which enables grouping of inference rules into logical hierarchical groups.
Inference group definitions start with the keyword `group` followed by the
name of the group. Each file can contain multiple inference group definitions,
but their names must be unique.

Let us define one inference group to encapsulate all inference rules used
for this exercise, and name it `SampleProject`. The definition will
look like::

  group SampleProject {
  ...
  }

Each inference group definition also translates directly into a corresponding
C++ class with the same name. With this group definition above, the
synthesized C++ class definition will resemble the following form::

  class SampleProject {
  ...
  };


Environment definitions
***********************

Each inference group definition contains a set of attributes that affect
all the inference rules within the group. These attributes are denoted as
key-value pairs and are specified within the group definition.
Some keys are required, while others are optional.
Below are descriptions of all supported environment definitions.

ClassName
^^^^^^^^^


Inference rule definitions
##########################

**Inference rule definitions** are at the heart of the Snowlake language.
Each inference rule definition uniquely captures the static type inference
logic associated with one language construct. The Snowlake compiler
synthesizes each inference definition into a corresponding C++ member
function, which is a member of the C++ class that is synthesized from the
corresponding parent inference group.

Each inference rule definition is made up of four parts:
**global definitions**, **arguments**, **premises**, and **proposition**,
as well as two entities that are make up premises and propositions:
**identifiables** and **deduced targets**.
Global definitions and arguments are input that the inference rule uses
for deriving its inferences. Premises are the logical rules that make up
the assumptions of a particular inference. Finally, each inference
definition consists one proposition definition that makes up the final
inferred type of the rule.


Global definitions
##################

**Global definitions** refer to named entities in the synthesized C++ code
that reference objects or other constructs at the global level.
Global definitions are simply declared names that tell the Snowlake compiler
that such definitions can be used throughout the inference rules in a
semantically correct manner.


Identifiables
#############

**Identifiables** in Snowlake are identifiers that simply refer to entities
or attributes of entities in the synthesized C++ code. Identifiables can be
chained with the dot (i.e. `'.'`) character to represent members on
existing identifiables.

For example, we can have an identifiable named `"binaryExpr"` that refer
to a variable named `"binaryExpr"` in C++, and `"binaryExpr.type"` that refer
to the type of the binary expression.


Deduced targets
###############

**Deduced targets** are declarations of the deduced types within an
inference rule. Deduced targets are synthesized into C++ variable
declarations and definitions, and thus can be used in subsequent
premise definitions.

There are three form of deduced targets: **singular form**,
**array form** (with and without size literal), and **computed form**.


Singular form
*************

Deduced targets in singular form represent individual named types
deduced in the inference rule.


Array form
**********

Deduced targets in array form represent a collection of types deduced
in the inference rule, and are synthesized into array/vector types in
C++ depending on if a fixed size literal is used.


Computed form
*************

Deduced targets in computed form represent types deduced through calling
a function. This form of deduced targets are used when the type deduction
result is not bound at compile time, but rather at run time. This is
important for many language constructs, such as class inheritance.

/*
 * Copyright 2006-2016 zorba.io
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#ifndef ZORBA_COMPILER_PATH_EXPR
#define ZORBA_COMPILER_PATH_EXPR


#include "compiler/expression/expr_base.h"

#include "zorbatypes/zstring.h"

#include <zorba/store_consts.h>

namespace zorba
{

class match_expr;


/*******************************************************************************

  PathExpr ::=  ("/" RelativePathExpr?) |
                ("//" RelativePathExpr) |
                RelativePathExpr

  RelativePathExpr ::= StepExpr (("/" | "//") StepExpr)*


  Formal Semantics [http://www.w3.org/TR/xquery-semantics]:
    /    == fn:root(self::node())
    /A   == fn:root(self::node())/A
    //A  == fn:root(self::node())/descendant-or-self::node()/A
    A//B == A/descendant-or-self::node()/B
  This implies that all path expressions are relative path expressions. So a
  relative path is defined as follows:

 RelativPathExpr ::= "/" | ("/" | "//")?  StepExpr (("/" | "//") StepExpr)*

********************************************************************************/
class relpath_expr : public expr
{
  friend class ExprIterator;
  friend class expr;
  friend class ExprManager;

protected:
  std::vector<expr*> theSteps;

protected:
  relpath_expr(
      CompilerCB* ccb,
      static_context* sctx,
      user_function* udf,
      const QueryLoc& loc);

public:
  size_t size() const { return theSteps.size(); }

  void add_back(expr* step);

  void erase(csize i) { theSteps.erase(theSteps.begin() + i); }

  csize numSteps() const { return theSteps.size(); }

  expr* operator[](csize n) const { return theSteps[n]; }

  std::vector<expr*>::const_iterator begin() const { return theSteps.begin(); }

  std::vector<expr*>::const_iterator end() const { return theSteps.end(); }

  void compute_scripting_kind();

  void accept(expr_visitor&);

  std::ostream& put(std::ostream&) const;
};


/*******************************************************************************

  StepExpr ::= AxisStep  |  FilterExpr

********************************************************************************/


/*******************************************************************************

  AxisStep ::= Axis NodeTest Predicate*

********************************************************************************/
class axis_step_expr : public expr
{
  friend class ExprIterator;
  friend class expr;
  friend class ExprManager;

protected:
  axis_kind_t             theAxis;
  bool                    theReverseOrder;
  expr                  * theNodeTest;

public:
  static bool is_reverse_axis(axis_kind_t kind);

protected:
  axis_step_expr(
     CompilerCB* ccb,
     static_context* sctx,
     user_function* udf,
     const QueryLoc&);

public:
  axis_kind_t getAxis() const { return theAxis; }

  void setAxis(axis_kind_t v) { theAxis = v; }

  void set_reverse_order() { theReverseOrder = true; }

  bool use_reverse_order() const { return theReverseOrder; }

  bool is_reverse_axis() const { return is_reverse_axis(getAxis()); }

  match_expr* getTest() const
  {
    return reinterpret_cast<match_expr*>(theNodeTest);
  }

  void setTest(match_expr* v);

  void compute_scripting_kind();

  void accept(expr_visitor&);

  std::ostream& put(std::ostream&) const;
};


/*******************************************************************************

  [78] NodeTest ::= KindTest | NameTest

  [79] NameTest ::= QName | Wildcard
  [80] Wildcard ::= "*" | (NCName ":" "*") | ("*" ":" NCName)

  [123] KindTest ::= DocumentTest | ElementTest | AttributeTest |
                     SchemaElementTest | SchemaAttributeTest |
                     PITest | CommentTest | TextTest | AnyKindTest

  If a match_expr represents a KindTest, then theWildKind and theWildName data
  members are not used. 

  If a match_expr represents a NameTest, then theTypeName and theNilledAllowed
  data members are not used. In this case, theWildKind is used to distinguish
  among 4 subcases:

  1. no wildcard: 
     theQName holds the expanded qname to match against an element or attribute
     node. theWildName is not used.

  2. full wildcard (*):
     Neither theQName nor theWildName are used.

  3. localname wildcard (pre:*):
     theQName holds an artificial qname: "ns:wildcard", where ns is the URI
     associated with pre. theWildName holds the pre.

  4. prefix wildcard (*:name):
     theQName is not used and theWildName holds the local name.
********************************************************************************/
class match_expr : public expr
{
  friend class ExprIterator;
  friend class expr;
  friend class ExprManager;

protected:
  match_test_t      theTestKind;
  match_test_t      theDocTestKind;

  match_wild_t      theWildKind;
  zstring           theWildName;

  store::Item_t     theQName;

  store::Item_t     theTypeName;
  bool              theNilledAllowed;

protected:
  match_expr(
      CompilerCB* ccb,
      static_context* sctx,
      user_function* udf,
      const QueryLoc&);

public:
  match_test_t getTestKind() const { return theTestKind; }

  void setTestKind(enum match_test_t v) { theTestKind = v; }

  match_test_t getDocTestKind() const { return theDocTestKind; }

  void setDocTestKind(enum match_test_t v) { theDocTestKind = v; }

  match_wild_t getWildKind() const { return theWildKind; }

  void setWildKind(enum match_wild_t v) { theWildKind = v; }

  const zstring& getWildName() const { return theWildName; }

  void setWildName(const zstring& v) { theWildName = v; }

  store::Item* getQName() const { return theQName.getp(); }

  void setQName(const store::Item_t& v) { theQName = v; }

  store::Item* getTypeName() const { return theTypeName.getp(); }

  void setTypeName(const store::Item_t& v) { theTypeName = v; }

  bool getNilledAllowed() const { return theNilledAllowed; }

  void setNilledAllowed(bool v) { theNilledAllowed = v; }

  store::StoreConsts::NodeKind getNodeKind() const;

  void compute_scripting_kind();

  bool matches(const match_expr* other) const;

  void accept(expr_visitor&);

  std::ostream& put(std::ostream&) const;
};



}

#endif

/*
 * Local variables:
 * mode: c++
 * End:
 */
/* vim:set et sw=2 ts=2: */

/*
 * Copyright 2006-2012 2006-2016 zorba.io.
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
 
// ******************************************
// *                                        *
// * THIS IS A GENERATED FILE. DO NOT EDIT! *
// * SEE .xml FILE WITH SAME NAME           *
// *                                        *
// ******************************************



#ifndef ZORBA_FUNCTIONS_FT_MODULE_H
#define ZORBA_FUNCTIONS_FT_MODULE_H


#include "common/shared_types.h"
#include "functions/function_impl.h"


namespace zorba {


void populate_context_ft_module(static_context* sctx);


#ifndef ZORBA_NO_FULL_TEXT

//full-text:current-compare-options
class full_text_current_compare_options : public function
{
public:
  full_text_current_compare_options(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};
#endif
#ifndef ZORBA_NO_FULL_TEXT

//full-text:current-lang
class full_text_current_lang : public function
{
public:
  full_text_current_lang(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};
#endif
#ifndef ZORBA_NO_FULL_TEXT

//full-text:host-lang
class full_text_host_lang : public function
{
public:
  full_text_host_lang(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};
#endif
#ifndef ZORBA_NO_FULL_TEXT

//full-text:is-stem-lang-supported
class full_text_is_stem_lang_supported : public function
{
public:
  full_text_is_stem_lang_supported(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};
#endif
#ifndef ZORBA_NO_FULL_TEXT

//full-text:is-stop-word
class full_text_is_stop_word : public function
{
public:
  full_text_is_stop_word(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};
#endif
#ifndef ZORBA_NO_FULL_TEXT

//full-text:is-stop-word-lang-supported
class full_text_is_stop_word_lang_supported : public function
{
public:
  full_text_is_stop_word_lang_supported(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};
#endif
#ifndef ZORBA_NO_FULL_TEXT

//full-text:is-thesaurus-lang-supported
class full_text_is_thesaurus_lang_supported : public function
{
public:
  full_text_is_thesaurus_lang_supported(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};
#endif
#ifndef ZORBA_NO_FULL_TEXT

//full-text:is-tokenizer-lang-supported
class full_text_is_tokenizer_lang_supported : public function
{
public:
  full_text_is_tokenizer_lang_supported(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};
#endif
#ifndef ZORBA_NO_FULL_TEXT

//full-text:stem
class full_text_stem : public function
{
public:
  full_text_stem(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};
#endif
#ifndef ZORBA_NO_FULL_TEXT

//full-text:strip-diacritics
class full_text_strip_diacritics : public function
{
public:
  full_text_strip_diacritics(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};
#endif
#ifndef ZORBA_NO_FULL_TEXT

//full-text:thesaurus-lookup
class full_text_thesaurus_lookup : public function
{
public:
  full_text_thesaurus_lookup(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};
#endif
#ifndef ZORBA_NO_FULL_TEXT

//full-text:tokenize-node
class full_text_tokenize_node : public function
{
public:
  full_text_tokenize_node(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};
#endif
#ifndef ZORBA_NO_FULL_TEXT

//full-text:tokenize-nodes
class full_text_tokenize_nodes : public function
{
public:
  full_text_tokenize_nodes(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};
#endif
#ifndef ZORBA_NO_FULL_TEXT

//full-text:tokenizer-properties
class full_text_tokenizer_properties : public function
{
public:
  full_text_tokenizer_properties(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};
#endif
#ifndef ZORBA_NO_FULL_TEXT

//full-text:tokenize-string
class full_text_tokenize_string : public function
{
public:
  full_text_tokenize_string(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};
#endif


} //namespace zorba


#endif
/*
 * Local variables:
 * mode: c++
 * End:
 */ 

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

#ifndef ZORBA_INTERNAL_ZTD_H
#define ZORBA_INTERNAL_ZTD_H

#include <cstring>
#include <functional>
#include <sstream>
#include <string>

#include <zorba/config.h>

#include "cxx_util.h"
#include "type_traits.h"

///////////////////////////////////////////////////////////////////////////////

namespace zorba {
namespace internal {
namespace ztd {

////////// tr1 ////////////////////////////////////////////////////////////////

/**
 * \internal
 * Base class for SFINAE (Substitution Failure Is Not An Error) types.
 */
class sfinae_base {
protected:
  typedef char no;
  typedef char yes[2];
public:
  void suppress_all_member_functions_are_private_warning();
};

/**
 * \internal
 * Declares a class that can be used to determine whether a given type \c T has
 * a particular member function with a certain signature.
 * For example:
 * \code
 * ZORBA_DECL_HAS_MEM_FN( c_str );
 *
 * template<typename T> inline
 * typename enable_if<has_c_str<T,char const* (T::*)() const>::value,
 *                    std::string>::type
 * to_string( T const &t ) {
 *   // case where T has c_str()
 * }
 *
 * template<typename T> inline
 * typename enable_if<!has_c_str<T,char const* (T::*)() const>::value,
 *                     std::string>::type
 * to_string( T const &t ) {
 *   // case where T does not have c_str()
 * }
 * \endcode
 * \hideinitializer
 */
#define ZORBA_DECL_HAS_MEM_FN(FN_NAME)                                \
  template<typename T,typename S>                                     \
  class has_##FN_NAME : public ::zorba::internal::ztd::sfinae_base {  \
    template<typename SignatureType,SignatureType> struct type_check; \
    template<class U> static yes& test(type_check<S,&U::FN_NAME>*);   \
    template<class U> static no& test(...);                           \
  public:                                                             \
    static bool const value = sizeof( test<T>(0) ) == sizeof( yes );  \
  }

/**
 * \internal
 * This namespace is used only to bundle the implementation details for
 * implementing \c has_insertion_operator<T>.
 * This implementation is based on http://stackoverflow.com/q/4434569/
 */
namespace has_insertion_operator_impl {
  typedef char no;
  typedef char yes[2];

  /**
   * This dummy class is used to make the matching of the dummy
   * \c operator&lt;&lt;() \e worse than the global \c operator&lt;&lt;(),
   * if any.
   */
  struct any_t {
    template<typename T> any_t( T const& );
  };

  /**
   * This dummy operator is matched only when there is \e no global
   * \c operator&lt;&lt;() otherwise declared for type \c T.
   *
   * @return Returns a \c no that selects defined(no).
   */
  no operator<<( std::ostream const&, any_t const& );

  /**
   * This function is matched only when there \e is a global
   * \c operator&lt;&lt;() declared for type \c T because
   * \c operator&lt;&lt;()'s return type is \c std::ostream&.
   *
   * @return Returns a yes& whose \c sizeof() equals \c sizeof(yes).
   */
  yes& defined( std::ostream& );

  /**
   * This function is matched only when the dummy \c operator&lt;&lt;() is
   * matched.
   *
   * @return Returns a no whose \c sizeof() equals \c sizeof(no).
   */
  no defined( no );

  /**
   * The implementation class that can be used to determine whether a given
   * type \c T has a global
   * <code>std::ostream& operator&lt;&lt;(std::ostream&,T const&)</code>
   * defined for it.
   * However, do not use this class directly.
   *
   * @tparam T The type to check.
   */
  template<typename T>
  class has_insertion_operator {
    static std::ostream &s;
    static T const &t;
  public:
    /**
     * This is \c true only when the type \c T has a global
     * \c operator&lt;&lt;() declared for it.
     * \hideinitializer
     */
    static bool const value = sizeof( defined( s << t ) ) == sizeof( yes );
  };
} // namespace has_insertion_operator_impl

/**
 * \internal
 * A class that can be used to determine whether a given type \c T has a global
 * <code>std::ostream& operator&lt;&lt;(std::ostream&,T const&)</code> defined
 * for it.
 * For example:
 * \code
 * template<typename T> inline
 * typename enable_if<has_insertion_operator<T>::value,std::string>::value
 * to_string( T const &t ) {
 *   // case where T has operator<<(ostream&,T const&)
 * }
 * \endcode
 *
 * @tparam T The type to check.
 */
template<typename T>
struct has_insertion_operator :
  has_insertion_operator_impl::has_insertion_operator<T>
{
};

////////// alignment ///////////////////////////////////////////////////////////

// See: http://stackoverflow.com/a/6959582/99089

namespace align_impl {

template<typename T,bool smaller>
struct align_type_impl;

template<typename T>
struct align_type_impl<T,false> {
  typedef T type;
};

template<typename T>
struct align_type_impl<T,true> {
  typedef char type;
};

template<typename T,typename U>
struct align_type {
  typedef typename align_type_impl<U,(sizeof(T) < sizeof(U))>::type type;
};

} // namespace align_impl

/**
 * An %aligner can be used inside a \c union to align it properly for type
 * \c T.
 *
 * @tparam T The type to align properly.
 */
template<typename T>
union aligner {
  typename align_impl::align_type<T,char>::type c;
  typename align_impl::align_type<T,short>::type s;
  typename align_impl::align_type<T,int>::type i;
  typename align_impl::align_type<T,long>::type l;
  typename align_impl::align_type<T,long long>::type ll;
  typename align_impl::align_type<T,float>::type f;
  typename align_impl::align_type<T,double>::type d;
  typename align_impl::align_type<T,long double>::type ld;
  typename align_impl::align_type<T,void*>::type p;
  typename align_impl::align_type<T,void (*)()>::type pf;
  typename align_impl::align_type<T,aligner*>::type ps;
  typename align_impl::align_type<T,void (aligner::*)()>::type pmf;
};

/**
 * A %raw_buf is a properly aligned chunk of raw memory for an object of type
 * \c T.
 *
 * @tparam T The type to hold an object of.
 */
template<typename T>
union raw_buf {
  aligner<T> dummy_for_alignment;
  char buf[ sizeof(T) ];
};

////////// c_str() /////////////////////////////////////////////////////////////

/**
 * \internal
 * Gets the \c char* to the given string.
 * 
 * @tparam StringType The string's type.
 * @param s The string to get the \c char* of.
 * @return Returns said \c char*.
 */
template<class StringType> inline
typename StringType::const_pointer c_str( StringType const &s ) {
  return s.c_str();
}

/**
 * \internal
 * Specialization of global c_str() for \c char* argument.
 *
 * @param s The C string to get the \c char* of.
 * @return Returns said \c char*.
 */
inline char const* c_str( char const *s ) {
  return s;
}

////////// destroy_delete (for unique_ptr) ////////////////////////////////////

/**
 * A deleter class that can be used with unique_ptr.  Instead of calling \c
 * delete on the pointed-to object, it calls its \c destroy() member function.
 */
template<typename T>
struct destroy_delete {
  destroy_delete() { }

  /**
   * Copy constructor.
   *
   * @tparam U The delete type of the deleter to copy-construct from such that
   * \c U* is convertible to \c T*.
   */
  template<typename U>
  destroy_delete( destroy_delete<U> const&,
    typename
      std::enable_if<ZORBA_TR1_NS::is_convertible<U*,T*>::value>::type*
        = nullptr )
  {
  }

  /**
   * Calls the \c destroy() member function of the pointed-to object.
   *
   * @param p A pointer to the object.
   */
  void operator()( T *p ) {
    if ( p )
      p->destroy();
  }
};

////////// less<char const*> ///////////////////////////////////////////////////

// This declaration exists only to declare that less is a template class.
template<typename T> struct less {
};

/**
 * \internal
 * Specialize the binary_function "less" so that C-style strings (char const*)
 * will work properly with STL containers.
 *
 * See also: Bjarne Stroustrup. "The C++ Programming Language, 3rd ed."
 * Addison-Wesley, Reading, MA, 1997.  p. 468.
 */
template<> struct less<char const*> :
  std::binary_function<char const*,char const*,bool>
{
  less() { }
  // This default constructor doesn't need to be defined, but g++ complains if
  // it isn't and you try to define a "const less" object.

  result_type
  operator()( first_argument_type a, second_argument_type b ) const {
    return std::strcmp( a, b ) < 0;
  }
};

////////// To-string conversion ////////////////////////////////////////////////

ZORBA_DECL_HAS_MEM_FN( c_str );
ZORBA_DECL_HAS_MEM_FN( str );
ZORBA_DECL_HAS_MEM_FN( toString );

/**
 * \internal
 * Short-hand macro for use with enable_if to determine whether the given type
 * has a member function with the signature
 * <code>char const* (T::*)() const</code>.
 * \hideinitializer
 */
#define ZORBA_HAS_C_STR(T) \
  ::zorba::internal::ztd::has_c_str<T,char const* (T::*)() const>::value

/**
 * \internal
 * Short-hand macro for use with enable_if to determine whether the given type
 * is a class having an API matching std::string.
 * \hideinitializer
 */
#define ZORBA_IS_STRING(T) ZORBA_HAS_C_STR(T)

/**
 * \internal
 * Tests whether a given type \a T is a C string type.
 *
 * @tparam T The type to check.
 */
template<typename T>
class is_c_string {
  typedef typename ZORBA_TR1_NS::remove_pointer<T>::type T_base;
  typedef typename ZORBA_TR1_NS::add_const<T_base>::type T_base_const;
public:
  static bool const value =
       ZORBA_TR1_NS::is_same<T_base_const*,char const*>::value
    || ZORBA_TR1_NS::is_same<T_base_const*,unsigned char const*>::value
    || ZORBA_TR1_NS::is_same<T_base_const*,signed char const*>::value;
};

/**
 * \internal
 * Converts an object to its string representation.
 *
 * @tparam T The object type that:
 *  - is not an array
 *  - is not a pointer
 *  - has an <code>ostream& operator&lt;&lt;(ostream&,T const&)</code> defined
 * @param t The object.
 * @return Returns a string representation of the object.
 */
template<typename T> inline
typename std::enable_if<!ZORBA_TR1_NS::is_array<T>::value
                     && !ZORBA_TR1_NS::is_pointer<T>::value
                     && has_insertion_operator<T>::value,
                        std::string>::type
to_string( T const &t ) {
  std::ostringstream o;
  o << t;
  return o.str();
}

/**
 * \internal
 * Specialization of \c to_string() for class types that have a \c c_str()
 * member function, i.e., string types.
 *
 * @tparam T The class type that:
 *  - has no <code>ostream& operator&lt;&lt;(ostream&,T const&)</code> defined
 *  - has <code>char const* T::c_str() const</code> defined
 * @param t The object.
 * @return Returns a string representation of the object.
 */
template<class T> inline
typename std::enable_if<!has_insertion_operator<T>::value
                     && ZORBA_HAS_C_STR(T),
                        std::string>::type
to_string( T const &t ) {
  return t.c_str();
}

/**
 * \internal
 * Specialization of \c to_string() for class types that have a \c str()
 * member function.
 *
 * @tparam T The class type that:
 *  - has no <code>ostream& operator&lt;&lt;(ostream&,T const&)</code> defined
 *  - has no <code>char const* T::c_str() const</code> defined
 *  - has no <code>std::string T::toString() const</code> defined
 *  - has <code>std::string T::str() const</code> defined
 * @param t The object.
 * @return Returns a string representation of the object.
 */
template<class T> inline
typename std::enable_if<!has_insertion_operator<T>::value
                     && !ZORBA_HAS_C_STR(T)
                     && has_str<T,std::string (T::*)() const>::value
                     && !has_toString<T,std::string (T::*)() const>::value,
                        std::string>::type
to_string( T const &t ) {
  return t.str();
}

/**
 * \internal
 * Specialization of \c to_string() for class types that have a \c toString()
 * member function.
 *
 * @tparam T The class type that:
 *  - has no <code>ostream& operator&lt;&lt;(ostream&,T const&)</code> defined
 *  - has no <code>char const* T::c_str() const</code> defined
 *  - has no <code>std::string T::str() const</code> defined
 *  - has <code>std::string T::toString() const</code> defined
 * @param t The object.
 * @return Returns a string representation of the object.
 */
template<class T> inline
typename std::enable_if<!has_insertion_operator<T>::value
                     && !ZORBA_HAS_C_STR(T)
                     && !has_str<T,std::string (T::*)() const>::value
                     && has_toString<T,std::string (T::*)() const>::value,
                        std::string>::type
to_string( T const &t ) {
  return t.toString();
}

/**
 * \internal
 * Specialization of \c to_string() for pointer types other than C strings.
 *
 * @tparam T The pointer type.
 * @param p The pointer.
 * @return If \a p is not \c NULL, returns the result of \c to_string(*p);
 * otherwise returns \c "<null>".
 */
template<typename T> inline
typename std::enable_if<ZORBA_TR1_NS::is_pointer<T>::value
                     && !is_c_string<T>::value,
                        std::string>::type
to_string( T p ) {
  typedef typename ZORBA_TR1_NS::remove_pointer<T>::type T_base;
  typedef typename ZORBA_TR1_NS::add_const<T_base>::type T_base_const;
  return p ? to_string( *static_cast<T_base_const*>( p ) ) : "<null>";
}

/**
 * \internal
 * Specialization of \c to_string() for C strings.
 *
 * @param s The C string.
 * @return Returns a string representation of the object.
 */
inline std::string to_string( char const *s ) {
  return s ? s : "<null>";
}

/**
 * \internal
 * Specialization of \c to_string() for C strings.
 *
 * @param s The C string.
 * @return Returns a string representation of the object.
 */
inline std::string to_string( unsigned char const *s ) {
  return s ? reinterpret_cast<char const*>( s ) : "<null>";
}

////////// misc ///////////////////////////////////////////////////////////////

/**
 * Helper class for implementing a solution to the "explicit bool conversion"
 * problem.  The canonical use is of the form:
 * \code
 *  class your_class {
 *    // ...
 *    operator explicit_bool::type() const {
 *      return explicit_bool::value_of( some_expression );
 *    }
 *  };
 * \endcode
 *
 * See: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2333.html
 */
class explicit_bool {
  struct pointer_conversion { int valid; };
public:
  typedef int pointer_conversion::*type;

  /**
   * Gets the explicit \c bool value for \c false.
   *
   * @return Returns said value.
   */
  static type false_value() {
    return 0;
  }

  /**
   * Gets the explicit \c bool value for \c true.
   *
   * @return Returns said value.
   */
  static type true_value() {
    return &pointer_conversion::valid;
  }

  /**
   * Converts the given value to an explicit \c bool value.
   *
   * @tparam T The type of the value to convert.
   * @param value The value to convert.
   * @return Return said value.
   */
  template<typename T> static
  typename std::enable_if<ZORBA_TR1_NS::is_convertible<T,bool>::value,
                          type>::type
  value_of( T const &value ) {
    //
    // Using a template here eliminates a MSVC++ 4800 warning:
    // "forcing value to 'true' or 'false' (performance warning)"
    //
    return value ? true_value() : false_value();
  }
};

///////////////////////////////////////////////////////////////////////////////

} // namespace ztd
} // namespace internal
} // namespace zorba
#endif /* ZORBA_INTERNAL_ZTD_H */
/* vim:set et sw=2 ts=2: */

///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2015-2016 Bryce Adelstein Lelbach aka wash
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(STD_FD8D1DFC_4745_40CA_A752_6E6AC86038D4)
#define STD_FD8D1DFC_4745_40CA_A752_6E6AC86038D4

#include <cstdint>

namespace std { namespace experimental
{

template <typename... Ts>
struct conjunction;

template <typename... Ts>
struct disjunction;

template <typename T, T... I>
struct integer_sequence;

template <std::size_t... Idxs>
using index_sequence = integer_sequence<std::size_t, Idxs...>;

namespace detail
{

template <typename Sequence0, typename Sequence1>
struct merge_and_renumber_integer_sequences;

template <typename Sequence0, typename Sequence1>
struct merge_and_renumber_reversed_integer_sequences;

} // std::experimental::detail

template <typename T, std::size_t N>
struct make_integer_sequence;

template <std::size_t N>
using make_index_sequence =
    make_integer_sequence<std::size_t, N>;

template <typename T, std::size_t N>
struct make_reversed_integer_sequence;

template <std::size_t N>
using make_reversed_index_sequence =
    make_reversed_integer_sequence<std::size_t, N>;

///////////////////////////////////////////////////////////////////////////////

namespace detail
{

// Reduction-style visitation of the extents of dimensions<>. Op, Reduction and
// Sentinel are function objects with a constexpr const method that takes the
// correct number of dimensions<> objects by value. 

template <
    typename Op
  , typename Reduction
  , typename Sentinel
  , std::size_t Idx
  , std::size_t Size
    >
struct dims_unary_reduction;

template <
    typename Op
  , typename Reduction
  , typename Sentinel
  , std::size_t Idx
  , std::size_t Size
    >
struct dims_binary_reduction;

template <
    typename Op
  , typename Reduction
  , typename Sentinel
  , std::size_t Idx
  , std::size_t Size
    >
struct dims_ternary_reduction;

///////////////////////////////////////////////////////////////////////////////

// <functional>-style function objects with value semantics.

struct identity_by_value;

struct multiplies_by_value;

struct span_by_value;

template <std::size_t Value> 
struct static_sentinel;

///////////////////////////////////////////////////////////////////////////////

// Runtime implementation of the std::extent metafunction. 

// Base case.
template <typename Idx>
inline std::size_t constexpr dynamic_extent(
    Idx idx
    ) noexcept;

template <typename Idx, typename Head, typename... Tail>
inline std::size_t constexpr dynamic_extent(
    Idx idx, Head head, Tail... tail
    ) noexcept;

// Maps a dimension index referring to a dynamic index (idx) to an index in the
// dynamic dimension array. E.g. if you have dimensions<3, dyn, 4, dyn>, this
// metafunction would map 1 to 0 (the first dynamic dimension) and 3 to 1 (the
// second one).

// Base case.
template <typename Idx>
inline constexpr std::size_t index_into_dynamic_dims(
    Idx idx
    ) noexcept;

template <typename Idx, typename Head, typename... Tail>
inline constexpr std::size_t index_into_dynamic_dims(
    Idx idx, Head head, Tail... tail
    ) noexcept;

///////////////////////////////////////////////////////////////////////////////

template <typename... T>
struct typelist;

///////////////////////////////////////////////////////////////////////////////

template <typename Key, typename Value, Key K, Value V>
struct integral_pair;

// Metafunction class; embedded apply<T0, T1> returns true if the key of the
// integral_pair T0 is less than the key of the integral_pair T1.
struct integral_pair_less;

// Metafunction class; embedded apply<T0, T1> returns true if integral_constant
// T0 is less than integral_constant T1. 
struct integral_constant_less;

///////////////////////////////////////////////////////////////////////////////

// Add a new element to the front of a typelist.
template <typename T, typename Sequence> 
struct type_list_prepend;

// Add a new element to a sorted type_list. Compare is a metafunction class;
// its embedded apply<T0, T1> template takes two parameters and returns a
// boolean integral_constant.
template <typename T, typename Sequence
        , typename Compare = integral_constant_less> 
struct type_list_push;

template <typename Compare, typename T, typename... Tail> 
struct type_list_push_impl;

// Produces a sorted type_list from an input type_list. Compare is a
// metafunction class; its embedded apply<T0, T1> template takes two parameters
// and returns a boolean integral_constant.
template <typename Sequence, typename Compare = integral_constant_less> 
struct type_list_sort;

///////////////////////////////////////////////////////////////////////////////
// Expression SFINAE workarounds for MSVC.

template <typename Dimensions, std::size_t N>
struct rank_greater_than;

template <typename Dimensions, std::size_t N>
struct rank_equal_to;

template <typename Dimensions, std::size_t N>
struct is_last_index;

///////////////////////////////////////////////////////////////////////////////

// Counts the number of dynamic dimensions.
template <std::size_t... Dims>
struct count_dynamic_dims;

// Builds a std::array with one entry for each dynamic dimension.
template <std::size_t... Dims>
struct make_dynamic_dims_array;

template <std::size_t... Dims>
using make_dynamic_dims_array_t =
    typename make_dynamic_dims_array<Dims...>::type;

// Creates a dimensions<> type of rank N with static extents of Value.
template <std::size_t N, std::size_t Value, std::size_t... Dims>
struct make_filled_dims;

template <std::size_t N, std::size_t Value, std::size_t... Dims>
using make_filled_dims_t = typename make_filled_dims<N, Value, Dims...>::type;

// Creates a typelist of key-value pairs from an integer_sequence, where
// the key is the position of the value in the input integer_sequence.
template <typename Sequence>
struct make_integer_sequence_index_mapping;

// Creates a key-value typelist from two input integer_sequences.
template <typename KeySequence, typename ValueSequence>
struct make_key_value_type_list;

///////////////////////////////////////////////////////////////////////////////

// Returns true if std::is_integral<> is true for all of the types in the
// parameter pack.
template <typename... T>
struct pack_is_integral;

// Returns true if T is an integral range slice specifier, e.g. one of the
// following, where I0 and I1 are integral types:
// * initializer_list<I0>
// * pair<I0, I1>
// * tuple<I0, I1>
// * array<I0, 2>
// * all (denoting the entire dimension)
template <typename T>
struct is_integral_range_slice_specifier;

// Returns true if T is a slice specifier.
template <typename T>
struct is_slice_specifier;

// Returns true if is_slice_specifier<> is true for all of the types in the
// parameter pack.
template <typename... T>
struct pack_is_slice_specifiers;

// Counts the number of dynamic dimensions.
template <typename... Dims>
struct count_integral_range_slice_specifiers;

///////////////////////////////////////////////////////////////////////////////

// Function-object recursive implementation of layout_left indexing. N is the
// rank in the index dimensions<> object.
template <
    typename Dimensions, typename Striding, typename Padding
  , std::size_t N
  , typename enable = void
    >
struct layout_mapping_left_indexer;

// Function-object recursive implementation of layout_right indexing. N is the
// rank in the index dimensions<> object.
template <
    typename Dimensions, typename Striding, typename Padding
  , std::size_t N
  , typename enable = void
    >
struct layout_mapping_right_indexer;

} // detail

///////////////////////////////////////////////////////////////////////////////

// Produces a dimensions<> object from a native array declaration.
template <typename T, std::size_t... Dims>
struct extract_dimensions;

template <typename T>
using extract_dimensions_t = typename extract_dimensions<T>::type;

///////////////////////////////////////////////////////////////////////////////

namespace detail {

struct all_tag {};

} // detail 

constexpr detail::all_tag all{};

///////////////////////////////////////////////////////////////////////////////

constexpr std::size_t dyn = -1;

template <std::size_t... Dims>
struct dimensions;

///////////////////////////////////////////////////////////////////////////////

// TODO: Specify ArrayRefLayout concept which these classes implement.

template <
    typename Dimensions
  , typename Striding
  , typename Padding
    >
struct layout_mapping_left;

// TODO
template <
    typename Dimensions
  , typename Striding
  , typename Padding
    >
struct layout_mapping_right; 

// TODO
template <
    typename Dimensions
  , typename Striding
  , typename Padding
  , typename Ordering
    >
struct basic_layout_order;

struct layout_left;

// TODO
struct layout_right; 

// TODO
template <std::size_t... Ordering>
struct layout_order;

using layout_native = layout_right;

///////////////////////////////////////////////////////////////////////////////

// TODO: Specify ArrayRefAccessor concept which these classes implement.

template <typename ValueType>
struct accessor_native;

///////////////////////////////////////////////////////////////////////////////

template <typename ValueType
        , typename Dim       = extract_dimensions_t<ValueType>
        , typename Layout    = layout_native
        , typename Accessor  = accessor_native<ValueType>
         >
struct mdspan;

}} // std::experimental

#endif // STD_FD8D1DFC_4745_40CA_A752_6E6AC86038D4


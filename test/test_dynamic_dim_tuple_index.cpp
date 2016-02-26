////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2015 Bryce Adelstein Lelbach aka wash
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <boost/detail/lightweight_test.hpp>

#include <array_ref>

int main()
{
    using std::experimental::detail::dynamic_dim_tuple_index;
    constexpr auto dyn = std::experimental::dynamic_dimension;

    BOOST_TEST_EQ((dynamic_dim_tuple_index<0, 0               >::value), 0);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<0, 0, 3            >::value), 0);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<0, 0, 3,   5       >::value), 0);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<0, 0, 3,   5,   9  >::value), 0);

    // The 0 == dynamic_dimension alias does not work here, so we do not test
    // it. The metafunction that maps 0 to dynamic_dimension is applied in the
    // template alias defining dimensions<>; count_dynamic_dims<> works on a
    // parameter pack directly, so 0s used here are not mapped to
    // dynamic_dimension.

    BOOST_TEST_EQ((dynamic_dim_tuple_index<0, 0, dyn, 5,   9  >::value), 0);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<1, 0, dyn, 5,   9  >::value), 1);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<2, 0, dyn, 5,   9  >::value), 1);

    BOOST_TEST_EQ((dynamic_dim_tuple_index<0, 0, 3,   dyn, 9  >::value), 0);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<1, 0, 3,   dyn, 9  >::value), 0);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<2, 0, 3,   dyn, 9  >::value), 1);

    BOOST_TEST_EQ((dynamic_dim_tuple_index<0, 0, 3,   5,   dyn>::value), 0);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<1, 0, 3,   5,   dyn>::value), 0);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<2, 0, 3,   5,   dyn>::value), 0);

    BOOST_TEST_EQ((dynamic_dim_tuple_index<0, 0, 3,   dyn, dyn>::value), 0);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<1, 0, 3,   dyn, dyn>::value), 0);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<2, 0, 3,   dyn, dyn>::value), 1);

    BOOST_TEST_EQ((dynamic_dim_tuple_index<0, 0, dyn, 5,   dyn>::value), 0);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<1, 0, dyn, 5,   dyn>::value), 1);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<2, 0, dyn, 5,   dyn>::value), 1);

    BOOST_TEST_EQ((dynamic_dim_tuple_index<0, 0, dyn, dyn, 9  >::value), 0);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<1, 0, dyn, dyn, 9  >::value), 1);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<2, 0, dyn, dyn, 9  >::value), 2);

    BOOST_TEST_EQ((dynamic_dim_tuple_index<0, 0, dyn, dyn, dyn>::value), 0);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<1, 0, dyn, dyn, dyn>::value), 1);
    BOOST_TEST_EQ((dynamic_dim_tuple_index<2, 0, dyn, dyn, dyn>::value), 2);

    return boost::report_errors();
}


#ifndef BOOST_SERIALIZATION_SLIST_HPP
#define BOOST_SERIALIZATION_SLIST_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif


/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// slist.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_HAS_SLIST

#include <slist>
#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/collections_load_imp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>

namespace boost {
namespace serialization {

template<class Archive, class U, class Allocator>
inline void save(
    Archive & ar,
    const BOOST_STD_EXTENSION_NAMESPACE::slist<U, Allocator> &t,
    const unsigned int file_version
){
    stl::save_collection<
        Archive,
        BOOST_STD_EXTENSION_NAMESPACE::slist<U, Allocator> 
    >(ar, t);
}

template<class Archive, class U, class Allocator>
inline void load(
    Archive & ar,
    BOOST_STD_EXTENSION_NAMESPACE::slist<U, Allocator> &t,
    const unsigned int file_version
){
    // retrieve number of elements
    t.clear();
    // retrieve number of elements
    unsigned int count;
    ar >> BOOST_SERIALIZATION_NVP(count);
    if(0 == count)
        return;

    stl::stack_construct<Archive, U> u(ar);
    ar >> make_nvp("item", u.reference());
    t.push_front(u.reference());
    BOOST_STD_EXTENSION_NAMESPACE::slist<U, Allocator>::iterator last = t.begin();
    while(--count > 0){
        stl::stack_construct<Archive, U> u(ar);
        ar >> make_nvp("item", u.reference());
        last = t.insert_after(last, u.reference());
    }
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class U, class Allocator>
inline void serialize(
    Archive & ar,
    BOOST_STD_EXTENSION_NAMESPACE::slist<U, Allocator> &t,
    const unsigned int file_version
){
    split_free(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#include <boost/serialization/collection_traits.hpp>

BOOST_SERIALIZATION_COLLECTION_TRAITS(BOOST_STD_EXTENSION_NAMESPACE::slist)

#endif  // BOOST_HAS_SLIST
#endif  // BOOST_SERIALIZATION_SLIST_HPP

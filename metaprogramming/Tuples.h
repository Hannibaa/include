#pragma once

/* 
       1. Recursive inheritance tuple
       1.1 implimentation of get<i>(tuple) => find correct base and cast to it
       1.2 easy with out metaprogramming library
*/

template<typename ... E>
struct Tuple {
    constexpr Tuple() = default;
};

template<typename E0, typename... E>
struct Tuple<E0, E...> : Tuple<E...> {
    explicit constexpr Tuple(E0 e0, E...rest)
        :Tuple<E...>(rest...)
        , data(e0)
    {}

    E0 data;
};

// deduction guide to make template argument deduction for constructors work (C++17)
template<typename T, typename ...Ts>
Tuple(T e0, Ts...rest) -> Tuple<std::unwrap_ref_decay_t<T>, std::unwrap_ref_decay_t<Ts>...>;


template<typename ...E>
auto makeTuple(E...e) {
    return Tuple<std::unwrap_ref_decay_t<E>...>{e...};
}

/////////////////////////////////// get //////////////////////////////////////////////////////

namespace detail {
    template<size_t i,typename TUPLE>
    struct get_impl : get_impl<i - 1, pop_front>{};


template<size_t i, typename TUPLE>
constexpr decltype(auto) get(TUPLE& t) {
    return detail::get_impl<i, std::remove_cvref_t<TUPLE>>::get(t);
}

/*
        2. Multiple inheritance tuple
*/




/*
        3. Boniface tuple

*/
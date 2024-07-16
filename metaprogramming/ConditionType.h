#pragma once

template<bool, typename T, typename U>  // if is true;
struct type_is_ { using type = T; };

template<typename T, typename U>
struct type_is_<false, T, U> { using type = U; };

template<typename T, typename U>
struct type_match_ : type_is_< (sizeof(T) > sizeof(U)), T, U > {};
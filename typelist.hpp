#pragma once

namespace tl {
struct null_t {};

template <class T, class U>
struct tl
{
    using head = T;
    using tail = U;
};

template <class T, class ... REST>
struct make { using type = tl<T, typename make<REST...>::type>; };
template <class T>
struct make<T> { using type = tl<T, null_t>; };

template <class ... Ts>
using make_t = typename make<Ts...>::type;


template <class TList, class T>
struct append;
template <>
struct append<null_t, null_t> { using type = null_t; };
template <class T>
struct append<null_t, T> { using type = make_t<T>; };
template <class Head, class T>
struct append<null_t, tl<Head, T>> { using type = tl<Head, T>; };
template <class Head, class Tail, class T>
struct append<tl<Head, Tail>, T>
{ using type = tl<Head, typename append<Tail, T>::type>; };

template <class TList, class T>
using append_t = typename append<TList, T>::type;


template <class TList>
struct list_content;
template <class Head, class Tail>
struct list_content<tl<Head, Tail>> {
    using head = Head;
    using tail = Tail;
};
template <>
struct list_content<null_t> {
    using head = null_t;
    using tail = null_t;
};

template <class TList>
using head_t = typename list_content<TList>::head;

template <class TList>
using tail_t = typename list_content<TList>::tail;


} // namespace tl

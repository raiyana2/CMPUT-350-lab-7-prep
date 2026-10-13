#ifndef PACK_H
#define PACK_H


//Wrote this with the help of ChatGPT

namespace pack_detail {

template <typename... Args>
constexpr int packSize = sizeof...(Args);


template <int QueryIndex, typename... Args>
struct _packIndexToType;

template <typename First, typename... Rest>
struct _packIndexToType<0, First, Rest...> {
    using type = First;
};

template <int QueryIndex, typename First, typename... Rest>
struct _packIndexToType<QueryIndex, First, Rest...> {
    static_assert(QueryIndex >= 0, "Index cannot be negative");
    using type = typename _packIndexToType<QueryIndex - 1, Rest...>::type;
};

template <int QueryIndex, typename... Args>
using packIndexToType =
    typename _packIndexToType<QueryIndex, Args...>::type;


template <typename QueryType, typename... Args>
constexpr int packTypeToIndex = -1;

template <typename QueryType, typename First, typename... Rest>
constexpr int packTypeToIndex<QueryType, First, Rest...> =
    packTypeToIndex<QueryType, Rest...> == -1
        ? -1
        : 1 + packTypeToIndex<QueryType, Rest...>;

template <typename QueryType, typename... Rest>
constexpr int packTypeToIndex<QueryType, QueryType, Rest...> = 0;

} 

template <typename... Args>
struct Pack {
    static constexpr int size = pack_detail::packSize<Args...>;

    template <int QueryIndex>
    using type = pack_detail::packIndexToType<QueryIndex, Args...>;

    template <typename QueryType>
    static constexpr int index =
        pack_detail::packTypeToIndex<QueryType, Args...>;
};

#endif // PACK_H

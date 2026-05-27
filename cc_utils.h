#pragma once

#include "ccl.h"

#define CCU_NEWLIST(Name, T, ...)                                                                  \
    ({                                                                                             \
        Name _list = Name##_new();                                                                 \
        T _arr[] = {__VA_ARGS__};                                                                  \
        for (size_t i = 0; i < sizeof(_arr) / sizeof(T); i++) {                                    \
            Name##_push(&_list, _arr[i]);                                                          \
        }                                                                                          \
        _list;                                                                                     \
    })

#define CCU_FIND(list, cond)                                                                       \
    ({                                                                                             \
        size_t _result = SIZE_MAX;                                                                 \
        for (size_t i = 0; i < (list).size; i++) {                                                 \
            if (cond) {                                                                            \
                _result = i;                                                                       \
                break;                                                                             \
            }                                                                                      \
        }                                                                                          \
        _result;                                                                                   \
    })

#define CCU_CONTAINS(list, target)                                                                 \
    ({                                                                                             \
        int _result = -1;                                                                          \
        if (CCU_FIND(list, list.data[i] == target) != SIZE_MAX) {                                  \
            _result = 0;                                                                           \
        }                                                                                          \
        _result;                                                                                   \
    })

#define CCU_ADD(Name, dst, T, ...)                                                                 \
    do {                                                                                           \
        T _arr[] = {__VA_ARGS__};                                                                  \
        for (size_t i = 0; i < sizeof(_arr) / sizeof(T); i++) {                                    \
            Name##_push(&dst, _arr[i]);                                                            \
        }                                                                                          \
    } while (0)

#define CCU_MAP(list, fn)                                                                          \
    for (size_t i = 0; i < (list).size; i++) {                                                     \
        (list).data[i] = fn((list).data[i]);                                                       \
    }

#define CCU_FOREACH(list, fn)                                                                      \
    for (size_t i = 0; i < (list).size; i++) {                                                     \
        fn((list).data[i]);                                                                        \
    }

#define CCU_EVERY(list, action)                                                                    \
    for (size_t i = 0; i < (list).size; i++) {                                                     \
        (list).data[i] = (list).data[i] action;                                                    \
    }
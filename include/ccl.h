#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CCL_ERR(text)                                                                              \
    do {                                                                                           \
        fprintf(stderr, text);                                                                     \
        exit(EXIT_FAILURE);                                                                        \
    } while (0);

#define CCL_PRINTL(fmt, list)                                                                      \
    do {                                                                                           \
        printf("[");                                                                               \
        for (size_t i = 0; i < (list).size; i++) {                                                 \
            printf(fmt, (list).data[i]);                                                           \
            if (i < (list).size - 1)                                                               \
                printf(", ");                                                                      \
        }                                                                                          \
        printf("]\n");                                                                             \
    } while (0);

#define CCL_BUILD_LIST(T, Name)                                                                    \
    typedef struct {                                                                               \
        T *data;                                                                                   \
        size_t cap;                                                                                \
        size_t size;                                                                               \
    } Name;                                                                                        \
                                                                                                   \
    static inline Name Name##_new(void) {                                                          \
        Name list = {0};                                                                           \
        list.size = 0;                                                                             \
        list.cap = 4;                                                                              \
        list.data = malloc(sizeof(T) * list.cap);                                                  \
        if (list.data == NULL) {                                                                   \
            CCL_ERR("MALLOC FAILED!\n")                                                            \
        }                                                                                          \
        return list;                                                                               \
    }                                                                                              \
                                                                                                   \
    static inline void Name##_free(Name *list) {                                                   \
        free(list->data);                                                                          \
        list->data = NULL;                                                                         \
        list->size = 0;                                                                            \
        list->cap = 0;                                                                             \
    }                                                                                              \
                                                                                                   \
    static inline void Name##_grow(Name *list) {                                                   \
        list->cap *= 2;                                                                            \
        T *temp = realloc(list->data, sizeof(T) * list->cap);                                      \
        if (temp == NULL) {                                                                        \
            CCL_ERR("REALLOC FAILED!\n")                                                           \
        }                                                                                          \
        list->data = temp;                                                                         \
    }                                                                                              \
                                                                                                   \
    static inline void Name##_push(Name *list, T value) {                                          \
        if (list->size >= list->cap) {                                                             \
            Name##_grow(list);                                                                     \
        }                                                                                          \
        list->data[list->size++] = value;                                                          \
    }                                                                                              \
                                                                                                   \
    static inline T *Name##_get(Name *list, size_t idx) {                                          \
        if (idx >= list->size) {                                                                   \
            CCL_ERR("INDEX OUT OF SIZE ERROR!\n");                                                 \
        }                                                                                          \
        return &list->data[idx];                                                                   \
    }                                                                                              \
                                                                                                   \
    static inline T Name##_pop(Name *list) {                                                       \
        if (list->size == 0) {                                                                     \
            CCL_ERR("INDEX OUT OF BOUNDS!\n");                                                     \
        }                                                                                          \
        return list->data[--list->size];                                                           \
    }                                                                                              \
                                                                                                   \
    static inline void Name##_insert(Name *list, size_t idx, T val) {                              \
        if (idx >= list->size) {                                                                   \
            CCL_ERR("INDEX OUT OF BOUNDS!\n");                                                     \
        }                                                                                          \
        if (list->size >= list->cap) {                                                             \
            Name##_grow(list);                                                                     \
        }                                                                                          \
        memmove(&list->data[idx + 1], &list->data[idx], sizeof(T) * (list->size - idx));           \
        list->data[idx] = val;                                                                     \
        list->size++;                                                                              \
    }                                                                                              \
                                                                                                   \
    static inline void Name##_remove(Name *list, size_t idx) {                                     \
        if (idx >= list->size) {                                                                   \
            CCL_ERR("INDEX OUT OF BOUNDS!\n");                                                     \
        }                                                                                          \
        memmove(&list->data[idx], &list->data[idx + 1], sizeof(T) * (list->size - idx - 1));       \
        list->size--;                                                                              \
    }                                                                                              \
                                                                                                   \
    static inline void Name##_extend(Name *list1, Name *list2) {                                   \
        for (size_t i = 0; i < list2->size; i++) {                                                 \
            Name##_push(list1, list2->data[i]);                                                    \
        }                                                                                          \
    }                                                                                              \
                                                                                                   \
    static inline Name Name##_copy(Name *src) {                                                    \
        Name list = Name##_new();                                                                  \
        for (size_t i = 0; i < src->size; i++) {                                                   \
            Name##_push(&list, src->data[i]);                                                      \
        }                                                                                          \
        return list;                                                                               \
    }                                                                                              \
                                                                                                   \
    static inline Name Name##_from(T *arr, size_t len) {                                           \
        Name list = Name##_new();                                                                  \
        for (size_t i = 0; i < len; i++) {                                                         \
            Name##_push(&list, *(arr + i));                                                        \
        }                                                                                          \
        return list;                                                                               \
    }                                                                                              \
                                                                                                   \
    static inline Name Name##_slice(Name *list, int start, int end, int step) {                    \
        if (start > end || end > list->size) {                                                     \
            CCL_ERR("INVALID SLICE RANGE\n");                                                        \
        }                                          \
        if (step == 0) {CCL_ERR("STEP CAN'T BE ZERO!\n");} \
        Name result = Name##_new();                                                                \
        if (step > 0) {                                                                            \
            for (int i = start; i <=end; i += step) {                                              \
                Name##_push(&result, list->data[i]);                                               \
            }                                                                                      \
        } else {                                                                                   \
            for (int i = end; i >= start; i += step) {                                              \
                Name##_push(&result, list->data[i]);                                               \
            }                                                                                      \
        }                                                                                          \
        return result;                                                                             \
    }

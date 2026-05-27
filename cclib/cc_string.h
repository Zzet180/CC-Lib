#pragma once

#include "cc_utils.h"
#include "ccl.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#define CCS_BUILD_STRING() CCL_BUILD_LIST(char, String)

#define CCS_BUILD_UTILS()                                                                          \
    static inline bool String_Equal(String *s1, String *s2) {                                      \
        if (s1->size != s2->size)                                                                  \
            return false;                                                                          \
        for (size_t i = 0; i < s1->size; i++) {                                                    \
            if (s1->data[i] != s2->data[i])                                                        \
                return false;                                                                      \
        }                                                                                          \
        return true;                                                                               \
    }                                                                                              \
                                                                                                   \
    static inline String String_FromCstr(char *src) {                                              \
        String result = String_new();                                                              \
        size_t i = 0;                                                                              \
        while (*(src + i) != '\0') {                                                               \
            String_push(&result, *(src + i));                                                      \
            i++;                                                                                   \
        }                                                                                          \
        return result;                                                                             \
    }                                                                                              \
                                                                                                   \
    static inline void String_print(String *s, char end) {                                         \
        fwrite(s->data, sizeof(char), s->size, stdout);                                            \
        printf("%c", end);                                                                         \
    }                                                                                              \
                                                                                                   \
    static inline String String_Input(char *text) {                                                \
        String result = String_new();                                                              \
        char c;                                                                                    \
        printf("%s", text);                                                                        \
        fflush(stdout);                                                                            \
        while ((c = getchar()) != '\n') {                                                          \
            String_push(&result, (char)c);                                                         \
        }                                                                                          \
        return result;                                                                             \
    }                                                                                              \
                                                                                                   \
    static inline char *String_ToCstr(String *s) {                                                 \
        String_push(s, '\0');                                                                      \
        s->size--;                                                                                 \
        return s->data;                                                                            \
    }                                                                                              \
                                                                                                   \
    static inline String String_RemoveChar(String *s, char splt) {                                 \
        String result = String_new();                                                              \
        for (size_t i = 0; i < s->size; i++) {                                                     \
            if (s->data[i] != splt)                                                                \
                String_push(&result, s->data[i]);                                                  \
        }                                                                                          \
        return result;                                                                             \
    }                                                                                              \
                                                                                                   \
    static inline String String_TrimChar(String *s, char splt) {                                   \
                                                                                                   \
        size_t start = 0;                                                                          \
        size_t end = s->size - 1;                                                                  \
        while (start < s->size && s->data[start] == splt)                                          \
            start++;                                                                               \
        while (end > start && s->data[end] == splt)                                                \
            end--;                                                                                 \
        return String_slice(s, start, end, 1);                                                     \
    }                                                                                              \
                                                                                                   \
    static inline String String_ToUpperCase(String *s) {                                           \
        String result = String_clone(s);                                                           \
        CCU_MAP(result, toupper);                                                                  \
        return result;                                                                             \
    }                                                                                              \
                                                                                                   \
    static inline String String_ToLowerCase(String *s) {                                           \
        String result = String_clone(s);                                                           \
        CCU_MAP(result, tolower);                                                                  \
        return result;                                                                             \
    }                                                                                              \
                                                                                                   \
    static inline bool String_StartsWith(String *s, String *pre) {                                 \
        if (pre->size > s->size)                                                                   \
            return false;                                                                          \
        for (size_t i = 0; i < pre->size; i++) {                                                     \
            if (s->data[i] != pre->data[i])                                                        \
                return false;                                                                      \
        }                                                                                          \
        return true;                                                                               \
    }                                                                                              \
                                                                                                   \
    static inline bool String_EndsWith(String *s, String *suf) {                                   \
        if (suf->size > s->size)                                                                   \
            return false;                                                                          \
        size_t offset = s->size - suf->size;                                                       \
        for (size_t i = 0; i < suf->size; i++) {                                                     \
            if (s->data[offset + i] != suf->data[i])                                               \
                return false;                                                                      \
        }                                                                                          \
        return true;                                                                               \
    }

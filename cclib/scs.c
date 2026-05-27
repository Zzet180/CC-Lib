#include <stdio.h>
#include <stdlib.h>

#define SCS_HANDLE_MALLOC_ERR(Name)                                            \
        do {                                                                   \
                if (Name == NULL) {                                            \
                        fprintf(stderr, "MALLOC ERROR!\n");                    \
                        exit(EXIT_FAILURE);                                    \
                }                                                              \
        } while (0)

//Simple C String

typedef struct {
        size_t cap;
        size_t len;
        char *data;
} Scstring;

//IMPORTANT

void Scstring_grow_cap(Scstring *s) {
        s->cap *= 2;
        char *temp = realloc(s->data, sizeof(char) * s->cap);
        if (temp == NULL) {
                fprintf(stderr, "REALLOC ERROR!\n");
                exit(EXIT_FAILURE);
        }
        s->data = temp;
}

void Scstring_set_cap(Scstring *s, size_t new_cap) {
        Scstring *temp = realloc(s->data, new_cap);
        if (temp == NULL) {
            fprintf(stderr, "REALLOC ERROR!\n");
            exit(EXIT_FAILURE);
        }
}

void Scstring_free(Scstring *s) {
        free(s->data);
        free(s);
}

void Scstring_add_null(Scstring *s) {
        s->data[s->len] = '\0';
}

void Scstring_push_char(Scstring *s, char c) {
        if (s->len + 1 >= s->cap) {
                Scstring_grow_cap(s);
        }
        s->data[s->len] = c;
        s->len++;
        Scstring_add_null(s);
}

void Scstring_concat(Scstring *s1, Scstring *s2) {
        for (size_t i = 0; i < s2->len; i++) {
                Scstring_push_char(s1, s2->data[i]);
        }
}

void Scstring_concat_with_cstr(Scstring *s, const char *cstr) {
        size_t i = 0;
        while (*(cstr + i) != '\0') {
                Scstring_push_char(s, *(cstr + i));
                i++;
        }
}

//User Basic
Scstring *Scstring_new(void) {
        Scstring *str = malloc(sizeof(Scstring));
        SCS_HANDLE_MALLOC_ERR(str);
        str->len = 0;
        str->cap = 4;
        str->data = malloc(sizeof(char) * str->cap);
        SCS_HANDLE_MALLOC_ERR(str->data);
        Scstring_add_null(str);
        return str;
}


Scstring *Scstring_from(const char *cstr) {
        Scstring *str = Scstring_new();
        Scstring_concat_with_cstr(str, cstr);
        return str;
}

Scstring *Scstring_clone(Scstring *s) {
        Scstring *str = Scstring_new();
        Scstring_concat(str, s);
        return str;
}


int main(void) {
    for (int i = 0; i < 1000000; i++) {
    Scstring *name = Scstring_from("Daniel Alonso");
    Scstring *name2 = Scstring_clone(name);
    Scstring_set_cap(name2, 1028);
    printf("Hello %s\n", name2->data);
    Scstring_free(name);
    }
    return 0;
}
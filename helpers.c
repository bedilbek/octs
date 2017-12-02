//
// Created by bedilbek on 11/27/17.
//

#include "helpers.h"

int differ(const void *self, const void *b) {
    const struct Class *const *cp = self;
    assert(self && *cp && (*cp)->differ);
    return (*cp)->differ(self, b);
}

void *clone(const void *self) {
    const struct Class **class = self;
    assert(class);
    if (self && *class && (*class)->clone)
        return (*class)->clone(self);
}

void *new(const void *class, ...) {
    const struct Class *_class = class;
    void *p = calloc(1, _class->size);
    assert(p);
    *(const struct Class **) p = class;
    if (_class->ctor) {
        va_list arguments;
        va_start(arguments, _class);
        p = _class->ctor(p, &arguments);
        va_end(arguments);
    }
    return p;
}

void delete(void *self) {
    const struct Class **cp = self;
    if (self && *cp && (*cp)->dtor)
        self = (*cp)->dtor(self);
    free(self);
}

void set(void *self, char *field, void *value) {
    const struct Class *const *cp = self;
    assert(self && *cp && (*cp)->set);
    return (*cp)->set(self, field, value);
}

char *toJson(void *self) {
    const struct Class *const *cp = self;
    assert(self && *cp && (*cp)->toJson);
    return (*cp)->toJson(self);
}

size_t sizeOf(const void *self) {
    const struct Class *const *cp = self;
    assert(self && *cp);
    return (*cp)->size;
}


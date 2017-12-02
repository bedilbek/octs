//
// Created by bedilbek on 12/2/17.
//

#include "dictionary.h"

static void *Dict_ctor(void *_self, va_list *arguments) {
    struct Dict *self = _self;

    const char *key = va_arg(*arguments, const char *);
    self->key = malloc(strlen(key) + 1);
    assert(self->key);
    strcpy(self->key, key);

    const char *value = va_arg(*arguments, const char *);
    self->value = malloc(strlen(value) + 1);
    assert(self->value);
    strcpy(self->value, value);

    self->data = cJSON_CreateObject();
    assert(self->data);
    return self;
}

static void *Dict_clone(const void *_self) {
    const struct Dict *self = _self;
    return new(Dict, self->key, self->value);
}

static void Dict_set(struct Dict *_self, char *field, void *value) {
    cJSON_AddStringToObject(_self->data, field, value);
}

static int Dict_differ(const void *_self, const void *_b) {
    const struct Dict *self = _self;
    const struct Dict *b = _b;
    if (self == b)
        return 0;
    if (!b || b->class != Dict)
        return 1;
    return strcmp(self->key, b->key) && strcmp(self->value, b->value);
}

static char *Dict_toJson(struct Dict *_self) {
    assert(_self && _self->data);
    return cJSON_Print(_self->data);
}

static void *Dict_dtor(void *_self) {
    struct Dict *self = _self;
    free(self->key), self->key = 0;
    free(self->value), self->value = 0;
    return self;
}

static const struct Class _Dict = {
        sizeof(struct Dict),
        Dict_ctor,
        Dict_dtor,
        Dict_clone,
        Dict_differ,
        Dict_set,
        Dict_toJson
};

const void *Dict = &_Dict;

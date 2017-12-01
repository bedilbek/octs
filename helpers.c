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

static void *String_ctor(void *_self, va_list *arguments) {
    struct String *self = _self;
    const char *text = va_arg(*arguments, const char *);
    self->text = malloc(strlen(text) + 1);
    assert(self->text);
    strcpy(self->text, text);
    return self;
}

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

static void *String_dtor(void *_self) {
    struct String *self = _self;
    free(self->text), self->text = 0;
    return self;
}


static void *Dict_dtor(void *_self) {
    struct Dict *self = _self;
    free(self->key), self->key = 0;
    free(self->value), self->value = 0;
    return self;
}

static void *Dict_clone(const void *_self) {
    const struct Dict *self = _self;
    return new(Dict, self->key, self->value);
}

static void Dict_set(struct Dict *_self, char *field, void *value) {
    cJSON_AddStringToObject(_self->data, field, value);
}

static char *Dict_toJson(struct Dict *_self) {
    assert(_self && _self->data);
    return cJSON_Print(_self->data);
}

static void *String_clone(const void *_self) {
    const struct String *self = _self;
    return new(String, self->text);
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

static int String_differ(const void *_self, const void *_b) {
    const struct String *self = _self;
    const struct String *b = _b;
    if (self == b)
        return 0;
    if (!b || b->class != String)
        return 1;
    return strcmp(self->text, b->text);
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

static const struct Class _String = {
        sizeof(struct String),
        String_ctor,
        String_dtor,
        String_clone,
        String_differ
};

const void *String = &_String;

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


size_t sizeOf(const void *self) {
    const struct Class *const *cp = self;
    assert(self && *cp);
    return (*cp)->size;
}


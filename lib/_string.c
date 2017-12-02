//
// Created by bedilbek on 12/2/17.
//

#include "_string.h"

static void *String_ctor(void *_self, va_list *arguments) {
    struct String *self = _self;
    const char *text = va_arg(*arguments, const char *);
    self->data = cJSON_CreateObject();
    assert(self->data);
    cJSON_AddStringToObject(self->data, "string", text);
    return self;
}

static void String_set(struct String *_self, char *field, void *value) {
    assert(_self && _self->data);
    cJSON_AddStringToObject(_self->data, "string", value);
}

static char *string_get(struct String *_self) {
    assert(_self && _self->data);
    return (cJSON_GetObjectItem(_self->data, "string"))->valuestring;
}

static char *String_toJson(struct String *_self) {
    assert(_self && _self->data);
    return (cJSON_GetObjectItem(_self->data, "string"))->valuestring;
}

static void *String_clone(const void *_self) {
    const struct String *self = _self;
    return new(String, (cJSON_GetObjectItem(self->data, "string"))->valuestring);
}

static int String_differ(const void *_self, const void *_b) {
    const struct String *self = _self;
    const struct String *b = _b;
    if (self == b)
        return 0;
    if (!b || b->class != String)
        return 1;
    return cJSON_Compare(self->data, b->data, 1);
}

static void *String_dtor(void *_self) {
    struct String *self = _self;
    cJSON_free(self->data);
    return self;
}

static const struct Class _String = {
        sizeof(struct String),
        String_ctor,
        String_dtor,
        String_clone,
        String_differ,
        String_set,
        string_get,
        String_toJson
};

const void *String = &_String;

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
    if (self && *cp && (*cp)->set)
        return (*cp)->set(self, field, value);
    else return;
}

void *get(void *self, char *field) {
    const struct Class *const *cp = self;
    if (self && *cp && (*cp)->get)
        return (*cp)->get(self, field);
    return "";
}


char *toJson(void *self) {
    const struct Class *const *cp = self;
    if (self && *cp && (*cp)->toJson)
        return (*cp)->toJson(self);
    return "";
}

void *cJSON_parser(cJSON *item) {
    if (cJSON_IsBool(item))
        return item->valueint;
    if (cJSON_IsNumber(item))
        return item->valueint;
    if (cJSON_IsString(item))
        return item->valuestring;
    return "";
}

size_t sizeOf(const void *self) {
    const struct Class *const *cp = self;
    assert(self && *cp);
    return (*cp)->size;
}

void setStatus(cJSON *response, char *status_code) {
    cJSON_AddStringToObject(response, "status", status_code);
}

void setErrMsg(cJSON *response, char *status_code) {
    cJSON_AddStringToObject(response, "err_msg", status_code);
}


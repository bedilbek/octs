//
// Created by bedilbek on 11/27/17.
//

#ifndef POSTGRES_TEST_OOPDESIGNPATTERNS_H
#define POSTGRES_TEST_OOPDESIGNPATTERNS_H

#include <memory.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "cJSON.h"

#define typename(x) _Generic((x), \
    int:    "int", \
    char*:  "char", \
    char: "char", \
    double:"double", \
    default:"char")


/**
 * Class definition for oop principles
 */
struct Class {
    size_t size;

    void *(*ctor)(void *self, va_list *arguments);

    void *(*dtor)(void *self);

    void *(*clone)(const void *self);

    int (*differ)(const void *self, const void *b);

    void (*set)(void *self, char *field, void *value);

    void *(*get)(void *self, char *field);

    char *(*toJson)(void *self);
};

/**
 * Allocates dynamic memory according to size of type parameter
 *
 * @param type
 * @param ...
 * @return pointer
 */
void *new(const void *__class, ...);

/**
 * Deallocates the space of item previously allocated by new()
 *
 * @param item
 * @return void
 */
extern void delete(void *self);

void set(void *self, char *field, void *value);

void *get(void *self, char *field);

char *toJson(void *self);

void *cJSON_parser(cJSON *item);

/**
 * Checks whether given two entities differ from each other or not
 *
 * @param self
 * @param b
 * @return boolean
 */
int differ(const void *self, const void *b);

/**
 * Returns the size of the given struct
 *
 * @param void* self
 * @return size_t
 */
size_t sizeOf(const void *self);

void *clone(const void *self);


#endif //POSTGRES_TEST_OOPDESIGNPATTERNS_H
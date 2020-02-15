/*************************************************************************
  > File Name: cstl_string.c
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Mon 28 Oct 2019 02:22:11 PM CST
 ************************************************************************/
#include "cstl_string.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#define CSTL_STRING_INTERNAL_LENGTH (16)
struct cstl_string_t
{
    union {
        char buffer[CSTL_STRING_INTERNAL_LENGTH];
        char *ptr;
    } data;
    size_t length;
};
static int string_format_init_from_args(string_t *se, const char *fmt, va_list args)
{
    int ret = -1;
    if (se != NULL && fmt != NULL)
    {
        va_list arg_save;
        va_copy(arg_save, args);
        int size = vsnprintf(NULL, 0, fmt, args);
        if (size < CSTL_STRING_INTERNAL_LENGTH)
        {
            vsnprintf((char *)&se->data.buffer, size + 1, fmt, arg_save);
            se->data.buffer[size] = '\0';
        }
        else
        {
            se->data.ptr = (char *)calloc(sizeof(char), size + 1);
            vsnprintf(se->data.ptr, size + 1, fmt, arg_save);
            se->data.ptr[size] = '\0';
        }
        se->length = size;
        ret = 0;
    }
    return ret;
}
int string_replace(string_t *se, const char *value)
{
    int ret = -1;
    if (se != NULL && value != NULL)
    {
        size_t len = strlen(value);
        size_t cur_len = string_length(se);
        if (len >= CSTL_STRING_INTERNAL_LENGTH)
        {
            if (cur_len > CSTL_STRING_INTERNAL_LENGTH)
            {
                if (len > cur_len)
                {
                    se->data.ptr = realloc(se->data.ptr, len + 1);
                    assert(se->data.ptr != NULL);
                }
                strncpy(se->data.ptr, value, len);
            }
        }
        else
        {
            strncpy((char *)&se->data.buffer, value, len);
        }
        se->data.ptr[len] = '\0';
        ret = 0;
    }
    return ret;
}
int string_copy_substring(string_t *se, const char *str, size_t n)
{
    if (se != NULL && str != NULL && n > 0)
    {
        size_t len = strlen(str);
        se->length = (n > len) ? len : n;
        bool flag = (len < CSTL_STRING_INTERNAL_LENGTH) ? true : false;
        if (flag)
        {
            memcpy(&se->data.buffer, str, n);
            se->data.buffer[se->length] = '\0';
            return 0;
        }
        se->data.ptr = (char *)calloc(1, se->length + 1);
        memcpy(&se->data.buffer, str, se->length);
        return 0;
    }
}

int string_init(string_t *se, const char *value)
{
    if (se != NULL)
    {
        if (value != NULL)
        {
            // CSTL_STRING_INTERNAL_LENGTH
            size_t length = strlen(value);
            bool flag = (length < CSTL_STRING_INTERNAL_LENGTH) ? true : false;
            se->length = length;
            if (flag)
            {
                memcpy(&se->data.buffer, value, length);
                se->data.buffer[length] = '\0';
                return 0;
            }
            se->data.ptr = strdup(value);
        }
        else
        {
            se->length = 0;
            se->data.ptr = NULL;
        }
        return 0;
    }
    return -1;
}
int string_reverse(string_t *se)
{
    if (se != NULL)
    {
        char *ptr = (se->length > CSTL_STRING_INTERNAL_LENGTH) ? (se->data.ptr) : ((char *)&se->data.buffer);
        size_t start = 0;
        size_t end = se->length - 1;
        while (start <= end)
        {
            char tmp = ptr[end];
            ptr[end--] = ptr[start];
            ptr[start++] = tmp;
            
        }
        return 0;
    }
    return -1;
}
string_t *string_format_create(const char *fmt, ...)
{

    string_t *se = (string_t *)calloc(1, sizeof(string_t));
    if (se != NULL)
    {

        va_list args;
        va_start(args, fmt);
        int ret = string_format_init_from_args(se, fmt, args);
        va_end(args);
        if (ret != 0)
        {
            free(se);
            se = NULL;
        }
    }
    return se;
}

int string_format_init(string_t *se, const char *fmt, ...)
{
    int ret = -1;
    if (se != NULL && fmt != NULL)
    {

        va_list args;
        va_start(args, fmt);
        ret = string_format_init_from_args(se, fmt, args);
        va_end(args);
    }
    return ret;
}
inline string_t *string_create(const char *value)
{
    string_t *se = NULL;
    if (value != NULL)
    {
        se = (string_t *)calloc(1, sizeof(string_t));
        if (string_init(se, value) != 0)
        {
            free(se);
            se = NULL;
        }
    }
    return se;
}
const char *string_at(string_t *se, size_t index)
{
    if (se != NULL && index < se->length)
    {
        return string_value(se) + index;
    }
    return NULL;
}
inline size_t string_length(string_t *se)
{
    if (se != NULL)
    {
        return se->length;
    }
    return 0;
}
const char *string_value(string_t *se)
{
    char *value = NULL;
    if (se != NULL)
    {
        if (se->length > 0 && se->length < CSTL_STRING_INTERNAL_LENGTH)
        {
            value = (char *)&se->data.buffer;
        }
        else if (se->length > 0 && se->length >= CSTL_STRING_INTERNAL_LENGTH)
        {
            value = se->data.ptr;
        }
    }
    return value;
}
void string_print(string_t *se)
{
    if (se != NULL)
    {
        const char *value = string_value(se);
        if (value != NULL)
        {
            fprintf(stdout, "value:%s,length:%d\n", value, se->length);
        }
    }
}
inline void string_destroy(string_t *se)
{
    if (se != NULL)
    {
        string_deinit(se);
        free(se);
        se = NULL;
    }
}
int string_copy(string_t *dest, string_t *src)
{
    if (dest != NULL && src != NULL)
    {
        const char *value = string_value(src);
        return string_init(dest, value);
    }
    return -1;
}
inline void string_deinit(string_t *se)
{
    if (se != NULL && se->length > 0)
    {
        if (se->length >= CSTL_STRING_INTERNAL_LENGTH)
        {
            free(se->data.ptr);
            se->length = 0;
        }
    }
}
#ifdef CSTL_STRING_TEST
int main(void)
{

    string_t *st1 = string_format_create("%s fuck you!", "hello");
    assert(st1 != NULL);
    string_print(st1);
    string_t st2;
    string_format_init(&st2, "%dyou!", 1024);
    string_print(&st2);
    string_reverse(&st2);
    string_print(&st2);
    string_deinit(&st2);
    string_destroy(st1);
    return 0;
}
#endif
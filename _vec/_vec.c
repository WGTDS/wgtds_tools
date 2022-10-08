/******************************************************************************
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <https://unlicense.org>
 *****************************************************************************/
/*-----------------------------------------------------------------------------
    Mock-up Vector-like Functions for C.

    Author  : White Guy That Don't Smile
    Date    : 2022/05/20, Friday, May 20th; 0908 HOURS
-----------------------------------------------------------------------------*/
#include "_vec.h"

/*==============================================================
    Vector Error
==============================================================*/
const char *_vsubject[2] =
{
    "information",
    "data"
};

void _verror( int status )
{
    printf( "/// ERROR ///\n>>> Vector " );
    printf( "%s", _vsubject[status] );
    printf( " is NULL!\n" );
    exit( 1 );
}

#ifndef USE_VECUTIL_MACROS
/*==============================================================
    Vector Free
==============================================================*/
vec_t *vfree( vec_t *vec )
{
    free( vec->org );
    free( vec );
    return (vec_t *)0;
}

/*==============================================================
    Vector Allocate
==============================================================*/
vec_t *valloc( const size_t size )
{
    vec_t *vec = (vec_t *)calloc( 1, sizeof(vec_t) );

    if ( vec == (vec_t *)0 ) {
        _verror( NULL_VEC_INFO );
    }
    else {
        vec->sz  = 0x10000 * size;
        vec->wd  = size;
        vec->org = malloc( vec->sz );

        if ( vec->org == (void *)0 ) {
            _verror( NULL_VEC_DATA );
        }
        else {
            vec->cur = vec->org;
            vec->nxt = (void *)((size_t)vec->cur + vec->sz);
        }
    }

    return vec;
}

/*==============================================================
    Vector Reallocate
==============================================================*/
vec_t *_vrealloc( vec_t *vec )
{
    if ( vec == (vec_t *)0 ) {
        _verror( NULL_VEC_INFO );
    }
    else {
        vec->sz += (0x10000 * vec->wd);
        vec->org = realloc( vec->org, vec->sz );

        if ( vec->org == (void *)0 ) {
            _verror( NULL_VEC_DATA );
        }
        else {
            vec->cur = (void *)((size_t)vec->org + (vec->ct * vec->wd));
            vec->nxt = (void *)((size_t)vec->org + vec->sz);
        }
    }

    return vec;
}

/*==============================================================
    Vector Append
==============================================================*/
void vappend( vec_t *vec, const void *data )
{
    if ( vec == (vec_t *)0 ) {
        _verror( NULL_VEC_INFO );
    }
    else {
        if ( vec->cur < vec->nxt ) {
            const char *ct = (const char *)data;
            char *st = (char *)vec->cur;
            size_t n = vec->wd;

            while ( n-- ) {
                *st++ = *ct++;
            }

            vec->cur = (void *)st;
            vec->ct++;
        }
        else {
            vec = _vrealloc( vec );
            vappend( vec, data );
        }
    }

    return;
}

/*==============================================================
    Vector Set Value
==============================================================*/
void vsetval( vec_t *vec, const size_t offset, const void *data )
{
    const char *ct = (const char *)data;
    char *st = (char *)((size_t)vec->org + (offset * vec->wd));
    size_t n = vec->wd;

    while ( n-- ) {
        *st++ = *ct++;
    }

    return;
}

/*==============================================================
    Vector Get Value
==============================================================*/
void vgetval( vec_t *vec, const void *data )
{
    if ( vec == (vec_t *)0 ) {
        _verror( NULL_VEC_INFO );
    }
    else {
        const char *ct = (const char *)vec->cur;
        char *st = (char *)data;
        size_t n = vec->wd;

        while ( n-- ) {
            *st++ = *ct++;
        }

        vec->cur = (void *)ct;
    }

    return;
}
#endif

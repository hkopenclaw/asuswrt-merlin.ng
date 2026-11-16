/* Copyright (c) 2020 tevador <tevador@gmail.com> */
/* See LICENSE for licensing information */

#ifndef CONTEXT_H
#define CONTEXT_H

#include <equix.h>
#include <hashx.h>
#include "solver_heap.h"

/* NOTE: the typedefs solver_heap and equix_ctx are already provided by
 * solver_heap.h and equix.h (included above); redeclaring them here breaks
 * pre-C11 compilers (duplicate typedef is only legal since C11). */
struct equix_ctx {
	hashx_ctx* hash_func;
	solver_heap* heap;
	equix_ctx_flags flags;
};

#endif

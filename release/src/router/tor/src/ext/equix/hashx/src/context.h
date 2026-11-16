/* Copyright (c) 2020 tevador <tevador@gmail.com> */
/* See LICENSE for licensing information */

#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdbool.h>

#include "hashx.h"
#include "blake2.h"
#include "siphash.h"
#include "program.h"

#ifdef __cplusplus
extern "C" {
#endif

HASHX_PRIVATE extern const blake2b_param hashx_blake2_params;

#ifdef __cplusplus
}
#endif

/* HashX context. */
/* NOTE: the typedefs hashx_program and hashx_ctx are already provided by
 * program.h and hashx.h (included above); redeclaring them here breaks
 * pre-C11 compilers (duplicate typedef is only legal since C11). */
struct hashx_ctx {
	uint8_t* compiler_mem;
	hashx_type ctx_type;
	hashx_type func_type;
	hashx_program program;
#ifndef HASHX_BLOCK_MODE
	siphash_state keys;
#else
	blake2b_param params;
#endif
};

#endif

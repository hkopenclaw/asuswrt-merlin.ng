/* Copyright (c) 2023, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file conflux_util.h
 * \brief Header file for conflux_util.c.
 **/

#ifndef TOR_CONFLUX_UTIL_H
#define TOR_CONFLUX_UTIL_H

/* Forward decls are provided by or.h and conflux.h. They cannot be
 * repeated here: duplicate typedefs are legal in C11 but rejected by
 * pre-C11 compilers (e.g. GCC 4.5.3, which has no C11 mode). */
#include "core/or/or.h"
#include "core/or/conflux.h"

/* True iff the given circuit_t circ is conflux related. */
static inline bool
CIRCUIT_IS_CONFLUX(const circuit_t *circ)
{
  if (circ->conflux_pending_nonce) {
    if (CIRCUIT_IS_ORIGIN(circ))
      tor_assert_nonfatal(circ->purpose == CIRCUIT_PURPOSE_CONFLUX_UNLINKED);
    return true;
  } else if (circ->conflux) {
    if (CIRCUIT_IS_ORIGIN(circ))
      tor_assert_nonfatal(circ->purpose == CIRCUIT_PURPOSE_CONFLUX_LINKED);
    return true;
  } else {
    tor_assert_nonfatal(circ->purpose != CIRCUIT_PURPOSE_CONFLUX_LINKED);
    tor_assert_nonfatal(circ->purpose != CIRCUIT_PURPOSE_CONFLUX_UNLINKED);
    return false;
  }
}

const uint8_t *conflux_get_nonce(const circuit_t *circ);
uint64_t conflux_get_circ_rtt(const circuit_t *circ);

int circuit_get_package_window(circuit_t *circ,
                               const crypt_path_t *cpath);
bool conflux_can_send(conflux_t *cfx);

bool edge_uses_cpath(const edge_connection_t *conn,
                     const crypt_path_t *cpath);
crypt_path_t *conflux_get_destination_hop(circuit_t *circ);
bool conflux_validate_source_hop(circuit_t *in_circ,
                            crypt_path_t *layer_hint);
uint64_t edge_get_max_rtt(const edge_connection_t *stream);
bool relay_crypt_from_last_hop(const origin_circuit_t *circ,
                          const crypt_path_t *layer_hint);

void conflux_update_p_streams(origin_circuit_t *, edge_connection_t *);
void conflux_update_half_streams(origin_circuit_t *, smartlist_t *);
void conflux_update_n_streams(or_circuit_t *, edge_connection_t *);
void conflux_update_resolving_streams(or_circuit_t *, edge_connection_t *);
void conflux_sync_circ_fields(conflux_t *cfx, origin_circuit_t *ref_circ);
void conflux_validate_stream_lists(const conflux_t *cfx);
void conflux_validate_legs(const conflux_t *cfx);

#endif /* TOR_CONFLUX_UTIL_H */


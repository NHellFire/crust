/*
 * Copyright © 2017-2019 The Crust Firmware Authors.
 * SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0-only
 */

#ifndef LIB_BITFIELD_H
#define LIB_BITFIELD_H

#include <stdint.h>
#include <util.h>

/**
 * Get the value in a bitfield.
 *
 * @param word  A word containing a bitfield.
 * @param start The offset of the starting bit (LSB) of the bitfield.
 * @param width The width of the bitfield in bits.
 */
static inline uint32_t
bitfield_get(uint32_t word, uint32_t start, uint32_t width)
{
	return (word >> start) & (BIT(width) - 1);
}

/**
 * Set the value in a bitfield.
 *
 * @param word  A word containing a bitfield.
 * @param start The offset of the starting bit (LSB) of the bitfield.
 * @param width The width of the bitfield in bits.
 * @param value The value to place in the bitfield.
 * @return      The original word, with the value of the bitfield replaced.
 */
static inline uint32_t
bitfield_set(uint32_t word, uint32_t start, uint32_t width, uint32_t value)
{
	return word ^ ((value << start ^ word) & ((BIT(width) - 1) << start));
}

#endif /* LIB_BITFIELD_H */

/*
 * Copyright © 2017-2020 The Crust Firmware Authors.
 * SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0-only
 */

#include <debug.h>
#include <serial.h>
#include <spr.h>
#include <system.h>

noreturn void main(uint32_t exception);

noreturn void
main(uint32_t exception)
{
	/* Enable logging via serial port as soon as possible. */
	serial_init();

	if (exception) {
		error("Exception %u at %p!",
		      exception, (void *)mfspr(SPR_SYS_EPCR_ADDR(0)));
	}

	debug_print_sprs();

	/* Cede control to the system state machine (never returns). */
	system_state_machine();
}

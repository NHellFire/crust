/*
 * Copyright © 2017 Samuel Holland <samuel@sholland.org>
 * SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0)
 */

#include <dm.h>
#include <drivers/clock/sunxi-ccu.h>
#include <platform/ccu.h>
#include <platform/devices.h>
#include <platform/irq.h>

extern struct driver sun4i_intc_driver;
extern struct driver sunxi_ccu_driver;

static struct device ccu    __device;
static struct device r_intc __device;

static struct device ccu = {
	.name    = "ccu",
	.address = DEV_CCU,
	.drv     = &sunxi_ccu_driver,
};

static struct device r_intc = {
	.name    = "r_intc",
	.address = DEV_R_INTC,
	.drv     = &sun4i_intc_driver,
};

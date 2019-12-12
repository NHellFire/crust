/*
 * Copyright © 2017-2019 The Crust Firmware Authors.
 * SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0-only
 */

#include <device.h>
#include <error.h>
#include <pmic.h>
#include <regulator.h>
#include <pmic/dummy.h>
#include <regulator/sy8106a.h>

static inline struct dummy_pmic *
to_dummy_pmic(struct device *dev)
{
	return container_of(dev, struct dummy_pmic, dev);
}

static int
dummy_pmic_power_off(struct device *dev)
{
	struct dummy_pmic *self = to_dummy_pmic(dev);
	int err;

	/* Turn CPU power off. */
	if (self->vdd_cpux.dev &&
	    (err = regulator_disable(self->vdd_cpux.dev, self->vdd_cpux.id)))
		return err;

	return SUCCESS;
}

static int
dummy_pmic_power_on(struct device *dev)
{
	struct dummy_pmic *self = to_dummy_pmic(dev);
	int err;

	/* Turn CPU power on. */
	if (self->vdd_cpux.dev &&
	    (err = regulator_enable(self->vdd_cpux.dev, self->vdd_cpux.id)))
		return err;

	return SUCCESS;
}

static int
dummy_pmic_probe(struct device *dev)
{
	struct dummy_pmic *self = to_dummy_pmic(dev);

	if (self->vdd_cpux.dev)
		device_probe(self->vdd_cpux.dev);

	return SUCCESS;
}

static const struct pmic_driver dummy_pmic_driver = {
	.drv = {
		.probe = dummy_pmic_probe,
	},
	.ops = {
		.reset    = dummy_pmic_power_on,
		.resume   = dummy_pmic_power_on,
		.shutdown = dummy_pmic_power_off,
		.suspend  = dummy_pmic_power_off,
	},
};

struct dummy_pmic dummy_pmic = {
	.dev = {
		.name = "dummy-pmic",
		.drv  = &dummy_pmic_driver.drv,
	},
#if CONFIG_REGULATOR_SY8106A
	.vdd_cpux = {
		.dev = &sy8106a.dev,
		.id  = SY8106A_REGL_VOUT,
	},
#endif
};

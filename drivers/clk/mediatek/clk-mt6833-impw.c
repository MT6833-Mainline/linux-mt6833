// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2020 MediaTek Inc.
 */

#include <linux/clk-provider.h>
#include <linux/platform_device.h>
#include <linux/module.h>

#include "clk-mtk.h"
#include "clk-gate.h"

#include <dt-bindings/clock/mediatek,mt6833-clk.h>

static const struct mtk_gate_regs impw_cg_regs = {
	.set_ofs = 0xe08,
	.clr_ofs = 0xe04,
	.sta_ofs = 0xe00,
};

#define GATE_IMPW(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &impw_cg_regs,			\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	}

static const struct mtk_gate impw_clks[] = {
	GATE_IMPW(CLK_IMPW_AP_CLOCK_RO_I2C0, "impw_ap_i2c0", "i2c_pseudo", 0),
	GATE_IMPW(CLK_IMPW_AP_CLOCK_RO_I2C5, "impw_ap_i2c5", "i2c_pseudo", 1),
	GATE_IMPW(CLK_IMPW_AP_CLOCK_RO_I2C7, "impw_ap_i2c7", "i2c_pseudo", 2),
};

static const struct mtk_clk_desc impw_desc = {
	.clks = impw_clks,
	.num_clks = ARRAY_SIZE(impw_clks),
};

static const struct of_device_id of_match_clk_mt6833_impw[] = {
	{ .compatible = "mediatek,mt6833-imp-iic-wrap-w", .data = &impw_desc },
	{}
};
MODULE_DEVICE_TABLE(of, of_match_clk_mt6833_impw);

static struct platform_driver clk_mt6833_impw_drv = {
	.probe = mtk_clk_simple_probe,
	.remove = mtk_clk_simple_remove,
	.driver = {
		.name = "clk-mt6833-impw",
		.of_match_table = of_match_clk_mt6833_impw,
	},
};

module_platform_driver(clk_mt6833_impw_drv);

MODULE_DESCRIPTION("MediaTek MT6833 imp_iic_wrap_w clocks driver");
MODULE_LICENSE("GPL");

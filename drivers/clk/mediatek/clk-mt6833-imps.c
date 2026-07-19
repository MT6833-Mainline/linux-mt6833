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

static const struct mtk_gate_regs imps_cg_regs = {
	.set_ofs = 0xe08,
	.clr_ofs = 0xe04,
	.sta_ofs = 0xe00,
};

#define GATE_IMPS(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &imps_cg_regs,			\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	}

static const struct mtk_gate imps_clks[] = {
	GATE_IMPS(CLK_IMPS_AP_CLOCK_RO_I2C8, "imps_ap_i2c8", "i2c_pseudo", 0),
	GATE_IMPS(CLK_IMPS_AP_CLOCK_RO_I2C9, "imps_ap_i2c9", "i2c_pseudo", 1),
};

static const struct mtk_clk_desc imps_desc = {
	.clks = imps_clks,
	.num_clks = ARRAY_SIZE(imps_clks),
};

static const struct of_device_id of_match_clk_mt6833_imps[] = {
	{ .compatible = "mediatek,mt6833-imp-iic-wrap-s", .data = &imps_desc },
	{}
};
MODULE_DEVICE_TABLE(of, of_match_clk_mt6833_imps);

static struct platform_driver clk_mt6833_imps_drv = {
	.probe = mtk_clk_simple_probe,
	.remove = mtk_clk_simple_remove,
	.driver = {
		.name = "clk-mt6833-imps",
		.of_match_table = of_match_clk_mt6833_imps,
	},
};

module_platform_driver(clk_mt6833_imps_drv);

MODULE_DESCRIPTION("MediaTek MT6833 imp_iic_wrap_s clocks driver");
MODULE_LICENSE("GPL");

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

static const struct mtk_gate_regs impn_cg_regs = {
	.set_ofs = 0xe08,
	.clr_ofs = 0xe04,
	.sta_ofs = 0xe00,
};

#define GATE_IMPN(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &impn_cg_regs,			\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	}

static const struct mtk_gate impn_clks[] = {
	GATE_IMPN(CLK_IMPN_AP_CLOCK_RO_I2C6, "impn_ap_i2c6", "i2c_pseudo", 0),
};

static const struct mtk_clk_desc impn_desc = {
	.clks = impn_clks,
	.num_clks = ARRAY_SIZE(impn_clks),
};

static const struct of_device_id of_match_clk_mt6833_impn[] = {
	{ .compatible = "mediatek,mt6833-imp-iic-wrap-n", .data = &impn_desc },
	{}
};
MODULE_DEVICE_TABLE(of, of_match_clk_mt6833_impn);

static struct platform_driver clk_mt6833_impn_drv = {
	.probe = mtk_clk_simple_probe,
	.remove = mtk_clk_simple_remove,
	.driver = {
		.name = "clk-mt6833-impn",
		.of_match_table = of_match_clk_mt6833_impn,
	},
};

module_platform_driver(clk_mt6833_impn_drv);

MODULE_DESCRIPTION("MediaTek MT6833 imp_iic_wrap_n clocks driver");
MODULE_LICENSE("GPL");

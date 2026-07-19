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

static const struct mtk_gate_regs impws_cg_regs = {
	.set_ofs = 0xe08,
	.clr_ofs = 0xe04,
	.sta_ofs = 0xe00,
};

#define GATE_IMPWS(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &impws_cg_regs,			\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	}

static const struct mtk_gate impws_clks[] = {
	GATE_IMPWS(CLK_IMPWS_AP_CLOCK_RO_I2C1, "impws_ap_i2c1", "i2c_pseudo", 0),
	GATE_IMPWS(CLK_IMPWS_AP_CLOCK_RO_I2C2, "impws_ap_i2c2", "i2c_pseudo", 1),
	GATE_IMPWS(CLK_IMPWS_AP_CLOCK_RO_I2C4, "impws_ap_i2c4", "i2c_pseudo", 2),
};

static const struct mtk_clk_desc impws_desc = {
	.clks = impws_clks,
	.num_clks = ARRAY_SIZE(impws_clks),
};

static const struct of_device_id of_match_clk_mt6833_impws[] = {
	{ .compatible = "mediatek,mt6833-imp-iic-wrap-ws", .data = &impws_desc },
	{}
};
MODULE_DEVICE_TABLE(of, of_match_clk_mt6833_impws);

static struct platform_driver clk_mt6833_impws_drv = {
	.probe = mtk_clk_simple_probe,
	.remove = mtk_clk_simple_remove,
	.driver = {
		.name = "clk-mt6833-impws",
		.of_match_table = of_match_clk_mt6833_impws,
	},
};

module_platform_driver(clk_mt6833_impws_drv);

MODULE_DESCRIPTION("MediaTek MT6833 imp_iic_wrap_ws clocks driver");
MODULE_LICENSE("GPL");

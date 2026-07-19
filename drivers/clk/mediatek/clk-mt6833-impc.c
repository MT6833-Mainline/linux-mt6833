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

static const struct mtk_gate_regs impc_cg_regs = {
	.set_ofs = 0xe08,
	.clr_ofs = 0xe04,
	.sta_ofs = 0xe00,
};

#define GATE_IMPC(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &impc_cg_regs,			\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	}

static const struct mtk_gate impc_clks[] = {
	GATE_IMPC(CLK_IMPC_AP_CLOCK_RO_I2C10, "impc_ap_i2c10", "i2c_pseudo", 0),
	GATE_IMPC(CLK_IMPC_AP_CLOCK_RO_I2C11, "impc_ap_i2c11", "i2c_pseudo", 1),
};

static const struct mtk_clk_desc impc_desc = {
	.clks = impc_clks,
	.num_clks = ARRAY_SIZE(impc_clks),
};

static const struct of_device_id of_match_clk_mt6833_impc[] = {
	{ .compatible = "mediatek,mt6833-imp-iic-wrap-c", .data = &impc_desc },
	{}
};
MODULE_DEVICE_TABLE(of, of_match_clk_mt6833_impc);

static struct platform_driver clk_mt6833_impc_drv = {
	.probe = mtk_clk_simple_probe,
	.remove = mtk_clk_simple_remove,
	.driver = {
		.name = "clk-mt6833-impc",
		.of_match_table = of_match_clk_mt6833_impc,
	},
};

module_platform_driver(clk_mt6833_impc_drv);

MODULE_DESCRIPTION("MediaTek MT6833 imp_iic_wrap_c clocks driver");
MODULE_LICENSE("GPL");

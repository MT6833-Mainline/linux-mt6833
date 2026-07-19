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

static const struct mtk_gate_regs impe_cg_regs = {
	.set_ofs = 0xe08,
	.clr_ofs = 0xe04,
	.sta_ofs = 0xe00,
};

#define GATE_IMPE(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &impe_cg_regs,			\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	}

static const struct mtk_gate impe_clks[] = {
	GATE_IMPE(CLK_IMPE_AP_CLOCK_RO_I2C3, "impe_ap_i2c3", "i2c_pseudo", 0),
};

static const struct mtk_clk_desc impe_desc = {
	.clks = impe_clks,
	.num_clks = ARRAY_SIZE(impe_clks),
};

static const struct of_device_id of_match_clk_mt6833_impe[] = {
	{ .compatible = "mediatek,mt6833-imp-iic-wrap-e", .data = &impe_desc },
	{}
};
MODULE_DEVICE_TABLE(of, of_match_clk_mt6833_impe);

static struct platform_driver clk_mt6833_impe_drv = {
	.probe = mtk_clk_simple_probe,
	.remove = mtk_clk_simple_remove,
	.driver = {
		.name = "clk-mt6833-impe",
		.of_match_table = of_match_clk_mt6833_impe,
	},
};

module_platform_driver(clk_mt6833_impe_drv);

MODULE_DESCRIPTION("MediaTek MT6833 imp_iic_wrap_e clocks driver");
MODULE_LICENSE("GPL");

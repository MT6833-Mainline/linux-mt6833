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

static const struct mtk_gate_regs imgsys1_cg_regs = {
	.set_ofs = 0x4,
	.clr_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_IMGSYS1(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &imgsys1_cg_regs,		\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	}

static const struct mtk_gate imgsys1_clks[] = {
	GATE_IMGSYS1(CLK_IMGSYS1_LARB9, "imgsys1_larb9", "img1_ck", 0),
	GATE_IMGSYS1(CLK_IMGSYS1_LARB10, "imgsys1_larb10", "img1_ck", 1),
	GATE_IMGSYS1(CLK_IMGSYS1_DIP, "imgsys1_dip", "img1_ck", 2),
	GATE_IMGSYS1(CLK_IMGSYS1_GALS, "imgsys1_gals", "img1_ck", 12),
};

static const struct mtk_clk_desc imgsys1_desc = {
	.clks = imgsys1_clks,
	.num_clks = ARRAY_SIZE(imgsys1_clks),
};

static const struct of_device_id of_match_clk_mt6833_imgsys1[] = {
	{ .compatible = "mediatek,mt6833-imgsys1", .data = &imgsys1_desc },
	{}
};
MODULE_DEVICE_TABLE(of, of_match_clk_mt6833_imgsys1);

static struct platform_driver clk_mt6833_imgsys1_drv = {
	.probe = mtk_clk_simple_probe,
	.remove = mtk_clk_simple_remove,
	.driver = {
		.name = "clk-mt6833-imgsys1",
		.of_match_table = of_match_clk_mt6833_imgsys1,
	},
};

module_platform_driver(clk_mt6833_imgsys1_drv);

MODULE_DESCRIPTION("MediaTek MT6833 imgsys1 clocks driver");
MODULE_LICENSE("GPL");

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

static const struct mtk_gate_regs imgsys2_cg_regs = {
	.set_ofs = 0x4,
	.clr_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_IMGSYS2(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &imgsys2_cg_regs,		\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	}

static const struct mtk_gate imgsys2_clks[] = {
	GATE_IMGSYS2(CLK_IMGSYS2_LARB9, "imgsys2_larb9", "img1_ck", 0),
	GATE_IMGSYS2(CLK_IMGSYS2_LARB10, "imgsys2_larb10", "img1_ck", 1),
	GATE_IMGSYS2(CLK_IMGSYS2_MFB, "imgsys2_mfb", "img1_ck", 6),
	GATE_IMGSYS2(CLK_IMGSYS2_WPE, "imgsys2_wpe", "img1_ck", 7),
	GATE_IMGSYS2(CLK_IMGSYS2_MSS, "imgsys2_mss", "img1_ck", 8),
	GATE_IMGSYS2(CLK_IMGSYS2_GALS, "imgsys2_gals", "img1_ck", 12),
};

static const struct mtk_clk_desc imgsys2_desc = {
	.clks = imgsys2_clks,
	.num_clks = ARRAY_SIZE(imgsys2_clks),
};

static const struct of_device_id of_match_clk_mt6833_imgsys2[] = {
	{ .compatible = "mediatek,mt6833-imgsys2", .data = &imgsys2_desc },
	{}
};
MODULE_DEVICE_TABLE(of, of_match_clk_mt6833_imgsys2);

static struct platform_driver clk_mt6833_imgsys2_drv = {
	.probe = mtk_clk_simple_probe,
	.remove = mtk_clk_simple_remove,
	.driver = {
		.name = "clk-mt6833-imgsys2",
		.of_match_table = of_match_clk_mt6833_imgsys2,
	},
};

module_platform_driver(clk_mt6833_imgsys2_drv);

MODULE_DESCRIPTION("MediaTek MT6833 imgsys2 clocks driver");
MODULE_LICENSE("GPL");

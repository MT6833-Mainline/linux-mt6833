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

static const struct mtk_gate_regs venc_cg_regs = {
	.set_ofs = 0x4,
	.clr_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_VENC(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &venc_cg_regs,			\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_setclr_inv,	\
	}

static const struct mtk_gate venc_clks[] = {
	GATE_VENC(CLK_VENC_SET0_LARB, "venc_set0_larb", "venc_ck", 0),
	GATE_VENC(CLK_VENC_SET1_VENC, "venc_set1_venc", "venc_ck", 4),
	GATE_VENC(CLK_VENC_SET2_JPGENC, "jpgenc", "venc_ck", 8),
	GATE_VENC(CLK_VENC_SET5_GALS, "venc_set5_gals", "venc_ck", 28),
};

static const struct mtk_clk_desc venc_desc = {
	.clks = venc_clks,
	.num_clks = ARRAY_SIZE(venc_clks),
};

static const struct of_device_id of_match_clk_mt6833_venc[] = {
	{ .compatible = "mediatek,mt6833-venc-gcon", .data = &venc_desc },
	{}
};
MODULE_DEVICE_TABLE(of, of_match_clk_mt6833_venc);

static struct platform_driver clk_mt6833_venc_drv = {
	.probe = mtk_clk_simple_probe,
	.remove = mtk_clk_simple_remove,
	.driver = {
		.name = "clk-mt6833-venc",
		.of_match_table = of_match_clk_mt6833_venc,
	},
};

module_platform_driver(clk_mt6833_venc_drv);

MODULE_DESCRIPTION("MediaTek MT6833 venc_gcon clocks driver");
MODULE_LICENSE("GPL");

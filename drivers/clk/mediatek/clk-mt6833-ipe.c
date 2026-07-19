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

static const struct mtk_gate_regs ipe_cg_regs = {
	.set_ofs = 0x4,
	.clr_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_IPE(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &ipe_cg_regs,			\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	}

static const struct mtk_gate ipe_clks[] = {
	GATE_IPE(CLK_IPE_LARB19, "ipe_larb19", "ipe_ck", 0),
	GATE_IPE(CLK_IPE_LARB20, "ipe_larb20", "ipe_ck", 1),
	GATE_IPE(CLK_IPE_SMI_SUBCOM, "ipe_smi_subcom", "ipe_ck", 2),
	GATE_IPE(CLK_IPE_FD, "ipe_fd", "ipe_ck", 3),
	GATE_IPE(CLK_IPE_FE, "ipe_fe", "ipe_ck", 4),
	GATE_IPE(CLK_IPE_RSC, "ipe_rsc", "ipe_ck", 5),
	GATE_IPE(CLK_IPE_DPE, "ipe_dpe", "dpe_ck", 6),
	GATE_IPE(CLK_IPE_GALS, "ipe_gals", "img2_ck", 8),
};

static const struct mtk_clk_desc ipe_desc = {
	.clks = ipe_clks,
	.num_clks = ARRAY_SIZE(ipe_clks),
};

static const struct of_device_id of_match_clk_mt6833_ipe[] = {
	{ .compatible = "mediatek,mt6833-ipesys", .data = &ipe_desc },
	{}
};
MODULE_DEVICE_TABLE(of, of_match_clk_mt6833_ipe);

static struct platform_driver clk_mt6833_ipe_drv = {
	.probe = mtk_clk_simple_probe,
	.remove = mtk_clk_simple_remove,
	.driver = {
		.name = "clk-mt6833-ipe",
		.of_match_table = of_match_clk_mt6833_ipe,
	},
};

module_platform_driver(clk_mt6833_ipe_drv);

MODULE_DESCRIPTION("MediaTek MT6833 ipesys clocks driver");
MODULE_LICENSE("GPL");

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

static const struct mtk_gate_regs cam_rb_cg_regs = {
	.set_ofs = 0x4,
	.clr_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_CAM_RB(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &cam_rb_cg_regs,		\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	}

static const struct mtk_gate cam_rb_clks[] = {
	GATE_CAM_RB(CLK_CAM_RB_LARBX, "cam_rb_larbx", "cam_ck", 0),
	GATE_CAM_RB(CLK_CAM_RB_CAM, "cam_rb_cam", "cam_ck", 1),
	GATE_CAM_RB(CLK_CAM_RB_CAMTG, "cam_rb_camtg", "cam_ck", 2),
};

static const struct mtk_clk_desc cam_rb_desc = {
	.clks = cam_rb_clks,
	.num_clks = ARRAY_SIZE(cam_rb_clks),
};

static const struct of_device_id of_match_clk_mt6833_cam_rb[] = {
	{ .compatible = "mediatek,mt6833-camsys-rawb", .data = &cam_rb_desc },
	{}
};
MODULE_DEVICE_TABLE(of, of_match_clk_mt6833_cam_rb);

static struct platform_driver clk_mt6833_cam_rb_drv = {
	.probe = mtk_clk_simple_probe,
	.remove = mtk_clk_simple_remove,
	.driver = {
		.name = "clk-mt6833-cam_rb",
		.of_match_table = of_match_clk_mt6833_cam_rb,
	},
};

module_platform_driver(clk_mt6833_cam_rb_drv);

MODULE_DESCRIPTION("MediaTek MT6833 camsys_rawb clocks driver");
MODULE_LICENSE("GPL");

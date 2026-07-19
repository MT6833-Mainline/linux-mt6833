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

static const struct mtk_gate_regs cam_ra_cg_regs = {
	.set_ofs = 0x4,
	.clr_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_CAM_RA(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &cam_ra_cg_regs,		\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	}

static const struct mtk_gate cam_ra_clks[] = {
	GATE_CAM_RA(CLK_CAM_RA_LARBX, "cam_ra_larbx", "cam_ck", 0),
	GATE_CAM_RA(CLK_CAM_RA_CAM, "cam_ra_cam", "cam_ck", 1),
	GATE_CAM_RA(CLK_CAM_RA_CAMTG, "cam_ra_camtg", "cam_ck", 2),
};

static const struct mtk_clk_desc cam_ra_desc = {
	.clks = cam_ra_clks,
	.num_clks = ARRAY_SIZE(cam_ra_clks),
};

static const struct of_device_id of_match_clk_mt6833_cam_ra[] = {
	{ .compatible = "mediatek,mt6833-camsys-rawa", .data = &cam_ra_desc },
	{}
};
MODULE_DEVICE_TABLE(of, of_match_clk_mt6833_cam_ra);

static struct platform_driver clk_mt6833_cam_ra_drv = {
	.probe = mtk_clk_simple_probe,
	.remove = mtk_clk_simple_remove,
	.driver = {
		.name = "clk-mt6833-cam_ra",
		.of_match_table = of_match_clk_mt6833_cam_ra,
	},
};

module_platform_driver(clk_mt6833_cam_ra_drv);

MODULE_DESCRIPTION("MediaTek MT6833 camsys_rawa clocks driver");
MODULE_LICENSE("GPL");

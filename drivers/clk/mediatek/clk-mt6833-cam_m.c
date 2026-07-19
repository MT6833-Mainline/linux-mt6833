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

static const struct mtk_gate_regs cam_m_cg_regs = {
	.set_ofs = 0x4,
	.clr_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_CAM_M(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &cam_m_cg_regs,			\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	}

static const struct mtk_gate cam_m_clks[] = {
	GATE_CAM_M(CLK_CAM_M_LARB13, "cam_m_larb13", "cam_ck", 0),
	GATE_CAM_M(CLK_CAM_M_LARB14, "cam_m_larb14", "cam_ck", 2),
	GATE_CAM_M(CLK_CAM_M_RESERVED0, "cam_m_reserved0", "cam_ck", 3),
	GATE_CAM_M(CLK_CAM_M_CAM, "cam_m_cam", "cam_ck", 6),
	GATE_CAM_M(CLK_CAM_M_CAMTG, "cam_m_camtg", "cam_ck", 7),
	GATE_CAM_M(CLK_CAM_M_SENINF, "cam_m_seninf", "cam_ck", 8),
	GATE_CAM_M(CLK_CAM_M_CAMSV1, "cam_m_camsv1", "cam_ck", 10),
	GATE_CAM_M(CLK_CAM_M_CAMSV2, "cam_m_camsv2", "cam_ck", 11),
	GATE_CAM_M(CLK_CAM_M_CAMSV3, "cam_m_camsv3", "cam_ck", 12),
	GATE_CAM_M(CLK_CAM_M_CCU0, "cam_m_ccu0", "cam_ck", 13),
	GATE_CAM_M(CLK_CAM_M_CCU1, "cam_m_ccu1", "cam_ck", 14),
	GATE_CAM_M(CLK_CAM_M_MRAW0, "cam_m_mraw0", "cam_ck", 15),
	GATE_CAM_M(CLK_CAM_M_RESERVED2, "cam_m_reserved2", "cam_ck", 16),
	GATE_CAM_M(CLK_CAM_M_FAKE_ENG, "cam_m_fake_eng", "cam_ck", 17),
	GATE_CAM_M(CLK_CAM_M_CCU_GALS, "cam_m_ccu_gals", "cam_ck", 18),
	GATE_CAM_M(CLK_CAM_M_CAM2MM_GALS, "cam_m_cam2mm_gals", "cam_ck", 19),
};

static const struct mtk_clk_desc cam_m_desc = {
	.clks = cam_m_clks,
	.num_clks = ARRAY_SIZE(cam_m_clks),
};

static const struct of_device_id of_match_clk_mt6833_cam_m[] = {
	{ .compatible = "mediatek,mt6833-camsys-main", .data = &cam_m_desc },
	{}
};
MODULE_DEVICE_TABLE(of, of_match_clk_mt6833_cam_m);

static struct platform_driver clk_mt6833_cam_m_drv = {
	.probe = mtk_clk_simple_probe,
	.remove = mtk_clk_simple_remove,
	.driver = {
		.name = "clk-mt6833-cam_m",
		.of_match_table = of_match_clk_mt6833_cam_m,
	},
};

module_platform_driver(clk_mt6833_cam_m_drv);

MODULE_DESCRIPTION("MediaTek MT6833 camsys_main clocks driver");
MODULE_LICENSE("GPL");

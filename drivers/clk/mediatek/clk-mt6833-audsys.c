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

static const struct mtk_gate_regs audsys0_cg_regs = {
	.set_ofs = 0x0,
	.clr_ofs = 0x0,
	.sta_ofs = 0x0,
};

static const struct mtk_gate_regs audsys1_cg_regs = {
	.set_ofs = 0x4,
	.clr_ofs = 0x4,
	.sta_ofs = 0x4,
};

static const struct mtk_gate_regs audsys2_cg_regs = {
	.set_ofs = 0x8,
	.clr_ofs = 0x8,
	.sta_ofs = 0x8,
};

#define GATE_AUDSYS0(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &audsys0_cg_regs,		\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_no_setclr,	\
	}

#define GATE_AUDSYS1(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &audsys1_cg_regs,		\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_no_setclr,	\
	}

#define GATE_AUDSYS2(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &audsys2_cg_regs,		\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_no_setclr,	\
	}

static const struct mtk_gate audsys_clks[] = {
	/* AUDSYS0 */
	GATE_AUDSYS0(CLK_AUDSYS_AFE, "aud_afe", "audio_ck", 2),
	GATE_AUDSYS0(CLK_AUDSYS_22M, "aud_22m", "aud_engen1_ck", 8),
	GATE_AUDSYS0(CLK_AUDSYS_24M, "aud_24m", "aud_engen2_ck", 9),
	GATE_AUDSYS0(CLK_AUDSYS_APLL2_TUNER, "aud_apll2_tuner", "aud_engen2_ck", 18),
	GATE_AUDSYS0(CLK_AUDSYS_APLL_TUNER, "aud_apll_tuner", "aud_engen1_ck", 19),
	GATE_AUDSYS0(CLK_AUDSYS_TDM, "aud_tdm_ck", "aud_1_ck", 20),
	GATE_AUDSYS0(CLK_AUDSYS_ADC, "aud_adc", "audio_ck", 24),
	GATE_AUDSYS0(CLK_AUDSYS_DAC, "aud_dac", "audio_ck", 25),
	GATE_AUDSYS0(CLK_AUDSYS_DAC_PREDIS, "aud_dac_predis", "audio_ck", 26),
	GATE_AUDSYS0(CLK_AUDSYS_TML, "aud_tml", "audio_ck", 27),
	GATE_AUDSYS0(CLK_AUDSYS_NLE, "aud_nle", "audio_ck", 28),
	/* AUDSYS1 */
	GATE_AUDSYS1(CLK_AUDSYS_I2S1_BCLK, "aud_i2s1_bclk", "audio_ck", 4),
	GATE_AUDSYS1(CLK_AUDSYS_I2S2_BCLK, "aud_i2s2_bclk", "audio_ck", 5),
	GATE_AUDSYS1(CLK_AUDSYS_I2S3_BCLK, "aud_i2s3_bclk", "audio_ck", 6),
	GATE_AUDSYS1(CLK_AUDSYS_I2S4_BCLK, "aud_i2s4_bclk", "audio_ck", 7),
	GATE_AUDSYS1(CLK_AUDSYS_CONNSYS_I2S_ASRC, "aud_connsys_i2s_asrc", "audio_ck", 12),
	GATE_AUDSYS1(CLK_AUDSYS_GENERAL1_ASRC, "aud_general1_asrc", "audio_ck", 13),
	GATE_AUDSYS1(CLK_AUDSYS_GENERAL2_ASRC, "aud_general2_asrc", "audio_ck", 14),
	GATE_AUDSYS1(CLK_AUDSYS_DAC_HIRES, "aud_dac_hires", "audio_h_ck", 15),
	GATE_AUDSYS1(CLK_AUDSYS_ADC_HIRES, "aud_adc_hires", "audio_h_ck", 16),
	GATE_AUDSYS1(CLK_AUDSYS_ADC_HIRES_TML, "aud_adc_hires_tml", "audio_h_ck", 17),
	GATE_AUDSYS1(CLK_AUDSYS_ADDA6_ADC, "aud_adda6_adc", "audio_ck", 20),
	GATE_AUDSYS1(CLK_AUDSYS_ADDA6_ADC_HIRES, "aud_adda6_adc_hires", "audio_h_ck", 21),
	GATE_AUDSYS1(CLK_AUDSYS_3RD_DAC, "aud_3rd_dac", "audio_ck", 28),
	GATE_AUDSYS1(CLK_AUDSYS_3RD_DAC_PREDIS, "aud_3rd_dac_predis", "audio_ck", 29),
	GATE_AUDSYS1(CLK_AUDSYS_3RD_DAC_TML, "aud_3rd_dac_tml", "audio_ck", 30),
	GATE_AUDSYS1(CLK_AUDSYS_3RD_DAC_HIRES, "aud_3rd_dac_hires", "audio_h_ck", 31),
	/* AUDSYS2 */
	GATE_AUDSYS2(CLK_AUDSYS_I2S5_BCLK, "aud_i2s5_bclk", "audio_ck", 0),
	GATE_AUDSYS2(CLK_AUDSYS_I2S6_BCLK, "aud_i2s6_bclk", "audio_ck", 1),
	GATE_AUDSYS2(CLK_AUDSYS_I2S7_BCLK, "aud_i2s7_bclk", "audio_ck", 2),
	GATE_AUDSYS2(CLK_AUDSYS_I2S8_BCLK, "aud_i2s8_bclk", "audio_ck", 3),
	GATE_AUDSYS2(CLK_AUDSYS_I2S9_BCLK, "aud_i2s9_bclk", "audio_ck", 4),
};

static const struct mtk_clk_desc aud_desc = {
	.clks = audsys_clks,
	.num_clks = ARRAY_SIZE(audsys_clks),
};

static const struct of_device_id of_match_clk_mt6833_audsys[] = {
	{ .compatible = "mediatek,mt6833-audsys", .data = &aud_desc },
	{}
};
MODULE_DEVICE_TABLE(of, of_match_clk_mt6833_audsys);

static struct platform_driver clk_mt6833_audsys_drv = {
	.probe = mtk_clk_simple_probe,
	.remove = mtk_clk_simple_remove,
	.driver = {
		.name = "clk-mt6833-audsys",
		.of_match_table = of_match_clk_mt6833_audsys,
	},
};

module_platform_driver(clk_mt6833_audsys_drv);

MODULE_DESCRIPTION("MediaTek MT6833 audio clocks driver");
MODULE_LICENSE("GPL");

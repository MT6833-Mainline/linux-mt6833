// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2020 MediaTek Inc.
 */

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/mfd/syscon.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/slab.h>

#include "clk-mtk.h"
#include "clk-pll.h"

#include <dt-bindings/clock/mediatek,mt6833-clk.h>

#define MT6833_PLL_FMAX		(3800UL * MHZ)
#define MT6833_PLL_FMIN		(1500UL * MHZ)
#define MT6833_INTEGER_BITS	8

#define PLL_B(_id, _name, _reg, _en_reg, _en_mask, _pwr_reg,		\
			_flags,						\
			_rst_bar_mask, _pd_reg, _pd_shift, _tuner_reg,	\
			_tuner_en_reg, _tuner_en_bit, _pcw_reg,		\
			_pcw_shift, _pcwbits, _div_table) {		\
		.id = _id,						\
		.name = _name,						\
		.reg = _reg,						\
		.en_reg = _en_reg,					\
		.en_mask = _en_mask,					\
		.pwr_reg = _pwr_reg,					\
		.flags = (_flags),					\
		.rst_bar_mask = _rst_bar_mask,				\
		.fmax = MT6833_PLL_FMAX,				\
		.fmin = MT6833_PLL_FMIN,				\
		.pd_reg = _pd_reg,					\
		.pd_shift = _pd_shift,					\
		.tuner_reg = _tuner_reg,				\
		.tuner_en_reg = _tuner_en_reg,				\
		.tuner_en_bit = _tuner_en_bit,				\
		.pcw_reg = _pcw_reg,					\
		.pcw_shift = _pcw_shift,				\
		.pcwbits = _pcwbits,					\
		.pcwibits = MT6833_INTEGER_BITS,			\
		.div_table = _div_table,				\
	}

#define PLL(_id, _name, _reg, _en_reg, _en_mask, _pwr_reg,		\
			_flags,						\
			_rst_bar_mask, _pd_reg, _pd_shift, _tuner_reg,	\
			_tuner_en_reg, _tuner_en_bit, _pcw_reg,		\
			_pcw_shift, _pcwbits)				\
		PLL_B(_id, _name, _reg, _en_reg, _en_mask, _pwr_reg,	\
			_flags,						\
			_rst_bar_mask, _pd_reg, _pd_shift, _tuner_reg,	\
			_tuner_en_reg, _tuner_en_bit, _pcw_reg,		\
			_pcw_shift, _pcwbits, NULL)			\

static const struct mtk_pll_data plls[] = {
	PLL(CLK_APMIXED_ARMPLL_LL, "armpll_ll", 0x0208,
		0x0208, 0x00000001,
		0x0214,
		PLL_AO, BIT(0),
		0x020c, 24,
		0, 0, 0,
		0x020c, 0, 22),
	PLL(CLK_APMIXED_ARMPLL_BL0, "armpll_bl0", 0x0218,
		0x0218, 0x00000001,
		0x0224,
		PLL_AO, BIT(0),
		0x021c, 24,
		0, 0, 0,
		0x021c, 0, 22),
	PLL(CLK_APMIXED_CCIPLL, "ccipll", 0x0258,
		0x0258, 0x00000001,
		0x0264,
		PLL_AO, BIT(0),
		0x025c, 24,
		0, 0, 0,
		0x025c, 0, 22),
	PLL(CLK_APMIXED_MPLL, "mpll", 0x0390,
		0x0390, 0x00000001,
		0x039c,
		PLL_AO, BIT(0),
		0x0394, 24,
		0, 0, 0,
		0x0394, 0, 22),
	PLL(CLK_APMIXED_MAINPLL, "mainpll", 0x0340,
		0x0340, 0x00000001,
		0x034c,
		HAVE_RST_BAR | PLL_AO, BIT(23),
		0x0344, 24,
		0, 0, 0,
		0x0344, 0, 22),
	PLL(CLK_APMIXED_UNIVPLL, "univpll", 0x0308,
		0x0308, 0x00000001,
		0x0314,
		HAVE_RST_BAR, BIT(23),
		0x030c, 24,
		0, 0, 0,
		0x030c, 0, 22),
	PLL(CLK_APMIXED_MSDCPLL, "msdcpll", 0x0350,
		0x0350, 0x00000001,
		0x035c,
		0, BIT(0),
		0x0354, 24,
		0, 0, 0,
		0x0354, 0, 22),
	PLL(CLK_APMIXED_MMPLL, "mmpll", 0x0360,
		0x0360, 0x00000001,
		0x036c,
		HAVE_RST_BAR, BIT(23),
		0x0364, 24,
		0, 0, 0,
		0x0364, 0, 22),
	PLL(CLK_APMIXED_ADSPPLL, "adsppll", 0x0370,
		0x0370, 0x00000001,
		0x037c,
		0, BIT(0),
		0x0374, 24,
		0, 0, 0,
		0x0374, 0, 22),
	PLL(CLK_APMIXED_MFGPLL, "mfgpll", 0x0268,
		0x0268, 0x00000001,
		0x0274,
		0, BIT(0),
		0x026c, 24,
		0, 0, 0,
		0x026c, 0, 22),
	PLL(CLK_APMIXED_TVDPLL, "tvdpll", 0x0380,
		0x0380, 0x00000001,
		0x038c,
		0, BIT(0),
		0x0384, 24,
		0, 0, 0,
		0x0384, 0, 22),
	PLL(CLK_APMIXED_APLL1, "apll1", 0x0318,
		0x0318, 0x00000001,
		0x0328,
		0, BIT(0),
		0x031c, 24,
		0x0040, 0x000C, 0,
		0x0320, 0, 32),
	PLL(CLK_APMIXED_APLL2, "apll2", 0x032c,
		0x032c, 0x00000001,
		0x033c,
		0, BIT(0),
		0x0330, 24,
		0x0044, 0x000C, 5,
		0x0334, 0, 32),
	PLL(CLK_APMIXED_NPUPLL, "npupll", 0x03B4,
		0x03B4, 0x00000001,
		0x03C0,
		0, BIT(0),
		0x03B8, 24,
		0, 0, 0,
		0x03B8, 0, 22),
	PLL(CLK_APMIXED_USBPLL, "usbpll", 0x03C4,
		0x03CC, 0x00000004,
		0x03CC,
		0, BIT(0),
		0x03C4, 24,
		0, 0, 0,
		0x03C4, 0, 22),
};

static int clk_mt6833_apmixed_probe(struct platform_device *pdev)
{
	struct clk_hw_onecell_data *clk_data;
	int r;
	struct device_node *node = pdev->dev.of_node;

	void __iomem *base;
	struct resource *res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(base)) {
		pr_notice("%s(): ioremap failed\n", __func__);
		return PTR_ERR(base);
	}

	clk_data = mtk_devm_alloc_clk_data(&pdev->dev, CLK_APMIXED_NR_CLK);
	if (!clk_data)
		return -ENOMEM;

	platform_set_drvdata(pdev, clk_data);

	mtk_clk_register_plls(node, plls, ARRAY_SIZE(plls),
			clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);

	if (r)
		pr_notice("%s(): could not register clock provider: %d\n",
			__func__, r);

	return r;
}

static void clk_mt6833_apmixed_remove(struct platform_device *pdev)
{
	struct clk_hw_onecell_data *clk_data = platform_get_drvdata(pdev);

	mtk_clk_unregister_plls(plls, ARRAY_SIZE(plls), clk_data);
}

static const struct of_device_id of_match_clk_mt6833_apmixedsys[] = {
	{
		.compatible = "mediatek,mt6833-apmixedsys",
	}, {
		/* sentinel */
	}
};

static struct platform_driver clk_mt6833_apmixed_drv = {
	.probe = clk_mt6833_apmixed_probe,
	.remove = clk_mt6833_apmixed_remove,
	.driver = {
		.name = "clk-mt6833-apmixedsys",
		.owner = THIS_MODULE,
		.of_match_table = of_match_clk_mt6833_apmixedsys,
	},
};
module_platform_driver(clk_mt6833_apmixed_drv);

MODULE_DESCRIPTION("MediaTek MT6833 apmixedsys clock driver");
MODULE_LICENSE("GPL");

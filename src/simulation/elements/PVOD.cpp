#include "simulation/ElementCommon.h"
//#TPT-Directive ElementClass Element_PVOD PT_PVOD 84
Element_PVOD::Element_PVOD()
{
	Identifier = "DEFAULT_PT_PVOD";
	Name = "PVOD";
	Colour = PIXPACK(0x792020);
	MenuVisible = 1;
	MenuSection = SC_POWERED;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 1;

	Weight = 100;

	HeatConduct = 251;
	Description = "动力 VOID. 激活时, 摧毁进入其内部的粒子.";

	Properties = TYPE_SOLID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_PVOD::update;
	Graphics = &Element_PVOD::graphics;
}

//#TPT-Directive ElementHeader Element_PVOD static int update(UPDATE_FUNC_ARGS)
int Element_PVOD::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	if (parts[i].life>0 && parts[i].life!=10)
		parts[i].life--;
	for (rx=-2; rx<3; rx++)
		for (ry=-2; ry<3; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				if (!r)
					continue;
				if (TYP(r)==PT_SPRK)
				{
					if (parts[ID(r)].life>0 && parts[ID(r)].life<4)
					{
						if (parts[ID(r)].ctype==PT_PSCN)
							parts[i].life = 10;
						else if (parts[ID(r)].ctype==PT_NSCN)
							parts[i].life = 9;
					}
				}
				else if (TYP(r)==PT_PVOD)
				{
					if (parts[i].life==10&&parts[ID(r)].life<10&&parts[ID(r)].life>0)
						parts[i].life = 9;
					else if (parts[i].life==0&&parts[ID(r)].life==10)
						parts[i].life = 10;
				}
			}
	return 0;
}


//#TPT-Directive ElementHeader Element_PVOD static int graphics(GRAPHICS_FUNC_ARGS)
int Element_PVOD::graphics(GRAPHICS_FUNC_ARGS)

{
	int lifemod = ((cpart->life>10?10:cpart->life)*16);
	*colr += lifemod;
	return 0;
}


Element_PVOD::~Element_PVOD() {}

#include "simulation/ElementCommon.h"
//#TPT-Directive ElementClass Element_STKM2 PT_STKM2 128
Element_STKM2::Element_STKM2()
{
	Identifier = "DEFAULT_PT_STKM2";
	Name = "STK2";
	Colour = PIXPACK(0x6464FF);
	MenuVisible = 1;
	MenuSection = SC_SPECIAL;
	Enabled = 1;

	Advection = 0.5f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.2f;
	Loss = 1.0f;
	Collision = 0.0f;
	Gravity = 0.0f;
	NewtonianGravity = 0.0f;
	Diffusion = 0.0f;
	HotAir = 0.00f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 50;

	DefaultProperties.temp = R_TEMP + 14.6f + 273.15f;
	HeatConduct = 0;
	Description = "火柴人2号. 别杀他! 用wasd控制他.";

	Properties = PROP_NOCTYPEDRAW;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 620.0f;
	HighTemperatureTransition = PT_FIRE;

	DefaultProperties.life = 100;

	Update = &Element_STKM2::update;
	Graphics = &Element_STKM::graphics;
	Create = &Element_STKM2::create;
	CreateAllowed = &Element_STKM2::createAllowed;
	ChangeType = &Element_STKM2::changeType;
}

//#TPT-Directive ElementHeader Element_STKM2 static int update(UPDATE_FUNC_ARGS)
int Element_STKM2::update(UPDATE_FUNC_ARGS)
{
	Element_STKM::run_stickman(&sim->player2, UPDATE_FUNC_SUBCALL_ARGS);
	return 0;
}

//#TPT-Directive ElementHeader Element_STKM2 static void create(ELEMENT_CREATE_FUNC_ARGS)
void Element_STKM2::create(ELEMENT_CREATE_FUNC_ARGS)
{
	int spawnID = sim->create_part(-3, x, y, PT_SPAWN2);
	if (spawnID >= 0)
		sim->player2.spawnID = spawnID;
}

//#TPT-Directive ElementHeader Element_STKM2 static bool createAllowed(ELEMENT_CREATE_ALLOWED_FUNC_ARGS)
bool Element_STKM2::createAllowed(ELEMENT_CREATE_ALLOWED_FUNC_ARGS)
{
	return sim->elementCount[PT_STKM2] <= 0 && !sim->player2.spwn;
}

//#TPT-Directive ElementHeader Element_STKM2 static void changeType(ELEMENT_CHANGETYPE_FUNC_ARGS)
void Element_STKM2::changeType(ELEMENT_CHANGETYPE_FUNC_ARGS)
{
	if (to == PT_STKM2)
	{
		Element_STKM::STKM_init_legs(sim, &sim->player2, i);
		sim->player2.spwn = 1;
	}
	else
		sim->player2.spwn = 0;
}

Element_STKM2::~Element_STKM2() {}

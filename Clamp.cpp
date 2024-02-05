#include "Clamp.h"

float Clamp(float min, float max, float value)
{
	if (value < min) { return min; }
	else if (value > max) { return max; }
	else { return value; }
}
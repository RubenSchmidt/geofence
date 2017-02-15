#include <stdint.h>

struct coordinate
{
	uint32_t latitude;
	uint32_t longitude;
};

//Declare the functions
int insideFence(struct coordinate *points, struct coordinate position, int nrOfPoints);
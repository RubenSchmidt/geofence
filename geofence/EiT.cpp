// EiT.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#define fenceArraySize 100
#include <stdint.h>
#include "fenceCheck.h"

struct coordinate fence[fenceArraySize];
struct coordinate pos;
int points;


int _tmain(int argc, _TCHAR* argv[])
{
//Get this data from SD card!
	//Number of fence points
	points = 4;

	//Square around Trondheim
	fence[0].latitude = 62892715;
	fence[0].longitude = 8786316;
	fence[1].latitude = 62825056;
	fence[1].longitude = 11796570;
	fence[2].latitude = 63913228;
	fence[2].longitude = 11851501;
	fence[3].latitude = 63927717;
	fence[3].longitude = 9851990;

	pos.latitude = 63427443;
	pos.longitude = 10397594;

	int status = insideFence(fence, pos, points);

	printf("Status:%d", status);
	getchar();
	return 0;
}
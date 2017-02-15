# include "fenceCheck.h"

int insideFence(struct coordinate *points, struct coordinate position, int nrOfPoints)
{
	int i, j = nrOfPoints-1;
	int oddNodes = 0;

	for (i = 0; i < nrOfPoints; i++)
	{
		if (points[i].latitude<position.latitude && points[j].latitude >= position.latitude || points[j].latitude<position.latitude&&points[i].latitude >= position.latitude)
		{
			if ((points[i].longitude + (position.latitude - points[i].latitude) / (points[j].latitude - points[i].latitude)*(points[j].longitude - points[i].longitude))<position.longitude)
			{
				if (oddNodes == 1)
				{
					oddNodes = 0;
				}
				else
				{
					oddNodes = 1;
				}
			}
		}
		j = i;
	}
	return oddNodes;
}
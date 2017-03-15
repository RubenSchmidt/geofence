#include <Arduino.h>
#include <stdint.h>
#include <limits.h>

#include "fenceCheck.h"
#include "distanceToFence.h"

const float pi = 3.14159265358979323846;
const float earthRadiusKm = 6371.0;


// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param point1 Coordinate struct for the first point
 * @param point2 Coordinate struct for the second point
 * @return The distance between the two points in kilometers
 */
double distanceEarth(coordinate point1, coordinate point2) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(point1.latitude/10000000.0);
  lon1r = deg2rad(point1.longitude/10000000.0);
  lat2r = deg2rad(point2.latitude/10000000.0);
  lon2r = deg2rad(point2.longitude/10000000.0);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v))*1000;
}

double shortestDistanceToAllPoints(coordinate *points, coordinate position, int numbOfPoints)
{
	double distance = INT_MAX;
	for (int i = 0; i < numbOfPoints-1; i++) {
      double dist = distanceEarth(position, points[i]);
			if (dist < distance) {
				distance = dist;
			}
  }
	return distance;
}

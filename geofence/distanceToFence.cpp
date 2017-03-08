


int distanceToFence(struct coordinate *points, struct coordinate position, int numbOfPoints)
{
	double a, b, c;
  int distance = 0;

  for (size_t i = 0; i < numbOfPoints; i++) {
      getLine(points[i].latitude, points[i].longitude, points[i+1].latitude, points[i+1].longitude, a, b, c);
      int dist = abs(a * position.latitude + b * position.longitude + c) / sqrt(a * a + b * b);
  }


	getLine(points[0].latitude, points[0].longitude, points[1].latitude, points[1].longitude, a, b, c);
	return
}

void getLine(struct coordinate pos1, struct coordinate pos2, &a, &b, &c)
{
	 // (x- p1X) / (p2X - p1X) = (y - p1Y) / (p2Y - p1Y)
	 a = pos2.longitude - pos1.longitude;
	 b = pos2.latitude - pos1.latitude;
	 c = pos1.latitude * pos2.longitude - pos2.latitude * pos1.longitude;
}

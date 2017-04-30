#include <stdint.h>

#include <SD.h>

#include "fenceCheck.h"
#include "fence_data.h"

load_fence_from_sd_error load_fence_from_sd(const char *filename, coordinate *buf, uint32_t *points) {
	if(!SD.exists(filename))
		return LOAD_FENCE_FROM_SD_FILE_MISSING;

	File map = SD.open(filename);

	if(!map)
		return LOAD_FENCE_FROM_SD_FILE_ERROR;

	map.read(points, sizeof(*points));

	for(int i = 0; i < *points; i++) {
		if(!map.available()) return LOAD_FENCE_FROM_SD_FILE_TRUNC;
		map.read(&buf[i].latitude, sizeof(int32_t));
		if(!map.available()) return LOAD_FENCE_FROM_SD_FILE_TRUNC;
		map.read(&buf[i].longitude, sizeof(int32_t));
	}

	return LOAD_FENCE_FROM_SD_OK;
}

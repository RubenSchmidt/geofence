#ifndef FENCE_DATA_H
#define FENCE_DATA_H

enum load_fence_from_sd_error {
	LOAD_FENCE_FROM_SD_OK = 0,
	LOAD_FENCE_FROM_SD_FILE_MISSING,
	LOAD_FENCE_FROM_SD_FILE_ERROR,
	LOAD_FENCE_FROM_SD_FILE_TRUNC
};

load_fence_from_sd_error load_fence_from_sd(const char *filename, coordinate *buf, uint32_t *points);

#endif

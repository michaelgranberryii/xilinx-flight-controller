#ifndef FIR_H
#define FIR_H

#include <stdint.h>

#define FIR_FILTER_LENGTH 20

typedef struct {
	float 	buf[FIR_FILTER_LENGTH];
	uint8_t bufIndex;

	float out;
} FIRFilter;

void FIRFilter_Init(FIRFilter *fir);
float FIRFilter_Update(FIRFilter *fir, float inp);

#endif

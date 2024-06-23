#include "fir.h"
/*

FIR filter designed with
http://t-filter.appspot.com

sampling frequency: 250 Hz

* 0 Hz - 20 Hz
  gain = 1
  desired ripple = 5 dB
  actual ripple = 12.731537284542577 dB

* 30 Hz - 100 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = -29.733486098338485 dB

*/

//#define FILTER_TAP_NUM 10

//static float FIR_IMPULSE_RESPONSE[FIR_FILTER_LENGTH] = {
//  0.03777830872906293,
//  0.035087693630929916,
//  0.06292620408902362,
//  0.06751177947170811,
//  0.07995816359787883,
//  0.07995816359787883,
//  0.06751177947170811,
//  0.06292620408902362,
//  0.035087693630929916,
//  0.03777830872906293
//};

static float FIR_IMPULSE_RESPONSE[FIR_FILTER_LENGTH] = {
  0.1f,
  0.1f,
  0.1f,
  0.1f,
  0.1f,
  0.1f,
  0.1f,
  0.1f,
  0.1f,
  0.1f,
  0.1f,
  0.1f,
  0.1f,
  0.1f,
  0.1f,
  0.1f,
  0.1f,
  0.1f,
  0.1f,
  0.1f
};

//static float FIR_IMPULSE_RESPONSE[FIR_FILTER_LENGTH] = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f};


void FIRFilter_Init(FIRFilter *fir) {

	/* Clear filter buffer */
	for (uint8_t n = 0; n < FIR_FILTER_LENGTH; n++) {

		fir->buf[n] = 0.0f;

	}

	/* Reset buffer index */
	fir->bufIndex = 0;

	/* Clear filter output */
	fir->out = 0.0f;

}

float FIRFilter_Update(FIRFilter *fir, float inp) {

	/* Store latest sample in buffer */
	fir->buf[fir->bufIndex] = inp;

	/* Increment buffer index and wrap around if necessary */
	fir->bufIndex++;

	if (fir->bufIndex == FIR_FILTER_LENGTH) {

		fir->bufIndex = 0;

	}

	/* Compute new output sample (via convolution) */
	fir->out = 0.0f;

	uint8_t sumIndex = fir->bufIndex;

	for (uint8_t n = 0; n < FIR_FILTER_LENGTH; n++) {

		/* Decrement index and wrap if necessary */
		if (sumIndex > 0) {

			sumIndex--;

		} else {

			sumIndex = FIR_FILTER_LENGTH - 1;

		}

		/* Multiply impulse response with shifted input sample and add to output */
		fir->out += FIR_IMPULSE_RESPONSE[n] * fir->buf[sumIndex];

	}

	/* Return filtered output */
	return fir->out;

}

#include "bufferArray.h"
#include <stdlib.h>

struct BUFFER {
  int *data;
  int n;
  int maxSize;
  int distanceData;
};

S BUFFERinit(int maxSize, int distanceData) {
  //int maxSize=50, int distanceData=20;
  S s = malloc(sizeof *s);
  s->data = malloc(sizeof(int) * maxSize);
  s->n = 0;
  s->maxSize = maxSize;
	s->distanceData = distanceData;
  return s;
}

int BUFFERempty(S s) { return s->n == 0; }

int BUFFERsize(S s) { return s->maxSize; }

void BUFFERpush(S s, int dataReceived) {
  s->data[s->n] = dataReceived;
  (s->n)++;
  if (s->n == s->maxSize) {
    s->n = 0;
  }
}

int BUFFERshowSum(S s) {
  int sum = 0, i;
  for (i = 0; i < s->maxSize; i++) {
    sum += s->data[i];
  }

  return sum;
}

static int findPeak(S s) {
  int i, max;
  for (i = 0, max = -1000; i < s->maxSize; i++) {
    if (s->data[i] > max) {
      max = s->data[i];
    }
  }
  return max;
}

static int howManyPeaks(S s, int peak) {
  int i, peaks;
  for (i = 0, peaks = 0; i < s->maxSize; i++) {
    if (s->data[i] == peak) {
      peaks++;
    }
  }
  return peaks;
}

static int* modelCalculation(S s) {
  int max = findPeak(s), peaks = howManyPeaks(s, max);
  int *returnData = malloc(sizeof(int) * (peaks - 1));
	//int returnData[50];
  int i, firstIndex = -1, lastIndex = -1, numFound;
  for (i = 0,numFound=0; i < s->maxSize && numFound != peaks;i++) {
    if (s->data[i] == max) {
      if (firstIndex == -1) {
        firstIndex = i;
				numFound++;
      } else {
        lastIndex = i;
        returnData[numFound-1] = (lastIndex - firstIndex ) * s->distanceData;
        //firstIndex = lastIndex;
				numFound++;
      }
    }
  }
	for (i = 0; i < peaks-1;i++) {
		returnData[i] = 60/returnData[i];
	}
  return returnData;
}

int* BUFFERmodelHR(S s) { 
	return modelCalculation(s); }

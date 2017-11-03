#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cuda_runtime.h"
#include "helper_functions.h"
#include "helper_cuda.h"

const int userNum = 1024;
const int itemNum = 2048;
const int infoNum = 80000;
const int requestNum = 20000;

// <<< 2048 >>>
__global__ void calcuLength(int **d_trainMatrix, float * lenVector)
{
	int item = blockIdx.x;
	int sum = 0;
	for (int i = 0; i < userNum; ++i) {
		if (d_trainMatrix[i][item] == 0) {
			continue;
		}
		sum += d_trainMatrix[i][item] * d_trainMatrix[i][item];
	}
	lenVector[item] = sqrt((float)sum);
	__syncthreads();
}

// <<< 4096, 1024>>>
__global__ void calcuSim(int ** d_trainMatrix, float * lenVector, float ** d_sim)
{
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	int item1 = index / 1024;
	int item2 = index % 1024;
	int sum = 0;
	for (int i = 0; i < userNum; ++i){
		sum += d_trainMatrix[i][item1] * d_trainMatrix[i][item2];
	}
	if (lenVector[item1] && lenVector[item2])
		d_sim[item1][item2] = d_sim[item2][item1] = sum/lenVector[item1]/lenVector[item2];
	else 
		d_sim[item1][item2] = d_sim[item2][item1] = 0;
	__syncthreads();
	// if (item1 < 100 && item2 < 100)
	// printf("%d and %d: %f\n", item1, item2, d_sim[item1][item2]);
}

// <<<32, 1024>>>
__global__ void calcuGrade(int ** d_trainMatrix, float ** d_sim, int * userVec, int * itemVec) 
{
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	printf("%d\n", index);return;
	if (index >= requestNum) return;
	int userID = userVec[index];
	int itemID = itemVec[index];

	float sum = 0;
	int count = 0;
	for (int i = 0; i < itemNum; ++i) {
		if (d_trainMatrix[userID][i]) {
			sum += d_sim[i][itemID] * d_trainMatrix[userID][i];
			count++;
		}
	}
	d_trainMatrix[userID][itemID] = sum / count;
	printf("%f\n", d_trainMatrix[userID][itemID]);
}

__global__ void show(float * fuck)
{
	printf("%f\n", fuck[10000]);
}

int main()
{	cudaError_t error;
	// input .base to h_trainMatrix
	int ** h_trainMatrix, * tempSpace;
	h_trainMatrix = (int **)malloc(userNum * sizeof(int *));
	tempSpace = (int *)malloc(itemNum * userNum * sizeof(int));
	for (int i = 0, j = 0; i < userNum; ++i, j+=itemNum) {
		h_trainMatrix[i] = &tempSpace[j];
	}
	FILE * fp = fopen("u1.base", "r");
	int userID, itemID, grade, time;
	for (int i = 0; i < infoNum; ++i) {
		fscanf(fp, "%d %d %d %d", &userID, &itemID, &grade, &time);
		h_trainMatrix[userID][itemID] = grade;
	}
	fclose(fp);

	// copy h_trainMatrix to d_trainMatrix
	int ** d_trainMatrix = NULL;	
	cudaMalloc((void **)&d_trainMatrix, userNum * sizeof(int *));
	cudaMalloc((void **)&tempSpace, itemNum * userNum * sizeof(int));
	int ** temptemp = (int **)malloc(userNum * sizeof(int *));
	for (int i = 0, j = 0; i < userNum; ++i, j+=itemNum) {
		temptemp[i] = &tempSpace[j];
	}
	cudaMemcpy(d_trainMatrix, temptemp, userNum * sizeof(int *), cudaMemcpyHostToDevice);
	cudaMemcpy(tempSpace, *h_trainMatrix, userNum * itemNum * sizeof(int), cudaMemcpyHostToDevice);
	
	// calculate length
	float * lenVector = NULL;
	cudaMalloc((void **)&lenVector, itemNum * sizeof(float));
	calcuLength <<<2048, 1>>> (d_trainMatrix, lenVector);

	// calculate similarity
	float ** d_sim = NULL;
	cudaMalloc((void **)&d_sim, itemNum * sizeof(float *));
	float ** temptemp1 = (float **)malloc(itemNum * sizeof(float *));
	float * tempSpace1;
	cudaMalloc((void **)&tempSpace1, itemNum * itemNum * sizeof(float));
	for (int i = 0, j = 0; i < itemNum; ++i, j+=itemNum) {
		temptemp1[i] = &tempSpace1[j];
	}
	cudaMemcpy(d_sim, temptemp1, itemNum * sizeof(float *), cudaMemcpyHostToDevice);
	calcuSim <<<4096, 1024>>> (d_trainMatrix, lenVector, d_sim);

	// // copy similarity to host
	// float ** h_sim = (float **)malloc(itemNum * sizeof(float *));
	// float * tempSpace2 = (float *)malloc(itemNum * itemNum * sizeof(float));
	// !!! unknown error cudaMemcpy(tempSpace2, tempSpace1, itemNum * itemNum * sizeof(float), cudaMemcpyDeviceToHost);	
	// for (int i = 0, j = 0; i < itemNum; ++i, j+=itemNum) {
	// 	h_sim[i] = &tempSpace2[j];
	// }
	
	// input .test and calculate
	fp = fopen("u1.test", "r");
	int temp1, temp2;
	int * h_userVec = (int *)malloc(requestNum * sizeof(int));
	int * h_itemVec = (int *)malloc(requestNum * sizeof(int));
	int * d_userVec, * d_itemVec;
	cudaMalloc((void **)&d_userVec, requestNum * sizeof(int));
	cudaMalloc((void **)&d_itemVec, requestNum * sizeof(int));
	for (int i = 0; i < requestNum; ++i) {
		fscanf(fp, "%d %d %d %d", h_userVec+i, h_itemVec+i, &temp1, &temp2);
	}
	fclose(fp);
error = cudaGetLastError();
printf("CUDA error: %s\n", cudaGetErrorString(error));
	cudaMemcpy(d_userVec, h_userVec, requestNum * sizeof(int), cudaMemcpyHostToDevice);	
	cudaMemcpy(d_itemVec, h_itemVec, requestNum * sizeof(int), cudaMemcpyHostToDevice);	
error = cudaGetLastError();
printf("CUDA error: %s\n", cudaGetErrorString(error));
	calcuGrade <<<1, 1>>> (d_trainMatrix, d_sim, d_userVec, d_itemVec);

	fp = fopen("u1.ans", "w");

	fclose(fp);

	// free
	cudaFree(d_trainMatrix);
	free(h_trainMatrix);
}

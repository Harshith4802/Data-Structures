/*include necessary header files*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/*sorts the given array of size N using bubble sort algorithm*/
void bubbleSort(int* array, int N){

	for (int i = 0 ; i < N - 1 ; ++i)
		for (int j = 0 ; j < N - i - 1; ++j)
			if (array[j] > array[j + 1]){
				/*swap array[j] and array[j + 1]*/
				int temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
}

void insertionSort(int* array, int N){

	for (int i = 1; i < N; ++i){
		/*take a copy of element to be inserted in sorted array[0...i]*/
		int temp = array[i];

		/*search for the correct position of temp in sorted array[0...i-1]*/
		int j = i - 1;
		while (j >=0 && array[j] > temp){
			/*copy (j)th element to (j+1)th index*/
			array[j+1] = array[j];
			/*decrease the value of j by 1*/
			j--;
		}

		/*paste temp at (j+1)th index*/
		array[j+1] = temp;
	}
}

void merge(int* array, int start, int mid, int end){
	/*take copies of two sorted arrays*/
	int size1 = mid - start + 1;
	int size2 = end - mid;
	int A[size1], B[size2];

	/*copy one part to array A*/
	for (int i = 0 ; i < size1; ++i)
		A[i] = array[start + i];

	/*copy another part to array B*/
	for (int i = 0 ; i < size2; ++i)
		B[i] = array[mid + 1 + i];

	/*indices to iterate through arrays*/
	int a_index = 0, b_index = 0, combinded_index = start;

	/*combine A and B to store in original array*/
	while (a_index  < size1 && b_index < size2){
		if (A[a_index] < B[b_index])
			array[combinded_index++] = A[a_index++];
		else
			array[combinded_index++] = B[b_index++];			
	}

	/*if A is exhausted then copy B entirely*/
	if (a_index == size1)
		while (b_index < size2)
			array[combinded_index++] = B[b_index++];

	/*if B is exhausted then copy A entirely*/
	if (b_index == size2)
		while (a_index < size1)
			array[combinded_index++] = A[a_index++];
}

/*sorts the given array of size N using merge sort algorithm*/
void mergeSort(int* array, int start, int end){
	/*check if array contains at least two elements to be sorted*/
	if (end > start){
		/*divide the array into two equal halves*/
		int mid = (start + end)/2;

		/*sort two halves recursively*/
		mergeSort(array, start, mid);
		mergeSort(array, mid + 1, end);

		/*merge two small sorted array to get a big sorted array*/
		merge(array, start, mid, end);
	}
}

int partition(int* array, int start, int end){
	/*keep last element at its correct position*/
	int l = start - 1;
	for (int i = start; i < end; ++i)
		if (array[i] < array[end]){
			/*current element is less than pivot element - swap A[l+1] and A[i]*/
			int temp = array[l + 1];
			array[l+1] = array[i];
			array[i] = temp;

			/*increment l*/
			l++;
		}
	/*swap A[l+1] and A[end]*/
	int temp = array[l + 1];
	array[l+1] = array[end];
	array[end] = temp;

	/*return the index of pivot element*/
	return (l + 1);
}

/*sorts the given array of size N using quick sort algorithm*/
void quickSort(int* array, int start, int end){
	/*check if array contains at least two elements to sort*/
	if (start < end){
		/*partition the array and get the pivot index*/
		int pivot_index = partition(array, start, end);
		/*apply quick sort recursively on two parts of the array*/
		quickSort(array, start, pivot_index - 1);
		quickSort(array, pivot_index + 1, end);
	}
}

void selectionSort(int* array, int N){

	for (int i = 0 ; i < N - 1; ++i){
		/*get the minimum element in array[i...N]*/
		/*assume the first element in array[i...N] is minimum*/
		int min_element = array[i];
		int min_index = i;
		/*search for minimum in array[i+1...N]*/
		for (int j = i + 1; j < N; ++j)
			if (array[j] < min_element){
				min_element = array[j];
				min_index = j;
			}
		/*swap array[i] with array[min_index]*/
		int temp = array[i];
		array[i] = array[min_index];
		array[min_index] = temp;
	}

}

void copyarr(int* a, int* b, int N){
	for (int i=0 ; i < N ; i++){
		b[i]=a[i];
		}
}

/*populates the given array of size N with random integers*/
void populateArray(int* array, int N){
	/*seed the random number generator with time*/
	srand(time(NULL));

	/*iterate through all elements in array and populate them*/
	for (int i = 0 ; i < N; ++i)
		array[i] = rand() % 10000;
}

/*prints the content of the array to console*/
void printArray(int* array, int N){
	for (int i = 0 ; i < N; ++i)
		printf ("%d ,", array[i]);
	printf ("\n");
}

/*driver function: program execution begins from here*/
int main(){
	
	////////////All the for loops below are taken for adding the values of time taken to calculate the average.///////////////

	/*used to get the time before and after the algorithm*/
	struct timeval start, end;
	/*used for computing the time difference*/
	unsigned long long int time1, time2, time_taken;

	/*create an array of size 10*/
	int N = 10000;
	int array[N],bub[N],ins[N],mer[N],qui[N],sel[N];

	/*populate the array with random entries*/
	populateArray(array, N);
	
	time_taken = 0;
	
	//////////////////////////////////////////
	//////////////Bubble Sort/////////////////
	//////////////////////////////////////////
		
	printf("Bubble Sort\n"); 
	
	
	for(int k=0 ; k < 10 ; k++){
	copyarr(array,bub,N);

	/*get the time before starting the algorithm*/
	gettimeofday(&start, NULL);

	/*sort the array using bubble sort algorithm*/
	bubbleSort(bub,N);

	/*get the time after finishing the algorithm*/
	gettimeofday(&end, NULL);

	/*compute the time taken in microseconds*/
	time1 = (start.tv_sec * 1000000 + start.tv_usec);
	time2 = (end.tv_sec * 1000000 + end.tv_usec);

	/*compute the difference in time*/
	time_taken = time_taken + time2 - time1;

	/*print the sorted content of the array*/
	

	/*print the time taken to console*/
	//~ printf ("Time taken(case %d): %lluus\n",k + 1, time2 - time1);
	}
		
	printf("Average time:%lfus\n", (double)(time_taken)/(double)10);
	time_taken = 0;
	
	printf("\n");
	
	
	for(int k=0 ; k < 10 ; k++)
	{
	for(int i=0 ; i<N ; i++)
		bub[i] = i;
		
	
	/*get the time before starting the algorithm*/
	gettimeofday(&start, NULL);

	/*sort the array using bubble sort algorithm*/
	bubbleSort(bub,N);

	/*get the time after finishing the algorithm*/
	gettimeofday(&end, NULL);

	/*compute the time taken in microseconds*/
	time1 = (start.tv_sec * 1000000 + start.tv_usec);
	time2 = (end.tv_sec * 1000000 + end.tv_usec);

	/*compute the difference in time*/
	time_taken = time_taken + time2 - time1;
	}
		
	printf("Best time:%lfus\n", (double)(time_taken)/(double)10);
	time_taken = 0;
	
	printf("\n");	
		
	for(int k=0 ; k < 10 ; k++)
	{
	for(int i=0 ; i<N ; i++)
		bub[i] = -i;	
	
	/*for having same array for each sort*/
	copyarr(array,bub,N);

	/*get the time before starting the algorithm*/
	gettimeofday(&start, NULL);

	/*sort the array using bubble sort algorithm*/
	bubbleSort(bub,N);

	/*get the time after finishing the algorithm*/
	gettimeofday(&end, NULL);

	/*compute the time taken in microseconds*/
	time1 = (start.tv_sec * 1000000 + start.tv_usec);
	time2 = (end.tv_sec * 1000000 + end.tv_usec);

	/*compute the difference in time*/
	time_taken = time_taken + time2 - time1;
	}
		
	printf("Worst time:%lfus\n", (double)(time_taken)/(double)10);
	time_taken = 0;
	
		
	
	printf("\n");
	

	
	//////////////////////////////////////////
	//////////////Selection Sort//////////////
	//////////////////////////////////////////
	printf("Selection Sort\n");
	
	
	for(int k=0 ; k < 10 ; k++){
	copyarr(array,sel,N);
	
	/*get the time before starting the algorithm*/
	gettimeofday(&start, NULL);

	/*sort the array using selection sort algorithm*/
	selectionSort(sel,N);

	/*get the time after finishing the algorithm*/
	gettimeofday(&end, NULL);

	/*compute the time taken in microseconds*/
	time1 = (start.tv_sec * 1000000 + start.tv_usec);
	time2 = (end.tv_sec * 1000000 + end.tv_usec);

	/*compute the difference in time*/
	time_taken = time_taken + time2 - time1;

	/*print the time taken to console*/
	//~ printf ("Time taken(case %d): %lluus\n",k + 1, time2 - time1);
	}
	
	printf("Average time:%lfus\n", (double)(time_taken)/(double)10);
	time_taken = 0;	
	
	printf("\n");
	
	for(int k=0 ; k < 10 ; k++)
	{
	copyarr(array,sel,N);	
	
	/*get the time before starting the algorithm*/
	gettimeofday(&start, NULL);

	/*sort the array using selection sort algorithm*/
	selectionSort(sel,N);

	/*get the time after finishing the algorithm*/
	gettimeofday(&end, NULL);

	/*compute the time taken in microseconds*/
	time1 = (start.tv_sec * 1000000 + start.tv_usec);
	time2 = (end.tv_sec * 1000000 + end.tv_usec);

	/*compute the difference in time*/
	time_taken = time_taken + time2 - time1;
	}
	
	printf("Best time:%lfus\n", (double)(time_taken)/(double)10);
	time_taken = 0;	
		
	printf("\n");
	
	for(int k=0 ; k < 10 ; k++)
	{
	copyarr(array,sel,N);	
	
	/*for having same array for each sort*/
	copyarr(array,sel,N);
	
	/*get the time before starting the algorithm*/
	gettimeofday(&start, NULL);

	/*sort the array using selection sort algorithm*/
	selectionSort(sel,N);

	/*get the time after finishing the algorithm*/
	gettimeofday(&end, NULL);

	/*compute the time taken in microseconds*/
	time1 = (start.tv_sec * 1000000 + start.tv_usec);
	time2 = (end.tv_sec * 1000000 + end.tv_usec);

	/*compute the difference in time*/
	time_taken = time_taken + time2 - time1;
	}
	
	printf("Worst time:%lfus\n", (double)(time_taken)/(double)10);
	time_taken = 0;	
	
	
	printf("\n");
	
	//////////////////////////////////////////
	//////////////Insertion Sort//////////////
	//////////////////////////////////////////
	printf("Insertion Sort\n");
	
	
	for(int k=0 ; k < 10 ; k++){
	copyarr(array,ins,N);
	
	/*get the time before starting the algorithm*/
	gettimeofday(&start, NULL);

	/*sort the array using insertion sort algorithm*/
	insertionSort(ins,N);

	/*get the time after finishing the algorithm*/
	gettimeofday(&end, NULL);

	/*compute the time taken in microseconds*/
	time1 = (start.tv_sec * 1000000 + start.tv_usec);
	time2 = (end.tv_sec * 1000000 + end.tv_usec);

	/*compute the difference in time*/
	time_taken = time_taken + time2 - time1;

	/*print the sorted content of the array*/
	

	/*print the time taken to console*/
	//~ printf ("Time taken(case %d): %lluus\n",k + 1, time2 - time1);
	}
	
	printf("Average time:%lfus\n", (double)(time_taken)/(double)10);
	time_taken = 0;
	
	printf("\n");
	
	for(int k=0 ; k < 10 ; k++)
	{
	for(int i=0 ; i<N ; i++)
		ins[i] = i;
		
	/*get the time before starting the algorithm*/
	gettimeofday(&start, NULL);

	/*sort the array using insertion sort algorithm*/
	insertionSort(ins,N);

	/*get the time after finishing the algorithm*/
	gettimeofday(&end, NULL);

	/*compute the time taken in microseconds*/
	time1 = (start.tv_sec * 1000000 + start.tv_usec);
	time2 = (end.tv_sec * 1000000 + end.tv_usec);

	/*compute the difference in time*/
	time_taken = time_taken + time2 - time1;
	}
	
	printf("Best time:%lfus\n", (double)(time_taken)/(double)10);
	time_taken = 0;
		
	printf("\n");
	
	
	for(int k=0 ; k < 10 ; k++)
	{
	for(int i=0 ; i<N ; i++)
		ins[i] = -i;	
	
	/*for having same array for each sort*/
	copyarr(array,ins,N);
	
	/*get the time before starting the algorithm*/
	gettimeofday(&start, NULL);

	/*sort the array using insertion sort algorithm*/
	insertionSort(ins,N);

	/*get the time after finishing the algorithm*/
	gettimeofday(&end, NULL);

	/*compute the time taken in microseconds*/
	time1 = (start.tv_sec * 1000000 + start.tv_usec);
	time2 = (end.tv_sec * 1000000 + end.tv_usec);

	/*compute the difference in time*/
	time_taken = time_taken + time2 - time1;
	}
	
	printf("Worst time:%lfus\n", (double)(time_taken)/(double)10);
	time_taken = 0;
	
		
	printf("\n");

	
	
	
	//////////////////////////////////////////
	//////////////Merge Sort//////////////////
	//////////////////////////////////////////
	printf("Merge Sort\n");
	
	
	for(int k=0 ; k < 10 ; k++){
	copyarr(array,mer,N);
	
	/*get the time before starting the algorithm*/
	gettimeofday(&start, NULL);

	/*sort the array using merge sort algorithm*/
	mergeSort(mer,0,N-1);

	/*get the time after finishing the algorithm*/
	gettimeofday(&end, NULL);

	/*compute the time taken in microseconds*/
	time1 = (start.tv_sec * 1000000 + start.tv_usec);
	time2 = (end.tv_sec * 1000000 + end.tv_usec);

	/*compute the difference in time*/
	time_taken = time_taken + time2 - time1;

	/*print the sorted content of the array*/
	
	/*print the time taken to console*/
	//~ printf ("Time taken(case %d): %lluus\n",k + 1, time2 - time1);
	}
	
	printf("Average time:%lfus\n", (double)(time_taken)/(double)10);
	time_taken = 0;
	
	printf("\n");
	
	
	for(int k=0 ; k < 10 ; k++)
	{
	copyarr(array,mer,N);
		
	/*get the time before starting the algorithm*/
	gettimeofday(&start, NULL);

	/*sort the array using merge sort algorithm*/
	mergeSort(mer,0,N-1);

	/*get the time after finishing the algorithm*/
	gettimeofday(&end, NULL);

	/*compute the time taken in microseconds*/
	time1 = (start.tv_sec * 1000000 + start.tv_usec);
	time2 = (end.tv_sec * 1000000 + end.tv_usec);

	/*compute the difference in time*/
	time_taken = time_taken + time2 - time1;
	}
	
	printf("Best time:%lfus\n", (double)(time_taken)/(double)10);
	time_taken = 0;
		
	printf("\n");

	for(int k=0 ; k < 10 ; k++)
	{
	copyarr(array,mer,N);
	
	/*for having same array for each sort*/
	copyarr(array,mer,N);
	
	/*get the time before starting the algorithm*/
	gettimeofday(&start, NULL);

	/*sort the array using merge sort algorithm*/
	mergeSort(mer,0,N-1);

	/*get the time after finishing the algorithm*/
	gettimeofday(&end, NULL);

	/*compute the time taken in microseconds*/
	time1 = (start.tv_sec * 1000000 + start.tv_usec);
	time2 = (end.tv_sec * 1000000 + end.tv_usec);

	/*compute the difference in time*/
	time_taken = time_taken + time2 - time1;
	}
	
	printf("Worst time:%lfus\n", (double)(time_taken)/(double)10);
	time_taken = 0;
	
		
	printf("\n");
	
	
	//////////////////////////////////////////
	//////////////Quick Sort//////////////////
	//////////////////////////////////////////
	
	printf("Quick Sort\n");
	
	
	for(int k=0 ; k < 10 ; k++){
	copyarr(array,qui,N);
	
	/*get the time before starting the algorithm*/
	gettimeofday(&start, NULL);

	/*sort the array using quick sort algorithm*/
	quickSort(qui,0,N-1);

	/*get the time after finishing the algorithm*/
	gettimeofday(&end, NULL);

	/*compute the time taken in microseconds*/
	time1 = (start.tv_sec * 1000000 + start.tv_usec);
	time2 = (end.tv_sec * 1000000 + end.tv_usec);

	/*compute the difference in time*/
	time_taken = time_taken + time2 - time1;

	/*print the sorted content of the array*/
	

	/*print the time taken to console*/
	//~ printf ("Time taken(case %d): %lluus\n",k + 1, time2 - time1);
	}
	
	printf("Average time:%lfus\n", (double)(time_taken)/(double)10);
	time_taken = 0;
	
	printf("\n");	
	
	for(int k=0 ; k < 10 ; k++)
	{
	copyarr(array,qui,N);	
	
	/*get the time before starting the algorithm*/
	gettimeofday(&start, NULL);

	/*sort the array using quick sort algorithm*/
	quickSort(qui,0,N-1);

	/*get the time after finishing the algorithm*/
	gettimeofday(&end, NULL);

	/*compute the time taken in microseconds*/
	time1 = (start.tv_sec * 1000000 + start.tv_usec);
	time2 = (end.tv_sec * 1000000 + end.tv_usec);

	/*compute the difference in time*/
	time_taken = time_taken + time2 - time1;
	}
	
	printf("Best time:%lfus\n", (double)(time_taken)/(double)10);
	time_taken = 0;
	
	printf("\n");
	
	for(int k=0 ; k < 10 ; k++)
	{
	for(int i=0 ; i<N ; i++)
		qui[i] = -i;	
	
	/*for having same array for each sort*/
	copyarr(array,qui,N);
	
	/*get the time before starting the algorithm*/
	gettimeofday(&start, NULL);

	/*sort the array using quick sort algorithm*/
	quickSort(qui,0,N-1);

	/*get the time after finishing the algorithm*/
	gettimeofday(&end, NULL);

	/*compute the time taken in microseconds*/
	time1 = (start.tv_sec * 1000000 + start.tv_usec);
	time2 = (end.tv_sec * 1000000 + end.tv_usec);

	/*compute the difference in time*/
	time_taken = time_taken + time2 - time1;
	}
	
	printf("Worst time:%lfus\n", (double)(time_taken)/(double)10);
	time_taken = 0;
	
		
	printf("\n");
	

	/*return 0 to caller to indicate normal termination of program*/
	return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


int* getrand() {
	int fd = open("/dev/random", O_RDONLY);
	if(fd == -1) {
		printf("Errno: %d\n", errno);
	}
	// printf("%d\n", fd);
	int * answer = malloc(sizeof(int));
	read(fd, answer, sizeof(int));
	close(fd);
	return answer;
}

int main() {
	int arr[10];
	int * randp;
	printf("\nValues in the first array:\n\n");
	for(int i = 0;i < 10; i++) {
		randp = getrand();
		arr[i] = *randp;
		printf("Position %d: %d\n", i, arr[i]);
		free(randp);
	}

	int tempfdw = open("./tempfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if(tempfdw == -1) {
		printf("Errno: %d\n", errno);
	}
	write(tempfdw, arr, 10*sizeof(int));
	close(tempfdw);

	int arrr[10];

	int tempfdr = open("./tempfile.txt", O_RDONLY);
	if(tempfdr == -1) {
		printf("Errno: %d\n", errno);
	}

	read(tempfdr, arrr, 10*sizeof(int));
	close(tempfdr);

	printf("\nValues in the second array:\n\n");
	for(int i = 0;i < 10; i++) {
		printf("Position %d: %d\n", i, arrr[i]);
	}

	if(*arr == *arrr) {
		printf("\nBoth arrays are the same!\n\n");
	}
	


	return 0;
}


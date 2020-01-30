#include "mpo.h"
#include "util.h"
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>


//_____________________________________________________________



int ReadData(const char *filename, void *data, const size_t size, const size_t n)
{
	FILE *fd = fopen(filename, "rb");
	if (fd == NULL)
	{
		duprintf("'fopen()' failed during call of 'ReadData()'.\n");
		return -1;
	}

	// obtain the file size
	fseek(fd, 0, SEEK_END);
	long filesize = ftell(fd);
	rewind(fd);
	// duprintf("file size: %d\n", filesize);
	if ((size_t)filesize != n*size)
	{
		duprintf("'ReadData()' failed: expected file size does not match.\n");
		fclose(fd);
		return -2;
	}

	// copy the file into the data array
	if (fread(data, size, n, fd) != n)
	{
		duprintf("'fread()' failed during call of 'ReadData()'.\n");
		fclose(fd);
		return -3;
	}

	fclose(fd);

	return 0;
}


int main(int argc, char *argv[])
{


  const int L = 5;

  const size_t d0 = 4;
  const size_t d1 = 5;

  // load physical quantum numbers from disk
  qnumber_t *qd0 = (qnumber_t *)algn_malloc(d0 * sizeof(qnumber_t));
  qnumber_t *qd1 = (qnumber_t *)algn_malloc(d1 * sizeof(qnumber_t));
  {
    status = ReadData("../test/mpo_test_qd0.dat", qd0, sizeof(qnumber_t), d0); if (status < 0) { return status; }
    status = ReadData("../test/mpo_test_qd1.dat", qd1, sizeof(qnumber_t), d1); if (status < 0) { return status; }
  }

  const size_t d[] = { d0, d0 };
  const size_t D[] = { 1, 5, 6, 7, 8, 1 };
  AllocateMPO(L, d, D, &Z);

  memcpy(Z.qd[0], qd0, d0*sizeof(qnumber_t));
  memcpy(Z.qd[1], qd0, d0*sizeof(qnumber_t));
  
  for (int i = 0; i < L; i++)
  {
    char filename[1024];
    sprintf(filename, "../test/mpo_test_C%i.dat", i);
    status = ReadData(filename, Z.A[i].data, sizeof(double complex), NumTensorElements(&Z.A[i]));
    if (status < 0) { return status; }
  }

  return 0;
}


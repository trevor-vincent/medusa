#include <complex>
#include <iostream>
#include <mpi.h>
#include <mptensor.hpp>

// Compile command: mpicxx -o mp_test mptensor_test.cpp -O3 -fopenmp  -I/home/tvincent/Research/Codes/mptensor/install/include -L/home/tvincent/Research/Codes/mptensor/install/lib -L/home/tvincent/Research/Codes/scalapack-2.1.0/install_fPIC/lib -lmptensor -lscalapack -llapack -lblas -lgfortran


inline double elem(mptensor::Index index) {
  return double(index[0] - 2.0*index[1] + 3.0*index[2] - 4.0*index[3]);
}

int main(int argc, char *argv[])
{
  typedef mptensor::Tensor<mptensor::scalapack::Matrix,std::complex<double>> ptensor;
  
  /* Start */
  MPI_Init(&argc, &argv);
  MPI_Comm comm = MPI_COMM_WORLD;
  int mpirank;
  int mpisize;
  bool mpiroot;
  MPI_Comm_rank(comm, &mpirank);
  MPI_Comm_size(comm, &mpisize);
  mpiroot = (mpirank==0);


  int d1 = 2;
  int d2 = 2;
  int D1 = 2;
  int D2 = 3;
  
  ptensor A(mptensor::Shape(d1,d2,D1,D2));


  mptensor::Index index;
  for(int i=0;i<A.local_size();++i) {
    index = A.global_index(i);
    A[i] = elem(index);
  }
  
  for(int i = 0; i < A.local_size(); i++){
    A[i] = std::conj(A[i]);
  }

  ptensor B = mptensor::transpose(A, mptensor::Index(1,0,2,3));
  ptensor C = mptensor::transpose(B, mptensor::Index(1,0,2,3));

  double error = 0.0;
  for(int i=0;i<A.local_size();++i) {
    std::complex<double> diff = A[i]-C[i];
    if(error<std::abs(diff)) error = std::abs(diff);
  }
  double max_error;
  MPI_Reduce(&error, &max_error, 1, MPI_DOUBLE, MPI_MAX, 0, comm);

  if (mpiroot) {
    std::cout << "# ";
    A.print_info(std::cout);
    std::cout << "# mpisize= " << mpisize << "\n";
    std::cout << "# error= " << max_error << "\n";
  }
  MPI_Finalize();
}

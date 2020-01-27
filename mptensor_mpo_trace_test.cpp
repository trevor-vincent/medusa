#include <bits/stdc++.h> 
using namespace std;


#include <iostream>
#include <mpi.h>
#include <mptensor.hpp>
#include "timer.hpp"



int main(int argc, char **argv) {
  using namespace mptensor;
  typedef Tensor<scalapack::Matrix,std::complex<double>> ptensor;
  using examples::benchmark::Timer;

  /* Start */
  MPI_Init(&argc, &argv);
  MPI_Comm comm = MPI_COMM_WORLD;
  int mpirank;
  int mpisize;
  bool mpiroot;
  MPI_Comm_rank(comm, &mpirank);
  MPI_Comm_size(comm, &mpisize);
  mpiroot = (mpirank==0);

  std::vector<ptensor> mpo(2);
  mpo[0] = ptensor(Shape(2,2,1,3));
  mpo[1] = ptensor(Shape(2,2,3,1));

  for(int i=0;i<mpo[0].local_size();++i) {
    mpo[0][i] = 1;
  }

  for(int i=0;i<mpo[1].local_size();++i) {
    mpo[1][i] = 1;
  }

  ptensor A = mptensor::contract(mpo[0], mptensor::Axes(0), mptensor::Axes(1));
  ptensor B = mptensor::contract(mpo[1], mptensor::Axes(0), mptensor::Axes(1));
  ptensor C = mptensor::tensordot(A,B, mptensor::Axes(1), mptensor::Axes(0));
  A.print_info(std::cout);
  B.print_info(std::cout);
  C.print_info(std::cout);
  cout << "C[0] = " << C[0] << endl;

  /* End */
  MPI_Finalize();
}

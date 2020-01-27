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

  mpo[0].print_info(std::cout);
  // ptensor Atrans = mptensor::transpose(mpo[0], mptensor::Index(1,0,2,3));
  // Atrans.print_info(std::cout);
  // for (int i = 0; i < Atrans.local_size(); i++)
    // Atrans[i] = std::conj(Atrans[i]);
  ptensor A = mptensor::tensordot(mpo[0],mpo[0], mptensor::Axes(1), mptensor::Axes(1));

  A.print_info(std::cout);
  A = mptensor::contract(A, mptensor::Axes(0), mptensor::Axes(3));
  
  A.print_info(std::cout);

  mpo[1].print_info(std::cout);
  ptensor B = mptensor::tensordot(mpo[1],mpo[1], mptensor::Axes(1), mptensor::Axes(1));

  B.print_info(std::cout);
  B = mptensor::contract(B, mptensor::Axes(0), mptensor::Axes(3));

  
  // ptensor Btrans = mptensor::transpose(mpo[1], mptensor::Index(1,0,2,3));
  // for (int i = 0; i < Btrans.local_size(); i++)
  //   Btrans[i] = std::conj(Btrans[i]);
  // ptensor B = mptensor::tensordot(mpo[1],Btrans, mptensor::Axes(1), mptensor::Axes(0));
  // B = mptensor::contract(B, mptensor::Axes(0), mptensor::Axes(1));
  // ptensor C = mptensor::tensordot(A,B, mptensor::Axes(1), mptensor::Axes(0));
 
  // A.print_info(std::cout);
  // B.print_info(std::cout);
  // C.print_info(std::cout);
  // cout << "C[0] = " << sqrt(std::real(C[0])) << endl;

  /* End */
  MPI_Finalize();
}

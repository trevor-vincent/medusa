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

  int num = atoi(argv[1]);
  vector<int> bond_dims(num+1,3);
  bond_dims[0] = 1;
  bond_dims[num] = 1;
  std::vector<ptensor> mpo(num);

  for (int i = 0; i < num; i++) {
    mpo[i] = ptensor(Shape(2,2,bond_dims[i],bond_dims[i+1]));
    for(int j=0;j<mpo[i].local_size();++j) {
      mpo[i][j] = 1;
    }
  }  

  // ptensor & temp = mpo[0];
  ptensor res = mptensor::contract(mpo[0], mptensor::Axes(0), mptensor::Axes(1));
  
  for (int i = 1; i < num; i++){
    cout << "i = " << i << endl;
    mpo[i].print_info(std::cout);
    ptensor B = mptensor::contract(mpo[i], mptensor::Axes(0), mptensor::Axes(1));
    B.print_info(std::cout);
    res = mptensor::tensordot(res, B, mptensor::Axes(1), mptensor::Axes(0));
    res.print_info(std::cout);
    cout << endl;
  }
  cout << "res[0] = " << res[0] << endl;

  
  // ptensor A = mptensor::contract(mpo[0], mptensor::Axes(0), mptensor::Axes(1));
  // ptensor B = mptensor::contract(mpo[1], mptensor::Axes(0), mptensor::Axes(1));
  // ptensor C = mptensor::tensordot(A,B, mptensor::Axes(1), mptensor::Axes(0));
  // A.print_info(std::cout);
  // B.print_info(std::cout);
  // C.print_info(std::cout);
  // cout << "C[0] = " << C[0] << endl;

  /* End */
  MPI_Finalize();
}

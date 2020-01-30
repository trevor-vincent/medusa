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

  std::vector<ptensor> mpo(4);
  mpo[0] = ptensor(Shape(2,2,1,3));
  mpo[1] = ptensor(Shape(2,2,3,3));
  mpo[2] = ptensor(Shape(2,2,3,3));
  mpo[3] = ptensor(Shape(2,2,3,1));

  for(int i=0;i<mpo[0].local_size();++i) {
    mpo[0][i] = 1;
  }

  for(int i=0;i<mpo[1].local_size();++i) {
    mpo[1][i] = 1;
  }


  for(int i=0;i<mpo[2].local_size();++i) {
    mpo[2][i] = 1;
  }


  for(int i=0;i<mpo[3].local_size();++i) {
    mpo[3][i] = 1;
  }


  
  mpo[0].print_info(std::cout);
  // ptensor Atrans = mptensor::transpose(mpo[0], mptensor::Index(1,0,2,3));
  // Atrans.print_info(std::cout);
  // for (int i = 0; i < Atrans.local_size(); i++)
    // Atrans[i] = std::conj(Atrans[i]);
  ptensor A = mptensor::tensordot(mpo[0],mpo[0], mptensor::Axes(1), mptensor::Axes(1));

  // A.print_info(std::cout);
  A = mptensor::contract(A, mptensor::Axes(0), mptensor::Axes(3));  
  A.print_info(std::cout);

  // mpo[1].print_info(std::cout);
  ptensor B = mptensor::tensordot(mpo[1],mpo[1], mptensor::Axes(1), mptensor::Axes(1));

  // B.print_info(std::cout);
  B = mptensor::contract(B, mptensor::Axes(0), mptensor::Axes(3));
  B.print_info(std::cout);

  ptensor AB = tensordot(A,B, Axes(1,3), Axes(0,2));


  
  ptensor C = mptensor::tensordot(mpo[2],mpo[2], mptensor::Axes(1), mptensor::Axes(1));
  C = mptensor::contract(C, mptensor::Axes(0), mptensor::Axes(3));
  C.print_info(std::cout);

  ptensor D = mptensor::tensordot(mpo[3],mpo[3], mptensor::Axes(1), mptensor::Axes(1));
  D = mptensor::contract(D, mptensor::Axes(0), mptensor::Axes(3));
  D.print_info(std::cout);  

  ptensor CD = tensordot(C,D, Axes(1,3), Axes(0,2));

  AB.print_info(std::cout);
  CD.print_info(std::cout);

  ptensor ABCD = tensordot(AB, CD, Axes(2,3), Axes(0,1));
  ABCD.print_info(std::cout);
  cout << "ABCD[0] = " << ABCD[0] << endl;


  cout << "new way" << endl;
  ptensor ABC = tensordot(AB, C, Axes(2,3), Axes(0,2));
  ptensor ABCD_2 = tensordot(AB, D, Axes(2,3), Axes(0,2));
  // ptensor ABCD_2 = tensordot(ABC, D, Axes(2,3), Axes(0,2));
  A.print_info(std::cout,"A");
  B.print_info(std::cout,"B");
  C.print_info(std::cout,"C");
  D.print_info(std::cout,"D");
  
  AB.print_info(std::cout, "AB");
  ABC.print_info(std::cout, "ABC");
  ABCD_2.print_info(std::cout, "ABCD");
  cout << "ABCD_2[0] = " << ABCD_2[0] << endl;

  // ABCD_2.print_info(std::cout);
  

  
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

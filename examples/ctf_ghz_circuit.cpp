#include <bits/stdc++.h>
#include "/home/tvincent/Research/Codes/ctf/install/include/ctf.hpp"
using namespace std;
using namespace CTF;


//comile: mpicxx -o test ctf_ghz_circuit.cpp -I/home/tvincent/Research/Codes/ctf/install/include -L/home/tvincent/Research/Codes/ctf/lib -L/home/tvincent/Research/Codes/scalapack-2.1.0/install_fPIC/lib -lctf -fopenmp -lblas -llapack -lscalapack -lgfortran

using complex_vector = std::vector<std::complex<double>>;


template <typename T>
CTF::Vector<T> set_to_vec(const std::vector<T> & vec){

  int64_t  np;
  int64_t * idx;
  T* data;
  CTF::Vector<T> ctf_vec(vec.size());
  ctf_vec.get_local_data(&np, &idx, &data);
  ctf_vec.write(np, idx, &vec[0]);
  return ctf_vec;
}


template <typename T>
std::vector<T> outer_product(const std::vector<T> & x, const std::vector<T> & y){

  int x_size = x.size();
  int y_size = y.size();
  std::vector<T> xy(x_size*y_size);  
  for (int i = 0; i < x_size; i++){
    for (int j= 0; j< y_size; j++) {
      xy[i*x_size + j] = x[i]*std::conj(y[j]);
    }
  }   
  return xy;
}



template<class T> std::ostream& operator<<(std::ostream& os, const CTF::Vector<T> & v)
{
  int64_t  np;
  int64_t * idx;
  T* data;
  v.get_local_data(&np, &idx, &data);  
  os << '{';
  for (int i = 0; i<np; ++i) {
    os << "  ";
    os << data[i];
  }
  os << '}';
  return os;
}



template<class T> std::ostream& operator<<(std::ostream& os, const CTF::Matrix<T> & v)
{
  int64_t  np;
  int64_t * idx;
  T* data;
  v.get_local_data(&np, &idx, &data);  
  os << '{';
  for (int i = 0; i<np; ++i) {
    os << "  ";
    os << data[i];
  }
  os << '}';
  return os;
}



int main(int argc, char *argv[])
{
  MPI_Init(&argc, &argv);
  
  CTF::Vector<std::complex<double>> up = set_to_vec(complex_vector({1,0}));
  CTF::Vector<std::complex<double>> down = set_to_vec(complex_vector({0,1}));
  CTF::Matrix<std::complex<double>> puu = set_to_vec(outer_product(complex_vector({1,0}), complex_vector({0,1})));

  cout << up << endl;


  MPI_Finalize();
  return 0;
}

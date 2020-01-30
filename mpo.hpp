#ifndef MPO_H
#define MPO_H

#include <complex>
#include <vector>
#include <utility>
#include <mptensor.hpp>
#include "MPS.hpp"

namespace Medusa {

class MPO
{
private:
  typedef mptensor::Tensor<mptensor::scalapack::Matrix,std::complex<double>> ptensor;
  std::vector<ptensor> data_;  
  
public:
  MPO();
  MPO(int lattice_size,
      const std::pair<size_t>& d,
      const std::vector<size_t>& D)
  {
    for (int i = 0; i < lattice_size; i++){
      data_[i] = mptensor(Shape(d.first, d.second, D[i], D[i+1]));
    }
    
    assert();
  }
  // std::vector<size_t> BondDims();
  // void Compose();
  // void Compress();
  // void Split();
  double Frobenius(const MPO & mpo){
    for (int i = mpo.data_.size() - 1; i >= 0; i--){
      const int perm[4] = { 1, 0, 2, 3 }; // transpose physical dimensions
      ptensor A_dagger = transpose(data_[i], mptensor::Index(1, 0, 2, 3));
      ptensor & A = data_[i];
      for (int i = 0; i < A_dagger.local_size(); i++){
	A_dagger[i] = std::conj(A_dagger[i]);
      }
      // mptensor::tensordot;
      // Tensor C = tensordot(A,B,Axes(1),Axes(0));
    }    
  }

  std::complex<double> Trace(const MPO & mpo){
    ptensor & A = mpo.data_[L-1];
    for (int i = L-1; i > 0; i--){
      B = contract(A, mptensor::Axes(0), mptensor::Axes(1));
      C = tensor_dot(B,mpo.data_[i-1],Axes(2),Axes(3));
    }
  }
  
  // MPS Dot(const MPS & mps);
  // MPO Sum(const MPO & mpo_1, const MPO & mpo_2);
  // void Chain(const MPO & mpo_1, const MPO & mpo_2);
  // std::complex<double> Trace(const MPO & mpo);
};

} // namespace Medusa

#endif /* MPO_H */

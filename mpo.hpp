#ifndef MPO_H
#define MPO_H

#include <complex>
#include <vector>
#include <utility>
#include "Tensor.hpp"
#include "MPS.hpp"

namespace Medusa {

class MPO
{
private:
  std::vector<Medusa::Tensor> data_;  
  
public:
  MPO();
  MPO(int lattice_size,
      const std::pair<size_t>& d,
      const std::vector<size_t>& D)
  {
    for (int i = 0; i < lattice_size; i++){
      data_[i] = Medusa::Tensor(std::vector<int>{d.first, d.second, D[i], D[i+1]});
    }
  }
  // std::vector<size_t> BondDims();
  // void Compose();
  // void Compress();
  // void Split();
  double Frobenius(const MPO & mpo){


  }
  // MPS Dot(const MPS & mps);
  // MPO Sum(const MPO & mpo_1, const MPO & mpo_2);
  // void Chain(const MPO & mpo_1, const MPO & mpo_2);
  // std::complex<double> Trace(const MPO & mpo);
};

} // namespace Medusa

#endif /* MPO_H */

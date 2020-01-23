#ifndef MPS_H
#define MPS_H

#include <complex>
#include <vector>
#include <utility>
#include "Vector.hpp"

namespace Medusa {

class MPS {
private:
  std::vector<Medusa::Vector> data_;

public:
  MPS();
  std::complex<double> Dot(const MPS &mps);
};

}; // namespace Medusa

#endif /* MPS_H */

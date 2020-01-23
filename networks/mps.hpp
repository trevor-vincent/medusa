#pragma once

class MPS {


  MPS(){
    
  }


private:
  //  dimensions d x D_i x D_{i+1}; array of length L
  std::vector<CTF::Tensor<std::complex<double>>> A;
   
  // tensor_t *A;        //!< tensors associated with sites, with dimensions d x D_i x D_{i+1}; array of length L
  // size_t d;           //!< physical dimension of each site
  // qnumber_t  *qd;     //!< physical quantum numbers at each site
  // qnumber_t **qD;     //!< quantum numbers of virtual bonds; array of size L+1
  // int L;              //!< lattice size
  

};


 

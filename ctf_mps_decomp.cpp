#include <bits/stdc++.h> 
#include "/home/tvincent/Research/Codes/ctf/install/include/ctf.hpp"
using namespace CTF;
using namespace std;

using complex_double = std::complex<double>;
using complex_vector = std::vector<std::complex<double>>;


int main(int argc, char *argv[])
{

  MPI_Init(&argc, &argv);
  World dw;
  int d1 = atoi(argv[1]);
  int d2 = atoi(argv[2]);
  int d3 = atoi(argv[3]);
  int d4 = atoi(argv[4]);
  int r1 = atoi(argv[5]);
  int r2 = atoi(argv[6]);
  int r3 = atoi(argv[7]);
  double sp_frac = atof(argv[8]);
  
  int dangling_lens[4] = {d1, d2, d3, d4};
  int bond_lens[4] = {r1,r2,r3};
  
  bool is_sparse = sp_frac < 1.;

  Tensor<complex_double> T(4, is_sparse, dangling_lens, dw);

  T.fill_sp_random(-1.,1.,sp_frac);

  Tensor<complex_double> U, D, A, B, G1, G2, G3, G4;

  T["ijkl"].svd(G1["ai"],D["aa"],V1["ajkl"],r1);
  A["jkl"] = D["aa"]*V1["ajkl"];
  // A["jkl"].svd(G2["ajk"],D["aa"],V1["al"],r1);

  
  // A["il"] = D["a"]*G1["al"];
  // A["il"].svd(
			     

  
  // U["aijk"] *= S["a"];
  // U["aijk"].svd(U["abij"],S["b"],V2["bk"],R+2);
  // U["abij"] *= S["b"];
  // U["abij"].svd(U["abci"],S["c"],V3["cj"],R+1);
  // U["abci"] *= S["c"];
  // U["abci"].svd(U["abcd"],S["d"],V4["di"],R);
  // U["abcd"] *= S["d"];

  double Tnorm;
  T.norm2(Tnorm);
  T["ijkl"] -= G1["al"]*G2["bk"]*G3["cj"]*G4["di"];
  double Tnorm2;
  T.norm2(Tnorm2);
  double Rn = ((double)R)/n;
  bool pass = Tnorm2 <= (Tnorm*(1.-Rn*Rn*Rn*Rn) + 1.e-4);

  
  MPI_Finalize();
  return 0;
}

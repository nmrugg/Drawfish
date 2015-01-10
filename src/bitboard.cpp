namespace Bitboards { void init(); }

int A[8];
int B[8];
int C;

/// Bitboards::init() initializes various bitboard tables. It is called at
/// startup and relies on global objects to be already zero-initialized.

void Bitboards::init() {

  for (int f = 0; f <= 7; ++f)
      A[f] = f > 0 ? A[f - 1] << 1 : 0x01010101;

  for (int f = 0; f <= 7; ++f)
      B[f] = (f > 0 ? A[f - 1] : 0) | (f < 7 ? A[f + 1] : 0);

  C = B[7];
}


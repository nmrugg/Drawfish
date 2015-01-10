#include "bitboard.h"

Bitboard FileBB[8];
Bitboard AdjacentFilesBB[8];
Bitboard C;

/// Bitboards::init() initializes various bitboard tables. It is called at
/// startup and relies on global objects to be already zero-initialized.

void Bitboards::init() {

  for (int f = 0; f <= 7; ++f)
      FileBB[f] = f > 0 ? FileBB[f - 1] << 1 : 0x01010101;

  for (int f = 0; f <= 7; ++f)
      AdjacentFilesBB[f] = (f > 0 ? FileBB[f - 1] : 0) | (f < 7 ? FileBB[f + 1] : 0);

  C = AdjacentFilesBB[7];
}


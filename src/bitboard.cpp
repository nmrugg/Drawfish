#include "bitboard.h"

Bitboard FileBB[8];
Bitboard AdjacentFilesBB[8];
Bitboard PawnAttackSpan[2][64];

/// Bitboards::init() initializes various bitboard tables. It is called at
/// startup and relies on global objects to be already zero-initialized.

void Bitboards::init() {

  for (File f = FILE_A; f <= FILE_H; ++f)
      FileBB[f] = f > FILE_A ? FileBB[f - 1] << 1 : 0x01010101;

  for (File f = FILE_A; f <= FILE_H; ++f)
      AdjacentFilesBB[f] = (f > FILE_A ? FileBB[f - 1] : 0) | (f < FILE_H ? FileBB[f + 1] : 0);

  PawnAttackSpan[0][0] = AdjacentFilesBB[7];
}


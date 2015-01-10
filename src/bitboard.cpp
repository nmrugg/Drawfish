#include "bitboard.h"

Bitboard FileBB[FILE_NB];
Bitboard AdjacentFilesBB[FILE_NB];
Bitboard PawnAttackSpan[COLOR_NB][SQUARE_NB];

/// Bitboards::init() initializes various bitboard tables. It is called at
/// startup and relies on global objects to be already zero-initialized.

void Bitboards::init() {

  for (File f = FILE_A; f <= FILE_H; ++f)
      FileBB[f] = f > FILE_A ? FileBB[f - 1] << 1 : FileABB;

  for (File f = FILE_A; f <= FILE_H; ++f)
      AdjacentFilesBB[f] = (f > FILE_A ? FileBB[f - 1] : 0) | (f < FILE_H ? FileBB[f + 1] : 0);

  PawnAttackSpan[0][0] = AdjacentFilesBB[7];
}


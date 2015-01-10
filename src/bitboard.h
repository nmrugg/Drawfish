#ifndef BITBOARD_H_INCLUDED
#define BITBOARD_H_INCLUDED

#include <string>

#include "types.h"

namespace Bitboards { void init(); }

const Bitboard FileABB = 0x0101010101010101ULL;
const Bitboard Rank1BB = 0xFF;

extern Bitboard AdjacentFilesBB[FILE_NB];

inline Bitboard adjacent_files_bb(File f) {
  return AdjacentFilesBB[f];
}

#endif // #ifndef BITBOARD_H_INCLUDED

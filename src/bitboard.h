#ifndef BITBOARD_H_INCLUDED
#define BITBOARD_H_INCLUDED

#include <string>

#include "types.h"

namespace Bitboards {

void init();

}

const Bitboard FileABB = 0x0101010101010101ULL;
const Bitboard FileBBB = FileABB << 1;
const Bitboard FileCBB = FileABB << 2;
const Bitboard FileDBB = FileABB << 3;
const Bitboard FileEBB = FileABB << 4;
const Bitboard FileFBB = FileABB << 5;
const Bitboard FileGBB = FileABB << 6;
const Bitboard FileHBB = FileABB << 7;

const Bitboard Rank1BB = 0xFF;
const Bitboard Rank2BB = Rank1BB << (8 * 1);
const Bitboard Rank3BB = Rank1BB << (8 * 2);
const Bitboard Rank4BB = Rank1BB << (8 * 3);
const Bitboard Rank5BB = Rank1BB << (8 * 4);
const Bitboard Rank6BB = Rank1BB << (8 * 5);
const Bitboard Rank7BB = Rank1BB << (8 * 6);
const Bitboard Rank8BB = Rank1BB << (8 * 7);

extern int SquareDistance[SQUARE_NB][SQUARE_NB];

extern Bitboard FileBB[FILE_NB];
extern Bitboard RankBB[RANK_NB];
extern Bitboard AdjacentFilesBB[FILE_NB];
extern Bitboard InFrontBB[COLOR_NB][RANK_NB];
extern Bitboard StepAttacksBB[PIECE_NB][SQUARE_NB];
extern Bitboard BetweenBB[SQUARE_NB][SQUARE_NB];
extern Bitboard LineBB[SQUARE_NB][SQUARE_NB];
extern Bitboard DistanceRingBB[SQUARE_NB][8];
extern Bitboard ForwardBB[COLOR_NB][SQUARE_NB];
extern Bitboard PassedPawnMask[COLOR_NB][SQUARE_NB];
extern Bitboard PawnAttackSpan[COLOR_NB][SQUARE_NB];
extern Bitboard PseudoAttacks[PIECE_TYPE_NB][SQUARE_NB];


/// Overloads of bitwise operators between a Bitboard and a Square for testing
/// whether a given bit is set in a bitboard, and for setting and clearing bits.

inline bool more_than_one(Bitboard b) {
  return b & (b - 1);
}


/// rank_bb() and file_bb() return a bitboard representing all the squares on
/// the given file or rank.

inline Bitboard rank_bb(Rank r) {
  return RankBB[r];
}

inline Bitboard rank_bb(Square s) {
  return RankBB[rank_of(s)];
}

inline Bitboard file_bb(File f) {
  return FileBB[f];
}

inline Bitboard file_bb(Square s) {
  return FileBB[file_of(s)];
}

/// adjacent_files_bb() returns a bitboard representing all the squares on the
/// adjacent files of the given one.

inline Bitboard adjacent_files_bb(File f) {
  return AdjacentFilesBB[f];
}

#endif // #ifndef BITBOARD_H_INCLUDED

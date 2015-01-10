#include <algorithm>
#include <cstring>   // For std::memset

#include "bitboard.h"
#include "bitcount.h"
//#include "misc.h"

int SquareDistance[SQUARE_NB][SQUARE_NB];

Bitboard FileBB[FILE_NB];
Bitboard RankBB[RANK_NB];
Bitboard AdjacentFilesBB[FILE_NB];
Bitboard InFrontBB[COLOR_NB][RANK_NB];
Bitboard StepAttacksBB[PIECE_NB][SQUARE_NB];
Bitboard BetweenBB[SQUARE_NB][SQUARE_NB];
Bitboard LineBB[SQUARE_NB][SQUARE_NB];
Bitboard DistanceRingBB[SQUARE_NB][8];
Bitboard ForwardBB[COLOR_NB][SQUARE_NB];
Bitboard PassedPawnMask[COLOR_NB][SQUARE_NB];
Bitboard PawnAttackSpan[COLOR_NB][SQUARE_NB];

/// Bitboards::init() initializes various bitboard tables. It is called at
/// startup and relies on global objects to be already zero-initialized.

void Bitboards::init() {

  for (File f = FILE_A; f <= FILE_H; ++f)
      FileBB[f] = f > FILE_A ? FileBB[f - 1] << 1 : FileABB;

  for (Rank r = RANK_1; r <= RANK_8; ++r)
      RankBB[r] = r > RANK_1 ? RankBB[r - 1] << 8 : Rank1BB;

  for (File f = FILE_A; f <= FILE_H; ++f)
      AdjacentFilesBB[f] = (f > FILE_A ? FileBB[f - 1] : 0) | (f < FILE_H ? FileBB[f + 1] : 0);

  for (Rank r = RANK_1; r < RANK_8; ++r)
      InFrontBB[WHITE][r] = ~(InFrontBB[BLACK][r + 1] = InFrontBB[BLACK][r] | RankBB[r]);

  for (Color c = WHITE; c <= BLACK; ++c)
      for (Square s = SQ_A1; s <= SQ_H8; ++s)
      {
          ForwardBB[c][s]      = InFrontBB[c][rank_of(s)] & FileBB[file_of(s)];
          PawnAttackSpan[c][s] = InFrontBB[c][rank_of(s)] & AdjacentFilesBB[file_of(s)];
          PassedPawnMask[c][s] = ForwardBB[c][s] | PawnAttackSpan[c][s];
      }

  for (Square s1 = SQ_A1; s1 <= SQ_H8; ++s1)
      for (Square s2 = SQ_A1; s2 <= SQ_H8; ++s2)
          if (s1 != s2)
          {
              SquareDistance[s1][s2] = std::max(distance<File>(s1, s2), distance<Rank>(s1, s2));
              DistanceRingBB[s1][SquareDistance[s1][s2] - 1] |= s2;
          }

  int steps[][9] = { {}, { 7, 9 }, { 17, 15, 10, 6, -6, -10, -15, -17 },
                     {}, {}, {}, { 9, 7, -7, -9, 8, 1, -1, -8 } };

  for (Color c = WHITE; c <= BLACK; ++c)
      for (PieceType pt = PAWN; pt <= KING; ++pt)
          for (Square s = SQ_A1; s <= SQ_H8; ++s)
              for (int i = 0; steps[pt][i]; ++i)
              {
                  Square to = s + Square(c == WHITE ? steps[pt][i] : -steps[pt][i]);

                  if (is_ok(to) && distance(s, to) < 3)
                      StepAttacksBB[make_piece(c, pt)][s] |= to;
              }
}


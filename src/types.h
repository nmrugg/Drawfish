#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <cassert>
#include <cctype>
#include <climits>
#include <cstdlib>

#include <inttypes.h>
const bool HasPopCnt = true;

#define unlikely(x) (x) // For code annotation purposes

#define CACHE_LINE_SIZE 64

#ifdef IS_64BIT
const bool Is64Bit = true;
#else
const bool Is64Bit = false;
#endif

typedef uint64_t Key;
typedef uint64_t Bitboard;

const int MAX_MOVES = 256;
const int MAX_PLY   = 128;

/// A move needs 16 bits to be stored
///
/// bit  0- 5: destination square (from 0 to 63)
/// bit  6-11: origin square (from 0 to 63)
/// bit 12-13: promotion piece type - 2 (from KNIGHT-2 to QUEEN-2)
/// bit 14-15: special move flag: promotion (1), en passant (2), castling (3)
/// NOTE: EN-PASSANT bit is set only when a pawn can be captured
///
/// Special cases are MOVE_NONE and MOVE_NULL. We can sneak these in because in
/// any normal move destination square is always different from origin square
/// while MOVE_NONE and MOVE_NULL have the same origin and destination square.

enum Move {
  MOVE_NONE,
  MOVE_NULL = 65
};

enum MoveType {
  NORMAL,
  PROMOTION = 1 << 14,
  ENPASSANT = 2 << 14,
  CASTLING  = 3 << 14
};

enum Color {
  WHITE, BLACK, NO_COLOR, COLOR_NB = 2
};

enum CastlingSide {
  KING_SIDE, QUEEN_SIDE, CASTLING_SIDE_NB = 2
};

enum CastlingRight {
  NO_CASTLING,
  WHITE_OO,
  WHITE_OOO   = WHITE_OO << 1,
  BLACK_OO    = WHITE_OO << 2,
  BLACK_OOO   = WHITE_OO << 3,
  ANY_CASTLING = WHITE_OO | WHITE_OOO | BLACK_OO | BLACK_OOO,
  CASTLING_RIGHT_NB = 16
};

template<Color C, CastlingSide S> struct MakeCastling {
  static const CastlingRight
  right = C == WHITE ? S == QUEEN_SIDE ? WHITE_OOO : WHITE_OO
                     : S == QUEEN_SIDE ? BLACK_OOO : BLACK_OO;
};

enum Phase {
  PHASE_ENDGAME,
  PHASE_MIDGAME = 128,
  MG = 0, EG = 1, PHASE_NB = 2
};

enum ScaleFactor {
  SCALE_FACTOR_DRAW    = 0,
  SCALE_FACTOR_ONEPAWN = 48,
  SCALE_FACTOR_NORMAL  = 64,
  SCALE_FACTOR_MAX     = 128,
  SCALE_FACTOR_NONE    = 255
};

enum Bound {
  BOUND_NONE,
  BOUND_UPPER,
  BOUND_LOWER,
  BOUND_EXACT = BOUND_UPPER | BOUND_LOWER
};

enum Value {
  VALUE_ZERO      = 0,
  VALUE_DRAW      = 0,
  VALUE_KNOWN_WIN = 10000,
  VALUE_MATE      = 32000,
  VALUE_INFINITE  = 32001,
  VALUE_NONE      = 32002,

  VALUE_MATE_IN_MAX_PLY  =  VALUE_MATE - 2 * MAX_PLY,
  VALUE_MATED_IN_MAX_PLY = -VALUE_MATE + 2 * MAX_PLY,

  VALUE_ENSURE_INTEGER_SIZE_P = INT_MAX,
  VALUE_ENSURE_INTEGER_SIZE_N = INT_MIN,

  PawnValueMg   = 198,   PawnValueEg   = 258,
  KnightValueMg = 817,   KnightValueEg = 846,
  BishopValueMg = 836,   BishopValueEg = 857,
  RookValueMg   = 1270,  RookValueEg   = 1278,
  QueenValueMg  = 2521,  QueenValueEg  = 2558,

  MidgameLimit  = 15581, EndgameLimit  = 3998
};

enum PieceType {
  NO_PIECE_TYPE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING,
  ALL_PIECES = 0,
  PIECE_TYPE_NB = 8
};

enum Piece {
  NO_PIECE,
  W_PAWN = 1, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
  B_PAWN = 9, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
  PIECE_NB = 16
};

enum Depth {

  ONE_PLY = 1,

  DEPTH_ZERO          =  0,
  DEPTH_QS_CHECKS     =  0,
  DEPTH_QS_NO_CHECKS  = -1,
  DEPTH_QS_RECAPTURES = -5,

  DEPTH_NONE = -6,
  DEPTH_MAX  = MAX_PLY
};

enum Square {
  SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
  SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
  SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
  SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
  SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
  SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
  SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
  SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,
  SQ_NONE,

  SQUARE_NB = 64,

  DELTA_N =  8,
  DELTA_E =  1,
  DELTA_S = -8,
  DELTA_W = -1,

  DELTA_NN = DELTA_N + DELTA_N,
  DELTA_NE = DELTA_N + DELTA_E,
  DELTA_SE = DELTA_S + DELTA_E,
  DELTA_SS = DELTA_S + DELTA_S,
  DELTA_SW = DELTA_S + DELTA_W,
  DELTA_NW = DELTA_N + DELTA_W
};

enum File {
  FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NB
};

enum Rank {
  RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NB
};


/// The Score enum stores a middlegame and an endgame value in a single integer
/// (enum). The least significant 16 bits are used to store the endgame value
/// and the upper 16 bits are used to store the middlegame value. The compiler
/// is free to choose the enum type as long as it can store the data, so we
/// ensure that Score is an integer type by assigning some big int values.
enum Score {
  SCORE_ZERO,
  SCORE_ENSURE_INTEGER_SIZE_P = INT_MAX,
  SCORE_ENSURE_INTEGER_SIZE_N = INT_MIN
};

inline Score make_score(int mg, int eg) { return Score((mg << 16) + eg); }

/// Extracting the signed lower and upper 16 bits is not so trivial because
/// according to the standard a simple cast to short is implementation defined
/// and so is a right shift of a signed integer.
inline Value mg_value(Score s) {
  return Value(((s + 0x8000) & ~0xffff) / 0x10000);
}

inline Value eg_value(Score s) {
  return Value((int)(unsigned(s) & 0x7FFFU) - (int)(unsigned(s) & 0x8000U));
}

#define ENABLE_BASE_OPERATORS_ON(T)                             \
inline T operator+(T d1, T d2) { return T(int(d1) + int(d2)); } \
inline T operator-(T d1, T d2) { return T(int(d1) - int(d2)); } \
inline T operator*(int i, T d) { return T(i * int(d)); }        \
inline T operator*(T d, int i) { return T(int(d) * i); }        \
inline T operator-(T d) { return T(-int(d)); }                  \
inline T& operator+=(T& d1, T d2) { return d1 = d1 + d2; }      \
inline T& operator-=(T& d1, T d2) { return d1 = d1 - d2; }      \
inline T& operator*=(T& d, int i) { return d = T(int(d) * i); }

ENABLE_BASE_OPERATORS_ON(Score)

#define ENABLE_FULL_OPERATORS_ON(T)                             \
ENABLE_BASE_OPERATORS_ON(T)                                     \
inline T& operator++(T& d) { return d = T(int(d) + 1); }        \
inline T& operator--(T& d) { return d = T(int(d) - 1); }        \
inline T operator/(T d, int i) { return T(int(d) / i); }        \
inline int operator/(T d1, T d2) { return int(d1) / int(d2); }  \
inline T& operator/=(T& d, int i) { return d = T(int(d) / i); }

ENABLE_FULL_OPERATORS_ON(Value)
ENABLE_FULL_OPERATORS_ON(PieceType)
ENABLE_FULL_OPERATORS_ON(Piece)
ENABLE_FULL_OPERATORS_ON(Color)
ENABLE_FULL_OPERATORS_ON(Depth)
ENABLE_FULL_OPERATORS_ON(Square)
ENABLE_FULL_OPERATORS_ON(File)
ENABLE_FULL_OPERATORS_ON(Rank)

#undef ENABLE_FULL_OPERATORS_ON
#undef ENABLE_BASE_OPERATORS_ON

/// Additional operators to add integers to a Value
inline Value operator+(Value v, int i) { return Value(int(v) + i); }
inline Value operator-(Value v, int i) { return Value(int(v) - i); }
inline Value& operator+=(Value& v, int i) { return v = v + i; }
inline Value& operator-=(Value& v, int i) { return v = v - i; }

/// Only declared but not defined. We don't want to multiply two scores due to
/// a very high risk of overflow. So user should explicitly convert to integer.
inline Score operator*(Score s1, Score s2);

/// Division of a Score must be handled separately for each term
inline Score operator/(Score s, int i) {
  return make_score(mg_value(s) / i, eg_value(s) / i);
}

extern Value PieceValue[PHASE_NB][PIECE_NB];

struct ExtMove {
  Move move;
  Value value;
};

inline bool operator<(const ExtMove& f, const ExtMove& s) {
  return f.value < s.value;
}

inline Color operator~(Color c) {
  return Color(c ^ BLACK);
}

inline Square operator~(Square s) {
  return Square(s ^ SQ_A8); // Vertical flip SQ_A1 -> SQ_A8
}

inline CastlingRight operator|(Color c, CastlingSide s) {
  return CastlingRight(WHITE_OO << ((s == QUEEN_SIDE) + 2 * c));
}

inline Value mate_in(int ply) {
  return VALUE_MATE - ply;
}

inline Value mated_in(int ply) {
  return -VALUE_MATE + ply;
}

inline Square make_square(File f, Rank r) {
  return Square((r << 3) | f);
}

inline Piece make_piece(Color c, PieceType pt) {
  return Piece((c << 3) | pt);
}

inline PieceType type_of(Piece pc)  {
  return PieceType(pc & 7);
}

inline Color color_of(Piece pc) {
  assert(pc != NO_PIECE);
  return Color(pc >> 3);
}

inline bool is_ok(Square s) {
  return s >= SQ_A1 && s <= SQ_H8;
}

inline File file_of(Square s) {
  return File(s & 7);
}

inline Rank rank_of(Square s) {
  return Rank(s >> 3);
}

inline Square relative_square(Color c, Square s) {
  return Square(s ^ (c * 56));
}

inline Rank relative_rank(Color c, Rank r) {
  return Rank(r ^ (c * 7));
}

inline Rank relative_rank(Color c, Square s) {
  return relative_rank(c, rank_of(s));
}

#endif // #ifndef TYPES_H_INCLUDED

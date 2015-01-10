int A[8];
int B[8];
int C;

int main() {

  for (int f = 0; f <= 7; ++f)
      A[f] = f;

  for (int f = 0; f <= 7; ++f)
      B[f] = (f > 0 ? A[f - 1] : 0) | (f < 7 ? A[f + 1] : 0);

  C = B[7];
}


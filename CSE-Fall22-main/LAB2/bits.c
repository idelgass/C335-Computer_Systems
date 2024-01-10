/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Points: 3
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
}

/* 
 * getByte - Extract nth byte from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + - << >>
 *   Points: 6
 */
int getByte(int x, int n) {
  // Left shift by 3 = *8
  return (x >> (n << 3)) & 0xFF;
}

/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + - << >>
 *  Points: 6
 */
int byteSwap(int x, int n, int m) {
  /* Extract nth byte to nth
   * Extract mth byte to mth
   * Clear nth byte
   * Set nth byte to mth
   * Clear mth byte
   * Set mth byte to nth*/
  int nth = (x >> (n << 3)) & 0xFF;
  int mth = (x >> (m << 3)) & 0xFF;
  x &= ~(0xFF << (n << 3));
  x |= mth << (n << 3);
  x &= ~(0xFF << (m << 3));
  x |= nth << (m << 3);  
  return x;
}

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + - << >>
 *   Points: 10
 */
int logicalShift(int x, int n) {
  // Using temp as a mask to extract sign bit
  int temp = (1 << 31) >> n;
  temp = temp << 1;
  temp = ~temp;
  x = x >> n;
  return x & temp;
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + - << >>
 *   Points: 15
 */
int bitCount(int x) {
  int temp1, temp2, temp3, sum;
  temp1 = 0x11 | (0x11 << 8);
  temp2 = temp1 | (temp1 << 16);
  temp3 = 0xF|(0xF<<8);

  sum = x & temp2;

  sum += (x >> 1) & temp2;
  sum += (x >> 2) & temp2;
  sum += (x >> 3) & temp2;
  
  sum += sum >> 16;
  sum = (sum & temp3) + ((sum >> 4) & temp3); 

  return (sum + (sum >> 8)) & 0x3F;
}

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + - << >>
 *   Points: 15
 */
int bang(int x) {
  int neg = ~x + 1;
  int xmasked = ((x >> 31) & 1);
  int negxmasked = ((neg >> 31) & 1);
  return (xmasked|negxmasked)^1;
}

/*
 * bitParity - returns 1 if x contains an odd number of 1's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + - << >>
 *   Points: 15
 */
int bitParity(int x) {
  return 2;
}

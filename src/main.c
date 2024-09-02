#include <windows.h>

// NOTE: Assumptions (based on gunnarmorling's readme, OLD assumptions did not use this)
// - station names are in the range [1, 100] bytes
// - temperatures are in the range [-99.9, 99.9] always with one fractional digit
// => fits as fixed point in s16, maximum accumulated fixed point temperature is 999*1e9 ~= 2^40
// - there are maximum 10000 unique station names
// => hash table could be as small as 1 MB
// - line endings are only \n on all platforms
//
// ~~NOTE: Assumptions~~ OLD
// - the program only needs to process 1 billion rows, and not be able to continue afterwards
// - the temperature measurements are in the range [-90, 57] *C and [-129, 135] *F, (coldest and hottest recorded temperatures according to Mr. Google)
// => the maximum accumulated temperature in fixed point is 900*1e9 ~= 2^40
// => either accumulated fixed point s64, accumulated f64 or running average f32
// - the longest station name is 85 letters (longest place name in the world)
// - most station names are probably less than 25 letters in length
// => most lines can probably be processed with a single 256 bit register, fallback otherwise
// - total possible number of station names cannot exceed ~4.3e6 (simplemaps claims to have a comprehensive database of the worlds cities and towns, totaling ~4.3e6 entries)
// => possible to fit all station names in a 128 MB table with 24 bytes per entry


int
main(int argc, char** argv)
{
  return 0;
}

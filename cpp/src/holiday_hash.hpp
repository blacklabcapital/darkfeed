/* C++ code produced by gperf version 3.0.4 */
/* Command-line: gperf -I -c -s 2 -Z HolidayHash --output-file=holiday_hash.hpp holidays.gperf  */
/* Computed positions: -k'4,7,10' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#include <string.h>

#define TOTAL_KEYWORDS 32
#define MIN_WORD_LENGTH 10
#define MAX_WORD_LENGTH 10
#define MIN_HASH_VALUE 7
#define MAX_HASH_VALUE 220
/* maximum key range = 214, duplicates = 0 */

class HolidayHash
{
private:
  static inline unsigned int hash (const char *str, unsigned int len);
public:
  static const char *in_word_set (const char *str, unsigned int len);
};

inline /*ARGSUSED*/
unsigned int
HolidayHash::hash (const char *str, unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221,  25,  20,
       65,   2,  15,  75,   5,   0,  35, 110, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221, 221, 221, 221,
      221, 221, 221, 221, 221, 221, 221
    };
  return asso_values[(unsigned char)str[9]] + asso_values[(unsigned char)str[6]] + asso_values[(unsigned char)str[3]+1];
}

const char *
HolidayHash::in_word_set (const char *str, unsigned int len)
{
  struct stringpool_t
    {
      char stringpool_str7[sizeof("2015-07-03")];
      char stringpool_str15[sizeof("2016-07-04")];
      char stringpool_str20[sizeof("2015-07-04")];
      char stringpool_str22[sizeof("2015-04-03")];
      char stringpool_str25[sizeof("2015-11-27")];
      char stringpool_str30[sizeof("2015-11-26")];
      char stringpool_str35[sizeof("2016-11-24")];
      char stringpool_str40[sizeof("2016-01-01")];
      char stringpool_str45[sizeof("2015-01-01")];
      char stringpool_str50[sizeof("2017-07-04")];
      char stringpool_str55[sizeof("2016-01-18")];
      char stringpool_str57[sizeof("2017-11-23")];
      char stringpool_str65[sizeof("2017-04-14")];
      char stringpool_str70[sizeof("2016-12-26")];
      char stringpool_str75[sizeof("2015-02-16")];
      char stringpool_str77[sizeof("2016-03-25")];
      char stringpool_str80[sizeof("2016-12-24")];
      char stringpool_str85[sizeof("2015-12-24")];
      char stringpool_str90[sizeof("2017-01-18")];
      char stringpool_str95[sizeof("2016-11-25")];
      char stringpool_str100[sizeof("2016-05-30")];
      char stringpool_str115[sizeof("2015-09-07")];
      char stringpool_str120[sizeof("2017-01-02")];
      char stringpool_str125[sizeof("2017-02-20")];
      char stringpool_str135[sizeof("2015-01-19")];
      char stringpool_str140[sizeof("2016-02-15")];
      char stringpool_str145[sizeof("2015-12-25")];
      char stringpool_str155[sizeof("2015-05-25")];
      char stringpool_str160[sizeof("2017-09-04")];
      char stringpool_str175[sizeof("2017-12-25")];
      char stringpool_str185[sizeof("2016-09-05")];
      char stringpool_str220[sizeof("2017-05-29")];
    };
  static const struct stringpool_t stringpool_contents =
    {
      "2015-07-03",
      "2016-07-04",
      "2015-07-04",
      "2015-04-03",
      "2015-11-27",
      "2015-11-26",
      "2016-11-24",
      "2016-01-01",
      "2015-01-01",
      "2017-07-04",
      "2016-01-18",
      "2017-11-23",
      "2017-04-14",
      "2016-12-26",
      "2015-02-16",
      "2016-03-25",
      "2016-12-24",
      "2015-12-24",
      "2017-01-18",
      "2016-11-25",
      "2016-05-30",
      "2015-09-07",
      "2017-01-02",
      "2017-02-20",
      "2015-01-19",
      "2016-02-15",
      "2015-12-25",
      "2015-05-25",
      "2017-09-04",
      "2017-12-25",
      "2016-09-05",
      "2017-05-29"
    };
  #define stringpool ((const char *) &stringpool_contents)
  static const int wordlist[] =
    {
      -1, -1, -1, -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str7,
      -1, -1, -1, -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str15,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str20,
      -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str22,
      -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str25,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str30,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str35,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str40,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str45,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str50,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str55,
      -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str57,
      -1, -1, -1, -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str65,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str70,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str75,
      -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str77,
      -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str80,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str85,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str90,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str95,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str100,
      -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str115,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str120,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str125,
      -1, -1, -1, -1, -1, -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str135,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str140,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str145,
      -1, -1, -1, -1, -1, -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str155,
      -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str160,
      -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str175,
      -1, -1, -1, -1, -1, -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str185,
      -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1,
      (int)(long)&((struct stringpool_t *)0)->stringpool_str220
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          int o = wordlist[key];
          if (o >= 0)
            {
              const char *s = o + stringpool;

              if (*str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
                return s;
            }
        }
    }
  return 0;
}
#line 39 "holidays.gperf"

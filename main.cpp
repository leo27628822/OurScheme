
# include <iostream>
# include <map>
# include <string>
# include <vector>
# include <sstream>
# include <exception>
# include <iomanip>
# include <cctype>
# include <cstdlib>
# include <cstring>
# include <cstdio>

using namespace std;

enum TokenType {
  EMPTY, NIL, INT, FLOAT, DOT, T, STRING, SHARP,
  OPERATOR, LEFT_PAREN, RIGHT_PAREN, SYMBOL,
  CONS, LIST, QUOTE, DEFINE, CAR, CDR, ISPAIR, ISLIST, ISATOM, ISNULL,
  ISINT, ISREAL, ISNUM, ISSTR, ISBOOL, ISSYM, ADD, SUB, MULT, DIV,
  NOT, AND, OR, BIGG, BIGEQ, SML, SMLEQ, EQ, STRAPP, STRBIG,
  STRSML, STREQL, ISEQV, ISEQL, BEGIN, IF, COND, LET, LAMBDA, PRINT, READ,
  WRITE, EVAL, DSPSTR, NEWLINE, SYMTOSTR, NUMTOSTR, SET, CEATEOBJ, ISERROBJ,
  VERBOS, ISVERBOS, EXIT, CLEAN, USRFUNC, ERROBJ
};

int main()
{
    cout << "Hello World!" << endl ;
    cout << "Hello World!" << endl ;
    return 0;
}

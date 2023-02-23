// CYCU PL's project-OurScheme
// 10927143 王胤迦 2023/02/14 開工
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

int gTestNum = 0, gLine = 0, gColumn = 0 ;
bool gEOF = false ;

enum TokenType {
  EMPTY, NIL, INT, FLOAT, DOT, T, STRING, SHARP,
  OPERATOR, LEFT_PARENTHESIS, RIGHT_PARENTHESIS, SYMBOL,
  CONS, LIST, QUOTE, DEFINE, CAR, CDR, ISPAIR, ISLIST, ISATOM, ISNULL,
  ISINT, ISREAL, ISNUM, ISSTR, ISBOOL, ISSYM, ADD, SUB, MULT, DIV,
  NOT, AND, OR, BIGG, BIGEQ, SML, SMLEQ, EQ, STRAPP, STRBIG,
  STRSML, STREQL, ISEQV, ISEQL, BEGIN, IF, COND, LET, LAMBDA, PRINT, READ,
  WRITE, EVAL, DSPSTR, NEWLINE, SYMTOSTR, NUMTOSTR, SET, CEATEOBJ, ISERROBJ,
  VERBOS, ISVERBOS, EXIT, CLEAN, USRFUNC, ERROBJ
};

enum ExcpType { NULLERR, EOFENCT, REQ_ATOM, REQ_RIGHT_P, EOLENCT, NONFUNC, NONLIST, WRONGTYPE, DEFERR,
                WRONGARGNUM, UNBOND, DEFLVERR, CLEANLVERR, EXITLVERR, DIVZRO, NORET, CNDERR, LETERR,
                LAMBERR, UNBONDPARA, UNBONDTEST, UNBONDCOND, NORET_B, SETERR
};

/* 
    最長寫到這邊---------------------------------------------------------------
*/

class Scanner {
public:
  
  Scanner() {
    gLine = gColumn = 0 ;
  } // Scanner()

  char Getchar() {
    char c = getchar();
    if ( c == -1 ) 
      return '\r';
    ++gColumn ;
    return c ;
  } // Getchar()

  void Putback( char ch ) {
    cin.putback( ch );
    --gCol;
  } // Putback()

private:
  string mLineBuf;
};
Scanner gScan ;

class Token ;
typedef Token * TokenPtr ;


class Token {
  public:
    int mType ;
    string mContent ;
    TokenPtr mPtrList[3] ;

    Token() {
      mType = EMPTY ;
      mContent = "" ;
      mPtrList[0] = mPtrList[1] = mPtrList[2] = NULL ;
    } // Token()

};

class Function {

  public:
    TokenPtr GetToken() {
      TokenPtr token = new Token() ;
      char ch = gScan.Getchar() ;
      if ( ch == '\r' ) {
        gEOF = true ;
        return token ;
      } // if
      if ( ch == '(' ) {
        token -> mType = LEFT_PARENTHESIS ;
        token -> mContent = "(" ;
        return token ;
      } // if
      if ( ch == ')' ) {
        token -> mType = RIGHT_PARENTHESIS ;
        token -> mContent = ")" ;
        return token ;
      } // if
      if ( ch == '.' ) {
        token -> mType = DOT ;
        token -> mContent = "." ;
        return token ;
      } // if
      if ( ch == '\'' ) {
        token -> mType = QUOTE ;
        token -> mContent = "'" ;
        return token ;
      } // if
      if ( ch == '#' ) {
        token -> mType = SHARP ;
        token -> mContent = "#" ;
        return token ;
      } // if
      if ( ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>' ) {
        token -> mType = OPERATOR ;
        token -> mContent = ch ;
        return token ;
      } // if
      if ( ch == ' ' || ch == '\t' || ch == '\n' ) {
        if ( ch == '\n' ) {
          ++gLine ;
          gColumn = 0 ;
        } // if
        return GetToken() ;
      } // if
      if ( ch == '"' ) {
        token -> mType = STRING ;
        token -> mContent = "" ;
        while ( ( ch = gScan.Getchar() ) != '"' ) {
          if ( ch == '\r' ) {
            throw ExcpType::EOLENCT ;
          } // if
          token -> mContent += ch ;
        } // while
        return token ;
      } // if
      if ( isdigit( ch ) ) {
        token -> mType = INT ;
        token -> mContent = ch ;
        while ( isdigit( ch = gScan.Getchar() ) ) {
          token -> mContent += ch ;
        } // while
        if ( ch == '.' ) {
          token -> mType = FLOAT ;
          token -> mContent += ch ;
    } // GetToken()

    void PrintToken( TokenPtr token ) {
      while ( token -> PtrList[2] != NULL ) {
        cout << token -> mContent << " " ;
        token = token -> PtrList[0] ;
      } // while
    } // PrintToken()

};
/*
class Parser {

}

class Evaluator {

}

class Execption {

}
*/

int main()
{
    cout << "Welcome to OurScheme!\n\n" ;

    cin >> gTestNum ;
    cin.ignore() ;
    TokenPtr token = NULL ;

    while ( !gEOF ) {
        cout << "> " ;
        gScan.Scan();
        // ss << fixed << setprecision( 3 ) << atof( t->mContent.c_str() ) ;
    } // while
    return 0;
}

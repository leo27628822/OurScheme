// CYCU PL's project-OurScheme
// 10927143 王胤迦 2023/02/14 開工
# include <iostream>
# include <map>
# include <string>
# include <vector>
# include <sstream>
# include <iomanip>
# include <cctype>
# include <cstdlib>
# include <string.h>
# include <stdio.h>

using namespace std ;

int gTestNum = 0 ;

enum Token_Type {
  LEFT_PAREN = 1, RIGHT_PAREN = 2, DOT = 3, QUOTE = 4, SYMBOL = 5,
  INT = 6, FLOAT = 7, STRING = 8, NIL = 9, TRUE = 10,
  SEMI_COLON = 11, ATOM = 12, PAREN_QUOTE = 13, DOT_PAREN = 14, 
  END_OF_FILE = 15, INITIAL = 16
};

enum Error_Type {
  UNEXPEXTED_ATOM_OR_LEFT_PAREN = 100,
  UNEXPECTED_RIGHT_PAREN = 200,
  NO_CLOSING_QUOTE = 300,
  ERROR_EOF = 400,
  QUIT_SCHEME = 500
};

struct Token {
  string name ;
  int type ;
  int line ;
  int column ;
  Token * left ;
  Token * right ;
};

typedef Token * NodePtr ;

/* 
    最長寫到這邊---------------------------------------------------------------
*/

class Scanner {

  public :

    int mLine ;
    int mColumn ;

    Scanner() {
      mLine = 1 ;
      mColumn = 0 ;
    } // Scanner()

    void SkipSpace() {
      char c = '\0' ;

      while ( ( c = cin.get() ) != EOF ) {
        mColumn++ ;

        if ( c == '\n' ) {
          mLine++ ;
          mColumn = 0 ;
        } // if

        c = cin.peek() ;
        if ( !isspace( c ) ) {
          return ;
        } // if

      } // while

    } // SkipSpace()

    void GetToken( Token & token ) {
      int ch = 0 ;
      string str = "" ;

      ch = cin.peek() ;
      if ( isspace( ch ) ) {
        SkipSpace() ;
      } // if

      ch = cin.peek() ;
      if ( ch == '(' || ch == ')' ) {
        GetParen( token ) ;
      } // if
      else if ( ch == '#' ) {
        GetPoundSign( token ) ;
      } // else if
      else if ( ch == '\'' || ch == '"' ) {
        GetQuote( token ) ;
      } // else if
      else if ( ch == ';' ) {
        GetSemicolon( token ) ;
      } // else if
      else if ( ch == '+' || ch == '-' || ch == '.' || 
                isdigit( ch ) ) {
        GetNumber( token ) ;
      } // else if
      else if ( ch == EOF ) {
        token.name = "" ;
        token.type = END_OF_FILE ;
      } //else if
      else {
        GetSymbol( token, str ) ;
      } // else
      
    } // GetToken()

    void GetParen( Token & token ) {
      char c = cin.peek() ;

      if ( c == '(' ) {
        c = cin.get() ;
        token.name += c ;
        token.type = LEFT_PAREN ;
        mColumn++ ;
        token.column = mColumn ;

        c = cin.peek() ;
        if ( isspace( c ) ) {
          SkipSpace() ;
        } // if
    
        c = cin.peek() ;
        if ( c == ')' ) {
          // get '()' 
          c = cin.get() ;
          mColumn++ ;
          token.column = mColumn ;
          token.name += c ;
          token.type = NIL ;
        } // if

      } // if
      else {
        c = cin.get() ;
        token.type = RIGHT_PAREN ;
        token.name += c ;
        mColumn++ ;
        token.column = mColumn ;
      } // else

      token.line = mLine ;

    } // GetParen()

    void GetSemicolon( Token & token ) {
      char c = cin.get() ;

      mColumn++ ;
      token.column = mColumn ;
      token.line = mLine ;

      GetGarbage() ;
      mLine++ ;
      mColumn = 0 ;

      token.name = c ;
      token.type = SEMI_COLON ;

    } // GetSemicolon()

    void GetPoundSign( Token & token ) {
      char c = cin.get() ;
      string str ;
      str += c ;
      mColumn++ ;
      token.column = mColumn ;
      token.line = mLine ;

      c = cin.peek() ;
      if ( c == 't' || c == 'f' ) {
        c = cin.get() ;
        mColumn++ ;
        str += c ;

        if ( c == 't' ) {
          token.type = TRUE ;
        } // if
        else {
          token.type = NIL ;
        } // else

        c = cin.peek() ;
        if ( isspace( c ) || c == '(' || c == ')' || 
             c == '"' || c == '\'' || c == ';' ) {
          token.name = str ;
          return ;
        } // if
        else {
          GetSymbol( token, str ) ;
        } // else

      } // if
      else if ( isspace( c ) ) {
        token.name = str ;
        token.type = SYMBOL ;
      } // else if
      else {
        GetSymbol( token, str ) ;
      } // else
    } // GetPoundSign()

    void GetSymbol( Token & token, string str ) {
      char c = cin.peek() ;
      bool stop = false ;
      string str_tmp = "" ;

      token.line = mLine ;
      if ( isspace( c ) || c == '(' || c == ')' || 
           c == '"' || c == '\'' || c == ';' ) {
        stop = true ;
      } // if

      while ( !stop && ( c = cin.get() ) != EOF ) {
        mColumn++ ;
        if ( token.column == 0 ) {
          token.column = mColumn ;
        } // if
        
        str += c ;
        c = cin.peek() ;

        if ( isspace( c ) || c == '(' || c == ')' || 
             c == '"' || c == '\'' || c == ';' ) {
          stop = true ;
        } // if

      } // while

      if ( str == "t" ) {
        token.type = TRUE ;
      } // if
      else if ( str == "f" ) {
        token.type = NIL ;
      } // else if
      else {
        token.type = SYMBOL ;
      } // else
      
      token.name = str ;

    } // GetSymbol()

    void GetQuote( Token & token ) {
      char c = cin.get() ;
      
    } // GetQuote()

} // Scanner

int main() {
  cin >> gTestNum ;
  cin.ignore() ;

  bool isExit = false ;
  Parser parser ;

  cout << "Welcome to OurScheme!\n\n" ;

  while ( !isExit ) {
    try {
      cout << "> " ;
      parser.ReadExp() ;
      parser.BuildTree() ;
      parser.Prettyprint( parser.GetRoot() ) ;
      parser.Init() ;
      cout << "\n" ;

    } catch ( Exception * error ) {

      parser.DealError( error ) ;
      if ( error -> mType == ERROR_EOF || error -> mType == QUIT_SCHEME ) {
        isExit = true ;
      } // if

    } // catch

  } // while

  cout << "\nThanks for using OurScheme!\n" ;

} // main()
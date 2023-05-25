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

int gTestNum = 0, gRow = 1, gCol = 0 ;
bool gHasOutput = false, gExit = false ;

// enum Token_Type { LEFT_PAREN, RIGHT_PAREN, INT, STRING, DOT, FLOAT,  NIL, T,  
//                 QUOTE, SYMBOL } ;

enum Token_Type {
  EMPTY, NIL, INT, FLOAT, DOT, T, STRING, HASH,
  OPERATOR, LEFT_PAREN, RIGHT_PAREN, SYMBOL,
  CONS, LIST, QUOTE, DEFINE, CAR, CDR, ISPAIR, ISLIST, ISATOM, ISNULL,
  ISINT, ISREAL, ISNUM, ISSTR, ISBOOL, ISSYM, ADD, SUB, MULT, DIV,
  NOT, AND, OR, BIGG, BIGEQ, SML, SMLEQ, EQ, STRAPP, STRBIG,
  STRSML, STREQL, ISEQV, ISEQL, BEGIN, IF, COND, LET, LAMBDA, PRINT, READ,
  WRITE, EVAL, DSPSTR, NEWLINE, SYMTOSTR, NUMTOSTR, SET, CEATEOBJ, ISERROBJ,
  VERBOS, ISVERBOS, EXIT, CLEAN, USRFUNC, ERROBJ
};

struct gToken{
  string content = "" ;
  int type = -1 ;
};

/* 
    最長寫到這邊---------------------------------------------------------------
*/

void ReadExpression( vector<gToken> & expression ) {

  bool end_of_read = false ;
  bool in_string = false, in_quote = false ;
  char c ;
  int num_of_paren = 0 ;
  gToken t ;
  while ( !end_of_read ) {
    if ( ( c = getchar() ) == EOF ) {
      c == '\r' ;
    } // if

    if ( t.type == -1 ) {
      if ( isalpha( c ) ) {
        if ( c == 't' ) {
          t.type == T ;
        } // if
        else {
          t.type == SYMBOL ;
        }
      } // if
      else if ( isdigit( c ) ) {
        t.type == INT ;
      } // else if
      else if ( c == '(' ) {
        t.type == LEFT_PAREN ;
        end_of_read = true ;
      } // else if
      else if ( c == ')' ) {
        t.type == RIGHT_PAREN ;
        end_of_read = true ;
      } //else if
      else if ( c == '.' ) {
        t.type == DOT ;
      } // else if
      else if ( c == '\'' ) {
        t.type == QUOTE ;
        end_of_read = true ;
      } // else if
      else if ( c == '\"' ) {
        t.type == STRING ;
      } // else if
      else if ( c == '#' ) {
        t.type == HASH ;
      } // else if
      else if ( c == '+' || c == '-' ) {
        t.type == OPERATOR ;
      } // else if
      else if ( isspace( c ) ) {
        if ( c == '\n' ) {
          if ( gHasOutput ) {
            gRow = 1 ;
            gHasOutput = false ;
          } // if
          else {
            gRow++ ;
          } // else

          gCol = 0 ;
        } // if
        else if ( c == '\r' ) {
          gExit = true ;
          throw "ERROR (no more input) : END-OF-FILE encountered" ;
        } // else if
      } // else if
      else if ( c == ';' ) {
        char tmp ;
        do {
          if (  ( tmp = getchar() ) == EOF ) {
            gExit = true ;
            throw "ERROR (no more input) : END-OF-FILE encountered" ;
          } // if
        } while ( tmp != '\n' ) ;

        cin.putback( tmp ) ;
      } // else if
      else {
        t.type = SYMBOL ;
      } // else
      
      if ( !isspace( c ) && c != ';' ) {
        t.content += c ;
      } // if

    } // if
    else if ( t.type == HASH ) {
      if ( isalpha( c ) ) {
        if ( c == 't' ) {
          t.type == T ;
        } // if
        else if ( c == 'f' ) {
          t.type == NIL ;
        } // else if
        else {
          t.type == SYMBOL ;
        } // else
        
        t.content += c ;
      } // if
      else if ( isdigit( c ) ) {
        t.type = SYMBOL ;
        t.content += c ;
      } // else if
      else if ( t == '(' || t == ')' || )  // DOOOOOOOOOOOOOOOOOOOOOO

    } // else if

  } // while

  
} // ReadExpression()

void PrintExpression( vector<gToken> & expression ) {
  cout << "Expression: " ;
  for ( int i = 0 ; i < expression.size() ; ++i ) {
    cout << expression[i].content << " " ;
  } // for
  cout << "\n" ;
} // PrintExpression()

int main()
{
  cout << "Welcome to OurScheme!" ;
  cout << "\n> " ;

  cin >> gTestNum ;
  cin.ignore() ;

  vector<gToken> expression ;
  string str_tmp ;
  cout << "\n> " ;

  while ( true ) {
    try {
      ReadExpression( expression ) ;
      PrintExpression( expression ) ;
      expression.clear() ;
      expression.shrink_to_fit() ;
      cout << "\n> " ;
    } catch ( const char * msg ) {
      cout << msg << "\n" ;
    } // catch
    
  } // while

  cout << "Thanks for using OurScheme!" ;
  return 0 ;

} // main()

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

int gTestNum = 0, gRow = 0, gCol = 0 ;
bool gEOF = false, gExit = false ;

enum Token_Type{ SYMBOL, INT, FLOAT, STRING, NIL, T, LEFT_PAREN, RIGHT_PAREN,
                 QUOTE, DOT } ;

struct gToken{
  string content = "" ;
  int type = -1 ;
};


/* 
    最長寫到這邊---------------------------------------------------------------
*/

class Scanner {
  public:

  Scanner() {
    gRow = gCol = 0 ;
  } // Scanner()

  char Getchar() {
    char c = getchar();
    if ( c == -1 ) 
      return '\r';
    ++gCol ;
    return c ;
  } // Getchar()

  void Putback( char ch ) {
    cin.putback( ch );
    --gCol ;
  } // Putback()

};

Scanner gScan ;

void ReadSExp( vector<gToken> & tk ) {

  bool done = false ;
  char c = '\0' ;
  stringstream ss ;
  gToken TokenType ;
  int paren = 0 ;
  while ( !done ) {

    c = gScan.Getchar() ;

    if ( c == ';' ) { // comment
      while ( c != '\n' && c != '\r' )
        c = gScan.Getchar() ;
    } // if
    else if ( c == '(' ) {
      TokenType.content += c ;
      TokenType.type = LEFT_PAREN ;
      tk.push_back( TokenType ) ;
      ++paren ;
    } // else if
    else if ( c == ')' ) {
      TokenType.content += c ;
      TokenType.type = RIGHT_PAREN ;
      tk.push_back( TokenType ) ;
      --paren ;
      if ( paren == 0 ) done = true ;
      else if ( paren < 0 ) {
        cout << "ERROR(unexpected token):\')\'expexted when token at Line " << gRow << " Column " << gCol << "\n" ;
        done = true ;
      } // else if
    } // else if
    else if ( c == '\'' ) {
      TokenType.type = QUOTE;
      c = gScan.Getchar();
      while (c != '\'') {
        TokenType.content += c;
        c = gScan.Getchar();
      }
      tk.push_back(TokenType);
      while ( c != '\r' && c != '\n' ) {
        TokenType.content += c ;
        c = gScan.Getchar() ;
      } // while

      tk.push_back( TokenType ) ;
      if ( c == '\r' ) {
        cout << "ERROR(no closing quote):END-OF-FILE encountered at Line " << gRow << " Column " << gCol << "\n" ;
        done = true ;
      } // else if

    } // else if
    else if ( c == '\"' ) {
      TokenType.type = STRING ;
      while ( c != '\r' &&  c != '\n' ) {
        TokenType.content += c ;
        c = gScan.Getchar() ;
      } // while

      if ( c == '\n' ) {
        cout << "ERROR(no closing quote):END-OF-LINE encountered at line " << gRow << " column " << gCol << "\n" ;
        done = true ;
      } // if
      else if ( c == '\r' ) {
        cout << "ERROR(no closing quote):END-OF-FILE encountered at line " << gRow << " column " << gCol << "\n" ;
        done = true ;
      } // else if
      else {
        tk.push_back( TokenType ) ;
      } // else

    } // else if
    else if ( c == '\n' ) {
      ++gRow ;
      gCol = 0 ;
    } // else if
    else if ( c == '\r' ) {
      gEOF = true ;
      done = true ;
    } // else if
    else if ( c == ' ' || c == '\t' ) {
      tk.push_back( TokenType ) ;
      TokenType.content = "" ;
      TokenType.type = -1 ;
    } // else if
    else if ( isdigit(c) ) {
      TokenType.type = INT ;
      while ( isdigit(c) ) {
        TokenType.content += c ;
        c = gScan.Getchar() ;
      } // while
      
      gScan.Putback(c) ;
    } // else
    else if ( isalpha(c) ) {
      TokenType.type = SYMBOL ;
      while ( isalpha(c) ) {
        TokenType.content += c ;
        c = gScan.Getchar() ;
      } // while

      gScan.Putback(c) ;
    } // else if
    else {
      cout << "ERROR: invalid token\n" ;
      done = true ;
    } // else

    if ( c != '\n' && c != '\r' )
      tk.push_back( TokenType ) ;
    TokenType.content = "" ;
    TokenType.type = -1 ;
    
  } // while
   
} // ReadToken()

void PrintToken( stringstream & ss ) {

  string s ;
  ss >> s ;
  cout << s << "\n" ; 

} // PrintToken()

int main()
{
  cout << "Welcome to OurScheme!\n" ;
  cout << "> " ;

  cin >> gTestNum ;
  cin.ignore() ;

  vector<gToken> expr ;

  while ( !gEOF ) {
    
    ReadSExp(expr) ;
    // PrintSExp(expr) ;

    expr.clear() ;
    cout << "> " ;
  } // while

  if ( gExit ) {
    cout << "ERROR(no more input):END-OF-FILE encoutered\n" ;
  } // if

  cout << "Thanks for using OurScheme!" ;
  return 0 ;

} // main()

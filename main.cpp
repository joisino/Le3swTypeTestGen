#include <bits/stdc++.h>

using namespace std;

mt19937 mt;

int cnt = 5;

void expr();

char randid(){
  int x = mt() % 3;
  return 'a' + x;
}

void ifexpr(){
  cout << "if ";
  expr();
  cout << " then ";
  expr();
  cout << " else ";
  expr();
}

void funexpr(){
  cout << "fun " << randid() << " -> ";
  expr();
}

void aexpr(){
  cnt--;
  int a = mt() % 16;
  if( cnt < 0 ){
    a = mt() % 12;
  }
  if( a < 9 ){
    cout << a+1;
  } else if( a == 9 ){
    cout << "true";
  } else if( a == 10 ){
    cout << "false";
  } else if( a == 11 ){
    cout << randid();
  } else if( a == 12 ){
    cout << "( ";
    expr();
    cout << " )";
  } else if( a == 13 ){
    ifexpr();
  } else if( a == 14 ){
    funexpr();
  }
}

void appexpr(){
  int a = mt() % 5;
  if( cnt < 0 ){
    a = 1;
  }
  if( a == 0 ){
    appexpr();
    cout << " ";
    aexpr();
  } else {
    aexpr();
  }
}

void pexpr(){
  int a = mt() % 2;
  if( cnt < 0 ){
    a = 1;
  }
  if( a == 0 ){
    pexpr();
    cout << " + ";
    appexpr();
  } else {
    appexpr();
  }
}

void ltexpr(){
  int a = mt() % 2;
  if( cnt < 0 ){
    a = 1;
  }
  if( a == 0 ){
    ltexpr();
    cout << " < ";
    pexpr();
  } else {
    pexpr();
  }
}

void letexpr(){
  cout << "let " << randid() << " = ";
  expr();
  cout << " in ";
  expr();
}

void letrecexpr(){
  cout << "let rec " << randid() << " = fun " << randid() << " -> ";
  expr();
  cout << " in ";
  expr();
}

void expr(){
  int a = mt() % 5;
  if( cnt < 0 ){
    a = 2;
  }
  if( a == 0 ){
    letexpr();
  } else if( a == 1 ){
    letrecexpr();
  } else {
    ltexpr();
  }
}

void let(){
  cout << "let " << randid() << " = ";
  expr();
  cout << ";;" << endl;
}

void reclet(){
  cout << "let rec " << randid() << " = fun " << randid() << " -> ";
  expr();
  cout << ";;" << endl;
}

void toplevel(){
  int a = mt() % 3;
  if( cnt < 0 ){
    a = 0;
  }
  if( a == 0 ){
    expr();
    cout << ";;" << endl;
  } else if( a == 1 ){
    let();
  } else if( a == 2 ){
    reclet();
  }
}

const int ARGMODE_COMPLEXITY = 0;
const int ARGMODE_SEED = 1;

void show_usage( char *filename ){
  cout << "Usage: " << filename << " [OPTION]" << endl;
  cout << "Options:" << endl;
  cout << "-h, --help: show help" << endl;
  cout << "-c COMP: set complexity" << endl;
  cout << "-s SEED: set seed" << endl;
}

int main( int argc, char **argv ){


  int seed = clock();
  
  int arg_mode = -1;
  for( int i = 1; i < argc; i++ ){
    string s = argv[i];
    if( arg_mode != -1 ){
      if( arg_mode == ARGMODE_COMPLEXITY ){
        cnt = stoi(s);
      }
      if( arg_mode == ARGMODE_SEED ){
        seed = stoi(s);
      }
      arg_mode = -1;
    }
    if( s == "-h" || s == "--help" ){
      show_usage( argv[0] );
      return 0;
    }
    if( s == "-c" ){
      arg_mode = ARGMODE_COMPLEXITY;
    }
    if( s == "-s" ){
      arg_mode = ARGMODE_SEED;
    }
  }

  mt.seed( seed );
  
  toplevel();
  
  return 0;
}

#include <bits/stdc++.h>

using namespace std;

mt19937 mt;

int level = 4;

int cnt = 3;

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
  int a = mt() % 13;
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
  }
}

void appexpr(){
  vector<int> cand(0);
  if( level >= 0 ){
    cand.push_back( 1 );
    cand.push_back( 1 );
    cand.push_back( 1 );
    cand.push_back( 1 );
  }
  if( level >= 3 ){
    cand.push_back( 0 );
  }
  int a = cand[mt() % (int)(cand.size())];
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
  vector<int> cand(0);
  if( level >= 0 ){
    cand.push_back( 0 );
    cand.push_back( 0 );
    cand.push_back( 0 );
    cand.push_back( 3 );
  }
  if( level >= 2 ){
    cand.push_back( 1 );
  }
  if( level >= 3 ){
    cand.push_back( 4 );
  }
  if( level >= 4 ){
    cand.push_back( 2 );
  }
  int a = cand[mt() % (int)(cand.size())];
  if( cnt < 0 ){
    a = 0;
  }
  if( a == 0 ){
    ltexpr();    
  } else if( a == 1 ){
    letexpr();
  } else if( a == 2 ){
    letrecexpr();
  } else if( a == 3 ){
    ifexpr();
  } else if( a == 4 ){
    funexpr();
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
  vector<int> cand(0);
  if( level >= 0 ){
    cand.push_back( 0 );
  }
  if( level >= 2 ){
    cand.push_back( 1 );
  }
  if( level >= 4 ){
    cand.push_back( 2 );
  }
  int a = cand[mt() % (int)(cand.size())];
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

enum ARGMODE {
  NONE,
  COMPLEXITY,
  SEED,
  LEVEL
};

void show_usage( char *filename ){
  cout << "Usage: " << filename << " [OPTION]" << endl;
  cout << "Options:" << endl;
  cout << "-h, --help: show help" << endl;
  cout << "-c COMP: set complexity" << endl;
  cout << "-s SEED: set seed" << endl;
  cout << "-l LEVEL: set level" << endl;
}

int main( int argc, char **argv ){

  int seed = clock();
  
  int arg_mode = NONE;
  for( int i = 1; i < argc; i++ ){
    string s = argv[i];
    if( arg_mode != NONE ){
      if( arg_mode == COMPLEXITY ){
        cnt = stoi(s);
      }
      if( arg_mode == SEED ){
        seed = stoi(s);
      }
      if( arg_mode == LEVEL ){
        level = stoi(s);
      }
      arg_mode = NONE;
    }
    if( s == "-h" || s == "--help" ){
      show_usage( argv[0] );
      return 0;
    }
    if( s == "-c" ){
      arg_mode = COMPLEXITY;
    }
    if( s == "-s" ){
      arg_mode = SEED;
    }
    if( s == "-l" ){
      arg_mode = LEVEL;
    }
  }

  mt.seed( seed );
  
  toplevel();
  
  return 0;
}

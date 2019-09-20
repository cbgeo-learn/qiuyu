#include<cstdlib>
#include <iostream>

    using namespace std;

class Matri {
  public:
  matri();
  matri(int m, int n);
  void rows(int argc, char *argv[]);
  void columns(int argc, char *argv[]);
  void printMatri();
}
Matri:matri() :Matri(1,1){}

Matri::rows(int argc,char *argv[]){
   cout<<"the number of rows and columns" << endl;
   int r;
   if(argc == 3)
     r = atoi(argv[1]);
   else
     cout<<"Incorrect input"<<endl;
  return r;
}

Matri::columns(int argc,char *argv[]){
   int c;
   if(argc ==3 )
     c = atoi (argv[2])
    return c;

}

Matri:matrix(int m, int n)
{
  int p[m][n];
  for(int i = 0; i < m; ++i)
  {
for:(int j = 0; j < n; ++j)
    {
      p[i][j] = 0;
    }
  }
}

int main() {
  Matri Trial;
  int a,b;
  a = Matri::rows();
  b = Matri::columns();
  int T[a][b];
  for(int i = 0; i < a; ++i)
  {for(int j = 0; j < b; ++j)
    {
      int num;
      std::cin >>num;
      T[i][j]=num;
    }
    Trial.printMatri();

}

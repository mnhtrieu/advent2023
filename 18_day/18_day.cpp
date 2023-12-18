#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=double;
#define FOR(i,a,b) for(ll i=a;i<(ll)b;++i)
#define F(n) FOR(i,0,n)
#define FF(n) FOR(j,0,n)
#define aa first
#define bb second
#define PB push_back
#define EQ(a,b) (fabs(a-b)<=(fabs(a+b)*EPS))
#define MOD ((ll)(1e9+7))

#define FILE "demo.in"
//#define FILE "input.in"

void part_1(const string & file);
void part_2(const string & file);
vector<ll> explode(string const & s, char delim);

typedef pair<ll,ll> coord;

ll sgn(char c) {
  if(c == 'U' || c == 'L' || c == '3' || c == '2') return -1;
  return 1;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  ll x = 0, y = 0, res = 0, line = 0, n;
  char c;
  while(in >> c >> n >> str) {
    if (c == 'L' || c == 'R') { 
      res += x*y - (x+sgn(c)*n)*y;
      line += n;
      x += sgn(c)*n;
    }
    else if (c == 'U' || c == 'D') {
      res += x*(y+sgn(c)*n) - x*y;
      line += n;
      y += sgn(c)*n;
    }
  }

  cout << "Part 1: " << res / 2 + line / 2 + 1 << endl;
}

void part_2(const string & file) {
  ifstream in (file);
  string str;

   ll x = 0, y = 0, res = 0, line = 0, n;
  char c;
  while(in >> c >> n >> str) {
    string hex = str.substr(2, str.size()-4);
    n = stol(hex, nullptr, 16);
    c = str[str.size()-2];
    if (c == '2' || c == '0') { 
      res += x*y - (x+sgn(c)*n)*y;
      line += n;
      x += sgn(c)*n;
    }
    else if (c == '3' || c == '1') {
      res += x*(y+sgn(c)*n) - x*y;
      line += n;
      y += sgn(c)*n;
    }
  }

  cout << "Part 2: " << res / 2 + line / 2 + 1 << endl;
}

vector<ll> explode(string const & s, char delim) {
    vector<ll> res;
    istringstream iss(s);

    for(string token; getline(iss, token, delim);)
      res.PB(stoi(token));

    return res;
}

int main(int argc, const char ** argv){
  ios::sync_with_stdio(0);cin.tie(0);
  
  string file = FILE;
  if (argc > 1) {
    file = argv[1];
  }

  part_1(file);
  part_2(file);
  return 0;
}

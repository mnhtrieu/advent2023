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

void part_1(const string & file) {
  ifstream in(file);
  string str;

  getline(in, str);
  stringstream ss(str.substr(strlen("Time:")));
  ll x;
  vector<ll> t;
  while(ss >> x) t.PB(x);
  
  getline(in, str);
  stringstream ss2(str.substr(strlen("Distance:")));
  vector<ll> d;
  while(ss2 >> x) d.PB(x);

  ll res = 1;
  FOR(i, 0, t.size()) {
    ll k = 0;
    FOR(j, 1, t[i]) if (j * (t[i]-j) > d[i]) k++;
    res *= k;
  }

  cout << "Part 1: "  <<  res << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str;
  
  getline(in, str);
  str = str.substr(strlen("Time:"));
  str.erase(remove(str.begin(), str.end(), ' '), str.end());
  ll t = stoll(str);

  getline(in, str);
  str = str.substr(strlen("Distance:"));
  str.erase(remove(str.begin(), str.end(), ' '), str.end());
  ll d = stoll(str);

  ll res = 0;
  FOR(j, 1, t) if (j * (t-j) > d) res++;


  cout << "Part 2: " << res << endl;
}

vector<ll> explode(string const & s, char delim)
{
    vector<ll> res;
    istringstream iss(s);

    for(string token; getline(iss, token, delim);){
      if (token == "x") res.PB(1);
      else res.PB(stoi(token));
    }

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


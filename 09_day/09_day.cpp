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

ll rec(const vector<ll> & v) {
  if(all_of(v.begin(), v.end(), [](ll i){return i==0;})) return 0;
  
  vector<ll> x;
  FOR(i, 1, v.size()) x.PB(v[i]-v[i-1]);

  ll y = rec(x);

  return y+v[v.size()-1];
}

ll rec2(const vector<ll> & v) {
  if(all_of(v.begin(), v.end(), [](ll i){return i==0;})) return 0;

  vector<ll> x;
  FOR(i, 1, v.size()) x.PB(v[i]-v[i-1]);

  ll y = rec2(x);

  return v[0]-y;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  ll res = 0;
  while(getline(in, str)) {
    
    stringstream ss (str);
    vector<ll> x;
    ll n;
    while(ss >> n) x.PB(n);
    res += rec(x);
    
  }

  cout << "Part 1: " << res << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str;

  ll res = 0;
  while(getline(in, str)) {
    
    stringstream ss (str);
    vector<ll> x;
    ll n;
    while(ss >> n) x.PB(n);
    res += rec2(x);
    
  }

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


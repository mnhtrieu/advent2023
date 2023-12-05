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
  stringstream is (str.substr(7));
  vector<ll> seeds;
  for(ll x = 0; is >> x;) seeds.PB(x);
  FOR(i, 0, 2) getline(in, str); 
  map<ll,pair<ll,ll>> m;
  vector<map<ll,pair<ll,ll>>> v;
  while(getline(in, str)) {
    if (str.size() == 0) continue;
    if (str.find("map:") != string::npos) {
      v.PB(m); m.clear(); continue;
    }

    stringstream ss(str);
    ll x,y,z;
    ss >> x >> y >> z;
    m.insert({y,{x,z}});
  }
  v.PB(m);

  ll res = INT_MAX;
  for(auto & i: seeds) {
    for(auto & j: v) {
      auto it = j.lower_bound(i);
      if (it != j.begin() && (it == j.end() || it->aa != i)) --it;
      if (it->aa <= i && i < it->aa+it->bb.bb) i = (it->bb.aa + (i-it->aa));
    }
    res = std::min(i, res);
  }

  cout << "Part 1: " << res << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str;

  getline(in, str);
  stringstream is (str.substr(7));
  vector<pair<ll,ll>> seeds;
  for(ll x = 0, y = 0; is >> x >> y;) seeds.PB({x,y});
  FOR(i, 0, 2) getline(in, str); 
  map<ll,pair<ll,ll>> m;
  vector<map<ll,pair<ll,ll>>> v;
  while(getline(in, str)) {
    if (str.size() == 0) continue;
    if (str.find("map:") != string::npos) {
      v.PB(m); m.clear(); continue;
    }

    stringstream ss(str);
    ll x,y,z;
    ss >> x >> y >> z;
    m.insert({y,{x,z}});
  }
  v.PB(m);

  ll res = INT_MAX;
  for(auto & i: seeds) {
    FOR(x, 0, i.bb-1) {
      ll tmp = i.aa+x;
      for(auto & j: v) {
        auto it = j.lower_bound(tmp);
        if (it != j.begin() && (it == j.end() || it->aa != tmp)) --it;
        if (it->aa <= tmp && tmp < it->aa+it->bb.bb) tmp = (it->bb.aa + (tmp-it->aa));
      }
      res = std::min(tmp, res);
    }
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


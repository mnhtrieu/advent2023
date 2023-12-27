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
vector<string> explode(string const & s, char delim);

pair<ll, ll> karger(map<string, multiset<string>> g) {
  map<string, ll> groups;
  for(auto & [k, v]: g) groups[k] = 1;

  while (g.size() > 2) {
    auto v1 = next(g.begin(), rand() % g.size())->aa;
    auto v2 = *next(g[v1].begin(), rand() % g[v1].size());

    g[v1].erase(v2);
    
    for (auto & e: g[v2]) {
      if (e == v1) continue;
      g[e].erase(v2); 
      g[e].insert(v1); 
      g[v1].insert(e);
    }

    g.erase(v2);
    groups[v1] += groups[v2];
  }

  return {g.begin()->bb.size(), groups[g.begin()->aa] * groups[next(g.begin(), 1)->aa]};
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  map<string, multiset<string>> g;

  while (getline(in, str)) {
    string src = str.substr(0, str.find(":"));
    vector<string> edges = explode(str.substr(str.find(":")+2), ' ');
    for(auto & i: edges) { 
      g[src].insert(i);
      g[i].insert(src);
    }
  }

  ll res = 0;
  while (true) {
    ll cut = 0;
    tie(cut, res) = karger(g);
    if (cut == 3) break;
  }
  cout << "Part 1: " << res << endl;

}

void part_2(const string & file) {
  ifstream in (file);
  string str;

  cout << "Part 2: " << endl;
}

vector<string> explode(string const & s, char delim) {
  vector<string> res;
  istringstream iss(s);

  for(string token; getline(iss, token, delim);) res.PB(token);
  return res;
}

int main(int argc, const char ** argv){
  ios::sync_with_stdio(0);cin.tie(0);
  srand(time(NULL));
  
  string file = FILE;
  if (argc > 1) {
    file = argv[1];
  }

  part_1(file);
  part_2(file);
  return 0;
}

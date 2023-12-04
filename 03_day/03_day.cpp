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
string trim(string s);

void is_part_number(ll x, ll y, vector<vector<char>> & v, map<pair<ll,ll>, ll> & m, const ll & stars) {
  FOR(i, -1, 2) {
    FOR(j, -1, 2) {
      if ((i == -1 && y == 0) ||
          (i == 1 && y >= v.size()-1) ||
          (j == -1 && x == 0) || 
          (j == 1 && x >= v[y+i].size()-1)) continue;
      if (!isdigit(v[y+i][x+j])) continue;
      m[{x+j, y+i}] = stars;
    }
  }
}

void process_number(ll & is_part_number, map<ll, vector<ll>> & res, vector<ll> & a) {
  if (is_part_number != -1) {
    ll j = 0;
    for(auto & i: a) j = j * 10 + i;
    res[is_part_number].PB(j);
  }
  a.clear();
  is_part_number = -1;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;
  vector<vector<char>> v;
  map<pair<ll,ll>, ll> m;

  while(in >> str) {
    vector<char> v2;
    for(auto const & i: str) v2.PB(i);
    v.PB(v2);
  }

  FOR(y, 0, v.size()) {
    FOR(x, 0, v[y].size()) {
      if (isdigit(v[y][x]) || v[y][x] == '.') continue;
      is_part_number(x, y, v, m, 0);
    }
  }
  
  map<ll, vector<ll>> tmp;

  FOR(y, 0, v.size()) {
    ll is_part_number = -1;
    vector<ll> a;
    FOR(x, 0, v[y].size()) {
      if (v[y][x] == '.' || !isdigit(v[y][x])) {
        process_number(is_part_number, tmp, a);
        continue;
      }
      a.PB(v[y][x] - '0');
      if (m.contains({x,y})) is_part_number = m[{x,y}];
    }
    process_number(is_part_number, tmp, a);
  }

  ll res = 0;
  for(auto [k, v] : tmp) {
    for(auto i : v) res += i;
  }

  cout << "Part 1: " << res << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str;
  vector<vector<char>> v;
  map<pair<ll,ll>, ll> m;

  while(in >> str) {
    vector<char> v2;
    for(auto const & i: str) v2.PB(i);
    v.PB(v2);
  }

  ll stars = 0;
  FOR(y, 0, v.size()) {
    FOR(x, 0, v[y].size()) {
      if (v[y][x] != '*') continue;
      is_part_number(x, y, v, m, stars);
      stars ++;
    }
  }

  map<ll, vector<ll>> tmp;

  FOR(y, 0, v.size()) {
    ll is_part_number = -1;
    vector<ll> a;
    FOR(x, 0, v[y].size()) {
      if (v[y][x] == '.' || !isdigit(v[y][x])) {
        process_number(is_part_number, tmp, a);
        continue;
      }
      a.PB(v[y][x] - '0');
      if (m.contains({x,y})) is_part_number = m[{x,y}];
    }

    process_number(is_part_number, tmp, a);
  }
  
  ll res = 0;
  for(auto [k, v] : tmp) {
    if (v.size() == 1) continue;
    ll r = 1;
    for(auto i : v) r *= i;
    res += r;
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

string trim(string str) {
    std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
    str.erase(end_pos, str.end());
    return str;
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


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

bool eval(ll y, ll x, vector<string> & raw, const set<char> & allowed) {
  if (y < 0 || y >= (ll)raw.size()) return false;
  if (x < 0 || x >= (ll)raw[0].size()) return false;

  if (allowed.contains(raw[y][x]) || raw[y][x] == 'S') return true;
  return false;
}

vector<coord> get_node(vector<string> & raw, ll y, ll x) {
  vector<coord> res;
  switch(raw[y][x]) {
    case '|':
      if (eval(y-1, x, raw, {'7', 'F', '|'})) res.PB({y-1, x});
      if (eval(y+1, x, raw, {'|', 'L', 'J'})) res.PB({y+1, x});
      break;
    case '-':
      if (eval(y, x-1, raw, {'-', 'L', 'F'})) res.PB({y, x-1});
      if (eval(y, x+1, raw, {'-', 'J', '7'})) res.PB({y, x+1});
      break;
    case 'L':
      if (eval(y-1, x, raw, {'7', 'F', '|'})) res.PB({y-1, x});
      if (eval(y, x+1, raw, {'-', 'J', '7'})) res.PB({y, x+1});
      break;
    case 'J':
      if (eval(y-1, x, raw, {'7', 'F', '|'})) res.PB({y-1, x});
      if (eval(y, x-1, raw, {'-', 'L', 'F'})) res.PB({y, x-1});
      break;
    case '7':
      if (eval(y+1, x, raw, {'|', 'L', 'J'})) res.PB({y+1, x});
      if (eval(y, x-1, raw, {'-', 'L', 'F'})) res.PB({y, x-1});
      break;
    case 'F':
      if (eval(y+1, x, raw, {'|', 'L', 'J'})) res.PB({y+1, x});
      if (eval(y, x+1, raw, {'-', 'J', '7'})) res.PB({y, x+1});
      break;
  }
  return res;
}

bool eval_start(ll y, ll x, vector<string> & raw, const set<char> & allowed, map<coord,vector<coord>> & m) {
  if (!m.contains({y, x})) return false;
  if (m[{y, x}].size() != 2) return false;

  if (allowed.contains(raw[y][x])) return true;
  return false;
}

vector<coord> get_start(vector<string> & raw, map<coord,vector<coord>> & m, coord c) {
  auto [y,x] = c;
  vector<coord> res;
  if (eval_start(y-1, x, raw, {'7', 'F', '|'}, m)) res.PB({y-1, x});
  if (eval_start(y+1, x, raw, {'|', 'L', 'J'}, m)) res.PB({y+1, x});
  if (eval_start(y, x-1, raw, {'-', 'L', 'F'}, m)) res.PB({y, x-1});
  if (eval_start(y, x+1, raw, {'-', 'J', '7'}, m)) res.PB({y, x+1});
  return res;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;
  vector<string> raw;
  map<coord,vector<coord>> m;

  while(getline(in, str)) raw.PB(str);

  coord start;
  FOR(y, 0, raw.size()-1) {
    FOR(x, 0, raw[y].size()-1) {
      if (raw[y][x] == '.') continue;
      if (raw[y][x] == 'S') { start = {y,x}; continue; }
      m[{y,x}] = get_node(raw, y, x);
    }
  }

  m[start] = get_start(raw, m, start);

  queue<pair<coord,ll>> q;
  set<coord> v;
  ll res = 0;
  q.push({start, 0});
  while(!q.empty()) {
    auto [c, s] = q.front(); q.pop();
    v.insert(c);
    res = max(res, s);

    for(auto & i: m[c]) {
      if (v.contains(i)) continue;
      q.push({i, s+1});
    }
  }
  
  cout << "Part 1: " << res << endl;
}



coord find_nearest(vector<string> & raw, set<coord> & v2) {
  FOR(i, 0, raw.size()) {
    FOR(j, 0, raw[i].size()) {
      if (
        raw[i][j] == '.' 
        && !v2.contains({i,j})
      ) 
      return {i,j};
    }
  }

  return {-1,-1};
}

void part_2(const string & file) {
  ifstream in (file);
  string str;
  vector<string> raw;
  map<coord,vector<coord>> m;

  while(getline(in, str)) raw.PB(str);

  coord start;
  FOR(y, 0, raw.size()-1) {
    FOR(x, 0, raw[y].size()-1) {
      if (raw[y][x] == '.') continue;
      if (raw[y][x] == 'S') { start = {y,x}; continue; }
      m[{y,x}] = get_node(raw, y, x);
    }
  }

  m[start] = get_start(raw, m, start);

  stack<coord> st;
  set<coord> v;
  st.push(start);
  while(!st.empty()) {
    coord c = st.top(); st.pop();
    v.insert(c);

    for(auto & i: m[c]) {
      if (v.contains(i)) continue;
      st.push(i);
    }
  }

  ll res = 0;
  set<char> pipes = {'|', 'L', 'J', 'S'};
  FOR(y, 0, raw.size()-1) {
    bool in = false;
    FOR(x, 0, raw[y].size()-1) {
      if (v.contains({y,x}) && pipes.contains(raw[y][x])) in = !in;
      if (!v.contains({y,x}) && in) res ++; 
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


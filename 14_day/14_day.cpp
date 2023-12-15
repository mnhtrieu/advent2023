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

vector<string> north(const vector<string> & m) {
  vector<string> n;
  FOR(i, 0, strlen(m[0].c_str())) {
    string a;
    FOR(j, 0, m.size()) a += m[j][i];
    n.PB(a);
  }

  return n;
}

vector<string> east(const vector<string> & m) {
  vector<string> n = m;
  for(auto & i : n) reverse(i.begin(), i.end()); 
  return n;
}

vector<string> south(const vector<string> & m) {
  vector<string> n;
  FOR(i, 0, strlen(m[0].c_str())) {
    string a;
    FOR(j, 0, m.size()) a += m[m.size()-j-1][i];
    n.PB(a);
  }

  return n;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  vector<string> m;

  while(getline(in, str)) m.PB(str);
  vector<string> tr = north(m);
  map<ll, vector<pair<ll,ll>>> cnt;

  ll col = 0;
  for(auto & r: tr) {
    auto end = r.begin()-1;
    while (end != r.end()) {
      ll idx = r.find_first_of('#', end-r.begin() + 1);
      auto prev = end + 1;
      if (idx == (ll)string::npos) end = r.end();
      else end = r.begin() + idx;

      if (end - prev == 0) continue;

      ll x = ranges::count(prev, end, 'O');
      cnt[col].PB({x, prev-r.begin()});
    }
    col ++;
  }

  ll n = tr[0].size();

  ll res = 0;
  for(auto & [k, v]: cnt) {
    for(auto & p : v) {
      ll start = n - p.bb;
      FOR(i, 0, p.aa)
        res += (start - i);
    }
  }

  cout << "Part 1: " << res << endl;
}

map<ll, pair<vector<ll>, vector<pair<ll,ll>>>> shake_down(const vector<string> & m) {
  ll col = 0;
  map<ll, pair<vector<ll>, vector<pair<ll,ll>>>> cnt;
  for(auto & r: m) {
    auto end = r.begin()-1;
    while (end != r.end()) {
      ll idx = r.find_first_of('#', end-r.begin() + 1);
      auto prev = end + 1;
      if (idx == (ll)string::npos) end = r.end();
      else end = r.begin() + idx;

      cnt[col].aa.PB(end-r.begin());
      if (end - prev == 0) continue;

      ll x = ranges::count(prev, end, 'O');
      cnt[col].bb.PB({x, prev-r.begin()});
    }
    col ++;
  }

  return cnt;
}

vector<string> construct(const map<ll, pair<vector<ll>, vector<pair<ll,ll>>>> & cnt, const vector<string> & m, ll way) {
  ll n = m.size();
  vector<string> res(n, string(m[0].size(), '.'));

  for(auto & [k, v]: cnt) {
    for(auto & p : v.bb) FOR(i, 0, p.aa) res[k][p.bb+i] = 'O';
    for(auto & p: v.aa) { if (p == (ll)m[0].size()) continue; res[k][p] = '#'; }
  }

  if (way == 0) {
    return north(res);
  } else if (way == 2) {
    for(auto & [k, v]: cnt) {
      for(auto & p : v.bb) FOR(i, 0, p.aa) res[k][p.bb+i] = 'O';
      for(auto & p: v.aa) { if (p == (ll)m[0].size()) continue; res[k][p] = '#'; }
    }
    res = south(res);
    for(auto & i: res) reverse(i.begin(), i.end());
    reverse(res.begin(), res.end());
  } else if (way == 3) {
    return east(res);
  }

  return res;
}

vector<string> cycle(vector<string> tmp) {
    tmp = construct(shake_down(north(tmp)), tmp, 0);
    tmp = construct(shake_down(tmp), tmp, 1);
    tmp = construct(shake_down(south(tmp)), tmp, 2);
    tmp = construct(shake_down(east(tmp)), tmp, 3);
    return tmp;
}

void part_2(const string & file) {
  ifstream in (file);
  string str;

  map<vector<string>, pair<ll,ll>> m;
  vector<string> tmp; 

  while(getline(in, str)) tmp.PB(str);

  ll cycles = 0;
  m[tmp] = {1, 0};
  while(true) {
    tmp = cycle(tmp);
    cycles ++;
    if (m[tmp].aa+1 == 2) break;
    m[tmp] = {m[tmp].aa+1, cycles};
  }
  ll cycle_final = (1000000000 - cycles) % (cycles-m[tmp].bb);
  FOR(i, 0, cycle_final) tmp = cycle(tmp);

  ll res = 0;
  FOR(i, 0, tmp.size()) res += ranges::count(tmp[i].begin(), tmp[i].end(), 'O') * (tmp.size()-i);

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


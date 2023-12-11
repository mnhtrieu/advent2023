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

vector<string> transpose(vector<string> m) {
  FOR(i, 0, m.size()) 
    FOR(j, i+1, m.size())
      swap(m[i][j], m[j][i]);

  FOR(i, 0, m.size())
    reverse(m[i].begin(), m[i].end());

  return m;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  vector<string> m;
  vector<ll> rows, cols;
  ll line = 0;
  while(getline(in, str)) {
    m.PB(str);
    if (all_of(str.begin(), str.end(), [](char c) { return c == '.'; })) rows.PB(line);
    line ++;
  }

  vector<string> tr = transpose(m);
  FOR(i, 0, tr.size())
    if (all_of(tr[i].begin(), tr[i].end(), [](char c) { return c == '.'; })) cols.PB(i);

  vector<pair<ll,ll>> coords;
  FOR(y, 0, m.size()) 
    FOR(x, 0, m[y].size()) 
      if (m[y][x] == '#') coords.PB({y,x});

  ll res = 0;
  FOR(i, 0, coords.size()) {
    FOR(j, i, coords.size()) {
      if (i == j) continue;
      auto [y1, x1] = coords[i]; auto [y2, x2] = coords[j];
      ll expand_rows = 0, expand_cols = 0;

      FOR(k, 0, rows.size()) if (std::min(y1, y2) < rows[k] && rows[k] < std::max(y1, y2)) expand_rows ++;
      FOR(k, 0, cols.size()) if (std::min(x1, x2) < cols[k] && cols[k] < std::max(x1, x2)) expand_cols ++;
      res += abs(y1-y2)+(expand_rows) + abs(x1-x2)+(expand_cols);
    }
  }

  cout << "Part 1: " << res << endl;
}

void part_2(const string & file) {
  ifstream in (file);
  string str;

  vector<string> m;
  vector<ll> rows, cols;
  ll line = 0;
  while(getline(in, str)) {
    m.PB(str);
    if (all_of(str.begin(), str.end(), [](char c) { return c == '.'; })) rows.PB(line);
    line ++;
  }

  vector<string> tr = transpose(m);
  FOR(i, 0, tr.size())
    if (all_of(tr[i].begin(), tr[i].end(), [](char c) { return c == '.'; })) cols.PB(i);

  vector<pair<ll,ll>> coords;
  FOR(y, 0, m.size()) 
    FOR(x, 0, m[y].size()) 
      if (m[y][x] == '#') coords.PB({y,x});

  ll res = 0, expand = 1000000;
  FOR(i, 0, coords.size()) {
    FOR(j, i, coords.size()) {
      if (i == j) continue;
      auto [y1, x1] = coords[i]; auto [y2, x2] = coords[j];
      ll expand_rows = 0, expand_cols = 0;

      FOR(k, 0, rows.size()) if (std::min(y1, y2) < rows[k] && rows[k] < std::max(y1, y2)) expand_rows ++;
      FOR(k, 0, cols.size()) if (std::min(x1, x2) < cols[k] && cols[k] < std::max(x1, x2)) expand_cols ++;
      res += abs(y1-y2)+((expand-1)*expand_rows) + abs(x1-x2)+((expand-1)*expand_cols);
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


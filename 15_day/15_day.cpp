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

void part_1(const string & file) {
  ifstream in(file);
  string str;
  getline(in, str);
  vector<string> strs = explode(str, ',');

  ll res = 0;
  for(auto & i: strs) {
    ll tmp = 0;
    FOR(j, 0, i.size()) tmp = ((tmp+ i[j]) * 17) % 256;
    res += tmp;
  }

  cout << "Part 1: " << res << endl;
}

ll hash2(const string & label) {
  ll tmp = 0;
  FOR(j, 0, label.size()) tmp = ((tmp+ label[j]) * 17) % 256;
  return tmp;
}

void part_2(const string & file) {
  ifstream in (file);
  string str;
  getline(in, str);
  vector<string> strs = explode(str, ',');
  vector<vector<pair<string,ll>>> m(256);

  for(auto & i: strs) {
    ll x = i.find_first_of('-'), focal = 0;
    string label;
    if (x == (ll)string::npos) { x = i.find_first_of('='); focal = stoll(i.substr(x+1)); } 
    else label = i.substr(0, x);

    char op = i.substr(x, 1)[0];
    label = i.substr(0, x);
    ll box = hash2(label);    

    auto it = find_if(m[box].begin(), m[box].end(), [&label](const pair<string,ll> & p) { return p.aa == label; });
    if (op == '=') { if (it == m[box].end()) m[box].PB({label, focal}); else it->bb = focal; } 
    else if (op == '-' && it != m[box].end()) m[box].erase(it);
  }

  ll res = 0;
  FOR(i, 0, m.size())
    FOR(j, 0, m[i].size()) 
      res += (i+1) * (j+1) * m[i][j].bb;

  cout << "Part 2: " << res << endl;
}

vector<string> explode(string const & s, char delim) {
    vector<string> res;
    istringstream iss(s);
    for(string token; getline(iss, token, delim);) res.PB(token);
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


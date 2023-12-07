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

ll eval(const string & str) {
  map<char,ll> cnt;
  for(auto & c: str) cnt[c]++;
  switch(cnt.size()) {
    case 5: return 1;
    case 4: return 2;
    case 3: 
      for(auto & [k, v] : cnt) if (v == 3) return 4;
      return 3;
    case 2: 
      for(auto & [k, v] : cnt) if (v == 4) return 6;
      return 5;
    default: return 7;
  }
}

char best(const map<char, ll> & cnt) {
  ll m = 0;
  char c = cnt.begin()->aa;
  for(auto & [k,v]: cnt) {
    if (k == 'J') continue;
    if (v > m) { m = v; c = k; }
  }
  return c;
}

ll eval2(map<char,ll> & cnt) {
  if (cnt.contains('J')) { 
    cnt[best(cnt)] += cnt['J']; 
    cnt.erase('J');
    return eval2(cnt); 
  }
  switch(cnt.size()) {
    case 5: return 1;
    case 4: return 2;
    case 3: 
      for(auto & [k, v] : cnt) if (v == 3) return 4;
      return 3;
    case 2: 
      for(auto & [k, v] : cnt) if (v == 4) return 6;
      return 5;
    default: return 7;
  }
}

void part_1(const string & file) {
  ifstream in(file);
  string str = "23456789TJQKA";
  unordered_map<char, ll> a;
  FOR(i, 0, str.size()) a[str[i]] = i;

  ll bid;
  map<ll, vector<pair<string,ll>>> m;
  while(in >> str >> bid) {
    m[eval(str)].PB({str, bid});
  }

  for(auto & [k, v]: m) sort(v.begin(), v.end(), [&a](const auto & x, const auto & y) {
    FOR(i, 0, x.aa.size()) if (a[x.aa[i]] != a[y.aa[i]]) return a[x.aa[i]] <= a[y.aa[i]];
    return true;
  });

  ll idx = 1, res = 0;
  for(const auto & [k, v]: m) {
    for(auto & [s,b]: v) { res += idx*b; idx++; }
  }

  cout << "Part 1: " << res << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str = "J23456789TQKA";
  unordered_map<char, ll> a;
  FOR(i, 0, str.size()) a[str[i]] = i;

  ll bid;
  map<ll, vector<pair<string,ll>>> m;
  while(in >> str >> bid) {
    map<char,ll> cnt;
    for(auto & c: str) cnt[c]++;
    m[eval2(cnt)].PB({str, bid});
  }

  for(auto & [k, v]: m) sort(v.begin(), v.end(), [&a](const auto & x, const auto & y) {
    FOR(i, 0, x.aa.size()) if (a[x.aa[i]] != a[y.aa[i]]) return a[x.aa[i]] <= a[y.aa[i]];
    return true;
  });

  ll idx = 1, res = 0;
  for(const auto & [k, v]: m) {
    for(auto & [s,b]: v) { res += idx*b; idx++; }
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


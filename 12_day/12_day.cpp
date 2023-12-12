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

ll rec(const string & str, ll pos, ll i, const vector<ll> & arr, bool put, map<pair<ll,ll>, map<bool, ll>> & dp) {
  if ((pos > (ll)str.size() && !put) || (pos > (ll)str.size() + 1)) 
    return dp[{pos,i}][put] = 0;

  if (dp[{pos,i}].contains(put)) return dp[{pos,i}][put];
  if (put) {
    FOR(j, pos-arr[i-1]-1, pos-1) if (str[j] == '.') return dp[{pos,i}][put] = 0;
    if (pos != (ll)str.size() + 1 && str[pos-1] == '#') return dp[{pos,i}][put] = 0;
  }

  if (i == (ll)arr.size()) {
    FOR(j, pos, str.size())
      if(str[j] == '#') return dp[{pos,i}][put] = 0;  
    return dp[{pos,i}][put] = 1;
  }

  ll res = 0;
  if (str[pos] != '.') res += rec(str, pos + arr[i] + 1, i + 1, arr, true, dp);
  if (str[pos] != '#') res += rec(str, pos + 1, i, arr, false, dp);

  return dp[{pos,i}][put] = res;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  ll res = 0;
  while(getline(in, str)) {
    map<pair<ll,ll>, map<bool, ll>> dp;
    string map = str.substr(0, str.find(" "));
    vector<ll> arr = explode(str.substr(str.find(" ")+1), ',');

    res += rec(map, 0, 0, arr, false, dp);
  }

  cout << "Part 1: " << res << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str;

  ll res = 0;
  while(getline(in, str)) {
    map<pair<ll,ll>, map<bool, ll>> dp;
    string map = str.substr(0, str.find(" "));
    vector<ll> arr = explode(str.substr(str.find(" ")+1), ',');
    
    map = map + "?" + map + "?" + map + "?" + map + "?" + map;
    vector<ll> arr2 = arr;
    FOR(i, 0, arr2.size()*4) arr.PB(arr2[i%arr2.size()]); 
    res += rec(map, 0, 0, arr, false, dp);
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


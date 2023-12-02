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

//#define FILE "demo.in"
#define FILE "input.in"

void part_1(const string & file);
void part_2(const string & file);
vector<ll> explode(string const & s, char delim);

void part_1(const string & file) {
  ifstream in(file);
  string str;
  ll res = 0;

  while (in >> str) {
    vector<ll> numbers;
    for (auto const & a: str) {
      if(isdigit(a)) numbers.PB(a - '0');
    }

    if (numbers.size() == 1) res += numbers[0]*10 + numbers[0];
    else if (numbers.size() > 1) res += numbers[0]*10 + numbers[numbers.size()-1];
  }

  cout << "Part 1: " << res << endl;
}

pair<ll,ll> jump(const string & s, const string & s2, const ll & idx, const ll & numidx) {
  FOR(i, 0, s2.size()) {
    if (s[idx+i] == s2[i]) continue;
    return {0,0};
  }

  return {1,numidx};
}

void part_2(const string & file) {
  ifstream in (file);
  string str;
  ll res = 0;
  vector<string> numStrs = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

  while (in >> str) {
    vector<ll> numbers;
    FOR(i, 0, str.size()) {
      bool x = false;
      FOR(j, 0, numStrs.size()) {
        auto [success, idx] = jump(str, numStrs[j], i, j);
        if (success == 0) continue;
        i += numStrs[idx].size()-2;
        x = true;
        numbers.PB(idx+1);
        break;
      }
      if (!x && isdigit(str[i])) numbers.PB(str[i]-'0');
    }

    if (numbers.size() == 1)  res += numbers[0]*10 + numbers[0];
    else res += numbers[0]*10 + numbers[numbers.size()-1];
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


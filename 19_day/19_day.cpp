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

enum OP {
  COMPARE_GREATER,
  COMPARE_LESSER,
  NOOP
};

struct condition {
  ll val;
  OP op;
  char token;
  string dest;

  bool compare() { return op == COMPARE_GREATER || op == COMPARE_LESSER; }
};


condition parse(const string & token) {
  if (token.find_first_of("<>") != string::npos) {
    string dest = token.substr(token.find(":")+1);
    char tkn = token[0];
    ll val = stol(token.substr(2, token.find(":")-2));
    OP op = token[1] == '>' ? COMPARE_GREATER : COMPARE_LESSER;
    return {val, op, tkn, dest};
  }
  
  return {-1, NOOP, 0, token};
}

bool eval(const condition & cond, map<char, ll> & vals) {
  switch (cond.op) {
    case COMPARE_GREATER: return vals[cond.token] > cond.val;
    case COMPARE_LESSER: return vals[cond.token] < cond.val;
    default: return true;
  }

  return true;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  map<string, vector<condition>> m;
  while(getline(in, str)) {
    if (str.size() <= 1) break;
    string key = str.substr(0, str.find("{"));
    str = str.substr(str.find("{")+1, str.size()-str.find("{")-2);
    vector<string> tokens = explode(str, ',');
    for(auto & i: tokens) m[key].PB(parse(i));
  }

  ll res = 0;
  while(getline(in, str)) {
    string start = "in";
    map<char, ll> vals;
    str = str.substr(1, str.size()-2);
    vector<string> tokens = explode(str, ',');
    for(auto & t: tokens) vals[t[0]] = stol(t.substr(2));

    while(true) {
      ll i = 0;
      for(i = 0; i < (ll)m[start].size(); ++ i) 
        if (eval(m[start][i], vals)) break;

      if (m[start][i].dest == "A") {
        for(auto & [k, v]: vals) res += v;
        break;
      }
      else if (m[start][i].dest == "R") break;
      else start = m[start][i].dest;
    }
  }

  cout << "Part 1: " << res << endl;
}

void rec(const string & start, map<string, vector<condition>> & conditions, map<char, pair<ll,ll>> intervals, ll & res) {
  if (start == "R") return;
  if (start == "A") {
    ll tmp = 1;
    for (auto & [k, v]: intervals) tmp *= v.bb - v.aa + 1;
    res += tmp;
    return;
  }

  auto rules = conditions[start];
  for(auto & rule: rules) {
    if (rule.op == NOOP) continue;
    map<char, pair<ll,ll>> tmp = intervals;
    if (rule.op == COMPARE_GREATER) {
      tmp[rule.token].aa = rule.val+1;
      intervals[rule.token].bb = rule.val;
    } else {
      tmp[rule.token].bb = rule.val-1;
      intervals[rule.token].aa = rule.val;
    }
    if (tmp[rule.token].aa != tmp[rule.token].bb) rec(rule.dest, conditions, tmp, res);
  }
  rec(rules[rules.size()-1].dest, conditions, intervals, res);
}

void part_2(const string & file) {
  ifstream in (file);
  string str;
  map<string, vector<condition>> m;
  while(getline(in, str)) {
    if (str.size() <= 1) break;
    string key = str.substr(0, str.find("{"));
    str = str.substr(str.find("{")+1, str.size()-str.find("{")-2);
    vector<string> tokens = explode(str, ',');
    for(auto & i: tokens) m[key].PB(parse(i));
  }

  ll res = 0;
  map<char, pair<ll,ll>> intervals = {{'x', {1, 4000}}, {'m', {1, 4000}}, {'a', {1, 4000}}, {'s', {1, 4000}}};
  rec("in", m, intervals, res);

  cout << "Part 2: " << res << endl;
}

vector<string> explode(string const & s, char delim){
  vector<string> res;
  istringstream iss(s);

  for(string token; getline(iss, token, delim);)
    res.PB(token);

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

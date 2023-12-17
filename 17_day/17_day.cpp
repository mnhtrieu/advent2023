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
#define INF (1ll<<61)
//#define FILE "input.in"

void part_1(const string & file);
void part_2(const string & file);
vector<ll> explode(string const & s, char delim);

typedef pair<ll,ll> coord;

bool is_out(const coord & c, ll n, ll m) {
  auto [y, x] = c;
  return (y < 0 || y >= n || x < 0 || x >= m);
}

enum DIRECTION {
  UP,
  RIGHT,
  DOWN,
  LEFT,
};

struct node {
  ll w;
  coord c;
  DIRECTION d;
  ll moves;
};

bool operator == (const node & n, const node& m) {
    return n.c == m.c && n.d == m.d && n.moves == m.moves;
  }

struct hasher {
   size_t operator()(const node &n) const {
      return n.c.aa * 10 + n.c.bb;
   }
};

static const coord DIRECTIONS[] = {{-1,0}, {0,1}, {1,0}, {0,-1}};

vector<tuple<ll,ll, DIRECTION>> edges(ll n, ll m, coord curr, DIRECTION dir) {
  vector<tuple<ll,ll, DIRECTION>> res;
  
  FOR(i, -1, 2) {
    DIRECTION new_dir = static_cast<DIRECTION>((dir + i + 4) % 4);
    coord new_pos = {curr.aa+DIRECTIONS[new_dir].aa, curr.bb+DIRECTIONS[new_dir].bb};
    if (!is_out(new_pos, n, m)) res.PB({new_pos.aa, new_pos.bb, new_dir});
  }

  return res;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  vector<string> v;
  while(getline(in, str)) v.PB(str);

  auto cmp = [](node & n, node & m) { return (n.w > m.w); };
  priority_queue<node, vector<node>, decltype(cmp)> q;
  unordered_set<node, hasher> b;
  pair<ll,ll> start = {0, 0}, end = {(ll)v.size()-1, (ll)v[0].size()-1};
  q.push({0, start, RIGHT, 0});
  q.push({0, start, DOWN, 0});

  ll res = 0;
  while(!q.empty()) {
    auto [w, coord, dir, mov] = q.top(); q.pop();
    if (!b.contains({w, coord, dir, mov})) {
      b.insert({w, coord, dir, mov});
      if (coord == end) {
        res = w;
        break;
      }
      
      vector<tuple<ll,ll, DIRECTION>> e = edges(v.size(), v[0].size(), coord, dir);
      for(auto [y, x, z]: e) {
        if (z == dir && mov >= 2) continue;
        ll d2 = w + (v[y][x] - '0');
        q.push({d2, {y,x}, z, (z == dir ? mov+1 : 0)});
      }
    }
  }
  
  cout << "Part 1: " << res << endl;
}

void part_2(const string & file) {
  ifstream in (file);
  string str;

  vector<string> v;
  while(getline(in, str)) v.PB(str);

  auto cmp = [](node & n, node & m) { return (n.w > m.w); };
  priority_queue<node, vector<node>, decltype(cmp)> q;
  unordered_set<node, hasher> b;
  pair<ll,ll> start = {0, 0}, end = {(ll)v.size()-1, (ll)v[0].size()-1};
  q.push({0, start, UP, 0});
  q.push({0, start, LEFT, 0});

  ll res = 0, i = 0;
  while(!q.empty()) {
    auto [w, coord, dir, mov] = q.top(); q.pop();
    if (!b.contains({w, coord, dir, mov})) {
      b.insert({w, coord, dir, mov});
      if (coord == end) {
        res = w;
        break;
      }
      
      vector<tuple<ll,ll, DIRECTION>> e = edges(v.size(), v[0].size(), coord, dir);
      for(auto [y, x, z]: e) {
        if (z == dir && mov >= 10) continue;

        ll d2 = w + (v[y][x] - '0');
        if (z == dir) {
          q.push({d2, {y,x}, z, mov+1});
          continue;
        }

        bool out = false; ll moves = 1;
        FOR(step, 1, 4) {
          y += DIRECTIONS[z].aa; x += DIRECTIONS[z].bb;
          if ((out = is_out({y,x},v.size(), v[0].size()))) break;
          d2 += v[y][x] - '0';
          moves ++;
        }

        if (!out) q.push({d2, {y,x}, z, moves});
      }
    }
  }

  cout << "Part 2: " << res << endl;
}

vector<ll> explode(string const & s, char delim) {
    vector<ll> res;
    istringstream iss(s);

    for(string token; getline(iss, token, delim);)
      res.PB(stoi(token));

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

#include <bits/stdc++.h>
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/register/point.hpp>

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

struct COORD {
  ll x;
  ll y;
  ll z;
};

typedef boost::geometry::model::box<COORD> box;
typedef pair<box, ll> rtree_value;
typedef boost::geometry::index::rtree<rtree_value, boost::geometry::index::rstar<8>> rtree;
BOOST_GEOMETRY_REGISTER_POINT_3D(::COORD, ll, boost::geometry::cs::cartesian, x, y, z)

void part_1(const string & file);
void part_2(const string & file);
vector<ll> explode(string const & s, char delim);

void move_brick(rtree & tree, const box & brick, ll z) {
  vector<rtree_value> res;
  tree.query(boost::geometry::index::intersects(brick), back_inserter(res));
  tree.remove(res[0]);
  auto [b, idx] = res[0];

  COORD u = b.min_corner(), v = b.max_corner();
  ll diff = u.z - z; u.z = z; v.z -= diff;
  tree.insert({{u,v}, idx});
}

vector<ll> drop_brick(rtree & tree, const box & brick) {
  COORD u = brick.min_corner(), v = brick.max_corner();
  if (u.z == 1) return {-1};
  box area = {{u.x, u.y, 1}, {v.x, v.y, u.z - 1}};
  vector<rtree_value> bricks;
  tree.query(boost::geometry::index::intersects(area), back_inserter(bricks));
  if (bricks.empty()) {
    move_brick(tree, brick, 1);
    return {-1};
  }

  ll z = INT_MIN;
  vector<rtree_value> top;
  FOR(i, 0, bricks.size()) z = max(bricks[i].aa.max_corner().z, z);
  FOR(i, 0, bricks.size()) if (bricks[i].aa.max_corner().z == z) top.PB(bricks[i]);
  move_brick(tree, brick, top[0].aa.max_corner().z + 1);

  vector<ll> res;
  FOR(i, 0, top.size()) res.PB(top[i].bb);
  return res;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  vector<box> bricks;

  while(getline(in, str)) {
    vector<ll> start = explode(str.substr(0, str.find("~")), ',');
    vector<ll> end = explode(str.substr(str.find("~")+1), ',');
    bricks.PB({
      {min(start[0], end[0]), min(start[1], end[1]), min(start[2], end[2])},
      {max(start[0], end[0]), max(start[1], end[1]), max(start[2], end[2])},
    });
  }

  ranges::sort(bricks, [](auto & l, auto & r) { return l.min_corner().z < r.min_corner().z; });
  rtree tree;
  FOR(i, 0, bricks.size()) tree.insert({bricks[i], i});

  map<ll, vector<ll>> m;
  FOR(i, 0, bricks.size()) m[i] = drop_brick(tree, bricks[i]);
  
  set<ll> res;
  FOR(i, 0, bricks.size()) res.insert(i);
  for (auto & [k, v]: m) if (v.size() == 1) res.erase(v[0]);
  
  cout << "Part 1: " << res.size() << endl;
}


ll count(map<ll, vector<ll>> m, ll i) {
  m.erase(i);
  map<ll, vector<ll>> inverted;
  for(auto & [k, v]: m) for (auto & j : v) inverted[j].PB(k);
  stack<ll> s; s.push(-1);
  set<ll> visited;
  while (!s.empty()) {
    ll brick = s.top(); s.pop();
    if (visited.contains(brick)) continue;
    if (brick != -1) visited.insert(brick);
    for (auto & i: inverted[brick]) s.push(i);
  }
  return m.size() - visited.size();
}

void part_2(const string & file) {
  ifstream in (file);
  string str;

  vector<box> bricks;

  while(getline(in, str)) {
    vector<ll> start = explode(str.substr(0, str.find("~")), ',');
    vector<ll> end = explode(str.substr(str.find("~")+1), ',');
    bricks.PB({
      {min(start[0], end[0]), min(start[1], end[1]), min(start[2], end[2])},
      {max(start[0], end[0]), max(start[1], end[1]), max(start[2], end[2])},
    });
  }

  ranges::sort(bricks, [](auto & l, auto & r) { return l.min_corner().z < r.min_corner().z; });
  rtree tree;
  FOR(i, 0, bricks.size()) tree.insert({bricks[i], i});

  map<ll, vector<ll>> m;
  FOR(i, 0, bricks.size()) m[i] = drop_brick(tree, bricks[i]);

  ll res = 0;
  FOR(i, 0, bricks.size()) res += count(m, i);

  cout << "Part 2: " << res << endl;
}

vector<ll> explode(string const & s, char delim) {
  vector<ll> res;
  istringstream iss(s);

  for(string token; getline(iss, token, delim);)
    res.PB(stol(token));

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

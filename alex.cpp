#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
#define pb push_back
#define FOR(i,a,b) for(ll i = (a); i < (b); i++)

typedef struct node {
  ll left = 0;
  ll right = 0;
  ll parent = 0;
  ll original_tree_size = 0;
  ll size_needed_right = 0;
  ll current_tree_size = 0;
  bool chosen = false;
} node;

vl trees;

// Calculates the size of the subtree in original AVL-tree with start as root
// O(n)
ll calculate_size(node* nodes, ll start) {
  if(start == 0)
    return 0;
  ll size =  1 + max(calculate_size(nodes, nodes[start].left), calculate_size(nodes, nodes[start].right));
  nodes[start].original_tree_size = size;
  return size;
}

// Generates a subtree with garantueed depth depth_to_go
// GENERATE algorithm
// O(log n)
void generate_depth(node* nodes, ll current, ll depth_to_go) {
  if(depth_to_go <= 0)
    return;

  if(nodes[nodes[current].left].original_tree_size >= depth_to_go - 1) {
    generate_depth(nodes, nodes[current].left, depth_to_go - 1);
    if(depth_to_go > 2)
      nodes[current].size_needed_right = depth_to_go - 2;
  } else {
    nodes[current].size_needed_right = depth_to_go - 1;
    if(depth_to_go > 2)
      generate_depth(nodes, nodes[current].left, depth_to_go - 2);
  }
  nodes[current].chosen = true;
  nodes[current].current_tree_size = depth_to_go;
}

// Checks if a subtree with certain size and number of available nodes is possible to choose
// O(log n)
bool check_poss(node *nodes, ll current, ll prev, ll size, ll *avail) {
  if(current == 0)
    return true;

  ll tmp_avail = *avail;

  // we come from left
  if(prev < current) {

    if(!nodes[current].chosen) {
      if(tmp_avail == 0)
        return false;

      tmp_avail--;
    }
    ll tmp_size_needed_right = nodes[current].size_needed_right;

    //calculate how many are available depending if we need to build a right childtree
    if(tmp_size_needed_right < size - 2) {
      tmp_avail += trees[tmp_size_needed_right] - trees[size - 2];
      if(tmp_avail < 0)
        return false;
      tmp_size_needed_right = size - 2;
    }
    if(check_poss(nodes, nodes[current].parent, current, size + 1, &tmp_avail)) {
      *avail = tmp_avail;
      nodes[current].chosen = true;
      nodes[current].size_needed_right = tmp_size_needed_right;
      nodes[current].current_tree_size = max(nodes[current].current_tree_size, size);
      return true;
    }

    return false;
  }

  // we come from right
  // the current node must be chosen unless it is impossible to choose this node and get a valid solution
  if(!nodes[current].chosen)
    return false;
  
  // the left tree must be at least size - 2 big to support the right tree
  if(nodes[nodes[current].left].current_tree_size < size - 2)
    return false;

  if(check_poss(nodes, nodes[current].parent, current, size + 1, &tmp_avail)) {
    *avail = tmp_avail;
    //nodes[current].chosen = true;   already true
    nodes[current].current_tree_size = max(nodes[current].current_tree_size, size);
    return true;
  }
  return false;
} 

// Try to choose a specific node with number of available nodes to spend
// O(log n)
void try_choose(node *nodes, ll current, ll *avail) {
  if(nodes[current].chosen) {
    if(nodes[current].size_needed_right > 0) {
      generate_depth(nodes, nodes[current].right, nodes[current].size_needed_right);
      nodes[current].size_needed_right = 0;
    }
    return;
  }

  if(*avail == 0)
    return;

  ll tmp_avail = *avail - 1;
  if(check_poss(nodes, nodes[current].parent, current, 2, &tmp_avail)) {
    nodes[current].chosen = true;
    nodes[current].current_tree_size = max(nodes[current].current_tree_size,1LL);
    *avail = tmp_avail;
  }
}

int main() {
  ios_base::sync_with_stdio(false);


  ll n, avail, root;
  cin >> n >> avail;

  node *nodes = new node[n + 1];

  FOR(i,1,n + 1) {
    ll father;
    cin >> father;
    if(father == -1)
      root = i;
    else {
      nodes[i].parent = father;
      if(father > i)
        nodes[father].left = i;
      else
        nodes[father].right = i;
    }
  }
  
  // generate MINIMAL AVL-trees
  trees.pb(0);
  trees.pb(1);
  ll c = 1;
  while(trees[c++] <= n) {
    trees.pb(1 + trees[c - 2] + trees[c - 1]);
  }

  calculate_size(nodes, root);
  
  FOR(i,1,n + 1) {
    try_choose(nodes, i, &avail);
  }

  FOR(i,1,n+1) {
    cout << (nodes[i].chosen ? 1 : 0);
  }
  cout << endl;

  delete[] nodes;
  return 0;
}

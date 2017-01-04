// Practice of Segment tree

#include<bits/stdc++.h>
using namespace std;

class Node{
public:
  int unpaired;
  int val;
  int from, to;
  Node(){
    unpaired = 0;
    val = 0;
    from = to = 0;
  }
};

// CAVEAT: treePos must start from 1
void makeTree(string inputString, Node tree[], int low, int high, int treePos){ 
  // base case
  if (low == high){
    tree[treePos].from = tree[treePos].to = low;
    if (inputString[low] == '(') tree[treePos].unpaired = 1;
    return;
  }
  int mid = (low + high)/2;

  Node left = tree[treePos*2];
  Node right = tree[treePos*2+1];
  
  makeTree(inputString, tree, low, mid, treePos*2);
  makeTree(inputString, tree, mid+1, high, treePos*2+1);

  int lenOfRight = right.to - right.from + 1;
  int match = min(left.unpaired, lenOfRight - right.val - right.unpaired);
  tree[treePos].unpaired = left.unpaired + right.unpaired - match;
  tree[treePos].val = left.val + right.val + match*2;
  tree[treePos].from = low;
  tree[treePos].to = high;
}

void display(Node tree[], int size){
  for (int i=1; i<size; i++){
    cout << "unpaired: " << tree[i].unpaired << " val: " << tree[i].val << endl;
  }
}

// Utility function
Node NodeCompare(Node one, Node two){
  int lenOf2 = two.to - two.from + 1;
  int match = min(one.unpaired, lenOf2 - two.val - two.unpaired);
  Node tempNode;
  tempNode.to = two.to;
  tempNode.from = one.from;
  tempNode.unpaired = one.unpaired + two.unpaired - match;
  tempNode.val = one.val + two.val + match*2;
  return tempNode;
}

// Utility function
Node searchForbraces(Node tree[], int i, int j, int treePos){
  if (j<tree[treePos].to or i>tree[treePos].from){
    Node n; //default values from constructor are the needed values
    return n;
  }
  else if (tree[treePos].from == i and tree[treePos].to == j){
    return tree[treePos];
  }

  return NodeCompare(searchForbraces(tree, i, j, treePos*2),searchForbraces(tree, i, j, treePos*2+1));
}

int search(Node tree[], int i, int j){
  return searchForbraces(tree, i, j, 1).val;
}

int main(){

  string inputString ="())(())(())(";
  Node tree[inputString.length()*2]; // tree must have double the size of input
  
  makeTree(inputString, tree, 0, inputString.length()-1, 1);//tree starts from 1
  // display(tree, inputString.length());

  cout << search(tree, 2, 10) << endl;
  
  return 0;
}

struct SegmentTreeNode {
  // variables to store aggregate statistics and
  // any other information required to merge these
  // aggregate statistics to form parent nodes
  
  void assignLeaf(int value) {
    // T is the type of input array element
    // Given the value of an input array element,
    // build aggregate statistics for this leaf node
  }
  
  void merge(SegmentTreeNode& left, SegmentTreeNode& right) {
    // merge the aggregate statistics of left and right
    // children to form the aggregate statistics of
    // their parent node
  }
  
  int getValue() {
    // V is the type of the required aggregate statistic
    // return the value of required aggregate statistic
    // associated with this node
  }
};


// T is the type of input array elements
// V is the type of required aggregrate statistic
template<class T, class V>
class SegmentTree{
	SegmentTreeNode* nodes;
	int N;

public:
	SegmentTree(T arr[], int N){
		this->N = N;
		nodes = new SegmentTreeNode[getSegmentTreeSize(N)];
		buildTree(arr, 1, 0, N-1);
	}

	~SegmentTree(){
		delete [] nodes;
	}

	V getValue(int lo, int hi){
		SegmentTreeNode rs = getValue(1, 0, N-1, lo, hi);
		return rs.getValue();
	}

	void update(int index, T value){
		update(1, 0, N-1, index, value);
	}


private:

	int getSegmentTreeSize(int N) {
		int size;
    	for (size=1; size < N; size*=2);
    	return size * 2;
  	}

	// T is the type of the input array
	void buildTree(T arr[], int pos, int lo, int hi){
		if (lo == hi){
			nodes[pos].assignLeaf(arr[lo]);
			return;
		}

		int mid = (lo + hi)/2;
		int lf = 2*pos, rt = lf+1;
		buildTree(arr, lf, lo, mid);
		buildTree(arr, rt, mid+1, hi);
		nodes[pos].merge(nodes[lf],nodes[rt]);
	}

	SegmentTreeNode getValue(int pos, int lf, int rt, int lo, int hi){
		if (lf==lo and rt==hi)
			return nodes[pos];

		int mid = (lf+rt)/2;
		if (hi <= mid)
			return getValue(2*pos, lf, mid, lo, hi);
		if (lo > mid)
			return getValue(2*pos+1, mid+1, rt, lo, hi);

		SegmentTreeNode lfResult = getValue(2*pos, lf, mid, lo, hi);
		SegmentTreeNode rtResult = getValue(2*pos+1, mid+1, rt, lo, hi);
		SegmentTreeNode result;
		result.merge(lfResult, rtResult);
		return result;
	}

	void update(int pos, int lo, int hi, int index, T value){
		if (lo == hi){
			nodes[pos].assignLeaf(value);
			return;
		}

		int lf = 2*pos, rt = lf+1;
		int mid = (lo+hi)/2;
		if (index <= mid)
			update(lf, lo, mid, index, value);
		else
			update(rt, mid+1, hi, index, value);
		nodes[pos].merge(nodes[lf],nodes[rt]);
	}

};

int main(){

	return 0;
}
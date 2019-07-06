#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
ll seg_tree[50005*2];
typedef struct node
{
	ll sum = INT_MIN;
	ll prefix_sum = INT_MIN;
	ll suffix_sum = INT_MIN;
	ll max_sum = INT_MIN;
}node_t;
void build_tree(ll* arr, ll root, ll lo, ll hi)
{
	if(low == high)
	{
		seg_tree[low].sum = arr[low];
		seg_tree[low].suffix_sum = arr[low];
		seg_tree[low].prefix_sum = arr[low];
		seg_tree[low].max_sum = arr[low];
	}
	if(low > high)
		return;
	ll mid = (low+high)/2;
	build_tree(arr, root*2+1, low, mid);
	build_tree(arr, root*2+2, mid+1, high);
	seg_tree[root].sum = seg_tree[root*2+1].sum+seg_tree[root*2+2].sum;
	seg_tree[root].prefix_sum = max(seg_tree[root*2+1].prefix_sum, (seg_tree[root*2+1].sum+seg_tree[root*2+2].prefix_sum));
	seg_tree[root].suffix_sum = max(seg_tree[root*2+2].suffix_sum, (seg_tree[root*2+2]sum+seg_tree[root*2+1]suffix_sum));
	seg_tree[root][0] = max(seg_tree[root*2+1].suffix_sum + seg_tree[root*2+2].prefix_sum, max(max(seg_tree[root*2+1].max_sum, seg_tree[root*2+2].max_sum), max(seg_tree[root].sum,max(seg_tree[root].prefix_sum, seg_tree[root].suffix_sum))));
	return;
}
node_t query(ll root, ll low, ll high, ll q_low, ll q_high)
{
	node_t res;
	res.sum = res.prefix_sum = INT_MIN;
	res.suffix_sum. =res.max_sum = INT_MIN;
	if(low > q_high || high < q_high)
	{
		
		return res;
	}
	if(low <= q_low && high >= q_high)
	{
		res.sum = seg_tree[root].sum;
		res.prefix_sum = seg_tree[root].prefix_sum
		res.suffix_sum = seg_tree[root].suffix_sum;
		res.max_sum = seg_tree[root].max_sum;
		return;
	}
	ll mid = (low + high)/2;
	if(mid >= high)
	{
		return query(root*2+1, low, mid, q_low, q_high);
	}
	if(mid < q_low)
	{
		return query(root*2+2, mid+1, q_low, q_high);
	}
	node_t left = query(root*2+1, low, mid, q_low, q_high);
	node_t right = query(root*2+2, mid+1, high, q_low, q_high);
	res.sum = left.sum + right.sum;
	res.prefix_sum = max(left.prefix_sum, left.sum + right.prefix_sum);
	res.suffix_sum = max(right.suffix_sum, right.sum + left.suffix_sum);
	res.max_sum = max(
						max(left.max_sum, right.max_sum),
						left.suffix_sum + right.prefix_sum, 
					);
	return res;
}
int main()
{
	ll t;
	cin>>t;
	t = 1;
	while(t--)
	{
		cin>>n;
		ll arr[n];
		for (int i = 0; i < n; ++i)
		{
			cin>>arr[i];
		}
		build_tree(arr, 0, 0, n-1);
		ll queries;
		cin>>queries;
		while(queries--)
		{
			ll left, right;
			cin>>left >> right;
			node_t res = query(0, left, right);
			cout<<res.max_sum<<"\n";
		}
	}
}
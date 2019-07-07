// #include<c++/9.1.0/bits/stdc++.h>
#include<iostream>
#include<limits>
using namespace std;
typedef long long ll;
ll n;
typedef struct node
{
	ll sum ;
	ll prefix_sum;
	ll suffix_sum ;
	ll max_sum ;
}node_t;
node_t seg_tree[50005*2];
void build_tree(ll* arr, ll root, ll low, ll high)
{
	if(low == high)
	{
		// cout<<"\nlow: "<<arr[low];
		seg_tree[root].sum = arr[low];
		seg_tree[root].suffix_sum = arr[low];
		seg_tree[root].prefix_sum = arr[low];
		seg_tree[root].max_sum = arr[low];
		return;
	}
	if(low > high)
		return;
	ll mid = (low+high)/2;
	build_tree(arr, root*2+1, low, mid);
	build_tree(arr, root*2+2, mid+1, high);
	seg_tree[root].sum = seg_tree[root*2+1].sum+seg_tree[root*2+2].sum;
	seg_tree[root].prefix_sum = max(seg_tree[root*2+1].prefix_sum, (seg_tree[root*2+1].sum+seg_tree[root*2+2].prefix_sum));
	seg_tree[root].suffix_sum = max(seg_tree[root*2+2].suffix_sum, (seg_tree[root*2+2].sum+seg_tree[root*2+1].suffix_sum));
	seg_tree[root].max_sum = max(max(seg_tree[root*2+1].max_sum, seg_tree[root*2+2].max_sum),seg_tree[root*2+1].suffix_sum + seg_tree[root*2+2].prefix_sum);
	return;
}
node_t query(ll root, ll low, ll high, ll q_low, ll q_high)
{
	node_t res;
	res.sum = res.prefix_sum = INT_MIN;
	res.suffix_sum =res.max_sum = INT_MIN;
	if(low > q_high || high < q_low)
	{
		return res;
	}
	if(low >= q_low && high <= q_high)
	{
		res.sum = seg_tree[root].sum;
		res.prefix_sum = seg_tree[root].prefix_sum;
		res.suffix_sum = seg_tree[root].suffix_sum;
		res.max_sum = seg_tree[root].max_sum;
		return res;
	}
	ll mid = (low + high)/2;
	if(mid >= q_high)
	{
		return query(root*2+1, low, mid, q_low, q_high);
	}
	if(mid < q_low)
	{
		return query(root*2+2, mid+1, high, q_low, q_high);
	}
	node_t left = query(root*2+1, low, mid, q_low, q_high);
	node_t right = query(root*2+2, mid+1, high, q_low, q_high);
	res.sum = left.sum + right.sum;
	res.prefix_sum = max(left.prefix_sum, left.sum + right.prefix_sum);
	res.suffix_sum = max(right.suffix_sum, right.sum + left.suffix_sum);
	res.max_sum = max(
						max(left.max_sum, right.max_sum),
						left.suffix_sum + right.prefix_sum
					);
	return res;
}
int main()
{
	freopen("/Users/vthombre/Desktop/sandbox/codes/input.txt", "r", stdin);
	freopen("/Users/vthombre/Desktop/sandbox/codes/output.txt", "w", stdout);
	ll t;
	// cin>>t;
	// cout<<"At least in file\n";
	t = 1;
	while(t--)
	{
		cin>>n;
		ll arr[n];
		for (ll i = 0; i < n; ++i)
		{
			cin>>arr[i];
		}
		build_tree(arr, 0, 0, n-1);
		// for (int i = 0; i < n*2; ++i)
		// {
		// 	cout<<seg_tree[i].sum<<" ";
		// }
		// cout<<"Tree build success\n";
		ll queries;
		cin>>queries;
		while(queries--)
		{
			ll left, right;
			cin>>left >> right;
			// cout<<left-1 <<" "<<right-1<<"\n";
			node_t res = query(0, 0, n-1, left-1, right-1);
			cout<<res.max_sum<<"\n";
		}
	}
}
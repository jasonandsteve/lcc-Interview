//
// Created by heyue on 2022/4/13.
//

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <unordered_map>
#include <math.h>
#include <algorithm>

using namespace std;

//动态规划77，爬楼梯
class Solution {
public:
	int climbStairs(int n) {
		if (n <= 1) return n;
		vector<int> dp(n + 1);
		dp[1] = 1;
		dp[2] = 2;
		for (int i = 3; i <= n; i++) {
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		return dp[n];
	}
};

//动归746使用最小花费爬楼梯

class Solution {
public:
	int minCostClimbingStairs(vector<int>& cost) {
		if (cost.size() <= 1) return cost[0];
		vector<int> dp(cost.size() + 1);
		dp[0] = cost[0];
		dp[1] = cost[1];
		for (int i = 2; i<cost.size(); i++) {
			dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
		}
		return min(dp[cost.size() - 2], dp[cost.size() - 1]);
	}
};
//不同路径
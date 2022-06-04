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
//62不同路径

class Solution {
public:
	int uniquePaths(int m, int n) {
		vector<vector<int>>dp(m, vector<int>(n, 0));
		for (int i = 0; i < m; i++)dp[i][0] = 1;
		for (int j = 0; j < n; j++)dp[0][j] = 1;
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
		return dp[m - 1][n - 1];

	}
};

//不同路径（有障碍版本）
class Solution {
public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		int m = obstacleGrid.size();
		int n = obstacleGrid[0].size();
		vector<vector<int>>dp(m, vector<int>(n, 0));
		for (int i = 0; i < m && obstacleGrid[i][0] == 0; i++) dp[i][0] = 1;
		for (int j = 0; j < n && obstacleGrid[0][j] == 0; j++) dp[0][j] = 1;
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				if (obstacleGrid[i][j] == 1) continue;
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
		return dp[m - 1][n - 1];
	}
};

//343 整数拆分
class Solution {
public:
	int integerBreak(int n) {
		vector<int> dp(n + 1);
		dp[2] = 1;
		for (int i = 3; i <= n; i++) {
			for (int j = 1; j <= i - 1; j++) {
				dp[i] = max(dp[i], max(j*(i - j), j*dp[i - j]));//我的错误是没考虑到，每次j在变换的，时候，得到的数值是一直变得，要把最大的保存下来。
			}
		}
		return dp[n];

	}
};

//96不同二叉搜索树
class Solution {
public:
	int numTrees(int n) {
		vector<int> dp(n + 1, 0);
		dp[0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < i; j++) {
				dp[i] += dp[j] * dp[i - j - 1];
			}
		}
		return dp[n];


	}
};
//电话号码的字母组合
class Solution {
private:
	const string letterMap[10] = {
		"",//0
		"",//1
		"abc",//2
		"def",//3
		"ghi",//4
		"jkl",//5
		"mno",//6
		"pqrs",//7
		"tuv",//8
		"wxyz",//9
	};

public:
	vector<string> result;
	string path;
	void backtracking(const string& digits, int index) {
		if (path.size() == digits.size()) {
			result.push_back(path);
			return;
		}
		int digit = digits[index] - '0';//将index指向的数字变为int
		string letters = letterMap[digit];//从对应表中取出对应的字符表
		cout << letters << endl;
		for (int i = 0; i < letters.size(); i++) {
			path.push_back(letters[i]);//处理
			backtracking(digits, index + 1);//递归，注意index+1，一下层要处理下一个数字
			path.pop_back();//回溯
		}


	}
	vector<string> letterCombinations(string digits) {
		result.clear();
		if (digits.size() == 0) {
			return result;
		}
		backtracking(digits, 0);
		return result;



	}
};

//寻找两个正序数组的中位数
#include <stdio.h>
#include <vector>
using namespace std;

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int n = nums1.size();
		int m = nums2.size();

		if (n > m)  //保证数组1一定最短
		{
			return findMedianSortedArrays(nums2, nums1);
		}

		// Ci 为第i个数组的割,比如C1为2时表示第1个数组只有2个元素。LMaxi为第i个数组割后的左元素。RMini为第i个数组割后的右元素。
		int LMax1, LMax2, RMin1, RMin2, c1, c2, lo = 0, hi = 2 * n;  //我们目前是虚拟加了'#'所以数组1是2*n长度

		while (lo <= hi)   //二分
		{
			c1 = (lo + hi) / 2;  //c1是二分的结果
			c2 = m + n - c1;

			LMax1 = (c1 == 0) ? INT_MIN : nums1[(c1 - 1) / 2];
			RMin1 = (c1 == 2 * n) ? INT_MAX : nums1[c1 / 2];
			LMax2 = (c2 == 0) ? INT_MIN : nums2[(c2 - 1) / 2];
			RMin2 = (c2 == 2 * m) ? INT_MAX : nums2[c2 / 2];

			if (LMax1 > RMin2)
				hi = c1 - 1;
			else if (LMax2 > RMin1)
				lo = c1 + 1;
			else
				break;
		}
		return (max(LMax1, LMax2) + min(RMin1, RMin2)) / 2.0;
	}
};


int main(int argc, char *argv[])
{
	vector<int> nums1 = { 2,3, 5 };
	vector<int> nums2 = { 1,4,7, 9 };

	Solution solution;
	double ret = solution.findMedianSortedArrays(nums1, nums2);
	return 0;
}
//分割等和子串;
class Solution {
public:
	bool canPartition(vector<int>& nums) {
		int sum = 0;
		//dp[i]中的i表示背包内总和
		//题目总说，每个数组中的元素不会超过100，数组的大小不会超过200
		//总和不会大于20000，背包最大只需要
		vector<int> dp(10001, 0);
		for (int i = 0; i < nums.size(); i++) {
			sum += nums[i];
		}
		if (sum % 2 == 1) return false;
		int target = sum / 2;

		for (int i = 0; i < nums.size(); i++) {
			for (int j = target; j >= nums[i]; j--) {
				dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
			}
		}
		if (dp[target] == target) return true;
		return false;


	}
};

//动规五部曲474
//背包问题
class Solution {
public:
	int findMaxForm(vector<string>& strs, int m, int n) {
		vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));//默认初始化为0
		for (string str : strs) {//遍历物品
			int oneNum = 0, zeroNum = 0;
			for (char c : str) {//统计物品中01数量
				if (c == '0') zeroNum++;
				else oneNum++;
			}
			for (int i = m; i >= zeroNum; i--) {//遍历背包容量从后向前遍历！！
				for (int j = n; j >= oneNum; j--) {
					dp[i][j] = max(dp[i][j], dp[i - zeroNum][j - oneNum] + 1);
				}
			}
		}
		return dp[m][n];

	}
};


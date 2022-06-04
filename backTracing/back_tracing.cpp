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


//leetcode  77组合
class Solution {
public:

	vector<vector<int>> result;
	vector<int> path;
	void backtracking(int n, int k, int startindex) {
		if (path.size() == k) {//中止条件
			result.push_back(path);
			return;
		}
		for (int i = startindex; i <= n; i++) {
			path.push_back(i);
			backtracking(n, k, i + 1);
			path.pop_back();//回溯
		}


	}
	vector<vector<int>> combine(int n, int k) {
		// result.clear();
		// path.clear();
		backtracking(n, k, 1);
		return result;

	}
};

leetcode216 组合总和III
class Solution {
public:

	vector<vector<int>> result;
	vector<int> path;
	void trackbacking(int targetSum, int k, int sum, int startindex) {
		if (path.size() == k) {
			if (sum == targetSum)result.push_back(path);
			return;
		}
		for (int i = startindex; i <= 9; i++) {
			sum += i;
			path.push_back(i);
			trackbacking(targetSum, k, sum, i + 1);
			sum -= i;
			path.pop_back();
		}

	}
	vector<vector<int>> combinationSum3(int k, int n) {
		trackbacking(n, k, 0, 1);
		return result;
	}



};

//全排列
class Solution {
public:
	vector<vector<int>> result;
	vector<int> path;
	void backtarcking(vector<int>& nums, vector<bool>& used) {
		if (path.size() == nums.size()) {
			result.push_back(path);
			return;
		}
		for (int i = 0; i < nums.size(); i++) {
			if (used[i] == true) continue;
			used[i] = true;
			path.push_back(nums[i]);
			backtarcking(nums, used);
			path.pop_back();
			used[i] = false;
		}

	}
	vector<vector<int>> permute(vector<int>& nums) {
		result.clear();
		path.clear();
		vector<bool>used(nums.size(), false);
		backtarcking(nums, used);
		return result;


	}
};
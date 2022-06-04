//
// Created by Orange on 2022/4/13.
//
/*
 * In this section, we will write the most useful and basic algorithms with cpp,such as
 * sort, find
 */
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <unordered_map>
#include <math.h>
#include <algorithm>

#include "basic/basic_algorithm.h"
#include "dynamicProgramming/dp.h"
#include "backTracing/back_tracing.h"
#include "linkList/link_list.h"
#include "stackQueen/stack_queen.h"

using namespace std;


int main(){
//    vector<int> pushed = {1, 2, 3, 4, 5};
//    vector<int> popped = {4, 5 ,1 ,2 ,3};
//    std::cout << validateStackSequences(pushed, popped) << endl;

//    double  x = 2.00000;
//    int n = 10;
//    std::cout<< "pow(x,n)="<<myPow(x,n)<<endl;


    MaxQueue* obj1 = new MaxQueue();
    obj1->push_back(6);
    cout<< "obj1 max_value: " << obj1->max_value() << " front_value:"<< obj1->pop_front() << endl;
    MaxQueue obj2;
    obj2.push_back(8);
    cout<< "obj2 max_value: " << obj2.max_value() << " front_value:"<< obj2.pop_front() << endl;





    return 0;
}


}

//周赛得题目
//242.有效得字母异位词
class Solution {
public:
	bool isAnagram(string s, string t) {
		int x[26] = { 0 }, y[26] = { 0 };
		for (int i = 0; i < s.size(); i++) x[s[i] - 'a'] ++;
		for (int i = 0; i < t.size(); i++) y[t[i] - 'a'] ++;
		for (int i = 0; i < 26; i++) {
			if (x[i] != y[i]) return false;
		}
		return true;

	}
};


////26删除有序数组中的重复项
class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() < 2)  return  nums.size();
		int j = 0;
		for (int i = 1; i< nums.size(); i++)
			if (nums[i] != nums[j]) nums[++j] = nums[i];
		return ++j;
	}
};

//27移除元素
class Solution {
public:
	int removeElement(vector<int>& nums, int val) {

		int j = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] != val) nums[j++] = nums[i];
		}
		return j;


	}
};

//28实现strStr() 匹配字符串
class Solution {
public:
	void getNext(int* next, const string& s) {
		int j = 0;
		next[0] = 0;
		for (int i = 1; i < s.size(); i++) {
			while (j > 0 && s[i] != s[j]) {
				j = next[j - 1];
			}
			if (s[i] == s[j]) {
				j++;
			}
			next[i] = j;
		}
	}
	int strStr(string haystack, string needle) {
		if (needle.size() == 0) {
			return 0;
		}
		int next[needle.size()];
		getNext(next, needle);
		int j = 0;
		for (int i = 0; i < haystack.size(); i++) {//这里的i是指向haystack的指针，j是指向needle的指针
			while (j > 0 && haystack[i] != needle[j]) {
				j = next[j - 1];
			}
			if (haystack[i] == needle[j]) {
				j++;
			}
			if (j == needle.size()) {//找到了匹配字符的地址
				return (i - needle.size() + 1);//返回地址
			}
		}
		return -1;
	}
};


29//两数相除，这题比较考验我们对时间复杂度的理解
class Solution {
public:
	int divide(int a, int b) {
		if (a == INT_MIN && b == -1) return INT_MAX;

		int sign = (a > 0) ^ (b > 0) ? -1 : 1;

		if (a > 0) a = -a;
		if (b > 0) b = -b;

		int res = 0;
		while (a <= b) {
			int value = b;
			int k = 1;
			// 0xc0000000 是十进制 -2^30 的十六进制的表示
			// 判断 value >= 0xc0000000 的原因：保证 value + value 不会溢出
			// 可以这样判断的原因是：0xc0000000 是最小值 -2^31 的一半，
			// 而 a 的值不可能比 -2^31 还要小，所以 value 不可能比 0xc0000000 小
			while (value >= 0xc0000000 && a <= value + value) {
				value += value;
				// 代码优化：如果 k 已经大于最大值的一半的话，那么直接返回最小值
				// 因为这个时候 k += k 的话肯定会大于等于 2147483648 ，这个超过了题目给的范围
				if (k > INT_MAX / 2) return INT_MIN;
				k += k;
			}
			a -= value;
			res += k;
		}

		// bug 修复：因为不能使用乘号，所以将乘号换成三目运算符
		return sign == 1 ? res : -res;
	}


};

//30串联所有单词的子串
class Solution {
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		int n = s.size();
		int stride = words[0].size();
		int limit = words.size() * stride;

		unordered_map<string, int> need;
		for (auto w : words) {
			need[w]++;
		}
		vector<int> ans;
		for (int start = 0; start <= stride - 1; start++) {
			// left 和 right 指向的是当前步子的第一个下标
			int left = start;
			int right = start;
			int cnt = 0;  // 记录窗口内满足要求的单词数量
			unordered_map<string, int> window;
			while (right < n) {
				// 右边届入窗
				string cur_right = s.substr(right, stride);
				if (need.count(cur_right)) {
					window[cur_right]++;
					if (window[cur_right] == need[cur_right]) {
						cnt++;
					}
				}
				// 左边届收缩
				if (right - left + stride > limit) {
					string cur_left = s.substr(left, stride);
					if (need.count(cur_left)) {
						if (window[cur_left] == need[cur_left]) {
							cnt--;
						}
						window[cur_left]--;
					}
					left += stride;
				}
				// 采集答案
				if (right - left + stride == limit && cnt == need.size()) {
					ans.push_back(left);
				}
				right += stride;
			}
		}

		return ans;
	}
};

//31下一个排列
class Solution {
public:
	void nextPermutation(vector <int> & nums) {
		int n = nums.size();
		if (n <= 1) return;
		int i = n - 2, j = n - 1, k = n - 1;
		//find A[i] < A[j]
		while (i >= 0 && nums[i] >= nums[j]) {
			--i, --j;
		}
		if (i >= 0) {
			//find A[i] < A[k]
			while (nums[i] >= nums[k]) --k;
			swap(nums[i], nums[k]);
		}
		reverse(nums.begin() + j, nums.end());
	}
};
/*思路：1从后向前查找第一个相邻升序的元素对 (i,j)，满足 A[i] < A[j]。此时 [j,end) 必然是降序
2在 [j,end) 从后向前查找第一个满足 A[i] < A[k] 的 k。A[i]、A[k] 分别就是上文所说的「小数」、「大数」
3将 A[i] 与 A[k] 交换
4可以断定这时 [j,end) 必然是降序，逆置 [j,end)，使其升序
如果在步骤 1 找不到符合的相邻元素对，说明当前 [begin,end) 为一个降序顺序，则直接跳到步骤 4
*/

//35搜索插入位置


class Solution {
public:
	int searchInsert(vector<int>& nums, int target) {
		int length = nums.size();
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] >= target) {
				return i;
			}
		}
		return nums.size();

	}
};
//36 有效数独
class Solution {
public:
	bool isValidSudoku(vector<vector<char>>& board) {
		int row[9][10] = { 0 };
		int col[9][10] = { 0 };
		int box[9][10] = { 0 };
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j<9; j++) {
				if (board[i][j] == '.') continue;
				int curnum = board[i][j] - '0';
				if (row[i][curnum] == 1) return false;
				if (col[j][curnum] == 1) return false;
				if (box[j / 3 + (i / 3) * 3][curnum] == 1) return false;
				row[i][curnum] = 1;// 之前都没出现过，现在出现了，就给它置为1，下次再遇见就能够直接返回false了。
				col[j][curnum] = 1;
				box[j / 3 + (i / 3) * 3][curnum] = 1;


			}

		}

		return true;
	}
};


//外观数列
class Solution {
public:
	string countAndSay(int n) {
		if (n == 1) return "1";
		auto s = countAndSay(n - 1);
		string res;
		for (int i = 0, j = 0; i<s.size();)
		{
			char c = s[i];
			while (i<s.size() && s[i] == c) ++i;
			int cnt = i - j;
			res += to_string(cnt) + c;
			j = i;
		}
		return res;
	}
};

//40组合总和||class Solution {
public:
	vector<vector<int>>result;
	vector<int>path;
	void backtracking(vector<int>& candidates, int target, int startIndex, int sum, vector<bool>& used) {
		if (sum >target) return;
		if (target == sum) {
			result.push_back(path);
			return;
		}
		for (int i = startIndex; i <candidates.size(); i++) {
			//used[i-1]=true;说明同一树枝candidates[i-1]使用过
			//used[i-1]=false;说明同一数层candidate[i-1]使用过
			if (i >0 && candidates[i] == candidates[i - 1] && used[i - 1] == false) {
				continue;
			}
			sum += candidates[i];
			path.push_back(candidates[i]);
			used[i] = true;
			backtracking(candidates, target, i + 1, sum, used);
			used[i] = false;
			sum -= candidates[i];
			path.pop_back();
		}

	}
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		vector<bool>used(candidates.size(), false);
		sort(candidates.begin(), candidates.end());
		backtracking(candidates, target, 0, 0, used);
		return result;
	}
};

//41缺失的第一个正数
//从第一个位置开始，让座位上的乘客走到自己应该坐的位置，并让该位置的人坐到第一个位置。一直进行这样的操作，直到第一个位置的人坐到自己位置。不过有时候有人喜欢套票，一旦发现第一个位置的人套票破，则中止交换，对第二到第n位置做相同的操作。
class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		for (int i = 0; i<nums.size(); i++) {
			while (0 < nums[i] && nums[i] <= nums.size() && nums[i] != nums[nums[i] - 1]) {
				swap(nums[i], nums[nums[i] - 1]);
			}
		}
		for (int i = 0; i< nums.size(); ++i) {
			if (nums[i] != i + 1) {
				return i + 1;
			}
		}
		return nums.size() + 1;
	}
};

//接雨水
class Solution {
public:
	int trap(vector<int>& height) {
		int n = height.size();
		// left[i]表示i左边的最大值，right[i]表示i右边的最大值
		vector<int> left(n), right(n);
		for (int i = 1; i < n; i++) {
			left[i] = max(left[i - 1], height[i - 1]);
		}
		for (int i = n - 2; i >= 0; i--) {
			right[i] = max(right[i + 1], height[i + 1]);
		}
		int water = 0;
		for (int i = 0; i < n; i++) {
			int level = min(left[i], right[i]);
			water += max(0, level - height[i]);
		}
		return water;
	}
};
/* 对于vector中每个点，水有多高取决于这个点左侧和右侧墙壁的最大高度。第一个for循环找每个点的左侧最大高度，第二个for循环找每个点右侧的最大高度，循环中跳过最左侧(i=0)和最右侧点(i=vector.size()-1)的原因是这两个点由于没有左侧墙壁或右侧墙壁所以最大墙壁高度肯定是0，故在初始化vector的时候已经将其默认设置成0了。在得到所有点的左右墙壁最大高度后，木桶原理取左右墙壁较低的那个高度减去当前位置墙壁作为地面的高度就得到了这个位置上水的高度。然后将所有点的水高度相加即为解。*/

//43字符串相乘
class Solution {
public:
	string multiply(string num1, string num2) {
		int n = num1.size(), m = num2.size();
		vector<int> a, b, c(n + m);
		for (int i = n - 1; i >= 0; i--) {
			a.push_back(num1[i] - '0');
		}
		for (int i = m - 1; i >= 0; i--) {
			b.push_back(num2[i] - '0');
		}

		// 模拟拿a去乘b的竖式乘法
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				c[i + j] += a[i] * b[j];
				c[i + j + 1] += c[i + j] / 10;
				c[i + j] %= 10;
			}
		}

		int l = n + m - 1;
		// 去除前导0, 直到剩下一个0
		while (l > 0 && c[l] == 0) {
			l--;
		}

		string res = "";
		for (int i = l; i >= 0; i--) {
			res += c[i] + '0';
		}

		return res;
	}
};

//44.通配符匹配
class Solution {
public:
	bool isMatch(string s, string p) {
		int m = s.length();
		int n = p.length();
		vector<vector<bool>>dp(m + 1, vector<bool>(n + 1, false));
		dp[0][0] = true;

		for (int j = 1; j <= n; j++) {
			if (p[j - 1] == '*')dp[0][j] = true;
			else break;
		}
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (p[j - 1] == '*') {
					dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
				}
				else if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1];
				}
				else {
					dp[i][j] = false;
				}
			}
		}
		return dp[m][n];
	}
};

//977 有序数组的平方
class Solution {
public:
	vector<int> sortedSquares(vector<int>& A) {
		int k = A.size() - 1;
		vector<int> result(A.size(), 0);

		for (int i = 0, j = A.size() - 1; i <= j;) {//注意这里要i<=j,因为最后要处理两个元素
			if (A[i] * A[i] < A[j] * A[j]) {
				result[k--] = A[j] * A[j];
				j--;
			}
			else {
				result[k--] = A[i] * A[i];
				i++;
			}
		}
		return result;
	}
};
//双指针法。

//48旋转图像
class Solution {
public:
	void rotate(vector<vector<int>>& matrix) {
		//先沿斜对角线翻转
		int n = matrix.size();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < i; j++)
				swap(matrix[i][j], matrix[j][i]);
		//再沿垂直竖线翻转
		for (int i = 0; i < n; i++) {
			for (int j = 0, k = n - 1; j <k; j++, k--) {
				swap(matrix[i][j], matrix[i][k]);
			}


		}
	}

};

//最大子树数组和
class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		int max = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			if (max < nums[i]) {
				max = nums[i];
			}
		}
		int sum = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (sum == 0 && nums[i] <= 0) continue;

			sum += nums[i];
			max = max > sum ? max : sum;
			if (sum <= 0) {//从这一点开始算
				sum = 0;
			}

		}
		return max;
	}
};
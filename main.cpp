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

//��������Ŀ
//242.��Ч����ĸ��λ��
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


////26ɾ�����������е��ظ���
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

//27�Ƴ�Ԫ��
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

//28ʵ��strStr() ƥ���ַ���
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
		for (int i = 0; i < haystack.size(); i++) {//�����i��ָ��haystack��ָ�룬j��ָ��needle��ָ��
			while (j > 0 && haystack[i] != needle[j]) {
				j = next[j - 1];
			}
			if (haystack[i] == needle[j]) {
				j++;
			}
			if (j == needle.size()) {//�ҵ���ƥ���ַ��ĵ�ַ
				return (i - needle.size() + 1);//���ص�ַ
			}
		}
		return -1;
	}
};


29//�������������ȽϿ������Ƕ�ʱ�临�Ӷȵ����
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
			// 0xc0000000 ��ʮ���� -2^30 ��ʮ�����Ƶı�ʾ
			// �ж� value >= 0xc0000000 ��ԭ�򣺱�֤ value + value �������
			// ���������жϵ�ԭ���ǣ�0xc0000000 ����Сֵ -2^31 ��һ�룬
			// �� a ��ֵ�����ܱ� -2^31 ��ҪС������ value �����ܱ� 0xc0000000 С
			while (value >= 0xc0000000 && a <= value + value) {
				value += value;
				// �����Ż������ k �Ѿ��������ֵ��һ��Ļ�����ôֱ�ӷ�����Сֵ
				// ��Ϊ���ʱ�� k += k �Ļ��϶�����ڵ��� 2147483648 �������������Ŀ���ķ�Χ
				if (k > INT_MAX / 2) return INT_MIN;
				k += k;
			}
			a -= value;
			res += k;
		}

		// bug �޸�����Ϊ����ʹ�ó˺ţ����Խ��˺Ż�����Ŀ�����
		return sign == 1 ? res : -res;
	}


};

//30�������е��ʵ��Ӵ�
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
			// left �� right ָ����ǵ�ǰ���ӵĵ�һ���±�
			int left = start;
			int right = start;
			int cnt = 0;  // ��¼����������Ҫ��ĵ�������
			unordered_map<string, int> window;
			while (right < n) {
				// �ұ߽��봰
				string cur_right = s.substr(right, stride);
				if (need.count(cur_right)) {
					window[cur_right]++;
					if (window[cur_right] == need[cur_right]) {
						cnt++;
					}
				}
				// ��߽�����
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
				// �ɼ���
				if (right - left + stride == limit && cnt == need.size()) {
					ans.push_back(left);
				}
				right += stride;
			}
		}

		return ans;
	}
};

//31��һ������
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
/*˼·��1�Ӻ���ǰ���ҵ�һ�����������Ԫ�ض� (i,j)������ A[i] < A[j]����ʱ [j,end) ��Ȼ�ǽ���
2�� [j,end) �Ӻ���ǰ���ҵ�һ������ A[i] < A[k] �� k��A[i]��A[k] �ֱ����������˵�ġ�С��������������
3�� A[i] �� A[k] ����
4���Զ϶���ʱ [j,end) ��Ȼ�ǽ������� [j,end)��ʹ������
����ڲ��� 1 �Ҳ������ϵ�����Ԫ�ضԣ�˵����ǰ [begin,end) Ϊһ������˳����ֱ���������� 4
*/

//35��������λ��


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
//36 ��Ч����
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
				row[i][curnum] = 1;// ֮ǰ��û���ֹ������ڳ����ˣ��͸�����Ϊ1���´����������ܹ�ֱ�ӷ���false�ˡ�
				col[j][curnum] = 1;
				box[j / 3 + (i / 3) * 3][curnum] = 1;


			}

		}

		return true;
	}
};


//�������
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

//40����ܺ�||class Solution {
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
			//used[i-1]=true;˵��ͬһ��֦candidates[i-1]ʹ�ù�
			//used[i-1]=false;˵��ͬһ����candidate[i-1]ʹ�ù�
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

//41ȱʧ�ĵ�һ������
//�ӵ�һ��λ�ÿ�ʼ������λ�ϵĳ˿��ߵ��Լ�Ӧ������λ�ã����ø�λ�õ���������һ��λ�á�һֱ���������Ĳ�����ֱ����һ��λ�õ��������Լ�λ�á�������ʱ������ϲ����Ʊ��һ�����ֵ�һ��λ�õ�����Ʊ�ƣ�����ֹ�������Եڶ�����nλ������ͬ�Ĳ�����
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

//����ˮ
class Solution {
public:
	int trap(vector<int>& height) {
		int n = height.size();
		// left[i]��ʾi��ߵ����ֵ��right[i]��ʾi�ұߵ����ֵ
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
/* ����vector��ÿ���㣬ˮ�ж��ȡ��������������Ҳ�ǽ�ڵ����߶ȡ���һ��forѭ����ÿ�����������߶ȣ��ڶ���forѭ����ÿ�����Ҳ�����߶ȣ�ѭ�������������(i=0)�����Ҳ��(i=vector.size()-1)��ԭ����������������û�����ǽ�ڻ��Ҳ�ǽ���������ǽ�ڸ߶ȿ϶���0�����ڳ�ʼ��vector��ʱ���Ѿ�����Ĭ�����ó�0�ˡ��ڵõ����е������ǽ�����߶Ⱥ�ľͰԭ��ȡ����ǽ�ڽϵ͵��Ǹ��߶ȼ�ȥ��ǰλ��ǽ����Ϊ����ĸ߶Ⱦ͵õ������λ����ˮ�ĸ߶ȡ�Ȼ�����е��ˮ�߶���Ӽ�Ϊ�⡣*/

//43�ַ������
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

		// ģ����aȥ��b����ʽ�˷�
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				c[i + j] += a[i] * b[j];
				c[i + j + 1] += c[i + j] / 10;
				c[i + j] %= 10;
			}
		}

		int l = n + m - 1;
		// ȥ��ǰ��0, ֱ��ʣ��һ��0
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

//44.ͨ���ƥ��
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

//977 ���������ƽ��
class Solution {
public:
	vector<int> sortedSquares(vector<int>& A) {
		int k = A.size() - 1;
		vector<int> result(A.size(), 0);

		for (int i = 0, j = A.size() - 1; i <= j;) {//ע������Ҫi<=j,��Ϊ���Ҫ��������Ԫ��
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
//˫ָ�뷨��

//48��תͼ��
class Solution {
public:
	void rotate(vector<vector<int>>& matrix) {
		//����б�Խ��߷�ת
		int n = matrix.size();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < i; j++)
				swap(matrix[i][j], matrix[j][i]);
		//���ش�ֱ���߷�ת
		for (int i = 0; i < n; i++) {
			for (int j = 0, k = n - 1; j <k; j++, k--) {
				swap(matrix[i][j], matrix[i][k]);
			}


		}
	}

};

//������������
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
			if (sum <= 0) {//����һ�㿪ʼ��
				sum = 0;
			}

		}
		return max;
	}
};
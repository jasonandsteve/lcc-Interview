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

//7整数翻转
class Solution {
public:
	int reverse(int x) {
		int out = 0;
		while (x != 0) {
			if ((out>214748364) || (out<-214748364)) return 0;
			out = out * 10 + x % 10;
			x = x / 10;
		}
		return out;
	}

};
/*如x=123，out=0;
out=0*10+123%10=3
x=123/10=12

out=3*10+12%10=32
x=12/10=1

out=32*10+1%10=123
x=1/10=0 完成翻转
*/

//8字符串转换整数
class Solution {
public:
	int myAtoi(string s) {
		bool flag = false;  // 是否开始读取数字部分
		int num = 0;  // 最终的数值大小
		int neg = -1;  // 是否为负数，1为负数，0为正数，-1表示未定义
		int length = s.size();  // 不能使用sizeof()
		int i = 0;
		for (i = 0; i<length; i++) {
			switch (s[i])
			{
			case ' ':
				if (flag) {
					i = length;  // 若开始处理数字后出现空格则结束，否则忽略
				}
				break;
			case '9':  // 考虑到边界条件，从大到小设置case数值
				if (num < -214748363) {  // -2147483639 越界
					num = -2147483648;
					i = length;
					break;
				}
			case '8':
				if (num > 214748363) {  // 2147483638 越界
					num = 2147483647;
					i = length;
					break;
				}
			case '7':
			case '6':
			case '5':
			case '4':
			case '3':
			case '2':
			case '1':
			case '0':
				if (num > 214748364) {  // 21474836350 到 21474836357 越界
					num = 2147483647;
					i = length;
					break;
				}
				if (num < -214748364) {  // -2147483650 到 -2147483657 越界
					num = -2147483648;
					i = length;
					break;
				}
				flag = true;  // 标记开始处理数字
				num *= 10;
				if (neg == -1) neg = 0;  // 若没有符号，则默认为正
				if (neg == 1) num -= s[i] - '0';
				if (neg == 0) num += s[i] - '0';
				break;
			case '-':
				flag = 1;  // 标记开始读取数字了
				if (neg == -1)neg = 1;
				else i = length;
				break;
			case '+':
				flag = 1;  // 标记开始读取数字了
				if (neg == -1)neg = 0;
				else i = length;
				break;
			default:
				i = length;  // 其他字符则直接结束
				break;
			}

		}
		return num;
	}
};
//穷举法

//11盛最多水的容器
/*讲解：
对O(n)的算法写一下自己的理解，一开始两个指针一个指向开头一个指向结尾，此时容器的底是最大的，接下来随着指针向内移动，
会造成容器的底变小，在这种情况下想要让容器盛水变多，就只有在容器的高上下功夫。 
那我们该如何决策哪个指针移动呢？我们能够发现不管是左指针向右移动一位，
还是右指针向左移动一位，容器的底都是一样的，都比原来减少了 1。这种情况下我们想要让指针移动后的容器面积增大，
就要使移动后的容器的高尽量大，所以我们选择指针所指的高较小的那个指针进行移动，
这样我们就保留了容器较高的那条边，放弃了较小的那条边，以获得有更高的边的机会。

*/
class Solution {
public:
	int maxArea(vector<int>& height) {
		int size = height.size();
		int left = 0, right = size - 1;
		int ans = 0;
		while (left < right) {
			ans = max(ans, (right - left)* min(height[left], height[right]));
			if (height[left] > height[right]) right--;
			else left++;

		}
		return ans;


	}
};

//12整数转罗马数字。
class Solution {
public:
	string intToRoman(int num) {
		int values[] = { 1000,900,500,400,100,90,50,40,10,9,5,4,1 };
		string reps[] = { "M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I" };

		string res;
		for (int i = 0; i < 13; i++) {
			while (num >= values[i]) {
				num -= values[i];//减去values值
				res += reps[i];//加上罗马字符
			}
		}
		return res;



	}
};

//13、罗马数字转整数
/*
这题懂了就非常简单。首先建立一个HashMap来映射符号和值，然后对字符串从左到右来，
如果当前字符代表的值不小于其右边，就加上该值；否则就减去该值。以此类推到最左边的数，最终得到的结果即是答案
*/
class Solution {
public:
	int romanToInt(string s) {
		int ans = 0, n = s.size();
		unordered_map<char, int> record = {
			{ 'I', 1 },
			{ 'V', 5 },
			{ 'X', 10 },
			{ 'L', 50 },
			{ 'C', 100 },
			{ 'D', 500 },
			{ 'M', 1000 }
		};

		for (int i = 0; i < n - 1; i++) {
			if (record[s[i]] < record[s[i + 1]])ans -= record[s[i]];
			else ans += record[s[i]];
		}
		return ans + record[s[n - 1]];
	}
};


//14最长公共前缀
class Solution {
public:
	string longestCommonPrefix(vector<string>& strs) {
		int min_len = strs[0].length();
		for (int k = 0; k < strs.size(); k++)
		{
			min_len = min_len < strs[k].length() ? min_len : strs[k].length();
		}

		int f = -1;//
		for (int i = 0; i < min_len; i++)
		{
			for (int k = 0; k < strs.size(); k++)
			{
				if (strs[k][i] != strs[0][i])
				{
					f = i;
					break;
				}
			}
			if (f != -1)
				break;
		}

		if (f == -1)
			return strs[0].substr(0, min_len);
		else
			return strs[0].substr(0, f);
	}
};

//15三数之和
class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());
		//找出a + b + c
		//a = nums[i], b = nums[left] ,c = nums[right]
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] > 0) {
				return result;
			}
			//     if(nums[i] == nums[i+1]){
			//        continue;
			//    }
			if (i > 0 && nums[i] == nums[i - 1]) {
				continue;
			}
			int left = i + 1;
			int right = nums.size() - 1;
			while (right > left) {
				if (nums[i] + nums[left] + nums[right] > 0) {
					right--;
				}
				else if (nums[i] + nums[left] + nums[right] < 0) {
					left++;
				}
				else {
					result.push_back(vector<int>{nums[i], nums[left], nums[right]});
					//去重逻辑应该放在一个三元组之后
					while (right > left && nums[right] == nums[right - 1]) right--;
					while (right > left && nums[left] == nums[left + 1]) left++;
					//找到答案时，双指针同时收缩
					right--;
					left++;
				}

			}

		}

		return result;
	}
};

//16最接近得三数之和
class Solution {
	public int threeSumClosest(int[] nums, int target) {
		// 排序
		Arrays.sort(nums);
		int closestNum = nums[0] + nums[1] + nums[2];
		for (int i = 0; i < nums.length - 2; i++) {
			int l = i + 1, r = nums.length - 1;
			while (l < r) {
				int threeSum = nums[l] + nums[r] + nums[i];
				if (Math.abs(threeSum - target) < Math.abs(closestNum - target)) {
					closestNum = threeSum;
				}
				if (threeSum > target) {
					r--;
				}
				else if (threeSum < target) {
					l++;
				}
				else {
					// 如果已经等于target的话, 肯定是最接近的
					return target;
				}

			}

		}

		return closestNum;
	}

}

//18四数之和
class Solution {
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		sort(nums.begin(), nums.end());
		vector<vector<int> > res;
		if (nums.size()<4)
			return res;
		int a, b, c, d, _size = nums.size();
		for (a = 0; a <= _size - 4; a++) {
			if (a>0 && nums[a] == nums[a - 1]) continue;      //确保nums[a] 改变了
			for (b = a + 1; b <= _size - 3; b++) {
				if (b>a + 1 && nums[b] == nums[b - 1])continue;   //确保nums[b] 改变了
				c = b + 1, d = _size - 1;
				while (c<d) {
					if (nums[a] + nums[b] - target<-(nums[c] + nums[d]))//原写法num[a]+num[b]+num[c]+num[d]<target为了防止溢出，见下面的补充修改
						c++;
					else if (nums[a] + nums[b] - target>-(nums[c] + nums[d]))//同上
						d--;
					else {
						res.push_back({ nums[a],nums[b],nums[c],nums[d] });
						while (c<d&&nums[c + 1] == nums[c])      //确保nums[c] 改变了
							c++;
						while (c<d&&nums[d - 1] == nums[d])      //确保nums[d] 改变了
							d--;
						c++;
						d--;
					}
				}
			}
		}
		return res;
	}
};
/*四数之和与前面三数之和的思路几乎是一样的，嗝。（刚好前些天才写了三数之和的题解）
如果前面的三数之和会做了的话，这里其实就是在前面的基础上多添加一个遍历的指针而已。
会做三数之和的可以不用看下面的了。。

使用四个指针(a<b<c<d)。固定最小的a和b在左边，c=b+1,d=_size-1 移动两个指针包夹求解。
保存使得nums[a]+nums[b]+nums[c]+nums[d]==target的解。偏大时d左移，偏小时c右移。c和d相
遇时，表示以当前的a和b为最小值的解已经全部求得。b++,进入下一轮循环b循环，当b循环结束后。
a++，进入下一轮a循环。 即(a在最外层循环，里面嵌套b循环，再嵌套双指针c,d包夹求解)。
。*/


//删除链表的倒数第N个结点
class Solution {
public:
	int cur = 0;
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		if (!head) return NULL;
		head->next = removeNthFromEnd(head->next, n);
		cur++;
		if (n == cur) return head->next;
		return head;

	}
};

//20 有效的括号
class Solution {
public:
	bool isValid(string s) {
		stack<int> st;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '(') st.push(')');
			else if (s[i] == '{') st.push('}');
			else if (s[i] == '[') st.push(']');
			//第三种情况：遍历字符串匹配的过程中，栈已经为空，没有匹配的字符，说明右括号没有找到对应的左括号return false
			//第二种情况：遍历字符串匹配的过程中，发现栈里面没有我们要匹配的字符，所以return false
			else if (st.empty() || st.top() != s[i]) return false;
			else if (st.top() == s[i]) st.pop();//st.top()与s[i]相等，栈弹出元素
		}
		//第一种情况：此时我们已经遍历完了字符串，但是栈不为空，说明有相应的左括号没有右括号来匹配，所以return false，否则return  true
		return st.empty();
	}
};

//注意：括号问题是用栈解决的经典问题。
//21合并两个有序链表
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (l1 == NULL) {
			return l2;
		}
		if (l2 == NULL) {
			return l1;
		}
		if (l1->val <= l2->val) {
			l1->next = mergeTwoLists(l1->next, l2);
			return l1;
		}
		l2->next = mergeTwoLists(l1, l2->next);
		return l2;
	}
};
//非常简单的递归




//22 括号生成
//DFS，类似于回溯算法
class Solution {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> res;
		func(res, "", 0, 0, n);
		return res;
	}

	void func(vector<string> &res, string str, int l, int r, int n) {
		if (l > n || r > n || r > l) return;
		if (l == n && r == n) { res.push_back(str); return; }
		func(res, str + '(', l + 1, r, n);
		func(res, str + ')', l, r + 1, n);
		return;
	}
};
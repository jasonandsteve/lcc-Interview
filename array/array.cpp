//
// Created by Orange on 2022/4/22.
//

#include <stdlib.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <algorithm>

using  namespace  std;

//376摆动序列

class Solution {
public:
	int wiggleMaxLength(vector<int>& nums) {
		int curDiff = 0;//当前一对差值
		int preDiff = 0;//前一对差值
		int result = 1;//记录峰值个数，序列默认序列最右边有一个峰值
		for (int i = 0; i < nums.size() - 1; i++) {
			curDiff = nums[i + 1] - nums[i];
			if ((curDiff > 0 && preDiff <= 0) || (preDiff >= 0 && curDiff<0)) {
				result++;
				preDiff = curDiff;
			}
		}
		return result;
	}
};

public sta

// Created by heyue on 2022/4/13
/*
 *kill the linklist
 *
 *
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

using namespace std;
//两两交换链表中的节点
class Solution {
public:
	ListNode* swapPairs(ListNode* head) {
		ListNode* dummyHead = new ListNode(0);//设置一个虚拟节点
		dummyHead->next = head;//将虚拟头节点指向head，方便后面做删除
		ListNode* cur = dummyHead;
		while (cur->next != nullptr && cur->next->next != nullptr) {
			ListNode* tmp = cur->next;//记录临时节点
			ListNode*tmp1 = cur->next->next->next;//记录临时节点

			cur->next = cur->next->next;//步骤一
			cur->next->next = tmp;   //步骤二
			cur->next->next->next = tmp1;//步骤三
			cur = cur->next->next;//cur移动两位，准备下一轮交换
		}
		return dummyHead->next;


	}
}; 



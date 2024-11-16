//选择排序
//每一趟从待排序的记录中选出关键字最小的记录，
//按顺序放在已排序的记录序列的最后，直到全部排完为止。
//在这里实现简单选择排序和堆排序
//默认为升序
//由于 swap（交换两个元素）操作的存在，选择排序是一种不稳定的排序算法。
#pragma once
#include<iostream>
#include<vector>

//简单选择排序 (SimpleSelection Sort)也称作直接选择排序。O(n^2)
//移动记录次数较少，当每一记录占用的空间较多时，此方法比直接插入排序快。
template<class T=int>
void Simple_Selection_Sort(T* a, int n)
{
	//找到n-1次最小值就已经有序了，
	for (int i = 0; i < n - 1; i++)
	{
		//交换的位置
		int ith = i;
		//找到最未排序的最小值,选择排序可以从这里入手提高效率
		for (int j = i + 1; j < n; j++)
		{
			if (a[j] < a[ith])ith = j;
		}
		//交换
		std::swap(a[ith], a[i]);
	}
}

//vector版本
template<class T = int>
void Simple_Selection_Sort(std::vector<T> a)
{
	int n = a.size();
	Simple_Selection_Sort(a.data(), n);
}


//堆排序（英语：Heapsort）
//利用 二叉堆 这种数据结构所设计的一种排序算法
//堆排序的本质是建立在堆上的选择排序
//或者说是将待排序的记录a[l..n]看成是一棵完全二叉树的顺序存储结构


//首先建立大顶堆,小数往下筛,大数往上浮
template<class T=int>
void sift_down(T* a, int start, int end)
{
	//父节点
	int parent = start;

	//子节点，因为从零开始，所以子节点为parent*2+1，parent*2+2（完全二叉树性质
	int child = parent * 2 + 1;

	//存在child,即子节点编号在区间[start,end]内（完全二叉树性质）
	while (child <= end)
	{
		//比较两个子节点（如果存在），取大值与父节点交换，使父节点大于两个子节点，形成大根堆
		if (child + 1 <= end && a[child] < a[child + 1])child++;

		//已经是大根堆
		if (a[child] <= a[parent])
		{
			return;
		}
		else
		{
			std::swap(a[parent], a[child]);
			//往下调整
			parent = child;
			child = parent * 2 + 1;
		}
	}
}


//这里为堆排序完整实现
template<class T=int>
void Heap_Sort(T* a, int n)
{
	if (n <= 1)return;

	//从最后一个节点的父节点完成堆化，因为数组从零开始，所以最后一个节点为n-1-1
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		sift_down(a, i, n - 1);
	}

	//建完堆
	//将第一个元素和已排序的前一位交换，接着重新调整，
	//将大数往上，小数往下，即重新找到下一个要排序的大数
	for (int i = n - 1; i > 0; i--)
	{
		//i为要交换的位置，即第n-i大的数
		std::swap(a[0], a[i]);

		//重新调整，但是结束区间不包括已排序值
		sift_down(a, 0, i - 1);
	}
}

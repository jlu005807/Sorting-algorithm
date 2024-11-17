#pragma once
#include<iostream>
#include<queue>

//前述各类排序方法,选择，插入，交换，归并都是建立在关键字比较的基础上
//基于比价的排序算法时间复杂度下限是O（n*log2n)
//而分配类排序根据关键字中各位的值，通过对待排序记录进行若干趟“分配” 与 “收集” 来实现排序的
//借助于多关键字排序的思想对单关键字排序的方法
//基数排序(RadixSorting)是典型的分配类排序


//链式基数排序
// “最低位优先法”，从第 k 关键字到第 1 关键字顺序进行比较


//计数排序,只适用于元素集中于一个范围的排序
template<class T=int>
void Counting_Sort(T* elem,int n)
{
	//求最大值和最小值
	T max = elem[0];
	T min = elem[0];

	for (int i = 0; i < n; i++)
	{
		if (elem[i] > max)max = elem[i];
		if (elem[i] < min)min = elem[i];
	}

	
	//元素范围
	int gap = max - min;

	//统计数组个数
	int* count_a = new int[gap + 1];


	//初始化count_a
	for (int i = 0; i < gap + 1; i++)
		count_a[i] = 0;

	//特殊类型需要重载运算符"-"
	for (int i = 0; i < n; i++)
		//根据关键词计数
		count_a[elem[i] - min]++;

	for (int i = 1; i < gap + 1; i++)
		//计算元素所在位置
		count_a[i] += count_a[i - 1];


	//临时数组
	T* sorted_a = new T[capcity];
	for (int i = n - 1; i >= 0; i--)
	{
		//如果有重复元素则位置减一
		int idx = --count_a[elem[i] - min];

		sorted_a[idx] = elem[i];
	}

	//返回
	for (int i = 0; i < n; i++)
	{
		elem[i] = sorted_a[i];
	}

	//释放空间
	delete[] sorted_a;
}

//局部计数排序,类似桶排序，但是依旧适用于元素集中的数组
template<class T = int>
void Bucket_Sort(T* elem, int n)
{
	if (n <= 0)return;

	//求最大值和最小值
	T max = elem[0];
	T min = elem[0];

	for (int i = 0; i < n; i++)
	{
		if (elem[i] > max)max = elem[i];
		if (elem[i] < min)min = elem[i];
	}


	int size = 1, cnt = 1;

	if (n != 0)
	{
		//桶中数组范围
		size = (max - min) / n + 1;
	}

	if (n != 0)
	{
		//桶数(至少为一
		cnt = (max - min) / size + 1;
	}

	//创建桶
	std::vector<std::vector<T>> buckets(cnt);

	//放入桶中
	for (int i = 0; i < n; i++) {

		//判断元素在哪个范围，即在哪个桶
		int idx = (elem[i] - min) / size;
		//入桶
		buckets[idx].push_back(elem[i]);
	}

	//分别利用关键词比较排序每个桶
	for (int i = 0; i < cnt; i++)
	{
		sort(buckets[i].begin(), buckets[i].end());
	}


	int index = 0;
	//重新放入原数组
	for (int i = 0; i < cnt; i++)
	{
		for (int j = 0; j < buckets[i].size(); j++)
		{
			elem[index++] = buckets[i][j];
		}
	}


}
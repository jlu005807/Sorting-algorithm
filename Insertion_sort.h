#pragma once
#include<iostream>
#include<vector>
#include<algorithm>

//插入排序,将待排列元素划分为「已排序」和「未排序」两部分，
//每次从「未排序的」元素中选择一个,按其关键字的大小插插入到「已排序的」元素中的正确位置。
//默认T类型有重载比较运算符（至少有<运算符）
//默认为升序


//直接插人排序，O(n^2)
//稳定排序,更适合于初始记录基本有序（正序）的情况
//也适用千链式存储结构，只是在单链表上无需移动记录，只需修改相应的指针
template<class T=int>
void Straight_Insertion_Sort(T a[], int n)
{
	//对顺序表L做直接插入排序
	//数组从0开始，第零个元素已经有序,所以从1开始排序
	for (int i = 1; i < n; i++)
	{
		//记录要插入的元素
		T key = a[i];
		
		//从i-1位置往前找位置,同时后移元素
		int j = i - 1;
		while (j >= 0 && key < a[j])
		{
			//后移
			a[j + 1] = a[j];
			j--;
		}

		//插入
		a[j + 1] = key;
	}
}

//vector
template<class T = int>
void Straight_Insertion_Sort(std::vector<T>& a)
{
	size_t n = a.size();
	//对顺序表L做直接插入排序
	//数组从零开始，第零个元素已经有序
	for (int i = 1; i < n; i++)
	{
		//记录要插入的元素
		T key = a[i];

		//从i-1位置往前找位置,同时后移元素
		int j = i - 1;
		while (j >= 0 && key < a[j])
		{
			//后移
			a[j + 1] = a[j];
			j--;
		}

		//插入
		a[j + 1] = key;
	}
}

//折半插人排序，O(n^2)
//在已经排序的有序数组里采用二分查找，提高找到插入位置的效率
//稳定排序,适合初始记录无序、n较大时的情况。
//只能用于顺序结构
template<class T = int>
void Binary_Insertion_Sort(T a[], int n)
{
	//对顺序表L做折半插入排序
	for (int i = 1; i < n; i++)
	{
		//记录要插入的元素
		T key = a[i];

		//二分查找位置,在[0,i-1]找
		int low = 0;
		int high = i - 1;
		while (low <= high)
		{
			//折半
			int mid = (low + high) / 2;
			//更新搜索区间
			if (key < a[mid])high = mid - 1;
			else low = mid + 1;
		}

		//找到插入位置，为high+1
		
		//后移元素,high+1可以为low
		for (int j = i - 1; j >= high + 1; j--)a[j + 1] = a[j];

		//插入
		a[high + 1] = key;
	}
}

//vector
template<class T = int>
void Binary_Insertion_Sort(std::vector<T>& a)
{
	size_t n = a.size();
	//对顺序表L做折半插入排序
	for (int i = 1; i < n; i++)
	{
		//记录要插入的元素
		T key = a[i];

		//二分查找位置,在[0,i-1]找
		int low = 0;
		int high = i - 1;
		while (low <= high)
		{
			//折半
			int mid = (low + high) / 2;
			//更新搜索区间
			if (key < a[mid])high = mid - 1;
			else low = mid + 1;
		}

		//找到插入位置，为high+1

		//后移元素,high+1可以为low
		for (int j = i - 1; j >= high + 1; j--)a[j + 1] = a[j];

		//插入
		a[high + 1] = key;
	}
}

//希尔排序（英语：Shell sort），O(n*(log(n))^2)，平均时间复杂度和最坏时间复杂度与间距序列的选取有关
//也称为缩小增量排序法,是插入排序的一种改进版本

//采用分组插入,待排序记录序列分割成几组，对每组分别进行直接插入排序，然后增加每组的数据量，重新分组,直到“增量”为1
//希尔对记录的分组，不是简单地 ”逐段分割＂，而是将相隔某个 “增量” 的记录分成一组。

//具体步骤
//将待排序序列分为若干子序列（每个子序列的元素在原始数组中间距相同）
//对这些子序列进行插入排序
//减小每个子序列中元素之间的间距，重复上述过程直至间距减少为1。

//记录跳跃式地移动导致排序方法是不稳定的，只能用千顺序结构
//n越大时，效果越明显。所以适合初始记录无序、n较大时的情况


//C语言版
template<class T>
void Shellinsert_C(T a[], int n,int dk)
{
	int d = dk;//此次增量
	//插入排序
	for (int i = d; i < n; i++)
	{
		int j;
		if (a[i] < a[i - d])
		{
			//存在无序
			int key = a[i];

			//插入
			for (j = i - d; j >= 0 && key < a[j]; j -= d)
			{
				a[j + d] = a[j];
			}

			a[j + d] = key;
		}
	}
}


template<class T>
void ShellSort_C(T a[], int n,int t,int dk[])
{
	//dk[]存放着生成好的增量序列
	//有多种增量序列
	//希尔增量序列（2^k - 1）
	//Hibbard增量序列（1, 3, 7, 15, ...）
	//Sedgewick增量序列（1, 5, 19, 41, ...）

	for (int i = 0; i < t; i++)
	{
		Shellinsert_C(a, n, a[i]);
	}
}


//c++版
template<class T>
void ShellSort(T a[], int n)
{
	//初始化间隔 h，使用 Knuth 序列计算使其小于数组长度的最大值
	int h = 1;

	//生成最大增量
	while (h < n / 3)
	{
		h = 3 * h + 1;
	}

	//进行希尔排序，逐渐减少间隔 h，直到 h 减小到 1（最后一次遍历）
	while (h >= 1)
	{
		//对每一个间隔为 h 的子数组进行插入排序
		for (int i = h; i < n; i++)
		{
			//将 a[i] 插入到其对应的子数组中的正确位置
			for (int j = i; j >= h && a[i] < a[j - h]; j -= h)
			{
				std::swap(a[j], a[j - h]);//类似后移
			}
		}
		// 缩小间隔，使 h 逐渐减小，最终变为 1
		h = h / 3;
	}
}

//c++版
template<class T>
void ShellSort(std::vector<T>& a)
{
	size_t n = a.size();
	//初始化间隔 h，使用 Knuth 序列计算使其小于数组长度的最大值
	size_t h = 1;

	//生成最大增量
	while (h < n / 3)
	{
		h = 3 * h + 1;
	}

	//进行希尔排序，逐渐减少间隔 h，直到 h 减小到 1（最后一次遍历）
	while (h >= 1)
	{
		//对每一个间隔为 h 的子数组进行插入排序
		for (size_t i = h; i < n; i++)
		{
			//将 a[i] 插入到其对应的子数组中的正确位置
			for (size_t j = i; j >= h && a[j] < a[j - h]; j -= h)
			{
				std::swap(a[j], a[j - h]);//类似后移
			}
		}
		// 缩小间隔，使 h 逐渐减小，最终变为 1
		h = h / 3;
	}
}


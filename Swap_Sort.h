#pragma once
#include<iostream>
#include<random>
#include<vector>

//交换排序的基本思想是：两两比较待排序记录的关键字，
//一旦发现两个记录不满足次序要求时则进行交换，直到整个序列全部满足要求为止。
//默认升序


//冒泡排序，O(n^2)
//两两比较相邻记录的关键字，如果发生逆序，则进行交换
//稳定排序,可用于链式存储结构
//当初始记录无序，n较大时
template<class T=int>
void Bubble_Sort(T a[], int n)
{
	//设置交换标识,开始时假设有交换
	bool flag = true;

	//只要一趟起泡排序有交换就继续
	while (flag)
	{
		//假设无交换
		flag = false;

		//遍历找逆序
		for (int i = 0; i < n - 1; i++)
		{
			//有逆序则交换
			if (a[i] < a[i + 1])
			{
				std::swap(a[i], a[i + 1]);
				//重置标识
				flag = true;
			}
		}
	}
}

template<class T = int>
void Bubble_Sort(std::vector<T> a)
{
	size_t n=a.size()
	//设置交换标识,开始时假设有交换
	bool flag = true;

	//只要一趟起泡排序有交换就继续
	while (flag)
	{
		//假设无交换
		flag = false;

		//遍历找逆序
		for (size_t i = 0; i < n - 1; i++)
		{
			//有逆序则交换
			if (a[i] < a[i + 1])
			{
				std::swap(a[i], a[i + 1]);
				//重置标识
				flag = true;
			}
		}
	}
}

//快速排序(QuickSort) 是由冒泡排序改进而得的，平均O(nlogn)
//快速排序的工作原理是通过 分治 的方式来将一个数组排序
//快速排序方法中的一次交换可能消除多个逆序。

//严蔚敏《数据结构》标准分割函数
template<class T=int>
void Quick_Sort(T a[], int left, int right)
{
	int low = left;
	int high = right;

	//退出递归
	if (low >= high)return;

	//这里选择第一个作为脊椎
	T pivot = a[low];

	//类似左右指针
	while (low < high)
	{
		//右指针左移直到小于基准
		while (low < high && a[high] >= pivot)
			--high;

		//交换
		a[low] = a[high];

		//左指针右移直到大于基准
		while (low < high && a[low] <= pivot)
			++low;

		//交换
		a[high] = a[low];
	}

	//放回基准值，此时low和high重合，左边的元素小于基准，右边的元素大于基准
	a[low] = pivot;

	//排序左区间
	Quick_Sort(a, left, low - 1);

	//排序右区间
	Quick_Sort(a, low + 1, right);
}

template<class T = int>
void Quick_Sort(std::vector<T>& a, int left, int right)
{
	int low = left;
	int high = right;

	//退出递归
	if (low >= high)return;

	//这里选择第一个作为脊椎
	T pivot = a[low];

	//类似左右指针
	while (low < high)
	{
		//右指针左移直到小于基准
		while (low < high && a[high] >= pivot)
			--high;

		//交换
		a[low] = a[high];

		//左指针右移直到大于基准
		while (low < high && a[low] <= pivot)
			++low;

		//交换
		a[high] = a[low];
	}

	//放回基准值，此时low和high重合，左边的元素小于基准，右边的元素大于基准
	a[low] = pivot;

	//排序左区间
	Quick_Sort(a, left, low - 1);

	//排序右区间
	Quick_Sort(a, low + 1, right);
}

//以下是其他快速排序
//对于快速排序里，划分左右区间有多种情况
//所以这样采用多态
template<class T>
class QuickSort
{
public:
	//不同方法的Sort不一样，即划分区间方法不同，或者说单趟排序不同所以分开实现
	virtual int Partion(T array[], int left, int right) = 0;

	//进行多趟排序相同一起实现,递归实现
	void Sort(T array[], int left, int right)
	{
		//退出递归条件
		if (left >= right)return;


		int idxkey = Sort(array, left, right);

		//继续排序左区间
		Sort(array, left, idxkey - 1);

		//排序右区间
		Sort(array, idxkey + 1, right);

	}

	//进行多趟排序相同一起实现,非递归实现
	//一个栈来保存需要处理的数组区间,
	//如果某个子数组的元素数量少于等于1，则不需要入栈处理
	void SortNoR(T a[], int left, int right)
	{
		//工作栈存放左右边界
		std::vector<std::pair<int, int>> stack;

		//存放开始左右边界
		stack.push_back({ left,right });

		//当栈不空
		while (!stack.empty())
		{
			//取出左右边界
			auto p = stack.back();
			stack.pop_back();
			
			////使用一次单趟的快排得到第一次的基准值
			int key = Partion(a, begin, end);

			//将基准值的左右边界入栈
			if (key + 1 < end)
			{
				//右边
				stack.push_back({ key + 1,right});
			}
			if (begin < key - 1)
			{
				//左边
				stack.push_back({ left,key - 1 });
			}
		}
	}




	//选择基准，一般选第一个或者最后一个，但是如果数组本来有序会导致效率低
	//可以三数取中（即选取第一个、最后一个以及中间的元素中的中位数）或者随机取数
	//下面为取基准的方法，可以优化快速排序
	//三数取中
	int getmid(T array[], int left, int right)
	{
		//获取中间值下标
		int mid = left + (right - left) / 2;

		//当left<mid
		if (array[left] < array[mid])
		{
			//如果mid<right
			if (array[mid] < array[right])
			{
				return mid;
			}
			else
			{
				//left>right
				if (array[left] > array[right])
				{
					return left;
				}
				else
				{
					return right;
				}
			}
		}
		else
		{
			//如果mid>right
			if (array[mid] > array[right])
			{
				return mid;
			}
			else
			{
				//left>right
				if (array[left] > array[right])
				{
					return left;
				}
				else
				{
					return right;
				}
			}
		}
	}

	//vector
	int getmid(std::vector<T> array, int left, int right)
	{
		//获取中间值下标
		int mid = left + (right - left) / 2;

		//当left<mid
		if (array[left] < array[mid])
		{
			//如果mid<right
			if (array[mid] < array[right])
			{
				return mid;
			}
			else
			{
				//left>right
				if (array[left] > array[right])
				{
					return left;
				}
				else
				{
					return right;
				}
			}
		}
		else
		{
			//如果mid>right
			if (array[mid] > array[right])
			{
				return mid;
			}
			else
			{
				//left>right
				if (array[left] > array[right])
				{
					return left;
				}
				else
				{
					return right;
				}
			}
		}
	}

	//随机法
	int getrandom(T array[], int left, int right)
	{
		std::random_device rd;   // 获取随机设备
		std::mt19937 gen(rd());  // 使用 Mersenne Twister 随机数生成器

		std::uniform_int_distribution<> size_dis(left, right);

		return size_dis;

	}

	//vector
	int getrandom(std::vector<T> array, int left, int right)
	{
		std::random_device rd;   // 获取随机设备
		std::mt19937 gen(rd());  // 使用 Mersenne Twister 随机数生成器

		std::uniform_int_distribution<> size_dis(left, right);

		return size_dis;

	}

};

//以子类分别实现不同单趟排序
//前后指针法
//可以先三数取中交换后，再选取数组的第一个元素作为基准数key
template<class T>
class FroandBack :public QuickSort<T>
{
	//返回左右区间的分界处，此处区间为左右闭区间即[left,right]
	int Partion(T array[], int left, int right)
	{
		//交换函数
		auto swap = [array](int left, int right)->void
		{
			T temp = array[left];
			array[left] = array[right];
			array[right] = temp;
			return;
		};

		int prev = left;
		int cur = left + 1;

		int idxkey = getmid(array, left, right);
		std::swap(array[idxkey], array[left]);

		int idxkey = left;//当前排序基准位置

		while (cur <= right)
		{
			//当cur找到比基准值小的值，cur与prev++位置的值交换
			if(array[cur] < array[idxkey] && ++prev != cur)
			{
				swap(cur, prev);
			}

			//当前指针后移
			++cur;
		}

		//最后cur越界（识别完所有的数据），交换prev和基准位置的值
		swap(prev, idxkey);

		//更新新基准位置
		idxkey = prev;

		return idxkey;
	}
};


//霍尔快排
template<class T>
class Hoare :public QuickSort<T>
{
	int Partion(T array[], int left, int right)
	{
		//用三数取中法得到key的位置
		int idxkey = getmid(array, left, right);
		std::swap(array[idxkey], array[left]);

		//当前排序基准位置
		int idxkey = left;

		//交换函数
		auto swap = [array](int left, int right)->void
		{
			T temp = array[left];
			array[left] = array[right];
			array[right] = temp;
			return;
		};

		while (left < right)
		{
			//右边左移找较小值
			while (left < right && array[right] >= array[idxkey])
				--right;

			//左边右移找较大值
			while (left < right && array[left] <= array[idxkey])
				++left;

			//交换
			swap(left, right);
		}

		//left和right相遇，交换
		swap(left, idxkey);

		//新基准位置
		idxkey = left;

		return idxkey;//返回基准位置

		// 霍尔单趟排序之后， 
		// key 位置左边的部分都比 keyi位置的值要小，
		// key 位置右边的部分都比 keyi位置的值要大。
	}
};

template<class T>
class Hole : public QuickSort<T>
{
	int Partion(T* array, int left, int right)//类似于Hoare
	{
		//用三数取中法得到key的位置
		int idxkey = getmid(array, left, right);
		std::swap(array[idxkey], array[left]);

		T key = array[left];//储存基准值
		int hole = left;//第一个坑

		while (left < right)
		{
			//右边左移找较小值
			while (left < right && array[right] >= key)
			{
				--right;
			}

			array[hole] = array[right];//填坑
			hole = right;//新坑

			//左边右移找较大值
			while (left < right && array[left] <= key)
			{
				++left;
			}

			array[hole] = array[left];
			hole = left;
		}

		array[hole] = key; //最后一个坑为新基准
		return hole;

	}
};


//以上为常规的快速排序
//以下是其他快速排序
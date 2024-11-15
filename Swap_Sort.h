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
			if (a[i] > a[i + 1])
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
	size_t n = a.size();
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
void Quick_Sort_C(T a[], int left, int right)
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
	Quick_Sort_C(a, left, low - 1);

	//排序右区间
	Quick_Sort_C(a, low + 1, right);
}

template<class T = int>
void Quick_Sort_C(std::vector<T>& a, int left, int right)
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


		int idxkey = Partion(array, left, right);

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
			int key = Partion(a, left, right);

			//将基准值的左右边界入栈
			if (key + 1 < right)
			{
				//右边
				stack.push_back({ key + 1,right});
			}
			if (left < key - 1)
			{
				//左边
				stack.push_back({ left,key - 1 });
			}
		}
	}




	//选择基准，一般选第一个或者最后一个，但是如果数组本来有序会导致效率低
	//可以三数取中（即选取第一个、最后一个以及中间的元素中的中位数）或者随机取数，以及中位数中的中位数
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
		return getmid(array.data(), left, right);
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
		return getrandom(array.data(), left, right);
	}

	//中位数中的中位数
	//该算法的流程如下：将整个序列划分为n/5组，每组元素数不超过 5 个；
	//寻找每组元素的中位数（因为元素个数较少，可以直接使用 插入排序 等算法）。
	//找出这n/5组元素中位数中的中位数。将该元素作为前述算法中每次划分时的分界值即可。
	//不考虑实现

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

		int key = QuickSort<T>::getmid(array, left, right);
		std::swap(array[key], array[left]);

		int idxkey = left;//当前排序基准位置

		while (cur <= right)
		{
			//当cur找到比基准值小的值，cur与prev++位置的值交换
			if(array[cur] <= array[idxkey] && ++prev != cur)
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
		int key = QuickSort<T>::getmid(array, left, right);
		std::swap(array[key], array[left]);

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
		int idxkey = QuickSort<T>::getmid(array, left, right);
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

		//填最后一个坑马，并且最后一个坑为新基准
		array[hole] = key; 
		return hole;

	}
};


//以上为常规的快速排序
//以下是其他快速排序


//三路划分法
//为了解决当数组中存在大量重复元素时，
// 传统的快速排序算法会导致不必要的比较和交换操作数组中存在大量重复元素问题
//小的甩到左边，大的甩到右边
//与 key 值相等的值推到中间
//[ begin , left-1 ] [ left , right ] [ right + 1 , end ]

// 模板的 T 参数表示元素的类型，此类型需要定义小于（<）运算
template<class T=int>
void Quick_Sort_Threeroad(T a[], const int n)
{
	if (n <= 1)return;

	//随机法取基准
	const T pivot = a[rand() % n];

	// i：当前操作的元素下标
	int i = 0;
	// arr[0, left)：存储小于 pivot 的元素
	int left = 0;
	// arr[right, len)：存储大于 pivot 的元素
	int right = n;

	// 完成一趟三路快排，将序列分为：
    // 小于 pivot 的元素 | 等于 pivot 的元素 | 大于 pivot 的元素
	while (i < right )//往前遍历
	{
		// 小于基准的元素交换到左边同时前移i
		if (a[i] < pivot)
		{
			std::swap(a[i++], a[left++]);
		}
		// 大于基准的元素交换到右边同时前移i
		else if (pivot<a[i])
		{
			//新交换过来的元素可能还是大于基准的，因此我们不急于让 i 继续向前遍历。
			std::swap(a[i], a[--right]);
		}
		// 相等的元素直接跳过不操作，只是前移i
		else i++;
	}

	Quick_Sort_Threeroad(a, left);

	Quick_Sort_Threeroad(a + right, n - right);

}

//小区间改造法
//当子区间的大小足够小时，可以考虑使用插入排序来代替递归调用
//通过设置一个阈值来决定是否使用插入排序

//实现插入排序
template<class T = int>
void Insertion_Sort(T* a, int n)
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

template<class T=int>
void Quick_Insert_Sort(T *a, int n)
{
	if (n <= 1)return;

	//类似三路划分
	//随机法取基准
	const T pivot = a[rand() % n];

	// i：当前操作的元素下标
	int i = 0;
	// arr[0, left)：存储小于 pivot 的元素
	int left = 0;
	// arr[right, len)：存储大于 pivot 的元素
	int right = n;

	// 完成一趟三路快排，将序列分为：
	// 小于 pivot 的元素 | 等于 pivot 的元素 | 大于 pivot 的元素
	while (i < right)//往前遍历
	{
		// 小于基准的元素交换到左边同时前移i
		if (a[i] < pivot)
		{
			std::swap(a[i++], a[left++]);
		}
		// 大于基准的元素交换到右边同时前移i
		else if (pivot < a[i])
		{
			//新交换过来的元素可能还是大于基准的，因此我们不急于让 i 继续向前遍历。
			std::swap(a[i], a[--right]);
		}
		// 相等的元素直接跳过不操作，只是前移i
		else i++;
	}

	//设置闸值为10
	//快排:: 小区间优化 因为插入排序在小数组上的性能往往比快速排序更好。
	if (n - right > 10)
	{
		Quick_Insert_Sort(a + right, n - right);
	}
	else
	{
		Insertion_Sort(a + right, n - right);
	}

	if (left > 10)
	{
		Quick_Sort_Threeroad(a, left);
	}
	else
	{
		Insertion_Sort(a, left);
	}

	return;
}



//内省排序
//内省排序（英语：Introsort 或 Introspective sort）是快速排序和 堆排序 的结合
//内省排序将快速排序的最大递归深度限制为[log2_n]，超过限制时就转换为堆排序。
//这样既保留了快速排序内存访问的局部性，又可以防止快速排序在某些情况下性能退化为 O(n^2)。
//暂时不实现
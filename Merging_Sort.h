#pragma once
//归井排序(Merging Sort),O(n*logn)
//将两个或两个以上的有序表合并成一个有序表的过程
//基于分治思想将数组分段排序后合并


//归并排序最核心的部分是合并（merge）过程：
//将两个有序的数组 a[i] 和 b[j] 合并为一个有序数组 c[k]。
template<class T=int>
void merge(const T* a, size_t alen, const T* b, size_t blen, T* c)
{
	//三个数组的工作指针
	size_t i = 0, j = 0, k = 0;

	//遍历比较
	while (i < alen && j < blen)
	{
		//先判断 b[j] < a[i]，保证稳定性
		if (b[j] < a[i])
		{
			c[k] = b[j];
			++j;
		}
		else
		{
			c[k] = a[i];
			++i;
		}
		//后移c的工作指针
		++k;
	}

	// 此时一个数组已空，另一个数组非空，将非空的数组并入 c 中
	for (; i < alen; ++i, ++k) c[k] = a[i];
	for (; j < blen; ++j, ++k) c[k] = b[j];

}

//pointer-style merge
template<class T = int>
void merge(const T* a, const T* a_end, const T* b, const T* b_end, T* c)
{
	//三个数组的工作指针
	size_t i = 0, j = 0, k = 0;

	int alen = a_end - a;
	int blen = b_end - b;

	//遍历比较
	while (i < alen && j < blen)
	{
		//先判断 b[j] < a[i]，保证稳定性
		if (b[j] < a[i])
		{
			c[k] = b[j];
			++j;
		}
		else
		{
			c[k] = a[i];
			++i;
		}
		//后移c的工作指针
		++k;
	}

	// 此时一个数组已空，另一个数组非空，将非空的数组并入 c 中
	for (; i < alen; ++i, ++k) c[k] = a[i];
	for (; j < blen; ++j, ++k) c[k] = b[j];
}

//注意下面的代码所表示的区间分别是 [l, r)，[l, mid)，[mid, r)。
//分治法实现归并排序
template<class T=int>
void Merge_Sort(T* a, int l, int r)
{
	//当数组长度为 1 时，该数组就已经是有序的，不用再分解
	if (r - l <= 1)return;

	//当数组长度大于 1 时，该数组很可能不是有序的。此时将该数组分为两段
	int mid = l + ((r - l) >> 1);

	//分治左右区间
	Merge_Sort(a, l, mid);
	Merge_Sort(a, mid , r);

	//创建临时数组
	T* temp = new T[r - l];

	//合并
	merge(a + l, a + mid, a + mid, a + r, temp);

	//返回
	for (int i = 0; i < r - l; i++)
	{
		a[i + l] = temp[i];
	}

	//释放空间
	delete[] temp;
}

//倍增法实现非递归的归并排序
template<class T=int>
void Merge_sort(T* a, size_t n)
{
	//临时数组
	T* temp = new T[n];

	//seg表示要合并的段的大小，每次翻倍
	for (size_t seg = 1; seg < n; seg <<= 1)
	{
		//从 left1 开始，将数组分为两段 [left1, right1) 和 [left2, right2)。
		//每次步长为 seg + seg，即跳过两个段的长度。
		for (size_t left1 = 0; left1 < n - seg; left1 += seg + seg)
		{
			size_t right1 = left1 + seg;
			size_t left2 = right1;

			//使用 std::min 确保第二段的右边界不会超过数组长度 n（处理最后一段）。
			size_t right2 = std::min(left2 + seg, n);

			//合并
			merge(a + left1, a + right1, a + left2, a + right2, temp + left1);

			//返回
			for (size_t i = left1; i < right2; ++i) a[i] = temp[i];
		}

	}

	//释放空间
	delete[] temp;
}
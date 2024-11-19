#pragma once
#include<iostream>
#include<algorithm>
#include<cstdint>
#include<stack>
#include<tuple>
#include<vector>

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
	T* sorted_a = new T[n];
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

//MSD 基数排序,
//基于 k - 关键字元素的比较方法，可以想到：先比较所有元素的第 1 关键字，就可以确定出各元素大致的大小关系；
//然后对 具有相同第 1 关键字的元素，再比较它们的第 2 关键字……以此类推。

using std::copy;  // 从 <algorithm> 引入 copy，用于复制数组元素
using std::make_tuple;
using std::stack;
using std::tie;
using std::tuple;
using std::vector;

using u32 = uint32_t;  // 简化 uint32_t 类型为 u32
using u64 = uint64_t;  // 简化 uint64_t 类型为 u64
using u32ptr = u32*;   // 定义 u32 的指针类型

// 实现 MSD（Most Significant Digit）基数排序,对自然数！！！排序
void MSD_radix_sort(u32ptr first, u32ptr last) 
{
	static constexpr u32 maxlogW = 32;  // 数据位宽最大为 32 位

	static constexpr u64 maxW = (u64)1 << maxlogW;  // 表示值域的上限 2^32

	static constexpr u32 logW = 8;  // 每次处理的位宽

	static constexpr u32 W = 1 << logW;  // 计数排序的值域宽度 2^8 = 256

	static constexpr u32 mask = W - 1;  // 用于键值计算的掩码，提取低 logW 位（255 = 0xFF）

	// 为计数排序分配临时输出空间
	u32ptr tmp = (u32ptr)calloc(last - first, sizeof(u32));

	// 定义栈节点类型：表示子数组范围和当前处理的位移
	using node = tuple<u32ptr, u32ptr, u32>;

	//排序的
	stack<node, vector<node>> s;

	// 初始将整个数组加入栈，位移为最高有效位起始
	s.push(make_tuple(first, last, maxlogW - logW));

	// 栈非空时继续处理
	while (!s.empty()) 
	{
		u32ptr begin, end;
		u32 shift;
		size_t length;

		// 从栈顶弹出当前处理的数组范围及位移
		tie(begin, end, shift) = s.top();

		length = end - begin;  // 子数组的长度

		//出栈
		s.pop();

		// 长度小于等于 1 的数组无需排序
		if (begin + 1 >= end) continue;

		// 计数排序：统计每个键值出现的次数

		u32 cnt[W] = {};  // 初始化计数数组

		//确定关键词
		auto key = [](const u32 x, const u32 shift) 
		{ 
			return (x >> shift) & mask; 
		};

		for (u32ptr it = begin; it != end; ++it) 
			++cnt[key(*it, shift)];

		for (u32 value = 1; value < W; ++value) 
			cnt[value] += cnt[value - 1];

		// 求完前缀和后，计算相同关键字的元素范围
		// 如果还有更低位需要处理，分割子数组并入栈
		if (shift >= logW) 
		{
			s.push(make_tuple(begin, begin + cnt[0], shift - logW));  // 第一段范围

			for (u32 value = 1; value < W; ++value)
			{
				s.push(make_tuple(begin + cnt[value - 1], begin + cnt[value], shift - logW)); // 其他范围
			}
		}

		// 将当前数组按照键值重新排列到临时空间，从后往前排放
		u32ptr it = end;
		do 
		{
			--it;
			--cnt[key(*it, shift)];
			tmp[cnt[key(*it, shift)]] = *it;
		} while (it != begin);

		// 将临时空间的内容复制回原数组
		copy(tmp, tmp + length, begin);
	}

	// 释放临时空间
	free(tmp);
}


using NTBS = char*;  // 定义 NTBS 类型为指向空终止字节字符串的指针
using NTBSptr = NTBS*;  // 定义 NTBSptr 类型为 NTBS 指针数组的指针

// 实现 MSD（Most Significant Digit）基数排序，适用于字符串数组
void MSD_radix_sort(NTBSptr first, NTBSptr last) 
{
	// 基数排序的值域宽度，ASCII 字符集最大值为 128
	static constexpr size_t W = 128;
	static constexpr size_t logW = 7;  // log_2(W)
	static constexpr size_t mask = W - 1;  // 用于键值计算的掩码

	// 为计数排序分配临时空间
	NTBSptr tmp = (NTBSptr)calloc(last - first, sizeof(NTBS));

	// 定义栈节点类型：表示子数组范围及当前处理的字符索引
	using node = tuple<NTBSptr, NTBSptr, size_t>;
	stack<node, vector<node>> s;

	// 初始将整个字符串数组加入栈，字符索引从 0 开始
	s.push(make_tuple(first, last, 0));

	// 栈非空时继续处理
	while (!s.empty()) 
	{
		NTBSptr begin, end;
		size_t index, length;

		// 从栈顶弹出当前处理的范围和字符索引
		tie(begin, end, index) = s.top();
		length = end - begin;
		s.pop();

		// 如果子数组长度小于等于 1，则无需排序
		if (begin + 1 >= end) continue;

		// 计数排序：统计每个字符出现的次数
		size_t cnt[W] = {};  // 初始化计数数组

		auto key = [](const NTBS str, const size_t index) 
		{
			return str[index];  // 获取字符串第 index 位字符
		};

		for (NTBSptr it = begin; it != end; ++it) ++cnt[key(*it, index)];

		for (size_t ch = 1; ch < W; ++ch) cnt[ch] += cnt[ch - 1];

		// 如果有更多字符需要排序，分割子数组并入栈
		for (size_t ch = 1; ch < W; ++ch)
		{
			s.push(make_tuple(begin + cnt[ch - 1], begin + cnt[ch], index + 1));
		}

		// 将当前字符串数组按照字符重新排列到临时空间
		NTBSptr it = end;
		do 
		{
			--it;
			--cnt[key(*it, index)];
			tmp[cnt[key(*it, index)]] = *it;
		} while (it != begin);

		// 将临时空间的内容复制回原字符串数组
		copy(tmp, tmp + length, begin);
	}

	// 释放临时空间
	free(tmp);
}



//LSD 基数排序
//从第 k 关键字到第 1 关键字顺序进行比较，就可以得到 LSD（Least Significant Digit first）基数排序，
//不使用递归就可以完成的排序算法。

//注意，当类里面有const参数时，类会删除默认重载等于运算符函数

// 定义元素类型，包含多个关键字
struct Element {
public:
	int key[100];  // 每个元素包含的关键字数组

	int K = 100;

	// 重载小于运算符，用于两个元素之间的比较
	bool operator<(const Element& y) const 
	{
		// 比较流程：按字典序比较多个关键字
		for (int i = 1; i <= K; ++i) {
			if (key[i] == y.key[i]) continue;  // 当前关键字相等，继续比较下一个
			return key[i] < y.key[i];         // 按关键字升序排序
		}
		return false;  // 如果所有关键字都相等，则认为两元素相等
	}

	
};

//构建一个类
class LSD_radix_Sort
{
public:
	const int N = 100010;  // 数组元素的最大数量
	const int W = 100010;  // 每个关键字的最大取值范围
	const int K = 100;     // 元素中关键字的最大数量

	int n;          // 当前数组中元素的数量
	int w[100010];       // 每个关键字的取值范围数组
	int k;          // 当前元素中关键字的数量
	int cnt[100010];     // 计数排序用的计数数组

	
	struct Element a[100010], b[100010];  // `a` 是原数组，`b` 是辅助数组，用于排序

	// 计数排序函数：对第 p 个关键字进行排序
	void counting_sort(int p) 
	{
		memset(cnt, 0, sizeof(cnt));  // 清空计数数组

		// 统计第 p 个关键字的出现次数
		for (int i = 1; i <= n; ++i) ++cnt[a[i].key[p]];

		// 计算前缀和：用于确定每个关键字对应的输出范围
		for (int i = 1; i <= w[p]; ++i) cnt[i] += cnt[i - 1];

		// 根据当前关键字，将元素稳定地存入辅助数组
		// 从后往前遍历，保证排序稳定性（相同关键字的元素保持原有相对顺序）
		for (int i = n; i >= 1; --i) b[cnt[a[i].key[p]]--] = a[i];

		// 将排序结果从辅助数组拷贝回原数组
		memcpy(a, b, sizeof(a));
	}

	// 基数排序函数：对所有关键字进行排序
	void radix_sort() 
	{
		// 从最高优先级关键字（第 k 个）开始，依次排序到最低优先级关键字（第 1 个）
		for (int i = k; i >= 1; --i) 
		{
			// 借助计数排序对当前关键字排序
			counting_sort(i);
		}
	}
};
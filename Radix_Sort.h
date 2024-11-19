#pragma once
#include<iostream>
#include<algorithm>
#include<cstdint>
#include<stack>
#include<tuple>
#include<vector>

//ǰ���������򷽷�,ѡ�񣬲��룬�������鲢���ǽ����ڹؼ��ֱȽϵĻ�����
//���ڱȼ۵������㷨ʱ�临�Ӷ�������O��n*log2n)
//��������������ݹؼ����и�λ��ֵ��ͨ���Դ������¼���������ˡ����䡱 �� ���ռ��� ��ʵ�������
//�����ڶ�ؼ��������˼��Ե��ؼ�������ķ���
//��������(RadixSorting)�ǵ��͵ķ���������


//��ʽ��������
// �����λ���ȷ������ӵ� k �ؼ��ֵ��� 1 �ؼ���˳����бȽ�


//��������,ֻ������Ԫ�ؼ�����һ����Χ������
template<class T=int>
void Counting_Sort(T* elem,int n)
{
	//�����ֵ����Сֵ
	T max = elem[0];
	T min = elem[0];

	for (int i = 0; i < n; i++)
	{
		if (elem[i] > max)max = elem[i];
		if (elem[i] < min)min = elem[i];
	}

	
	//Ԫ�ط�Χ
	int gap = max - min;

	//ͳ���������
	int* count_a = new int[gap + 1];


	//��ʼ��count_a
	for (int i = 0; i < gap + 1; i++)
		count_a[i] = 0;

	//����������Ҫ���������"-"
	for (int i = 0; i < n; i++)
		//���ݹؼ��ʼ���
		count_a[elem[i] - min]++;

	for (int i = 1; i < gap + 1; i++)
		//����Ԫ������λ��
		count_a[i] += count_a[i - 1];


	//��ʱ����
	T* sorted_a = new T[n];
	for (int i = n - 1; i >= 0; i--)
	{
		//������ظ�Ԫ����λ�ü�һ
		int idx = --count_a[elem[i] - min];

		sorted_a[idx] = elem[i];
	}

	//����
	for (int i = 0; i < n; i++)
	{
		elem[i] = sorted_a[i];
	}

	//�ͷſռ�
	delete[] sorted_a;
}

//�ֲ���������,����Ͱ���򣬵�������������Ԫ�ؼ��е�����
template<class T = int>
void Bucket_Sort(T* elem, int n)
{
	if (n <= 0)return;

	//�����ֵ����Сֵ
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
		//Ͱ�����鷶Χ
		size = (max - min) / n + 1;
	}

	if (n != 0)
	{
		//Ͱ��(����Ϊһ
		cnt = (max - min) / size + 1;
	}

	//����Ͱ
	std::vector<std::vector<T>> buckets(cnt);

	//����Ͱ��
	for (int i = 0; i < n; i++) {

		//�ж�Ԫ�����ĸ���Χ�������ĸ�Ͱ
		int idx = (elem[i] - min) / size;
		//��Ͱ
		buckets[idx].push_back(elem[i]);
	}

	//�ֱ����ùؼ��ʱȽ�����ÿ��Ͱ
	for (int i = 0; i < cnt; i++)
	{
		sort(buckets[i].begin(), buckets[i].end());
	}


	int index = 0;
	//���·���ԭ����
	for (int i = 0; i < cnt; i++)
	{
		for (int j = 0; j < buckets[i].size(); j++)
		{
			elem[index++] = buckets[i][j];
		}
	}

}

//MSD ��������,
//���� k - �ؼ���Ԫ�صıȽϷ����������뵽���ȱȽ�����Ԫ�صĵ� 1 �ؼ��֣��Ϳ���ȷ������Ԫ�ش��µĴ�С��ϵ��
//Ȼ��� ������ͬ�� 1 �ؼ��ֵ�Ԫ�أ��ٱȽ����ǵĵ� 2 �ؼ��֡����Դ����ơ�

using std::copy;  // �� <algorithm> ���� copy�����ڸ�������Ԫ��
using std::make_tuple;
using std::stack;
using std::tie;
using std::tuple;
using std::vector;

using u32 = uint32_t;  // �� uint32_t ����Ϊ u32
using u64 = uint64_t;  // �� uint64_t ����Ϊ u64
using u32ptr = u32*;   // ���� u32 ��ָ������

// ʵ�� MSD��Most Significant Digit����������,����Ȼ������������
void MSD_radix_sort(u32ptr first, u32ptr last) 
{
	static constexpr u32 maxlogW = 32;  // ����λ�����Ϊ 32 λ

	static constexpr u64 maxW = (u64)1 << maxlogW;  // ��ʾֵ������� 2^32

	static constexpr u32 logW = 8;  // ÿ�δ����λ��

	static constexpr u32 W = 1 << logW;  // ���������ֵ���� 2^8 = 256

	static constexpr u32 mask = W - 1;  // ���ڼ�ֵ��������룬��ȡ�� logW λ��255 = 0xFF��

	// Ϊ�������������ʱ����ռ�
	u32ptr tmp = (u32ptr)calloc(last - first, sizeof(u32));

	// ����ջ�ڵ����ͣ���ʾ�����鷶Χ�͵�ǰ�����λ��
	using node = tuple<u32ptr, u32ptr, u32>;

	//�����
	stack<node, vector<node>> s;

	// ��ʼ�������������ջ��λ��Ϊ�����Чλ��ʼ
	s.push(make_tuple(first, last, maxlogW - logW));

	// ջ�ǿ�ʱ��������
	while (!s.empty()) 
	{
		u32ptr begin, end;
		u32 shift;
		size_t length;

		// ��ջ��������ǰ��������鷶Χ��λ��
		tie(begin, end, shift) = s.top();

		length = end - begin;  // ������ĳ���

		//��ջ
		s.pop();

		// ����С�ڵ��� 1 ��������������
		if (begin + 1 >= end) continue;

		// ��������ͳ��ÿ����ֵ���ֵĴ���

		u32 cnt[W] = {};  // ��ʼ����������

		//ȷ���ؼ���
		auto key = [](const u32 x, const u32 shift) 
		{ 
			return (x >> shift) & mask; 
		};

		for (u32ptr it = begin; it != end; ++it) 
			++cnt[key(*it, shift)];

		for (u32 value = 1; value < W; ++value) 
			cnt[value] += cnt[value - 1];

		// ����ǰ׺�ͺ󣬼�����ͬ�ؼ��ֵ�Ԫ�ط�Χ
		// ������и���λ��Ҫ�����ָ������鲢��ջ
		if (shift >= logW) 
		{
			s.push(make_tuple(begin, begin + cnt[0], shift - logW));  // ��һ�η�Χ

			for (u32 value = 1; value < W; ++value)
			{
				s.push(make_tuple(begin + cnt[value - 1], begin + cnt[value], shift - logW)); // ������Χ
			}
		}

		// ����ǰ���鰴�ռ�ֵ�������е���ʱ�ռ䣬�Ӻ���ǰ�ŷ�
		u32ptr it = end;
		do 
		{
			--it;
			--cnt[key(*it, shift)];
			tmp[cnt[key(*it, shift)]] = *it;
		} while (it != begin);

		// ����ʱ�ռ�����ݸ��ƻ�ԭ����
		copy(tmp, tmp + length, begin);
	}

	// �ͷ���ʱ�ռ�
	free(tmp);
}


using NTBS = char*;  // ���� NTBS ����Ϊָ�����ֹ�ֽ��ַ�����ָ��
using NTBSptr = NTBS*;  // ���� NTBSptr ����Ϊ NTBS ָ�������ָ��

// ʵ�� MSD��Most Significant Digit�����������������ַ�������
void MSD_radix_sort(NTBSptr first, NTBSptr last) 
{
	// ���������ֵ���ȣ�ASCII �ַ������ֵΪ 128
	static constexpr size_t W = 128;
	static constexpr size_t logW = 7;  // log_2(W)
	static constexpr size_t mask = W - 1;  // ���ڼ�ֵ���������

	// Ϊ�������������ʱ�ռ�
	NTBSptr tmp = (NTBSptr)calloc(last - first, sizeof(NTBS));

	// ����ջ�ڵ����ͣ���ʾ�����鷶Χ����ǰ������ַ�����
	using node = tuple<NTBSptr, NTBSptr, size_t>;
	stack<node, vector<node>> s;

	// ��ʼ�������ַ����������ջ���ַ������� 0 ��ʼ
	s.push(make_tuple(first, last, 0));

	// ջ�ǿ�ʱ��������
	while (!s.empty()) 
	{
		NTBSptr begin, end;
		size_t index, length;

		// ��ջ��������ǰ����ķ�Χ���ַ�����
		tie(begin, end, index) = s.top();
		length = end - begin;
		s.pop();

		// ��������鳤��С�ڵ��� 1������������
		if (begin + 1 >= end) continue;

		// ��������ͳ��ÿ���ַ����ֵĴ���
		size_t cnt[W] = {};  // ��ʼ����������

		auto key = [](const NTBS str, const size_t index) 
		{
			return str[index];  // ��ȡ�ַ����� index λ�ַ�
		};

		for (NTBSptr it = begin; it != end; ++it) ++cnt[key(*it, index)];

		for (size_t ch = 1; ch < W; ++ch) cnt[ch] += cnt[ch - 1];

		// ����и����ַ���Ҫ���򣬷ָ������鲢��ջ
		for (size_t ch = 1; ch < W; ++ch)
		{
			s.push(make_tuple(begin + cnt[ch - 1], begin + cnt[ch], index + 1));
		}

		// ����ǰ�ַ������鰴���ַ��������е���ʱ�ռ�
		NTBSptr it = end;
		do 
		{
			--it;
			--cnt[key(*it, index)];
			tmp[cnt[key(*it, index)]] = *it;
		} while (it != begin);

		// ����ʱ�ռ�����ݸ��ƻ�ԭ�ַ�������
		copy(tmp, tmp + length, begin);
	}

	// �ͷ���ʱ�ռ�
	free(tmp);
}



//LSD ��������
//�ӵ� k �ؼ��ֵ��� 1 �ؼ���˳����бȽϣ��Ϳ��Եõ� LSD��Least Significant Digit first����������
//��ʹ�õݹ�Ϳ�����ɵ������㷨��

//ע�⣬����������const����ʱ�����ɾ��Ĭ�����ص������������

// ����Ԫ�����ͣ���������ؼ���
struct Element {
public:
	int key[100];  // ÿ��Ԫ�ذ����Ĺؼ�������

	int K = 100;

	// ����С�����������������Ԫ��֮��ıȽ�
	bool operator<(const Element& y) const 
	{
		// �Ƚ����̣����ֵ���Ƚ϶���ؼ���
		for (int i = 1; i <= K; ++i) {
			if (key[i] == y.key[i]) continue;  // ��ǰ�ؼ�����ȣ������Ƚ���һ��
			return key[i] < y.key[i];         // ���ؼ�����������
		}
		return false;  // ������йؼ��ֶ���ȣ�����Ϊ��Ԫ�����
	}

	
};

//����һ����
class LSD_radix_Sort
{
public:
	const int N = 100010;  // ����Ԫ�ص��������
	const int W = 100010;  // ÿ���ؼ��ֵ����ȡֵ��Χ
	const int K = 100;     // Ԫ���йؼ��ֵ��������

	int n;          // ��ǰ������Ԫ�ص�����
	int w[100010];       // ÿ���ؼ��ֵ�ȡֵ��Χ����
	int k;          // ��ǰԪ���йؼ��ֵ�����
	int cnt[100010];     // ���������õļ�������

	
	struct Element a[100010], b[100010];  // `a` ��ԭ���飬`b` �Ǹ������飬��������

	// �������������Ե� p ���ؼ��ֽ�������
	void counting_sort(int p) 
	{
		memset(cnt, 0, sizeof(cnt));  // ��ռ�������

		// ͳ�Ƶ� p ���ؼ��ֵĳ��ִ���
		for (int i = 1; i <= n; ++i) ++cnt[a[i].key[p]];

		// ����ǰ׺�ͣ�����ȷ��ÿ���ؼ��ֶ�Ӧ�������Χ
		for (int i = 1; i <= w[p]; ++i) cnt[i] += cnt[i - 1];

		// ���ݵ�ǰ�ؼ��֣���Ԫ���ȶ��ش��븨������
		// �Ӻ���ǰ��������֤�����ȶ��ԣ���ͬ�ؼ��ֵ�Ԫ�ر���ԭ�����˳��
		for (int i = n; i >= 1; --i) b[cnt[a[i].key[p]]--] = a[i];

		// ���������Ӹ������鿽����ԭ����
		memcpy(a, b, sizeof(a));
	}

	// �����������������йؼ��ֽ�������
	void radix_sort() 
	{
		// ��������ȼ��ؼ��֣��� k ������ʼ����������������ȼ��ؼ��֣��� 1 ����
		for (int i = k; i >= 1; --i) 
		{
			// ������������Ե�ǰ�ؼ�������
			counting_sort(i);
		}
	}
};
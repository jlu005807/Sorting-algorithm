#pragma once
#include<iostream>
#include<queue>

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
	T* sorted_a = new T[capcity];
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
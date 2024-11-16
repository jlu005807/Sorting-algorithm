//ѡ������
//ÿһ�˴Ӵ�����ļ�¼��ѡ���ؼ�����С�ļ�¼��
//��˳�����������ļ�¼���е����ֱ��ȫ������Ϊֹ��
//������ʵ�ּ�ѡ������Ͷ�����
//Ĭ��Ϊ����
//���� swap����������Ԫ�أ������Ĵ��ڣ�ѡ��������һ�ֲ��ȶ��������㷨��
#pragma once
#include<iostream>
#include<vector>

//��ѡ������ (SimpleSelection Sort)Ҳ����ֱ��ѡ������O(n^2)
//�ƶ���¼�������٣���ÿһ��¼ռ�õĿռ�϶�ʱ���˷�����ֱ�Ӳ�������졣
template<class T=int>
void Simple_Selection_Sort(T* a, int n)
{
	//�ҵ�n-1����Сֵ���Ѿ������ˣ�
	for (int i = 0; i < n - 1; i++)
	{
		//������λ��
		int ith = i;
		//�ҵ���δ�������Сֵ,ѡ��������Դ������������Ч��
		for (int j = i + 1; j < n; j++)
		{
			if (a[j] < a[ith])ith = j;
		}
		//����
		std::swap(a[ith], a[i]);
	}
}

//vector�汾
template<class T = int>
void Simple_Selection_Sort(std::vector<T> a)
{
	int n = a.size();
	Simple_Selection_Sort(a.data(), n);
}


//������Ӣ�Heapsort��
//���� ����� �������ݽṹ����Ƶ�һ�������㷨
//������ı����ǽ����ڶ��ϵ�ѡ������
//����˵�ǽ�������ļ�¼a[l..n]������һ����ȫ��������˳��洢�ṹ


//���Ƚ����󶥶�,С������ɸ,�������ϸ�
template<class T=int>
void sift_down(T* a, int start, int end)
{
	//���ڵ�
	int parent = start;

	//�ӽڵ㣬��Ϊ���㿪ʼ�������ӽڵ�Ϊparent*2+1��parent*2+2����ȫ����������
	int child = parent * 2 + 1;

	//����child,���ӽڵ���������[start,end]�ڣ���ȫ���������ʣ�
	while (child <= end)
	{
		//�Ƚ������ӽڵ㣨������ڣ���ȡ��ֵ�븸�ڵ㽻����ʹ���ڵ���������ӽڵ㣬�γɴ����
		if (child + 1 <= end && a[child] < a[child + 1])child++;

		//�Ѿ��Ǵ����
		if (a[child] <= a[parent])
		{
			return;
		}
		else
		{
			std::swap(a[parent], a[child]);
			//���µ���
			parent = child;
			child = parent * 2 + 1;
		}
	}
}


//����Ϊ����������ʵ��
template<class T=int>
void Heap_Sort(T* a, int n)
{
	if (n <= 1)return;

	//�����һ���ڵ�ĸ��ڵ���ɶѻ�����Ϊ������㿪ʼ���������һ���ڵ�Ϊn-1-1
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		sift_down(a, i, n - 1);
	}

	//�����
	//����һ��Ԫ�غ��������ǰһλ�������������µ�����
	//���������ϣ�С�����£��������ҵ���һ��Ҫ����Ĵ���
	for (int i = n - 1; i > 0; i--)
	{
		//iΪҪ������λ�ã�����n-i�����
		std::swap(a[0], a[i]);

		//���µ��������ǽ������䲻����������ֵ
		sift_down(a, 0, i - 1);
	}
}

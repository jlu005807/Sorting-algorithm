#pragma once
#include<iostream>
#include<vector>
#include<algorithm>

//��������,��������Ԫ�ػ���Ϊ�������򡹺͡�δ���������֣�
//ÿ�δӡ�δ����ġ�Ԫ����ѡ��һ��,����ؼ��ֵĴ�С����뵽��������ġ�Ԫ���е���ȷλ�á�
//Ĭ��T���������رȽ��������������<�������
//Ĭ��Ϊ����


//ֱ�Ӳ�������O(n^2)
//�ȶ�����,���ʺ��ڳ�ʼ��¼�����������򣩵����
//Ҳ����ǧ��ʽ�洢�ṹ��ֻ���ڵ������������ƶ���¼��ֻ���޸���Ӧ��ָ��
template<class T=int>
void Straight_Insertion_Sort(T a[], int n)
{
	//��˳���L��ֱ�Ӳ�������
	//�����0��ʼ�������Ԫ���Ѿ�����,���Դ�1��ʼ����
	for (int i = 1; i < n; i++)
	{
		//��¼Ҫ�����Ԫ��
		T key = a[i];
		
		//��i-1λ����ǰ��λ��,ͬʱ����Ԫ��
		int j = i - 1;
		while (j >= 0 && key < a[j])
		{
			//����
			a[j + 1] = a[j];
			j--;
		}

		//����
		a[j + 1] = key;
	}
}

//vector
template<class T = int>
void Straight_Insertion_Sort(std::vector<T>& a)
{
	size_t n = a.size();
	//��˳���L��ֱ�Ӳ�������
	//������㿪ʼ�������Ԫ���Ѿ�����
	for (int i = 1; i < n; i++)
	{
		//��¼Ҫ�����Ԫ��
		T key = a[i];

		//��i-1λ����ǰ��λ��,ͬʱ����Ԫ��
		int j = i - 1;
		while (j >= 0 && key < a[j])
		{
			//����
			a[j + 1] = a[j];
			j--;
		}

		//����
		a[j + 1] = key;
	}
}

//�۰��������O(n^2)
//���Ѿ������������������ö��ֲ��ң�����ҵ�����λ�õ�Ч��
//�ȶ�����,�ʺϳ�ʼ��¼����n�ϴ�ʱ�������
//ֻ������˳��ṹ
template<class T = int>
void Binary_Insertion_Sort(T a[], int n)
{
	//��˳���L���۰��������
	for (int i = 1; i < n; i++)
	{
		//��¼Ҫ�����Ԫ��
		T key = a[i];

		//���ֲ���λ��,��[0,i-1]��
		int low = 0;
		int high = i - 1;
		while (low <= high)
		{
			//�۰�
			int mid = (low + high) / 2;
			//������������
			if (key < a[mid])high = mid - 1;
			else low = mid + 1;
		}

		//�ҵ�����λ�ã�Ϊhigh+1
		
		//����Ԫ��,high+1����Ϊlow
		for (int j = i - 1; j >= high + 1; j--)a[j + 1] = a[j];

		//����
		a[high + 1] = key;
	}
}

//vector
template<class T = int>
void Binary_Insertion_Sort(std::vector<T>& a)
{
	size_t n = a.size();
	//��˳���L���۰��������
	for (int i = 1; i < n; i++)
	{
		//��¼Ҫ�����Ԫ��
		T key = a[i];

		//���ֲ���λ��,��[0,i-1]��
		int low = 0;
		int high = i - 1;
		while (low <= high)
		{
			//�۰�
			int mid = (low + high) / 2;
			//������������
			if (key < a[mid])high = mid - 1;
			else low = mid + 1;
		}

		//�ҵ�����λ�ã�Ϊhigh+1

		//����Ԫ��,high+1����Ϊlow
		for (int j = i - 1; j >= high + 1; j--)a[j + 1] = a[j];

		//����
		a[high + 1] = key;
	}
}

//ϣ������Ӣ�Shell sort����O(n*(log(n))^2)��ƽ��ʱ�临�ӶȺ��ʱ�临�Ӷ��������е�ѡȡ�й�
//Ҳ��Ϊ��С��������,�ǲ��������һ�ָĽ��汾

//���÷������,�������¼���зָ�ɼ��飬��ÿ��ֱ����ֱ�Ӳ�������Ȼ������ÿ��������������·���,ֱ����������Ϊ1
//ϣ���Լ�¼�ķ��飬���Ǽ򵥵� ����ηָ�����ǽ����ĳ�� �������� �ļ�¼�ֳ�һ�顣

//���岽��
//�����������з�Ϊ���������У�ÿ�������е�Ԫ����ԭʼ�����м����ͬ��
//����Щ�����н��в�������
//��Сÿ����������Ԫ��֮��ļ�࣬�ظ���������ֱ��������Ϊ1��

//��¼��Ծʽ���ƶ��������򷽷��ǲ��ȶ��ģ�ֻ����ǧ˳��ṹ
//nԽ��ʱ��Ч��Խ���ԡ������ʺϳ�ʼ��¼����n�ϴ�ʱ�����


//C���԰�
template<class T>
void Shellinsert_C(T a[], int n,int dk)
{
	int d = dk;//�˴�����
	//��������
	for (int i = d; i < n; i++)
	{
		int j;
		if (a[i] < a[i - d])
		{
			//��������
			int key = a[i];

			//����
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
	//dk[]��������ɺõ���������
	//�ж�����������
	//ϣ���������У�2^k - 1��
	//Hibbard�������У�1, 3, 7, 15, ...��
	//Sedgewick�������У�1, 5, 19, 41, ...��

	for (int i = 0; i < t; i++)
	{
		Shellinsert_C(a, n, a[i]);
	}
}


//c++��
template<class T>
void ShellSort(T a[], int n)
{
	//��ʼ����� h��ʹ�� Knuth ���м���ʹ��С�����鳤�ȵ����ֵ
	int h = 1;

	//�����������
	while (h < n / 3)
	{
		h = 3 * h + 1;
	}

	//����ϣ�������𽥼��ټ�� h��ֱ�� h ��С�� 1�����һ�α�����
	while (h >= 1)
	{
		//��ÿһ�����Ϊ h ����������в�������
		for (int i = h; i < n; i++)
		{
			//�� a[i] ���뵽���Ӧ���������е���ȷλ��
			for (int j = i; j >= h && a[i] < a[j - h]; j -= h)
			{
				std::swap(a[j], a[j - h]);//���ƺ���
			}
		}
		// ��С�����ʹ h �𽥼�С�����ձ�Ϊ 1
		h = h / 3;
	}
}

//c++��
template<class T>
void ShellSort(std::vector<T>& a)
{
	size_t n = a.size();
	//��ʼ����� h��ʹ�� Knuth ���м���ʹ��С�����鳤�ȵ����ֵ
	size_t h = 1;

	//�����������
	while (h < n / 3)
	{
		h = 3 * h + 1;
	}

	//����ϣ�������𽥼��ټ�� h��ֱ�� h ��С�� 1�����һ�α�����
	while (h >= 1)
	{
		//��ÿһ�����Ϊ h ����������в�������
		for (size_t i = h; i < n; i++)
		{
			//�� a[i] ���뵽���Ӧ���������е���ȷλ��
			for (size_t j = i; j >= h && a[j] < a[j - h]; j -= h)
			{
				std::swap(a[j], a[j - h]);//���ƺ���
			}
		}
		// ��С�����ʹ h �𽥼�С�����ձ�Ϊ 1
		h = h / 3;
	}
}


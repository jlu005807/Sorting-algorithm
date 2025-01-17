#pragma once
#include<iostream>
#include<random>
#include<vector>
#include"Selection_Sort.h"//ʵ����ʡ����

//��������Ļ���˼���ǣ������Ƚϴ������¼�Ĺؼ��֣�
//һ������������¼���������Ҫ��ʱ����н�����ֱ����������ȫ������Ҫ��Ϊֹ��
//Ĭ������


//ð������O(n^2)
//�����Ƚ����ڼ�¼�Ĺؼ��֣����������������н���
//�ȶ�����,��������ʽ�洢�ṹ
//����ʼ��¼����n�ϴ�ʱ
template<class T=int>
void Bubble_Sort(T a[], int n)
{
	//���ý�����ʶ,��ʼʱ�����н���
	bool flag = true;

	//ֻҪһ�����������н����ͼ���
	while (flag)
	{
		//�����޽���
		flag = false;

		//����������
		for (int i = 0; i < n - 1; i++)
		{
			//�������򽻻�
			if (a[i] > a[i + 1])
			{
				std::swap(a[i], a[i + 1]);
				//���ñ�ʶ
				flag = true;
			}
		}
	}
}

//ð������ĸĽ�
//һ�˱Ƚ��У����ȽϽ��������ִ�ĳ��λ��t��ʼ���ٽ�������˵��t���Ժ�ļ�¼����
//�Ӷ���һ�˱ȽϽ��е�t����
template<class T = int>
void Bubble_Sort_modify(T a[], int n)
{
	if (n <= 1)return;

	//ֹͣ��ʶ
	int stop = n-1;
	while (stop!=0)
	{
		//һ��ð�������¼���������λ�ã�-1��ʾ�޼�¼����
		int t = 0;
		for (int i = 0; i < stop; i++)
		{
			if (a[i + 1] < a[i])
			{
				//��������¼����λ��
				std::swap(a[i], a[i + 1]);
				t = i;
			}
		}

		stop = t;
	}
}
//˫��ð�������ϸ����³��������
template<class T=int>
void Double_Bubble_Sort(T* a, int n)
{
	//�ϸ����³�������
	int left = 0;
	int right = n - 1;

	bool swapped = true;

	while(left <= right && swapped)
	{
		swapped = false;

		//�ϸ�������������
		for (int i = left; i < right; i++)
		{
			if (a[i + 1] < a[i])
			{
				std::swap(a[i], a[i + 1]);
				swapped = true;
				right = i;
			}
		}

		//�³���С������
		for (int i = right; i > left; i--)
		{
			if (a[i] < a[i - 1])
			{
				std::swap(a[i], a[i - 1]);
				swapped = true;
				left = i;
			}
		}
	}
}


//��������(QuickSort) ����ð������Ľ����õģ�ƽ��O(nlogn)
//��������Ĺ���ԭ����ͨ�� ���� �ķ�ʽ����һ����������
//�������򷽷��е�һ�ν������������������

//��ε�������ݽṹ����׼�ָ��
template<class T=int>
void Quick_Sort_C(T a[], int left, int right)
{
	int low = left;
	int high = right;

	//�˳��ݹ�
	if (low >= high)return;

	//����ѡ���һ����Ϊ��׵
	T pivot = a[low];

	//��������ָ��
	while (low < high)
	{
		//��ָ������ֱ��С�ڻ�׼
		while (low < high && a[high] >= pivot)
			--high;

		//����
		a[low] = a[high];

		//��ָ������ֱ�����ڻ�׼
		while (low < high && a[low] <= pivot)
			++low;

		//����
		a[high] = a[low];
	}

	//�Żػ�׼ֵ����ʱlow��high�غϣ���ߵ�Ԫ��С�ڻ�׼���ұߵ�Ԫ�ش��ڻ�׼
	a[low] = pivot;

	//����������
	Quick_Sort_C(a, left, low - 1);

	//����������
	Quick_Sort_C(a, low + 1, right);
}

template<class T = int>
void Quick_Sort_C(std::vector<T>& a, int left, int right)
{
	int low = left;
	int high = right;

	//�˳��ݹ�
	if (low >= high)return;

	//����ѡ���һ����Ϊ��׵
	T pivot = a[low];

	//��������ָ��
	while (low < high)
	{
		//��ָ������ֱ��С�ڻ�׼
		while (low < high && a[high] >= pivot)
			--high;

		//����
		a[low] = a[high];

		//��ָ������ֱ�����ڻ�׼
		while (low < high && a[low] <= pivot)
			++low;

		//����
		a[high] = a[low];
	}

	//�Żػ�׼ֵ����ʱlow��high�غϣ���ߵ�Ԫ��С�ڻ�׼���ұߵ�Ԫ�ش��ڻ�׼
	a[low] = pivot;

	//����������
	Quick_Sort(a, left, low - 1);

	//����������
	Quick_Sort(a, low + 1, right);
}

//������������������
//���ڿ���������������������ж������
//�����������ö�̬
template<class T>
class QuickSort
{
public:
	//��ͬ������Sort��һ�������������䷽����ͬ������˵��������ͬ���Էֿ�ʵ��
	virtual int Partion(T array[], int left, int right) = 0;

	//���ж���������ͬһ��ʵ��,�ݹ�ʵ��
	void Sort(T array[], int left, int right)
	{
		//�˳��ݹ�����
		if (left >= right)return;


		int idxkey = Partion(array, left, right);

		//��������������
		Sort(array, left, idxkey - 1);

		//����������
		Sort(array, idxkey + 1, right);

	}

	//���ж���������ͬһ��ʵ��,�ǵݹ�ʵ��
	//һ��ջ��������Ҫ�������������,
	//���ĳ���������Ԫ���������ڵ���1������Ҫ��ջ����
	void SortNoR(T a[], int left, int right)
	{
		//����ջ������ұ߽�
		std::vector<std::pair<int, int>> stack;

		//��ſ�ʼ���ұ߽�
		stack.push_back({ left,right });

		//��ջ����
		while (!stack.empty())
		{
			//ȡ�����ұ߽�
			auto p = stack.back();
			stack.pop_back();
			
			////ʹ��һ�ε��˵Ŀ��ŵõ���һ�εĻ�׼ֵ
			int key = Partion(a, left, right);

			//����׼ֵ�����ұ߽���ջ
			if (key + 1 < right)
			{
				//�ұ�
				stack.push_back({ key + 1,right});
			}
			if (left < key - 1)
			{
				//���
				stack.push_back({ left,key - 1 });
			}
		}
	}




	//ѡ���׼��һ��ѡ��һ���������һ��������������鱾������ᵼ��Ч�ʵ�
	//��������ȡ�У���ѡȡ��һ�������һ���Լ��м��Ԫ���е���λ�����������ȡ�����Լ���λ���е���λ��
	//����Ϊȡ��׼�ķ����������Ż���������
	//����ȡ��
	int getmid(T array[], int left, int right)
	{
		//��ȡ�м�ֵ�±�
		int mid = left + (right - left) / 2;

		//��left<mid
		if (array[left] < array[mid])
		{
			//���mid<right
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
			//���mid>right
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

	//�����
	int getrandom(T array[], int left, int right)
	{
		std::random_device rd;   // ��ȡ����豸
		std::mt19937 gen(rd());  // ʹ�� Mersenne Twister �����������

		std::uniform_int_distribution<> size_dis(left, right);

		return size_dis;

	}

	//vector
	int getrandom(std::vector<T> array, int left, int right)
	{
		return getrandom(array.data(), left, right);
	}

	//��λ���е���λ��
	//���㷨���������£����������л���Ϊn/5�飬ÿ��Ԫ���������� 5 ����
	//Ѱ��ÿ��Ԫ�ص���λ������ΪԪ�ظ������٣�����ֱ��ʹ�� �������� ���㷨����
	//�ҳ���n/5��Ԫ����λ���е���λ��������Ԫ����Ϊǰ���㷨��ÿ�λ���ʱ�ķֽ�ֵ���ɡ�
	//������ʵ��

};

//������ֱ�ʵ�ֲ�ͬ��������
//ǰ��ָ�뷨
//����������ȡ�н�������ѡȡ����ĵ�һ��Ԫ����Ϊ��׼��key
template<class T>
class FroandBack :public QuickSort<T>
{
	//������������ķֽ紦���˴�����Ϊ���ұ����伴[left,right]
	int Partion(T array[], int left, int right)
	{
		//��������
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

		int idxkey = left;//��ǰ�����׼λ��

		while (cur <= right)
		{
			//��cur�ҵ��Ȼ�׼ֵС��ֵ��cur��prev++λ�õ�ֵ����
			if(array[cur] <= array[idxkey] && ++prev != cur)
			{
				swap(cur, prev);
			}

			//��ǰָ�����
			++cur;
		}

		//���curԽ�磨ʶ�������е����ݣ�������prev�ͻ�׼λ�õ�ֵ
		swap(prev, idxkey);

		//�����»�׼λ��
		idxkey = prev;

		return idxkey;
	}
};


//��������
template<class T>
class Hoare :public QuickSort<T>
{
	int Partion(T array[], int left, int right)
	{
		//������ȡ�з��õ�key��λ��
		int key = QuickSort<T>::getmid(array, left, right);
		std::swap(array[key], array[left]);

		//��ǰ�����׼λ��
		int idxkey = left;

		//��������
		auto swap = [array](int left, int right)->void
		{
			T temp = array[left];
			array[left] = array[right];
			array[right] = temp;
			return;
		};

		while (left < right)
		{
			//�ұ������ҽ�Сֵ
			while (left < right && array[right] >= array[idxkey])
				--right;

			//��������ҽϴ�ֵ
			while (left < right && array[left] <= array[idxkey])
				++left;

			//����
			swap(left, right);
		}

		//left��right����������
		swap(left, idxkey);

		//�»�׼λ��
		idxkey = left;

		return idxkey;//���ػ�׼λ��

		// ������������֮�� 
		// key λ����ߵĲ��ֶ��� keyiλ�õ�ֵҪС��
		// key λ���ұߵĲ��ֶ��� keyiλ�õ�ֵҪ��
	}
};

template<class T>
class Hole : public QuickSort<T>
{
	int Partion(T* array, int left, int right)//������Hoare
	{
		//������ȡ�з��õ�key��λ��
		int idxkey = QuickSort<T>::getmid(array, left, right);
		std::swap(array[idxkey], array[left]);

		T key = array[left];//�����׼ֵ
		int hole = left;//��һ����

		while (left < right)
		{
			//�ұ������ҽ�Сֵ
			while (left < right && array[right] >= key)
			{
				--right;
			}

			array[hole] = array[right];//���
			hole = right;//�¿�

			//��������ҽϴ�ֵ
			while (left < right && array[left] <= key)
			{
				++left;
			}

			array[hole] = array[left];
			hole = left;
		}

		//�����һ�������������һ����Ϊ�»�׼
		array[hole] = key; 
		return hole;

	}
};


//����Ϊ����Ŀ�������
//������������������


//��·���ַ�
//Ϊ�˽���������д��ڴ����ظ�Ԫ��ʱ��
// ��ͳ�Ŀ��������㷨�ᵼ�²���Ҫ�ıȽϺͽ������������д��ڴ����ظ�Ԫ������
//С��˦����ߣ����˦���ұ�
//�� key ֵ��ȵ�ֵ�Ƶ��м�
//[ begin , left-1 ] [ left , right ] [ right + 1 , end ]

// ģ��� T ������ʾԪ�ص����ͣ���������Ҫ����С�ڣ�<������
template<class T=int>
void Quick_Sort_Threeroad(T a[], const int n)
{
	if (n <= 1)return;

	//�����ȡ��׼
	const T pivot = a[rand() % n];

	// i����ǰ������Ԫ���±�
	int i = 0;
	// arr[0, left)���洢С�� pivot ��Ԫ��
	int left = 0;
	// arr[right, len)���洢���� pivot ��Ԫ��
	int right = n;

	// ���һ����·���ţ������з�Ϊ��
    // С�� pivot ��Ԫ�� | ���� pivot ��Ԫ�� | ���� pivot ��Ԫ��
	while (i < right )//��ǰ����
	{
		// С�ڻ�׼��Ԫ�ؽ��������ͬʱǰ��i
		if (a[i] < pivot)
		{
			std::swap(a[i++], a[left++]);
		}
		// ���ڻ�׼��Ԫ�ؽ������ұ�ͬʱǰ��i
		else if (pivot<a[i])
		{
			//�½���������Ԫ�ؿ��ܻ��Ǵ��ڻ�׼�ģ�������ǲ������� i ������ǰ������
			std::swap(a[i], a[--right]);
		}
		// ��ȵ�Ԫ��ֱ��������������ֻ��ǰ��i
		else i++;
	}

	Quick_Sort_Threeroad(a, left);

	Quick_Sort_Threeroad(a + right, n - right);

}

//С������취
//��������Ĵ�С�㹻Сʱ�����Կ���ʹ�ò�������������ݹ����
//ͨ������һ����ֵ�������Ƿ�ʹ�ò�������

//ʵ�ֲ�������
template<class T = int>
void Insertion_Sort(T* a, int n)
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

template<class T=int>
void Quick_Insert_Sort(T *a, int n)
{
	if (n <= 1)return;

	//������·����
	//�����ȡ��׼
	const T pivot = a[rand() % n];

	// i����ǰ������Ԫ���±�
	int i = 0;
	// arr[0, left)���洢С�� pivot ��Ԫ��
	int left = 0;
	// arr[right, len)���洢���� pivot ��Ԫ��
	int right = n;

	// ���һ����·���ţ������з�Ϊ��
	// С�� pivot ��Ԫ�� | ���� pivot ��Ԫ�� | ���� pivot ��Ԫ��
	while (i < right)//��ǰ����
	{
		// С�ڻ�׼��Ԫ�ؽ��������ͬʱǰ��i
		if (a[i] < pivot)
		{
			std::swap(a[i++], a[left++]);
		}
		// ���ڻ�׼��Ԫ�ؽ������ұ�ͬʱǰ��i
		else if (pivot < a[i])
		{
			//�½���������Ԫ�ؿ��ܻ��Ǵ��ڻ�׼�ģ�������ǲ������� i ������ǰ������
			std::swap(a[i], a[--right]);
		}
		// ��ȵ�Ԫ��ֱ��������������ֻ��ǰ��i
		else i++;
	}

	//����բֵΪ10
	//����:: С�����Ż� ��Ϊ����������С�����ϵ����������ȿ���������á�
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



//��ʡ����
//��ʡ����Ӣ�Introsort �� Introspective sort���ǿ�������� ������ �Ľ��
//��ʡ���򽫿�����������ݹ��������Ϊ[log2_n]����������ʱ��ת��Ϊ������
//�����ȱ����˿��������ڴ���ʵľֲ��ԣ��ֿ��Է�ֹ����������ĳЩ����������˻�Ϊ O(n^2)��
//����������ĳЩ����������˻�Ϊ O(n^2)�ֳ�Ϊ����������������


template<class T = int>
void Introspective_Sort(T* a, int n,int deep)
{
	if (n <= 1)return;

	//�жϿ��������Ƿ��������壬������ֵΪ2logn
	if (deep >= 2 * log2(n))
	{
		Heap_Sort(a,n);
		return;
	}

	//������·����
	//�����ȡ��׼
	const T pivot = a[rand() % n];

	// i����ǰ������Ԫ���±�
	int i = 0;
	// arr[0, left)���洢С�� pivot ��Ԫ��
	int left = 0;
	// arr[right, len)���洢���� pivot ��Ԫ��
	int right = n;

	// ���һ����·���ţ������з�Ϊ��
	// С�� pivot ��Ԫ�� | ���� pivot ��Ԫ�� | ���� pivot ��Ԫ��
	while (i < right)//��ǰ����
	{
		// С�ڻ�׼��Ԫ�ؽ��������ͬʱǰ��i
		if (a[i] < pivot)
		{
			std::swap(a[i++], a[left++]);
		}
		// ���ڻ�׼��Ԫ�ؽ������ұ�ͬʱǰ��i
		else if (pivot < a[i])
		{
			//�½���������Ԫ�ؿ��ܻ��Ǵ��ڻ�׼�ģ�������ǲ������� i ������ǰ������
			std::swap(a[i], a[--right]);
		}
		// ��ȵ�Ԫ��ֱ��������������ֻ��ǰ��i
		else i++;
	}

	Introspective_Sort(a, left,deep+1);

	Introspective_Sort(a + right, n - right,deep+1);

	return;
}
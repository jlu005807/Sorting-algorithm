#pragma once
#include<iostream>
#include<random>
#include<vector>

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
			if (a[i] < a[i + 1])
			{
				std::swap(a[i], a[i + 1]);
				//���ñ�ʶ
				flag = true;
			}
		}
	}
}

template<class T = int>
void Bubble_Sort(std::vector<T> a)
{
	size_t n=a.size()
	//���ý�����ʶ,��ʼʱ�����н���
	bool flag = true;

	//ֻҪһ�����������н����ͼ���
	while (flag)
	{
		//�����޽���
		flag = false;

		//����������
		for (size_t i = 0; i < n - 1; i++)
		{
			//�������򽻻�
			if (a[i] < a[i + 1])
			{
				std::swap(a[i], a[i + 1]);
				//���ñ�ʶ
				flag = true;
			}
		}
	}
}

//��������(QuickSort) ����ð������Ľ����õģ�ƽ��O(nlogn)
//��������Ĺ���ԭ����ͨ�� ���� �ķ�ʽ����һ����������
//�������򷽷��е�һ�ν������������������

//��ε�������ݽṹ����׼�ָ��
template<class T=int>
void Quick_Sort(T a[], int left, int right)
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

template<class T = int>
void Quick_Sort(std::vector<T>& a, int left, int right)
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


		int idxkey = Sort(array, left, right);

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
			int key = Partion(a, begin, end);

			//����׼ֵ�����ұ߽���ջ
			if (key + 1 < end)
			{
				//�ұ�
				stack.push_back({ key + 1,right});
			}
			if (begin < key - 1)
			{
				//���
				stack.push_back({ left,key - 1 });
			}
		}
	}




	//ѡ���׼��һ��ѡ��һ���������һ��������������鱾������ᵼ��Ч�ʵ�
	//��������ȡ�У���ѡȡ��һ�������һ���Լ��м��Ԫ���е���λ�����������ȡ��
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
		std::random_device rd;   // ��ȡ����豸
		std::mt19937 gen(rd());  // ʹ�� Mersenne Twister �����������

		std::uniform_int_distribution<> size_dis(left, right);

		return size_dis;

	}

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

		int idxkey = getmid(array, left, right);
		std::swap(array[idxkey], array[left]);

		int idxkey = left;//��ǰ�����׼λ��

		while (cur <= right)
		{
			//��cur�ҵ��Ȼ�׼ֵС��ֵ��cur��prev++λ�õ�ֵ����
			if(array[cur] < array[idxkey] && ++prev != cur)
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
		int idxkey = getmid(array, left, right);
		std::swap(array[idxkey], array[left]);

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
		int idxkey = getmid(array, left, right);
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

		array[hole] = key; //���һ����Ϊ�»�׼
		return hole;

	}
};


//����Ϊ����Ŀ�������
//������������������
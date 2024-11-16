#pragma once
//�龮����(Merging Sort),O(n*logn)
//���������������ϵ������ϲ���һ�������Ĺ���
//���ڷ���˼�뽫����ֶ������ϲ�


//�鲢��������ĵĲ����Ǻϲ���merge�����̣�
//��������������� a[i] �� b[j] �ϲ�Ϊһ���������� c[k]��
template<class T=int>
void merge(const T* a, size_t alen, const T* b, size_t blen, T* c)
{
	//��������Ĺ���ָ��
	size_t i = 0, j = 0, k = 0;

	//�����Ƚ�
	while (i < alen && j < blen)
	{
		//���ж� b[j] < a[i]����֤�ȶ���
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
		//����c�Ĺ���ָ��
		++k;
	}

	// ��ʱһ�������ѿգ���һ������ǿգ����ǿյ����鲢�� c ��
	for (; i < alen; ++i, ++k) c[k] = a[i];
	for (; j < blen; ++j, ++k) c[k] = b[j];

}

//pointer-style merge
template<class T = int>
void merge(const T* a, const T* a_end, const T* b, const T* b_end, T* c)
{
	//��������Ĺ���ָ��
	size_t i = 0, j = 0, k = 0;

	int alen = a_end - a;
	int blen = b_end - b;

	//�����Ƚ�
	while (i < alen && j < blen)
	{
		//���ж� b[j] < a[i]����֤�ȶ���
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
		//����c�Ĺ���ָ��
		++k;
	}

	// ��ʱһ�������ѿգ���һ������ǿգ����ǿյ����鲢�� c ��
	for (; i < alen; ++i, ++k) c[k] = a[i];
	for (; j < blen; ++j, ++k) c[k] = b[j];
}

//ע������Ĵ�������ʾ������ֱ��� [l, r)��[l, mid)��[mid, r)��
//���η�ʵ�ֹ鲢����
template<class T=int>
void Merge_Sort(T* a, int l, int r)
{
	//�����鳤��Ϊ 1 ʱ����������Ѿ�������ģ������ٷֽ�
	if (r - l <= 1)return;

	//�����鳤�ȴ��� 1 ʱ��������ܿ��ܲ�������ġ���ʱ���������Ϊ����
	int mid = l + ((r - l) >> 1);

	//������������
	Merge_Sort(a, l, mid);
	Merge_Sort(a, mid , r);

	//������ʱ����
	T* temp = new T[r - l];

	//�ϲ�
	merge(a + l, a + mid, a + mid, a + r, temp);

	//����
	for (int i = 0; i < r - l; i++)
	{
		a[i + l] = temp[i];
	}

	//�ͷſռ�
	delete[] temp;
}

//������ʵ�ַǵݹ�Ĺ鲢����
template<class T=int>
void Merge_sort(T* a, size_t n)
{
	//��ʱ����
	T* temp = new T[n];

	//seg��ʾҪ�ϲ��ĶεĴ�С��ÿ�η���
	for (size_t seg = 1; seg < n; seg <<= 1)
	{
		//�� left1 ��ʼ���������Ϊ���� [left1, right1) �� [left2, right2)��
		//ÿ�β���Ϊ seg + seg�������������εĳ��ȡ�
		for (size_t left1 = 0; left1 < n - seg; left1 += seg + seg)
		{
			size_t right1 = left1 + seg;
			size_t left2 = right1;

			//ʹ�� std::min ȷ���ڶ��ε��ұ߽粻�ᳬ�����鳤�� n���������һ�Σ���
			size_t right2 = std::min(left2 + seg, n);

			//�ϲ�
			merge(a + left1, a + right1, a + left2, a + right2, temp + left1);

			//����
			for (size_t i = left1; i < right2; ++i) a[i] = temp[i];
		}

	}

	//�ͷſռ�
	delete[] temp;
}
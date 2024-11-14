//�����㷨��Ӣ�Sorting algorithm����һ�ֽ�һ���ض������ݰ�ĳ��˳��������е��㷨��
//�����㷨���ֶ���������Ҳ��಻ͬ��

//�ȶ���
//�ȶ�����ָ��ȵ�Ԫ�ؾ�������֮�����˳���Ƿ����˸ı䡣
//�������򡢼������򡢲�������ð�����򡢹鲢�������ȶ�����
//ѡ�����򡢶����򡢿�������ϣ���������ȶ�����

#include"Insertion_sort.h"
#include"random_array.h"

void Test_InsertSort()
{
	random_array m_random;

	std::vector<int> arr = m_random.generateRandomArray();
	std::cout << "Original array: ";
	m_random.printArray(arr);


    // �����������
    std::vector<int> arr1 = arr;
    Straight_Insertion_Sort(arr1);
    std::cout << "Sorted by Straight Insertion Sort: ";
    m_random.printArray(arr1);

    std::vector<int> arr2 = arr;
    Binary_Insertion_Sort(arr2);
    std::cout << "Sorted by Binary Insertion Sort:   ";
    m_random.printArray(arr2);

    std::vector<int> arr3 = arr;
    ShellSort(arr3);
    std::cout << "Sorted by Shell Sort:              ";
    m_random.printArray(arr3);
}


int main()
{
    Test_InsertSort();

    system("Pause");
}
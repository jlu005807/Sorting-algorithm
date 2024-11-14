//排序算法（英语：Sorting algorithm）是一种将一组特定的数据按某种顺序进行排列的算法。
//排序算法多种多样，性质也大多不同。

//稳定性
//稳定性是指相等的元素经过排序之后相对顺序是否发生了改变。
//基数排序、计数排序、插入排序、冒泡排序、归并排序是稳定排序。
//选择排序、堆排序、快速排序、希尔排序不是稳定排序。

#include"Insertion_sort.h"
#include"random_array.h"

void Test_InsertSort()
{
	random_array m_random;

	std::vector<int> arr = m_random.generateRandomArray();
	std::cout << "Original array: ";
	m_random.printArray(arr);


    // 进行排序并输出
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
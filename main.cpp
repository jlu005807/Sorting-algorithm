//排序算法（英语：Sorting algorithm）是一种将一组特定的数据按某种顺序进行排列的算法。
//排序算法多种多样，性质也大多不同。

//稳定性
//稳定性是指相等的元素经过排序之后相对顺序是否发生了改变。
//基数排序、计数排序、插入排序、冒泡排序、归并排序是稳定排序。
//选择排序、堆排序、快速排序、希尔排序不是稳定排序。

#include"Insertion_sort.h"
#include"Swap_Sort.h"
#include"Selection_Sort.h"
#include"Merging_Sort.h"
#include"Radix_Sort.h"
#include"random_array.h"

//测试插入排序
void Test_InsertSort()
{
	random_array m_random;

	std::vector<int> arr = m_random.generateRandomVector();
    std::cout << "Original array: " << std::endl;
	printArray(arr);
    std::sort(arr.begin(),arr.end());

    // 进行排序并输出
    std::vector<int> arr1 = arr;
    Straight_Insertion_Sort(arr1);
    std::cout << "Sorted by Straight Insertion Sort: " << std::endl;
    printArray(arr1);

    std::vector<int> arr2 = arr;
    Binary_Insertion_Sort(arr2);
    std::cout << "Sorted by Binary Insertion Sort:   " << std::endl;
    printArray(arr2);

    std::vector<int> arr3 = arr;
    ShellSort(arr3);
    std::cout << "Sorted by Shell Sort:              " << std::endl;
    printArray(arr3);
}

//测试交换排序
void Test_SwapSort()
{
    random_array m_random;
    auto p = m_random.generateRandomVector();
    
    // 打印原始数组
    std::cout << "Original Array:" << std::endl;
    printArray(p);
    int size = p.size();

    // 冒泡排序测试
    std::cout << "\nBubble Sort Test:" << std::endl;
    int* bubbleArray = new int[size];
    std::copy(p.begin(), p.end(), bubbleArray); // 复制数组
    Bubble_Sort(bubbleArray, size);
    printArray(std::vector<int>(bubbleArray, bubbleArray + size));  // 打印排序后的数组
    delete[] bubbleArray;  // 释放内存

    // 快速排序测试
    std::cout << "\nQuick Sort C Test:" << std::endl;
    int* quickArray = new int[size];
    std::copy(p.begin(), p.end(), quickArray);  // 复制数组
    Quick_Sort_C(quickArray, 0, size - 1);
    printArray(std::vector<int>(quickArray, quickArray + size));  // 打印排序后的数组
    delete[] quickArray;  // 释放内存

    // 复制一份数组用于不同排序算法
    std::vector<int> arrayForFroandBack = p;
    std::vector<int> arrayForHoare = p;
    std::vector<int> arrayForHole = p;

    // 测试FroandBack排序
    std::cout << "\nTesting FroandBack QuickSort:" << std::endl;
    FroandBack<int> froandBackSort;
    froandBackSort.Sort(arrayForFroandBack.data(), 0, arrayForFroandBack.size() - 1);
    printArray(arrayForFroandBack);

    // 测试Hoare排序
    std::cout << "\nTesting Hoare QuickSort:" << std::endl;
    Hoare<int> hoareSort;
    hoareSort.Sort(arrayForHoare.data(), 0, arrayForHoare.size() - 1);
    printArray(arrayForHoare);

    // 测试Hole排序
    std::cout << "\nTesting Hole QuickSort:" << std::endl;
    Hole<int> holeSort;
    holeSort.Sort(arrayForHole.data(), 0, arrayForHole.size() - 1);
    printArray(arrayForHole);

    // 复制一份数组用于不同排序算法
    std::vector<int> arrayForQuickInsertSort = p;
    std::vector<int> arrayForQuickSortThreeroad = p;

    // 测试 Quick_Sort_Threeroad
    std::cout << "\nTesting Quick_Sort_Threeroad:" << std::endl;
    Quick_Sort_Threeroad(arrayForQuickSortThreeroad.data(), size);
    printArray(arrayForQuickSortThreeroad.data(), size);

    // 测试 Quick_Insert_Sort
    std::cout << "\nTesting Quick_Insert_Sort:" << std::endl;
    Quick_Insert_Sort(arrayForQuickInsertSort.data(), size);
    printArray(arrayForQuickInsertSort.data(), size);

    // 测试内省排序
    std::vector<int> arrayIntrospectiveSort = p;

    // 调用内省排序，初始深度为 0
    Introspective_Sort(arrayIntrospectiveSort.data(), p.size(), 0);

    std::cout << "\nIntrospective Sort Result:" << std::endl;
    printArray(arrayIntrospectiveSort);

}

void Test_Selection_Sort()
{
    random_array m_random;
    auto p = m_random.generateRandomVector();

    // 打印原始数组
    std::cout << "Original Array:" << std::endl;
    printArray(p);
    int size = p.size();

    // 测试简单选择排序
    int* simple_selection_sorted=new int[size];
    std::copy(std::begin(p), std::end(p), simple_selection_sorted);
    Simple_Selection_Sort(simple_selection_sorted, size);

    std::cout << "\nSimple Selection Sort Result:" << std::endl;
    printArray(simple_selection_sorted, size);

    // 测试堆排序
    int* heap_sorted = new int[size];
    std::copy(std::begin(p), std::end(p), heap_sorted);
    Heap_Sort(heap_sorted,size);

    std::cout << "\nHeap Sort Result:" << std::endl;
    printArray(heap_sorted, size);

}

void Test_MergeSort()
{
    random_array m_random;
    auto p = m_random.generateRandomVector();

    // 打印原始数组
    std::cout << "Original Array:" << std::endl;
    printArray(p);
    int size = p.size();

  

    // 测试递归归并排序
    std::vector<int> arrayRecursive = p;
    Merge_Sort(arrayRecursive.data(), 0, arrayRecursive.size());
    std::cout << "\nRecursive Merge Sort Result:" << std::endl;
    printArray(arrayRecursive.data(), arrayRecursive.size());

    // 测试非递归归并排序
    std::vector<int> arrayNonRecursive = p;
    Merge_sort(arrayNonRecursive.data(), arrayNonRecursive.size());
    std::cout << "\nNon-Recursive Merge Sort Result:" << std::endl;
    printArray(arrayNonRecursive.data(), arrayNonRecursive.size());

}

void Test_Radix_Sort()
{
    random_array m_random;
    auto p = m_random.generateRandomVector();

    // 打印原始数组
    std::cout << "Original Array:" << std::endl;
    printArray(p);
    int size = p.size();

    // 测试计数排序
    std::vector<int> arrayCounting = p;
    Counting_Sort(arrayCounting.data(), size);
    std::cout << "\nCounting Sort Result:" << std::endl;
    printArray(arrayCounting);

    // 测试桶排序
    std::vector<int> arrayBucket = p;
    Bucket_Sort(arrayBucket.data(), size);
    std::cout << "\nBucket Sort Result:" << std::endl;
    printArray(arrayBucket);

    // 测试MSD基数排序
    std::vector<uint32_t> arrayMSD(p.begin(), p.end());
    MSD_radix_sort(arrayMSD.data(), arrayMSD.data() + arrayMSD.size());
    std::cout << "\nMSD Radix Sort Result:" << std::endl;
    printArray(arrayMSD);

    //对于字符串和LSD基数排序不考虑测试

}

int main()
{ 
    Test_InsertSort();

    system("Pause");

    Test_SwapSort();

    system("Pause");

    Test_Selection_Sort();

    system("Pause");

    Test_MergeSort();

    system("Pause");

    Test_Radix_Sort();

    system("Pause");
}
//�����㷨��Ӣ�Sorting algorithm����һ�ֽ�һ���ض������ݰ�ĳ��˳��������е��㷨��
//�����㷨���ֶ���������Ҳ��಻ͬ��

//�ȶ���
//�ȶ�����ָ��ȵ�Ԫ�ؾ�������֮�����˳���Ƿ����˸ı䡣
//�������򡢼������򡢲�������ð�����򡢹鲢�������ȶ�����
//ѡ�����򡢶����򡢿�������ϣ���������ȶ�����

#include"Insertion_sort.h"
#include"Swap_Sort.h"
#include"Selection_Sort.h"
#include"Merging_Sort.h"
#include"Radix_Sort.h"
#include"random_array.h"

//���Բ�������
void Test_InsertSort()
{
	random_array m_random;

	std::vector<int> arr = m_random.generateRandomVector();
    std::cout << "Original array: " << std::endl;
	printArray(arr);
    std::sort(arr.begin(),arr.end());

    // �����������
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

//���Խ�������
void Test_SwapSort()
{
    random_array m_random;
    auto p = m_random.generateRandomVector();
    
    // ��ӡԭʼ����
    std::cout << "Original Array:" << std::endl;
    printArray(p);
    int size = p.size();

    // ð���������
    std::cout << "\nBubble Sort Test:" << std::endl;
    int* bubbleArray = new int[size];
    std::copy(p.begin(), p.end(), bubbleArray); // ��������
    Bubble_Sort(bubbleArray, size);
    printArray(std::vector<int>(bubbleArray, bubbleArray + size));  // ��ӡ����������
    delete[] bubbleArray;  // �ͷ��ڴ�

    // �����������
    std::cout << "\nQuick Sort C Test:" << std::endl;
    int* quickArray = new int[size];
    std::copy(p.begin(), p.end(), quickArray);  // ��������
    Quick_Sort_C(quickArray, 0, size - 1);
    printArray(std::vector<int>(quickArray, quickArray + size));  // ��ӡ����������
    delete[] quickArray;  // �ͷ��ڴ�

    // ����һ���������ڲ�ͬ�����㷨
    std::vector<int> arrayForFroandBack = p;
    std::vector<int> arrayForHoare = p;
    std::vector<int> arrayForHole = p;

    // ����FroandBack����
    std::cout << "\nTesting FroandBack QuickSort:" << std::endl;
    FroandBack<int> froandBackSort;
    froandBackSort.Sort(arrayForFroandBack.data(), 0, arrayForFroandBack.size() - 1);
    printArray(arrayForFroandBack);

    // ����Hoare����
    std::cout << "\nTesting Hoare QuickSort:" << std::endl;
    Hoare<int> hoareSort;
    hoareSort.Sort(arrayForHoare.data(), 0, arrayForHoare.size() - 1);
    printArray(arrayForHoare);

    // ����Hole����
    std::cout << "\nTesting Hole QuickSort:" << std::endl;
    Hole<int> holeSort;
    holeSort.Sort(arrayForHole.data(), 0, arrayForHole.size() - 1);
    printArray(arrayForHole);

    // ����һ���������ڲ�ͬ�����㷨
    std::vector<int> arrayForQuickInsertSort = p;
    std::vector<int> arrayForQuickSortThreeroad = p;

    // ���� Quick_Sort_Threeroad
    std::cout << "\nTesting Quick_Sort_Threeroad:" << std::endl;
    Quick_Sort_Threeroad(arrayForQuickSortThreeroad.data(), size);
    printArray(arrayForQuickSortThreeroad.data(), size);

    // ���� Quick_Insert_Sort
    std::cout << "\nTesting Quick_Insert_Sort:" << std::endl;
    Quick_Insert_Sort(arrayForQuickInsertSort.data(), size);
    printArray(arrayForQuickInsertSort.data(), size);

    // ������ʡ����
    std::vector<int> arrayIntrospectiveSort = p;

    // ������ʡ���򣬳�ʼ���Ϊ 0
    Introspective_Sort(arrayIntrospectiveSort.data(), p.size(), 0);

    std::cout << "\nIntrospective Sort Result:" << std::endl;
    printArray(arrayIntrospectiveSort);

}

void Test_Selection_Sort()
{
    random_array m_random;
    auto p = m_random.generateRandomVector();

    // ��ӡԭʼ����
    std::cout << "Original Array:" << std::endl;
    printArray(p);
    int size = p.size();

    // ���Լ�ѡ������
    int* simple_selection_sorted=new int[size];
    std::copy(std::begin(p), std::end(p), simple_selection_sorted);
    Simple_Selection_Sort(simple_selection_sorted, size);

    std::cout << "\nSimple Selection Sort Result:" << std::endl;
    printArray(simple_selection_sorted, size);

    // ���Զ�����
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

    // ��ӡԭʼ����
    std::cout << "Original Array:" << std::endl;
    printArray(p);
    int size = p.size();

  

    // ���Եݹ�鲢����
    std::vector<int> arrayRecursive = p;
    Merge_Sort(arrayRecursive.data(), 0, arrayRecursive.size());
    std::cout << "\nRecursive Merge Sort Result:" << std::endl;
    printArray(arrayRecursive.data(), arrayRecursive.size());

    // ���Էǵݹ�鲢����
    std::vector<int> arrayNonRecursive = p;
    Merge_sort(arrayNonRecursive.data(), arrayNonRecursive.size());
    std::cout << "\nNon-Recursive Merge Sort Result:" << std::endl;
    printArray(arrayNonRecursive.data(), arrayNonRecursive.size());

}

void Test_Radix_Sort()
{
    random_array m_random;
    auto p = m_random.generateRandomVector();

    // ��ӡԭʼ����
    std::cout << "Original Array:" << std::endl;
    printArray(p);
    int size = p.size();

    // ���Լ�������
    std::vector<int> arrayCounting = p;
    Counting_Sort(arrayCounting.data(), size);
    std::cout << "\nCounting Sort Result:" << std::endl;
    printArray(arrayCounting);

    // ����Ͱ����
    std::vector<int> arrayBucket = p;
    Bucket_Sort(arrayBucket.data(), size);
    std::cout << "\nBucket Sort Result:" << std::endl;
    printArray(arrayBucket);

    // ����MSD��������
    std::vector<uint32_t> arrayMSD(p.begin(), p.end());
    MSD_radix_sort(arrayMSD.data(), arrayMSD.data() + arrayMSD.size());
    std::cout << "\nMSD Radix Sort Result:" << std::endl;
    printArray(arrayMSD);

    //�����ַ�����LSD�������򲻿��ǲ���

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
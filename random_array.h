#pragma once
#include <iostream>
#include <random>
#include <vector>

// ����ָ����Χ�ڵ������������
class random_array
{
public:
    std::vector<int> generateRandomVector()
    {
        std::random_device rd;   // ��ȡ����豸
        std::mt19937 gen(rd());  // ʹ�� Mersenne Twister �����������

        // �����������Ĵ�С
        std::uniform_int_distribution<> size_dis(20, 50);
        int size = size_dis(gen);
       

        // ����������½�
        std::uniform_int_distribution<> lower_dis(-100, 0);
        std::uniform_int_distribution<> upper_dis(0, 1000);
        int lower = lower_dis(gen);
        int upper = upper_dis(gen);

        // �����������
        std::uniform_int_distribution<> value_dis(lower, upper);
        std::vector<int> arr(size); // ����һ��ָ����С����������
        for (int i = 0; i < size; i++) 
        {
            arr[i] = value_dis(gen); // �������
        }

        return arr; // �������ɵ�����
    }
    
    //����һ��ָ��������С
    std::pair<int*,int> generateRandomArray()
    {
        std::random_device rd;   // ��ȡ����豸
        std::mt19937 gen(rd());  // ʹ�� Mersenne Twister �����������

        // �����������Ĵ�С
        std::uniform_int_distribution<> size_dis(20, 200);
        int size = size_dis(gen);


        // ����������½磨���磺������� 1 �� 50 ����Сֵ�� 51 �� 100 �����ֵ��
        std::uniform_int_distribution<> lower_dis(0, 10);
        std::uniform_int_distribution<> upper_dis(10, 1000);
        int lower = lower_dis(gen);
        int upper = upper_dis(gen);

        // �����������
        std::uniform_int_distribution<> value_dis(lower, upper);
        int *arr=new int[size]; // ����һ��ָ����С����������
        for (int i = 0; i < size; i++)
        {
            arr[i] = value_dis(gen); // �������
        }

        return { arr,size }; // �������ɵ�����
    }
};

// ��ӡ����
void printArray(const std::vector<int>& arr)
{
    for (const int& num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// ��ӡ����
void printArray(const std::vector<uint32_t>& arr)
{
    for (const int& num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// ��ӡ����
void printArray(const int* arr, int n)
{
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

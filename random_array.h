#pragma once
#include <iostream>
#include <random>
#include <vector>

// ����ָ����Χ�ڵ������������
class random_array
{
public:
    std::vector<int> generateRandomArray()
    {
        std::random_device rd;   // ��ȡ����豸
        std::mt19937 gen(rd());  // ʹ�� Mersenne Twister �����������

        // �����������Ĵ�С�����磺������� 1 �� 20 �������С��
        std::uniform_int_distribution<> size_dis(1, 10);
        int size = size_dis(gen);

        // ����������½磨���磺������� 1 �� 50 ����Сֵ�� 51 �� 100 �����ֵ��
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

    // ��ӡ����
    void printArray(const std::vector<int>& arr)
    {
        for (const int& num : arr) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
};


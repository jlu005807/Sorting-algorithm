#pragma once
#include <iostream>
#include <random>
#include <vector>

// 生成指定范围内的随机整数数组
class random_array
{
public:
    std::vector<int> generateRandomVector()
    {
        std::random_device rd;   // 获取随机设备
        std::mt19937 gen(rd());  // 使用 Mersenne Twister 随机数生成器

        // 随机决定数组的大小
        std::uniform_int_distribution<> size_dis(20, 50);
        int size = size_dis(gen);
       

        // 随机决定上下界
        std::uniform_int_distribution<> lower_dis(-100, 0);
        std::uniform_int_distribution<> upper_dis(0, 1000);
        int lower = lower_dis(gen);
        int upper = upper_dis(gen);

        // 生成随机数组
        std::uniform_int_distribution<> value_dis(lower, upper);
        std::vector<int> arr(size); // 创建一个指定大小的整数数组
        for (int i = 0; i < size; i++) 
        {
            arr[i] = value_dis(gen); // 填充数组
        }

        return arr; // 返回生成的数组
    }
    
    //返回一个指针和数组大小
    std::pair<int*,int> generateRandomArray()
    {
        std::random_device rd;   // 获取随机设备
        std::mt19937 gen(rd());  // 使用 Mersenne Twister 随机数生成器

        // 随机决定数组的大小
        std::uniform_int_distribution<> size_dis(20, 200);
        int size = size_dis(gen);


        // 随机决定上下界（例如：随机生成 1 到 50 的最小值和 51 到 100 的最大值）
        std::uniform_int_distribution<> lower_dis(0, 10);
        std::uniform_int_distribution<> upper_dis(10, 1000);
        int lower = lower_dis(gen);
        int upper = upper_dis(gen);

        // 生成随机数组
        std::uniform_int_distribution<> value_dis(lower, upper);
        int *arr=new int[size]; // 创建一个指定大小的整数数组
        for (int i = 0; i < size; i++)
        {
            arr[i] = value_dis(gen); // 填充数组
        }

        return { arr,size }; // 返回生成的数组
    }
};

// 打印数组
void printArray(const std::vector<int>& arr)
{
    for (const int& num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// 打印数组
void printArray(const std::vector<uint32_t>& arr)
{
    for (const int& num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// 打印数组
void printArray(const int* arr, int n)
{
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

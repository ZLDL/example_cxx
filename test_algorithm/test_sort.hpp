//
// Created by Wangzhuxing on 2018/8/18.
//

#ifndef EXAMPLE_CXX_TEST_SORT_HPP
#define EXAMPLE_CXX_TEST_SORT_HPP

#include <iostream>
#include <vector>
#include <functional>

class Sort {
public:
    /// 1. bubble sort
    bool bubbleSort(int array[], const int size) {
        std::cout << __FUNCTION__ << " : ";
        bool bSwap = false;
        for (int i = 0; i < size-1; i++) {  // 最多进行 n-1 次
            bSwap = false;
            for (int j = size-1; j > i; j--) {  // 从下往上扫描
                if (array[j] < array[j-1]) {
                    // simple swap
                    array[j] = array[j] + array[j-1];
                    array[j-1] = array[j] - array[j-1];
                    array[j] = array[j] - array[j-1];

                    bSwap = true;
                }
            }
            if (!bSwap) {
                break;
            }
        }
        return true;
    }
    /// 2. quick sort
    std::function<int(int[], int, int)> partition = [](int arr[], int left, int right) {
#if 0
        int temp = arr[left];
        while (left < right) {
            while (left < right && arr[right] >= temp)
                right--;

            if (left < right) {
                arr[left++] = arr[right];
            }

            while (left < right && arr[left] < temp)
                left++;

            if (left < right) {
                arr[right--] = arr[left];
            }
        }
        arr[left] = temp;
#else
        // 当 left < right 即移动的点还没到中间时循环
        while(left < right) {
            // 右边区开始，保证 left < right 并且 arr[left] 小于或者等于 arr[right] 的时候就向左遍历
            while(left < right && arr[left] <= arr[right])
                --right;
            // 这时候已经跳出循环，说明 right > left 或者 arr[left] 大于 arr[right] 了，
            // 如果 left < right 那就是 arr[left] 大于 arr[right]，那就交换
            if(left < right) {
                int temp = arr[left];
                arr[left] = arr[right];
                arr[right] = temp;
            }

            // 对另一边执行同样的操作
            while(left < right && arr[left] <= arr[right])
                ++left;
            if(left < right){
                int temp = arr[left];
                arr[left] = arr[right];
                arr[right] = temp;
            }
        }
#endif
        return left;
    };
    bool quickSort(int array[], const int start, const int end) {
        std::cout << __FUNCTION__ << " : ";
        if (start < end) {
            int pos = partition(array, start, end);
            quickSort(array, start, pos-1);
            quickSort(array, pos+1, end);
        }
        return true;
    }
    bool quickSort_stack(int array[], const int start, const int end) {
        std::cout << __FUNCTION__ << " : ";
        int* stack = new int[end - start + 1];
        int len = 0;
        stack[len++] = start;
        stack[len++] = end;
        while (len > 0) {
            int right = stack[--len];
            int left = stack[--len];
            int pos = partition(array, left, right);
            if (pos - 1 > left) {
                stack[len++] = left;
                stack[len++] = pos-1;
            }
            if (pos + 1 < right) {
                stack[len++] = pos + 1;
                stack[len++] = right;
            }
        }
        delete[] stack;
        return true;
    }
    /// 3. insert sort
    bool insertSort(int array[], int size) {
        std::cout << __FUNCTION__ << " : ";
        for (int i = 1; i <= size; ++i) {
            for(int j = i; j > 0; --j) {
                if(array[j] < array[j -1]) {
                    int temp = array[j];
                    array[j] = array[j - 1];
                    array[j - 1] = temp;
                }
            }
        }
        return true;
    }
    /// 4. shell sort
    bool shellSort(int arr[], int size, int d[], int d_size) {
        std::cout << __FUNCTION__ << " : ";
        for (int k = 0; k < d_size; k++) {
            int gap = d[k];
            for (int j = 0; j < gap; j++) { // 对于增量值 gap，一共 gap 组，0~gap-1

                for (int i = j + gap; i < size; i++) {

                    if (arr[i] < arr[i - gap]) { // 如果大于，不需要插入排序
                        int pivot = arr[i];
                        int t = i - gap;
                        while (t >= 0 && pivot < arr[t]) {
                            arr[t + gap] = arr[t];
                            t = t - gap;
                        }
                        arr[t + gap] = pivot;
                    }
                }
            }
        }
        return true;
    }
    /// 5. heap sort
    std::function<void(int[], int, int)> heapify_ = [](int arr[], int first, int end) {
        int father = first;
        int son = father * 2 + 1;
        while(son < end){
            if(son + 1 < end && arr[son] < arr[son+1]) ++son;
            //如果父节点大于子节点则表示调整完毕
            if(arr[father] > arr[son]) break;
            else {
                //不然就交换父节点和子节点的元素
                int temp = arr[father];
                arr[father] = arr[son];
                arr[son] = temp;
                //父和子节点变成下一个要比较的位置
                father = son;
                son = 2 * father + 1;
            }
        }
    };
    bool heapSort(int arr[], const int len) {
        std::cout << __FUNCTION__ << " : ";
        int i = 0;
        //初始化堆，从最后一个父节点开始
        for(i = len/2 - 1; i >= 0; --i){
            heapify_(arr, i, len);
        }
        //从堆中的取出最大的元素再调整堆
        for(i = len - 1;i > 0;--i){
            int temp = arr[i];
            arr[i] = arr[0];
            arr[0] = temp;
            //调整成堆
            heapify_(arr, 0, i);
        }
        return true;
    }
    /// 6. merge sort
    void Merge(int arr[], int reg[], int start, int end) {
        if (start >= end)return;
        int len = end - start, mid = (len >> 1) + start;

        //分成两部分
        int start1 = start, end1 = mid;
        int start2 = mid + 1, end2 = end;
        //然后合并
        Merge(arr, reg, start1, end1);
        Merge(arr, reg, start2, end2);


        int k = start;
        //两个序列一一比较,哪的序列的元素小就放进reg序列里面,然后位置+1再与另一个序列原来位置的元素比较
        //如此反复,可以把两个有序的序列合并成一个有序的序列
        while (start1 <= end1 && start2 <= end2)
            reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];

        //然后这里是分情况,如果arr2序列的已经全部都放进reg序列了然后跳出了循环
        //那就表示arr序列还有更大的元素(一个或多个)没有放进reg序列,所以这一步就是接着放
        while (start1 <= end1)
            reg[k++] = arr[start1++];

        //这一步和上面一样
        while (start2 <= end2)
            reg[k++] = arr[start2++];
        //把已经有序的reg序列放回arr序列中
        for (k = start; k <= end; k++)
            arr[k] = reg[k];
    };
    bool mergeSort(int arr[], int len) {
        std::cout << __FUNCTION__ << " : ";
        int reg[len];
        Merge(arr, reg, 0, len-1);
        return true;
    }
    /// 7. select sort
    bool selectSort(int arr[], int size) {
        std::cout << __FUNCTION__ << " : ";
        for (int i = 0; i < size; i++) {
            int min = i;
            for (int j = i + 1; j < size; j++) {
                if (arr[j] < arr[min])
                    min = j;

            }
            if (min != i) {
                int temp = arr[min];
                arr[min] = arr[i];
                arr[i] = temp;
            }
        }
        return true;
    }
};


int test_sort()
{
    std::cout << "--------" << __FUNCTION__ << "--------" << std::endl;

    int array[10] = { 2, 6, 14, 9, 5, 7, 1, 8, 55, 4};
    std::vector<int> vec = { 2, 6, 14, 9, 5, 7, 1, 8, 55, 4};

    std::cout << "before sort, order: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << array[i] << ", ";
    }
    std::cout << std::endl;

    Sort algorithm;
#if 0
    algorithm.bubbleSort(array, 10);
#elif 0
    algorithm.quickSort(array, 0, 9);
#elif 0
    algorithm.quickSort_stack(array, 0, 9);
#elif 0
    algorithm.insertSort(array, 10);
#elif 0
    int d[3] = {5, 3, 1};
    algorithm.shellSort(array, 10, d, 3);
#elif 0
    algorithm.heapSort(array, 10);
#elif 0
    algorithm.mergeSort(array, 10);
#elif 1
    algorithm.selectSort(array, 10);
#endif

    for (int i = 0; i < 10; ++i) {
        std::cout << array[i] << ", ";
    }
    std::cout << std::endl;
    return 0;
}

#endif //EXAMPLE_CXX_TEST_SORT_HPP

#ifndef ALGORITHM_TEMPLATE_CPP_SHELLSORT_H
#define ALGORITHM_TEMPLATE_CPP_SHELLSORT_H

#include <vector>

template <typename T>
class Shellsort {
public:
    Shellsort() = delete;

    static void sort(std::vector<T> &arr);  // 排序(默认升序)
};

template<typename T>
void Shellsort<T>::sort(std::vector<T> &arr) {
    int h = arr.size() / 2;
    while (h > 0) {
        for (int start = 0; start < h; start++) {
            // 对arr[start]、arr[start + h]、arr[start + 2h]...进行插入排序
            for (int i = start + h; i < arr.size(); i += h) {
                T tmp = arr[i];
                int j;
                for (j = i; j - h >= 0 && tmp < arr[j - h]; j -= h)
                    arr[j] = arr[j - h];
                arr[j] = tmp;
            }
            h /= 2;
        }
    }
}


#endif //ALGORITHM_TEMPLATE_CPP_SHELLSORT_H

#ifndef ALGORITHM_TEMPLATE_CPP_SHELLSORT_H
#define ALGORITHM_TEMPLATE_CPP_SHELLSORT_H

#include <vector>

template <typename T>
class Shellsort {
public:
    Shellsort() = delete;

    static void sort(std::vector<T> &arr);  // 排序(默认升序)，步长序列: 1、2、4、8、...(h = h * 2)
    static void sort2(std::vector<T> &arr);  // 排序(默认升序)，步长序列: 1、4、13、40、...(h = h * 3 + 1)
};

template<typename T>
void Shellsort<T>::sort(std::vector<T> &arr) {
    auto h = arr.size() / 2;
    while (h > 0) {
        // 对arr[h, n)进行插入排序
        for (int i = h; i < arr.size(); i ++) {
            auto tmp = arr[i];
            int j;
            for (j = i; j - h >= 0 && tmp < arr[j - h]; j -= h)
                arr[j] = arr[j - h];
            arr[j] = tmp;
        }
        h /= 2;
    }
}

template<typename T>
void Shellsort<T>::sort2(std::vector<T> &arr) {
    auto h = 1;
    while (h < arr.size())
        h = h * 3 + 1;
    while (h > 0) {
        // 对arr[h, n)进行插入排序
        for (int i = h; i < arr.size(); i++) {
            auto tmp = arr[i];
            int j;
            for (j = i; j - h >= 0 && tmp < arr[j - h]; j -= h)
                arr[j] = arr[j - h];
            arr[j] = tmp;
        }
        h /= 3;
    }
}

#endif //ALGORITHM_TEMPLATE_CPP_SHELLSORT_H

#ifndef ALGORITHM_TEMPLATE_CPP_REVERSE_PAIRS_H
#define ALGORITHM_TEMPLATE_CPP_REVERSE_PAIRS_H

#include <vector>

/**
 * 求解逆序对问题：
 * 方法1:
 *     暴力求解
 *     时间复杂度：O(n^2)
 * 方法2:
 *     使用归并排序实现
 *     后一段的元素归并上来时，和前一段的所有剩余元素都形成逆序数对
 *     时间复杂度：O(nlogn)
 */

template <typename T>
class ReversePairs {
public:
    ReversePairs() = delete;

    static int countReversePairs1(std::vector<T> &arr);  // 暴力实现
    static int countReversePairs2(std::vector<T> &arr);  // 归并排序实现

private:
    static int sort(std::vector<T> &arr, int l, int r, std::vector<T> &tmp);
    static int merge(std::vector<T> &arr, int l, int mid, int r, std::vector<T> &tmp);
};

template<typename T>
int ReversePairs<T>::countReversePairs1(std::vector<T> &arr) {
    int res = 0;
    for (int i = 0; i < arr.size(); i++)
        for (int j = i + 1; j < arr.size(); j++)
            if (arr[i] > arr[j])
                res++;
    return res;
}

template<typename T>
int ReversePairs<T>::countReversePairs2(std::vector<T> &arr) {
    std::vector<T> tmp(arr.size());
    return sort(arr, 0, arr.size() - 1, tmp);  // 返回的是arr[0..n - 1]逆序对的数目
}

template<typename T>
int ReversePairs<T>::sort(std::vector<T> &arr, int l, int r, std::vector<T> &tmp) {
    if (l >= r)
        return 0;

    int res = 0;
    int mid = l + (r - l) / 2;
    res += sort(arr, l, mid, tmp);
    res += sort(arr, mid + 1, r, tmp);

    if (arr[mid] > arr[mid + 1])
        res += merge(arr, l, mid, r, tmp);
}

template<typename T>
int ReversePairs<T>::merge(std::vector<T> &arr, int l, int mid, int r, std::vector<T> &tmp) {
    std::copy(arr.begin() + l, arr.begin() + r + 1, tmp.begin() + l);

    int i = l;
    int j = mid + 1;
    int res = 0;

    for (int k = l; k <= r; k++) {
        if (i > mid) {
            arr[k] = tmp[j];
            j++;
        }
        else if (j > r) {
            arr[k] = tmp[i];
            i++;
        }
        else if (tmp[i] <= tmp[j]) {
            arr[k] = tmp[i];
            i++;
        }
        else {
            res += mid - i + 1;
            arr[k] = tmp[j];
            j++;
        }
    }
    return res;
}

#endif //ALGORITHM_TEMPLATE_CPP_REVERSE_PAIRS_H

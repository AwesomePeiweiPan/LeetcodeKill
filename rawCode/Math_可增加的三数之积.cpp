#include <iostream>
#include <algorithm>
using namespace std;

long long maximizeProduct(int a, int b, int c, int k) {
    // 将三个数字放入数组并排序
    int nums[3] = {a, b, c};
    sort(nums, nums + 3); // 排序：nums[0] <= nums[1] <= nums[2]

    // 首先使最小值和次小值尽可能相等
    int diff1 = nums[1] - nums[0]; // 需要增加的次数使 nums[0] 等于 nums[1]
    if (k >= diff1) {
        nums[0] += diff1;
        k -= diff1;
    } else {
        nums[0] += k;
        k = 0;
    }

    // 然后使 nums[0] 和 nums[1] 尽可能接近 nums[2]
    int diff2 = nums[2] - nums[0]; // 需要增加的次数使 nums[0] 和 nums[1] 等于 nums[2]
    if (k >= 2 * diff2) {
        nums[0] += diff2;
        nums[1] += diff2;
        k -= 2 * diff2;
    } else {
        int increase = k / 2;
        nums[0] += increase;
        nums[1] += increase;
        k -= 2 * increase;
    }

    // 最后将剩余的操作次数尽可能均匀分配给三个数
    int evenly = k / 3;
    nums[0] += evenly;
    nums[1] += evenly;
    nums[2] += evenly;
    k %= 3; // 剩余未能均分的次数

    // 处理不能均分的剩余操作次数
    for (int i = 0; i < k; ++i) {
        nums[i]++;
    }

    // 计算最终的乘积
    cout<<nums[0]<<","<<nums[1]<<","<<nums[2]<<endl;
    return 1LL * nums[0] * nums[1] * nums[2];
}

int main() {
    int a, b, c, k;
    cin >> a >> b >> c >> k;
    
    // 输出最大乘积
    cout << maximizeProduct(a, b, c, k) << endl;
    return 0;
}

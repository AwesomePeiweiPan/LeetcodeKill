void compute_mean_variance(const std::vector<int>& numbers, const std::vector<std::pair<size_t, size_t>>& intervals, 
                           std::vector<float>& means, std::vector<float>& variances) {
    size_t n = numbers.size();
    // 前缀和数组
    vector<long long> prefixSum(n + 1, 0);
    vector<long long> prefixSquareSum(n + 1, 0);

    // 计算前缀和和前缀平方和
    for (size_t i = 0; i < n; ++i) {
        prefixSum[i + 1] = prefixSum[i] + numbers[i];
        prefixSquareSum[i + 1] = prefixSquareSum[i] + numbers[i] * numbers[i];
    }

    // 对每个区间计算均值和方差
    for (const auto& interval : intervals) {
        size_t start = interval.first;
        size_t end = interval.second;
        size_t count = end - start + 1;

        // 计算区间和及平方和
        long long sum = prefixSum[end + 1] - prefixSum[start];
        long long squareSum = prefixSquareSum[end + 1] - prefixSquareSum[start];

        // 计算均值
        float mean = static_cast<float>(sum) / count;
        means.push_back(mean);

        // 计算方差
        float variance = static_cast<float>(squareSum) / count - mean * mean;
        variances.push_back(variance);
    }
}

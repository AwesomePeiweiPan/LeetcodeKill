#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

// polygon按顺时针存储了多边形的顶点，例如：{{0, 0}, {0, 1}, {1, 1}, {1, 0}} 表示一个正方形，期望输出的面积为1
double calculate_polygon_area(const vector<pair<double, double>>& polygon) {
    int n = polygon.size(); // 顶点数量
    double area = 0.0;

    // 使用 Shoelace 公式计算面积
    for (int i = 0; i < n; i++) {
        double x1 = polygon[i].first; // 当前顶点的 x 坐标
        double y1 = polygon[i].second; // 当前顶点的 y 坐标
        
        //这里是因为需要考虑 n-1 个顶点的与第0个原点的链接问题
        double x2 = polygon[(i + 1) % n].first; // 下一个顶点的 x 坐标
        double y2 = polygon[(i + 1) % n].second; // 下一个顶点的 y 坐标
        area += (x1 * y2 - x2 * y1); // 累加叉积
    }

    return abs(area) / 2.0; // 返回面积的绝对值除以 2
}

int main() {
    // 示例多边形：一个正方形
    vector<pair<double, double>> polygon = {{0, 0}, {0, 1}, {1, 1}, {1, 0}};
    
    // 计算并输出多边形的面积
    double area = calculate_polygon_area(polygon);
    cout << "Area of the polygon: " << area << endl;

    return 0;
}


/*
Created by Charliegu on 2023/5/6.
编写一个点类Point,数据成员包括x坐标和y坐标。编写一个圆形类Circle,数据成员包括圆心和半径。要求使用组合关系实现这两个类，并且提供以下功能:
 1. 计算圆形的周长和面积
 2. 判断点是否在圆内
 3. 判断两个圆是否相交
 4. 支持两个Point类相加
 -----
 1. 构造函数最好立即对其初始化，而非先定义再赋值
 2. 当对象作为函数参数是使用引用类型，以减少内存开销
*/

#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

// point_x: X坐标
// point_y: Y坐标
class Point {
private:
    double point_x, point_y;
public:
    Point(double x, double y) : point_x(x), point_y(y) {}

    double getPX() {
        return point_x;
    }

    double getPY() {
        return point_y;
    }

    Point operator+(Point &anotherPoint) {
        return {point_x + anotherPoint.getPX(), point_y + anotherPoint.getPY()};
    }
};

// circleCenter 圆心
// circleRadius 半径
// C++的Π是 M_PI
class Circle {
private:
    Point circleCenter;
    double circleRadius;
public:
    Circle(Point center, double radius) : circleCenter(center), circleRadius(radius) {}

    double calCircumference() { return 2 * M_PI * circleRadius; }

    double calCircleArea() { return M_PI * circleRadius * circleRadius; }

    // 这里不开方了，直接将半径平方
    bool isPointInsideCircle(Point &point) {
        double distance =
                pow((point.getPX() - circleCenter.getPX()), 2) + pow((point.getPY() - circleCenter.getPY()), 2);
        // 只有在圆内才返回true，否则都是false
        return distance < pow(circleRadius, 2);
    }

    bool isCircleIntersect(Circle &anotherCircle) {
        double distance =
                pow((anotherCircle.circleCenter.getPX() - circleCenter.getPX()), 2) +
                pow((anotherCircle.circleCenter.getPY() - circleCenter.getPY()), 2);
        return distance <= pow((circleRadius + anotherCircle.circleRadius), 2);
    }


};

int main() {
    double circle_x0, circle_y0, circle_radius0;
    cout << "请输入圆心的坐标，以空格分割" << endl;
    cin >> circle_x0 >> circle_y0;
    Point circle_center0(circle_x0, circle_y0);
    cout << "请输入圆的半径,不能为负数" << endl;
    do {
        cin >> circle_radius0;
        if (circle_radius0 < 0) {
            cout << "圆的半径不能为负数,请重新输入" << endl;
        }
    } while (circle_radius0 < 0);
    Circle circle0(circle_center0, circle_radius0);
    // 计算圆的周长和面积
    double result_circumference, result_circleArea;
    result_circumference = circle0.calCircumference();
    result_circleArea = circle0.calCircleArea();
    cout << "周长是" << result_circumference << endl;
    cout << "面积是" << result_circleArea << endl;
    cout << "请输入一个点的坐标，判断该点是否在圆内" << endl;
    double point_x0, point_y0;
    cin >> point_x0 >> point_y0;
    Point point0(point_x0, point_y0);
    if (circle0.isPointInsideCircle(point0)) {
        cout << "该点在圆内" << endl;
    } else {
        cout << "该点不在圆内" << endl;
    }
    cout << "请输入另外一个点的坐标，测试Point类相加" << endl;
    double point_x1, point_y1;
    cin >> point_x1 >> point_y1;
    Point point1(point_x1, point_y1);
    Point resultPointSum = point0 + point1;
    cout << "两个Point相加，新的Point坐标为(" << resultPointSum.getPX() << "," << resultPointSum.getPY() << ")" << endl;
    double circle_x1, circle_y1, circle_radius1;
    cout << "请输入另一个圆心的坐标，判断两圆是否相交" << endl;
    cin >> circle_x1 >> circle_y1;
    Point circlec_Center1(circle_x1, circle_y1);
    cout << "请输入圆的半径" << endl;
    do {
        cin >> circle_radius1;
        if (circle_radius1 < 0) {
            cout << "圆的半径不能为负数,请重新输入" << endl;
        }
    } while (circle_radius1 < 0);
    Circle circle1(circlec_Center1, circle_radius1);
    if (circle0.isCircleIntersect(circle1)) {
        cout << "两圆相交" << endl;
    } else {
        cout << "两圆不相交" << endl;
    }

}
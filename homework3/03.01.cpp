#include<iostream>
#include<vector>
#include<print>
#include<cmath>

struct Point {
    int x;
    int y;
};

Point left_up_intersection_of_points(Point a, Point b) {
    return Point {std::max(a.x, b.x), std::max(a.y, b.y)};
}

Point right_down_intersection_of_points(Point a, Point b) {
    return Point {std::min(a.x, b.x), std::min(a.y, b.y)};
}

Point left_up_min_shell(Point a, Point b) {
    return Point {std::min(a.x, b.x), std::min(a.y, b.y)};
}

Point right_down_min_shell(Point a, Point b) {
    return Point {std::max(a.x, b.x), std::max(a.y, b.y)};
}

struct Rectangle {
    Point right_down_point;
    Point left_up_point;
};

bool has_not_intersaction(Rectangle a, Rectangle b) {
    if (a.left_up_point.y >= b.right_down_point.y || b.left_up_point.y >= a.right_down_point.y) {
        return true;
    }
    if (a.right_down_point.x <= b.left_up_point.x || b.right_down_point.x <= a.left_up_point.x) {
        return true;
    }
    return false;
}

long long square_of_rectangle(const Rectangle & rectangle) {
    return (rectangle.right_down_point.y - rectangle.left_up_point.y) * (rectangle.right_down_point.x - rectangle.left_up_point.x);
}

long long get_square_of_intersection(const std::vector<Rectangle> & rectangles) {
    Rectangle rectangle_of_intersection = rectangles[0];
    for (auto i = 1uz; i < rectangles.size(); ++i) {
        if (has_not_intersaction(rectangle_of_intersection, rectangles[i])) {
            return 0;
        }
        rectangle_of_intersection.left_up_point = left_up_intersection_of_points(rectangle_of_intersection.left_up_point, rectangles[i].left_up_point);
        rectangle_of_intersection.right_down_point = right_down_intersection_of_points(rectangle_of_intersection.right_down_point, rectangles[i].right_down_point);
    }
    return square_of_rectangle(rectangle_of_intersection);
}

long long get_square_of_min_shell(const std::vector<Rectangle> & rectangles) {
    Rectangle rectangle_of_min_shell = rectangles[0];
    for (auto i = 1uz; i < rectangles.size(); ++i) {
        rectangle_of_min_shell.left_up_point = left_up_min_shell(rectangle_of_min_shell.left_up_point, rectangles[i].left_up_point);
        rectangle_of_min_shell.right_down_point = right_down_min_shell(rectangle_of_min_shell.right_down_point, rectangles[i].right_down_point);
    }
    return square_of_rectangle(rectangle_of_min_shell);

}

std::vector<Rectangle> initInputVector() {
    std::vector<Rectangle> rectangles = {};
    Rectangle rect;
    while (std::cin >> rect.left_up_point.x >> rect.left_up_point.y >> rect.right_down_point.x >> rect.right_down_point.y) {
        rectangles.push_back(rect);
    }
    return rectangles;
}

int main() {
    std::vector<Rectangle> rectangles = initInputVector();
    if (rectangles.empty()) {
        return 0;
    }
    long long square_of_intersection = get_square_of_intersection(rectangles);
    long long square_of_min_shell = get_square_of_min_shell(rectangles);
    std::print("square_of_intersection - {}, square_of_min_shell - {}\n", square_of_intersection, square_of_min_shell);
}
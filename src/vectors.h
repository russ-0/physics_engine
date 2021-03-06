#ifndef PHYSICS_VECTORS_H
#define PHYSICS_VECTORS_H

#include "point.h"

double magnitude(double x, double y);
double determinant(double a, double b, double c, double d);

struct Vector {
    Vector(Point *t = new Point, Point *h = new Point) : tail(t), head(h) {}
    ~Vector() = default;

    Point *tail;
    Point *head;
    double x_cmp = head->x - tail->x;
    double y_cmp = head->y - tail->y;
    double mag = magnitude(x_cmp, y_cmp);

    bool operator==(const Vector& other) const;
    Vector normal() const;  // normalized perpendicular
    Vector perpendicular() const;
};

double dot(const Vector& a, const Vector& b);   // dot product of 2 vectors
bool colinear_intersection(const Point *p, const Point *q, const Point *r); // checking if 2 lines are colinear
int point_orientation(const Point *p, const Point *q, const Point *r);  // orientation of 3 points on belonging to 2 lines
bool overlap(const Vector& a, const Vector& b); // check for overlapping lines
Vector operator+(const Vector& a, const Vector& b);
Vector operator+=(Vector& a, const Vector& b);
Vector operator-(const Vector& a, const Vector& b);
Vector operator-=(Vector& a, const Vector& b);
Vector operator*(double scalar, const Vector &a);

#endif

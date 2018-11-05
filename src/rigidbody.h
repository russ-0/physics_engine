#ifndef PHYSICS_RIGIDBODY_H
#define PHYSICS_RIGIDBODY_H

#include <iostream>
#include <utility>
#include <unistd.h>
#include <cmath>
#include <vector>
#include "vectors.h"
#include <typeinfo>

struct Rectangle;
struct Circle;

struct RigidBody{
    RigidBody() : mass(1), pos(new Point), vel(new Vector), accel(new Vector) {}
    RigidBody(double m, Point *p, Vector *v, Vector *a) : mass(m), pos(p), vel(v), accel(a) {}

    double mass;
    Point *pos;
    Vector *vel;
    Vector *accel;
    Vector net_force;
    std::vector<Vector> forces;          // stores all forces acting on particle

    void set_vel(Vector *v);
    void set_accel(Vector *a);
    void update_accel();
    void sum_forces();
    Vector get_netforce() const;
    virtual bool collides_with(const Rectangle &r) const = 0;   // look into using constexpr
    virtual bool collides_with(const Circle &c) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const RigidBody& rbd);
};

struct Rectangle : public RigidBody {
    Rectangle(): RigidBody(), length(1), width (1) {set_corners();}
    Rectangle(double l, double w, double m, Point *p, Vector *v, Vector *a): RigidBody(m, p, v, a), length(l), width(w) {set_corners();}

    double length;
    double width;
    Point *min;     // Top right corner
    Point *max;     // Bottom left corner

    void set_corners();
    bool collides_with(const Rectangle &r) const override;
    bool collides_with(const Circle &c) const override;
};

struct Circle : public RigidBody {
    Circle(): RigidBody(), radius(1) {}
    Circle(double r, double m, Point *p, Vector *v, Vector *a): RigidBody(m, p, v, a), radius(r) {}

    double radius;

    bool collides_with(const Rectangle &r) const override;
    bool collides_with(const Circle &c) const override;
};

void apply_force(RigidBody& rb, const Vector &f);

void move(RigidBody& rb, float dt);

bool scan_collision(const RigidBody &a, RigidBody &b);

#endif

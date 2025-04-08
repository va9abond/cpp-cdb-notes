/*
    clang++ -Werror -Wall -Wextra -pedantic ball.cpp -o ball
    ./ball
*/

#include <iostream>

class ball;

class ball {
public:
    ball() { update_ball_count(); }

    ball (double time, double vx_, double vy_, double x_, double y_) :
        t(time), vx(vx_), vy(vy_), x(x_), y(y_)
    {
        update_ball_count();
    }

    void push (double v, double alpha);
    void fly (double time);

    double get_time() const { return t; }
    double get_vx()   const { return vx; }
    double get_vy()   const { return vy; }
    double get_x()    const { return x; }
    double get_y()    const { return y; }

    void set_time (double time) { t = time; } // +validation
    void set_vx   (double vx_)  { vx = vx_; } // +validation
    void set_vy   (double vy_)  { vy = vy_; } // +validation
    void set_x    (double x_)   { x = x_; }   // +validation
    void set_y    (double y_)   { y = y_; }   // +validation

    static unsigned int get_count() { return ball_count; }

    int do_it (float a, int b) const {
        std::cout << "do_it with a: " << a << ", and b: " << b << '\n';
        return 0;
    };

private:
    double t  = 0.0;
    double vx = 0.0;
    double vy = 0.0;
    double x  = 0.0;
    double y  = 0.0;

private:
    static unsigned int ball_count;

    void update_ball_count() const {
        ++ball_count;
    }
};

unsigned int ball::ball_count = 0;

typedef int (ball::*do_it_ptr)(float, int) const;
// using do_it_ptr = int (ball::*)(float, int) const;

int main()
{
    do_it_ptr ptr = &ball::do_it;
    ball b1; std::cout << "ball_count: " << ball::get_count() << '\n';

    (b1.*ptr)(1.0, 2);

    ball b2; std::cout << "ball_count: " << ball::get_count() << '\n';

    return 0;
}

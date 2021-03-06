// unit_test.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "../tween.hpp"

#define test(exp) printf(#exp " = %f\n", exp)

int main()
{
    test(tween::linear(0.0f, 1.0f, 0.5f));

    test(tween::quad::in(0.0f, 1.0f, 0.5f));
    test(tween::quad::out(0.0f, 1.0f, 0.5f));
    test(tween::quad::inout(0.0f, 1.0f, 0.5f));

    test(tween::cubic::in(0.0f, 1.0f, 0.5f));
    test(tween::cubic::out(0.0f, 1.0f, 0.5f));
    test(tween::cubic::inout(0.0f, 1.0f, 0.5f));

    test(tween::quart::in(0.0f, 1.0f, 0.5f));
    test(tween::quart::out(0.0f, 1.0f, 0.5f));
    test(tween::quart::inout(0.0f, 1.0f, 0.5f));

    test(tween::quint::in(0.0f, 1.0f, 0.5f));
    test(tween::quint::out(0.0f, 1.0f, 0.5f));
    test(tween::quint::inout(0.0f, 1.0f, 0.5f));

    test(tween::sine::in(0.0f, 1.0f, 0.5f));
    test(tween::sine::out(0.0f, 1.0f, 0.5f));
    test(tween::sine::inout(0.0f, 1.0f, 0.5f));

    test(tween::expo::in(0.0f, 1.0f, 0.5f));
    test(tween::expo::out(0.0f, 1.0f, 0.5f));
    test(tween::expo::inout(0.0f, 1.0f, 0.5f));

    test(tween::circle::in(0.0f, 1.0f, 0.5f));
    test(tween::circle::out(0.0f, 1.0f, 0.5f));
    test(tween::circle::inout(0.0f, 1.0f, 0.5f));

    test(tween::elastic::in(0.0f, 1.0f, 0.5f));
    test(tween::elastic::out(0.0f, 1.0f, 0.5f));
    test(tween::elastic::inout(0.0f, 1.0f, 0.5f));

    test(tween::bounce::in(0.0f, 1.0f, 0.5f));
    test(tween::bounce::out(0.0f, 1.0f, 0.5f));
    test(tween::bounce::inout(0.0f, 1.0f, 0.5f));
    
    getchar();
    return 0;
}


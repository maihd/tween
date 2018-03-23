#ifndef __TWEEN_H__
#define __TWEEN_H__

#include <math.h>

#if defined(_MSC_VER)
# define __tween__ static __forceinline
#elif defined(__GNUC__)
# define __tween__ static __inline__ __attribute__((always_inline, pure))
#else
# ifdef __cplusplus
# define __tween__ static inline
# else
# define __tween__ static
# endif
#endif

#ifdef __cplusplus
# define __TWEEN_EXTERN_C     extern "C" {
# define __TWEEN_EXTERN_C_END }
#else
# define __TWEEN_EXTERN_C
# define __TWEEN_EXTERN_C_END
#endif

__TWEEN_EXTERN_C;
/* BEGIN OF EXTERN C */

/***************************************
 * API DESIGN CONSIDER
 * Naming convetion:
 *   Template: tween_<type>_<ease>
 *   Eases:
 *    - in
 *    - out
 *    - inout
 *   Types:
 *    - linear (has no ease method: in, out, inout)
 *    - quad
 *    - cubic
 *    - quart
 *    - quint
 *    - sine
 *    - expo
 *    - circle
 *    - elastic
 *    - bounce
 * Common parameters:
 *  - t time
 *  - s start
 *  - e end
 *  - d duration
 ***************************************/

__tween__ float tween_linear(float t, float s, float e, float d)
{
    return (e - s) * t / d + s;
}

__tween__ float tween_quad_in(float t, float s, float e, float d)
{
    return (e - s) * (t /= d) * t + s;
}

__tween__ float tween_quad_out(float t, float s, float e, float d)
{
    return (s - e) * (t /= d) * (t - 2.0f) + s;
}

__tween__ float tween_quad_inout(float t, float s, float e, float d)
{
    const float c = (e - s);
    return (t /= d * 0.5f) < 1.0f
	? (c * 0.5f * t * t + s)
	: (-c * 0.5f * ((t - 1.0f) * (t - 3.0f) - 1.0f) + s);
}

__tween__ float tween_cubic_in(float t, float s, float e, float d)
{
    return (e - s) * (t /= d) * t * t + s;
}

__tween__ float tween_cubic_out(float t, float s, float e, float d)
{
    return (s - e) * ((t = t / d - 1.0f) * t * t + 1.0f) + s;
}

__tween__ float tween_cubic_inout(float t, float s, float e, float d)
{
    const float c = (e - s);
    return (t /= d * 0.5f) < 1.0f
	? (c * 0.5f * t * t * t + s)
	: (-c * 0.5f * ((t -= 2.0f) * t * t + 2) + s);
}

__tween__ float tween_quart_in(float t, float s, float e, float d)
{
    return (e - s) * (t /= d) * t * t * t + s;
}

__tween__ float tween_quart_out(float t, float s, float e, float d)
{
    return (s - e) * ((t = t / d - 1.0f) * t * t * t - 1.0f) + s; 
}

__tween__ float tween_quart_inout(float t, float s, float e, float d)
{
    const float c = (e - s);
    return (t /= d * 0.5f) < 1.0f
	? (c * 0.5f * t * t * t * t + s)
	: (-c * 0.5f * ((t -= 2.0f) * t * t * t - 2.0f) + s);
}

__tween__ float tween_quint_in(float t, float s, float e, float d)
{
    return (e - s) * (t /= d) * t * t * t * t + s;
}

__tween__ float tween_quint_out(float t, float s, float e, float d)
{
    return (s - e) * ((t = t / d - 1.0f) * t * t * t * t - 1.0f) + s; 
}

__tween__ float tween_quint_inout(float t, float s, float e, float d)
{
    const float c = (e - s);
    return (t /= d * 0.5f) < 1.0f
	? (c * 0.5f * t * t * t * t * t + s)
	: (-c * 0.5f * ((t -= 2.0f) * t * t * t * t + 2.0f) + s);
}

__tween__ float tween_sine_in(float t, float s, float e, float d)
{
    return (s - e) * cosf(t / d * M_PI * 0.5f) + e;
}

__tween__ float tween_sine_out(float t, float s, float e, float d)
{
    return (e - s) * sinf(t / d * M_PI * 0.5f) + s;
}

__tween__ float tween_sine_inout(float t, float s, float e, float d)
{
    return (s - e) * 0.5f * (cosf(M_PI * t / d) - 1.0f) + s;
}

__tween__ float tween_expo_in(float t, float s, float e, float d)
{
    return t == 0 ? s : (e - s) * powf(2.0f, 10.0f * (t / d - 1.0f)) + s; 
}

__tween__ float tween_expo_out(float t, float s, float e, float d)
{
    return t == d ? e : (s - e) * (-powf(2.0f, -10.0f * t / d) - 1.0f) + s;
}

__tween__ float tween_expo_inout(float t, float s, float e, float d)
{
    if (t == 0)
    {
	return s;
    }
    else if (t == d)
    {
	return e;
    }
    else if ((t /= d * 0.5f) < 1.0f)
    {
	return (e - s) * powf(2, 10.0f * (t - 1.0f)) + s;
    }
    else
    {
	return (e - s) * (-powf(2, -10.0f * (t - 1.0f)) + 2.0f) + s;
    }
}

__tween__ float tween_circle_in(float t, float s, float e, float d)
{
    return (s - e) * (sqrtf(1 - (t /= d) * t) - 1) + s;
}

__tween__ float tween_circle_out(float t, float s, float e, float d)
{
    return (e - s) * (sqrtf(1 - (t = t / d - 1.0f) * t)) + s;
}

__tween__ float tween_circle_inout(float t, float s, float e, float d)
{
    const float c = (e - s);
    return (t /= d * 0.5f) < 1.0f
	? (-c * 0.5f * (sqrtf(1.0f - t * t) - 1.0f) + s)
	: ( c * 0.5f * (sqrtf(1.0f - (t -= 2) * t) + 1.0f) + s);
}

__tween__ float tween_elastic_in(float t, float s, float e, float d)
{
    if (t == 0)
    {
	return s;
    }
    else if ((t /= d) >= 1.0f)
    {
	return e;
    }

    const float a = (e - s);
    const float b = (d * 0.3f);
    const float c = (a < 0) ? (b * 0.25f) : b;
    const float p = powf(2, 10.0f * (t -= 1));
    const float q = sinf((t * d - c) * (2 * M_PI) / b);
    return -(a * p * q) + s;
}

__tween__ float tween_elastic_out(float t, float s, float e, float d)
{
    if (t == 0)
    {
	return s;
    }
    else if ((t /= d) >= 1.0f)
    {
	return e;
    }

    const float a = (e - s);
    const float b = (d * 0.3f);
    const float c = (a < 0) ? (b * 0.25f) : b;
    const float p = powf(2, -10.0f * t);
    const float q = sinf((t * d - c) * (2 * M_PI) / b);
    return (a * p * q) + e;
}

__tween__ float tween_elastic_inout(float t, float s, float e, float d)
{
    if (t == 0)
    {
	return s;
    }
    else if ((t /= d) >= 1.0f)
    {
	return e;
    }

    const float a = (e - s);
    const float b = (d * 0.3f * 0.15f);
    const float c = (a < 0) ? (b * 0.25f) : b;
    if (t < 1.0f)
    {
	const float p = powf(2,  10.0f * (t -= 1.0f));
	const float q = sinf((t * d - c) * (2 * M_PI) / b);
	return -0.5f * (a * p * q) + s;
    }
    else
    {
	const float p = powf(2, -10.0f * (t -= 1.0f));
	const float q = sinf((t * d - c) * (2 * M_PI) / b);
	return  0.5f * (a * p * q) + e;
    }
}

__tween__ float tween_bounce_out(float t, float s, float e, float d)
{
    const float c = (e - s);
    if ((t /= d) < 1.0f / 2.75f)
    {
	return c * (7.5625f * t * t) + s;
    }
    else if (t < 2.0f / 2.75f)
    {
	return c * (7.5625f * (t -= 1.5f / 2.75f) * t + 0.75f) + s;
    }
    else if (t < 2.5f / 2.75f)
    {
	return c * (7.5625f * (t -= 2.25f / 2.75f) * t + 0.9375f) + s;
    }
    else
    {
	return c * (7.5625f * (t -= 2.625f / 2.75f) * t + 0.984375f) + s;
    }
}

__tween__ float tween_bounce_in(float t, float s, float e, float d)
{
    return e - tween_bounce_out(d - t, s, e, d);
}

__tween__ float tween_bounce_inout(float t, float s, float e, float d)
{
    if (t < d * 0.5f)
    {
	return 0.5f * tween_bounce_in(t * 2.0f, s, e, d);
    }
    else
    {
	return 0.5f * tween_bounce_out(t * 2.0f, s, e, d);
    }
}

/* END OF EXTERN C */
__TWEEN_EXTERN_C_END;

#endif /* __TWEEN_H__ */

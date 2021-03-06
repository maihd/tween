#ifndef __TWEEN_HPP__
#define __TWEEN_HPP__

/***********************************************************
 * API DESIGN CONSIDER
 * BEGIN
 *   Template: 
 *    - Main:      value_t tween::<type>::<ease>(value_t s, value_t e, float t)
 *    - Extension: value_t tween::<type>::<ease>(value_t s, value_t e, float t, float d)
 * 
 *   Parameters:
 *    - s: start value
 *    - e: end   value
 *    - t: delta time in 3 parameters version, total time in 4 parameters version
 *    - d: delta time (available only in 4 parameters version)
 * 
 *   Value types:
 *    - int   : less useful than float
 *    - float : mainly support
 *    - vec2  : extensions, require vmath
 *    - vec3  : extensions, require vmath
 * 
 *   Eases:
 *    - in
 *    - out
 *    - inout
 * 
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
 * END
 * 
 * References:
 *  - vmath: https://github.com/maihd/vmath.git
 ***********************************************************/

#ifndef __cplusplus
#error "This version require C++"
#endif

#include <math.h>

#ifndef __tween__
#  if defined(_MSC_VER)
#    define __tween__ static __forceinline
#  elif defined(__GNUC__)
#    define __tween__ static __inline__ __attribute__((always_inline))
#  else
#    ifdef __cplusplus
#    define __tween__ static inline
#    else
#    define __tween__ static
#    endif
#  endif
#endif /* __tween__ */      

#ifndef PI
#define PI 3.14159265358979f
#endif

namespace tween
{
    __tween__ float linear(float s, float e, float t)
    {
        return s + (e - s) * t;
    }

    __tween__ float linear(float s, float e, float t, float d)
    {
        return linear(s, e, t / d);
    }

    namespace quad 
    {   
        __tween__ float in(float s, float e, float t)
        {
            return s + (e - s) * t * t;
        }

        __tween__ float out(float s, float e, float t)
        {
            return s + (s - e) * t * (t - 2.0f);
        }

        __tween__ float inout(float s, float e, float t)
        {
            return (t *= 2.0f) < 1.0f
                ? s + (e - s) * 0.5f * t * t
                : s + (s - e) * 0.5f * ((t -= 1.0f) * (t - 2.0f) - 1.0f);
        }

        __tween__ float in(float s, float e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ float out(float s, float e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ float inout(float s, float e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }

    namespace cubic
    {
        __tween__ float in(float s, float e, float t)
        {
            return s + (e - s) * t * t * t;
        }

        __tween__ float out(float s, float e, float t)
        {
            return s + (e - s) * ((t -= 1.0f) * t * t + 1.0f);
        }

        __tween__ float inout(float s, float e, float t)
        {
            return (t *= 2.0f) < 1.0f
                ? s + (e - s) * 0.5f * t * t * t
                : s + (e - s) * 0.5f * ((t -= 2.0f) * t * t + 2.0f);
        }

        __tween__ float in(float s, float e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ float out(float s, float e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ float inout(float s, float e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }

    namespace quart
    {
        __tween__ float in(float s, float e, float t)
        {
            return s + (e - s) * t * t * t * t;
        }

        __tween__ float out(float s, float e, float t)
        {
            return s + (s - e) * ((t -= 1.0f) * t * t * t - 1.0f);
        }

        __tween__ float inout(float s, float e, float t)
        {
            return (t *= 2.0f) < 1.0f
                ? s + (e - s) * 0.5f * t * t * t * t
                : s + (s - e) * 0.5f * ((t -= 2.0f) * t * t * t - 2.0f);
        }

        __tween__ float in(float s, float e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ float out(float s, float e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ float inout(float s, float e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }

    namespace quint
    {
        __tween__ float in(float s, float e, float t)
        {
            return s + (e - s) * t * t * t * t * t;
        }

        __tween__ float out(float s, float e, float t)
        {
            return s + (e - s) * ((t -= 1.0f) * t * t * t * t + 1.0f);
        }

        __tween__ float inout(float s, float e, float t)
        {
            return (t *= 2.0f) < 1.0f
                ? s + (e - s) * 0.5f * t * t * t * t * t
                : s + (e - s) * 0.5f * ((t -= 2.0f) * t * t * t * t + 2.0f);
        }

        __tween__ float in(float s, float e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ float out(float s, float e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ float inout(float s, float e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }

    namespace sine
    {
        __tween__ float in(float s, float e, float t)
        {
            return e + (s - e) * cosf(t * PI * 0.5f);
        }

        __tween__ float out(float s, float e, float t)
        {
            return s + (e - s) * sinf(t * PI * 0.5f);
        }

        __tween__ float inout(float s, float e, float t)
        {
            return s + (s - e) * 0.5f * (cosf(t * PI) - 1.0f);
        }

        __tween__ float in(float s, float e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ float out(float s, float e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ float inout(float s, float e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }

    namespace expo
    {
        __tween__ float in(float s, float e, float t)
        {
            return t <= 0.0f ? s : s + (e - s) * powf(2.0f, 10.0f * (t - 1.0f));
        }

        __tween__ float out(float s, float e, float t)
        {
            return t >= 1.0f ? e : s + (e - s) * (1.0f - powf(2.0f, -10.0f * t));
        }

        __tween__ float inout(float s, float e, float t)
        {
            if (t <= 0.0f) return s;
            if (t >= 1.0f) return e;
            
            return t < 0.5f
                ? in(s, s + (e - s) * 0.5f, t * 2.0f)
                : out(s + (e - s) * 0.5f, e, (t - 0.5f) * 2.0f);
        }

        __tween__ float in(float s, float e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ float out(float s, float e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ float inout(float s, float e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }

    namespace circle
    {
        __tween__ float in(float s, float e, float t)
        {
            return s + (s - e) * (sqrtf(1.0f - t * t) - 1.0f);
        }

        __tween__ float out(float s, float e, float t)
        {
            return s + (e - s) * (sqrtf(1.0f - (t - 1.0f) * (t - 1.0f)));
        }

        __tween__ float inout(float s, float e, float t)
        {
            return (t *= 2.0f) < 1.0f
                ? s + (s - e) * 0.5f * (sqrtf(1.0f - t * t) - 1.0f)
                : s + (e - s) * 0.5f * (sqrtf(1.0f - (t - 2.0f) * (t - 2.0f)) + 1.0f);
        }

        __tween__ float in(float s, float e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ float out(float s, float e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ float inout(float s, float e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }

    namespace elastic
    {
        __tween__ float in(float s, float e, float t)
        {
            if (t <= 0.0f) return s;
            if (t >= 1.0f) return e;

            const float a = (e - s);
            const float b = 0.3f;
            const float c = (a < 0) ? (b * 0.25f) : b;
            const float p = powf(2, 10.0f * (t -= 1.0f));
            const float q = sinf((t - c) * (2 * PI) / b);
            return s - (a * p * q);
        }

        __tween__ float out(float s, float e, float t)
        {
            if (t <= 0.0f) return s;
            if (t >= 1.0f) return e;

            const float a = (e - s);
            const float b = 0.3f;
            const float c = (a < 0) ? (b * 0.25f) : b;
            const float p = powf(2, -10.0f * t);
            const float q = sinf((t - c) * (2.0f * PI) / b);
            return e + (a * p * q);
        }

        __tween__ float inout(float s, float e, float t)
        {
            if (t <= 0.0f) return s;
            if (t >= 1.0f) return e;

            const float a = (e - s);
            const float b = 0.3f * 0.15f;
            const float c = (a < 0) ? (b * 0.25f) : b;
            if (t < 1.0f)
            {
                const float p = powf(2, 10.0f * (t -= 1.0f));
                const float q = sinf((t - c) * (2.0f * PI) / b);
                return s - 0.5f * (a * p * q);
            }
            else
            {
                const float p = powf(2, -10.0f * (t -= 1.0f));
                const float q = sinf((t - c) * (2.0f * PI) / b);
                return e + 0.5f * (a * p * q);
            }
        }

        __tween__ float in(float s, float e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ float out(float s, float e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ float inout(float s, float e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }

    namespace bounce
    {
        __tween__ float out(float s, float e, float t);
        __tween__ float in(float s, float e, float t)
        {
            return e - out(s, e, 1.0f - t);
        }

        __tween__ float out(float s, float e, float t)
        {
            const float c = (e - s);
            if (t < 1.0f / 2.75f)
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

        __tween__ float inout(float s, float e, float t)
        {
            return t < 0.5f
                ? in(s, s + (e - s) * 0.5f, t * 2.0f)
                : out(s + (e - s) * 0.5f, e, (t - 0.5f) * 2.0f);
        }

        __tween__ float in(float s, float e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ float out(float s, float e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ float inout(float s, float e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }
}
#endif

#if defined(__VMATH_H__) && !defined(__TWEEN_VMATH__)
#define __TWEEN_VMATH__
namespace tween
{
    __tween__ vec2_t linear(vec2_t s, vec2_t e, float t)
    {
        vec2_t r;
        r.x = linear(s.x, e.x, t);
        r.y = linear(s.y, e.y, t);
        return r;
    }

    __tween__ vec3_t linear(vec3_t s, vec3_t e, float t)
    {
        vec3_t r;
        r.x = linear(s.x, e.x, t);
        r.y = linear(s.y, e.y, t);
        r.z = linear(s.z, e.z, t);
        return r;
    }

    __tween__ vec2_t linear(vec2_t s, vec2_t e, float t, float d)
    {
        return linear(s, e, t / d);
    }

    __tween__ vec3_t linear(vec3_t s, vec3_t e, float t, float d)
    {
        return linear(s, e, t / d);
    }

    namespace quad
    {
        __tween__ vec2_t in(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            r.z = in(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            r.z = out(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            r.z = inout(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t in(vec2_t s, vec2_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }

    namespace cubic
    {
        __tween__ vec2_t in(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            r.z = in(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            r.z = out(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            r.z = inout(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t in(vec2_t s, vec2_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }

    namespace quart
    {
        __tween__ vec2_t in(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            r.z = in(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            r.z = out(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            r.z = inout(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t in(vec2_t s, vec2_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }

    namespace quint
    {
        __tween__ vec2_t in(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            r.z = in(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            r.z = out(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            r.z = inout(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t in(vec2_t s, vec2_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }

    namespace sine
    {
        __tween__ vec2_t in(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            r.z = in(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            r.z = out(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            r.z = inout(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t in(vec2_t s, vec2_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }

    namespace expo
    {
        __tween__ vec2_t in(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            r.z = in(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            r.z = out(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            r.z = inout(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t in(vec2_t s, vec2_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }

    namespace circle
    {
        __tween__ vec2_t in(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            r.z = in(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            r.z = out(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            r.z = inout(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t in(vec2_t s, vec2_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }

    namespace elastic
    {
        __tween__ vec2_t in(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            r.z = in(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            r.z = out(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            r.z = inout(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t in(vec2_t s, vec2_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }

    namespace bounce
    {
        __tween__ vec2_t in(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = in(s.x, e.x, t);
            r.y = in(s.y, e.y, t);
            r.z = in(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = out(s.x, e.x, t);
            r.y = out(s.y, e.y, t);
            r.z = out(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t)
        {
            vec2_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            return r;
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t)
        {
            vec3_t r;
            r.x = inout(s.x, e.x, t);
            r.y = inout(s.y, e.y, t);
            r.z = inout(s.z, e.z, t);
            return r;
        }

        __tween__ vec2_t in(vec2_t s, vec2_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec3_t in(vec3_t s, vec3_t e, float t, float d)
        {
            return in(s, e, t / d);
        }

        __tween__ vec2_t out(vec2_t s, vec2_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec3_t out(vec3_t s, vec3_t e, float t, float d)
        {
            return out(s, e, t / d);
        }

        __tween__ vec2_t inout(vec2_t s, vec2_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }

        __tween__ vec3_t inout(vec3_t s, vec3_t e, float t, float d)
        {
            return inout(s, e, t / d);
        }
    }
}
#endif /* __VMATH_H__ */
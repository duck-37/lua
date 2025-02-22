/*
** $Id: vector_extensions.hpp $
**
** Vector-specific extensions to the glm API:
**  1. API-completing functions, usually handling cases of functions without
**     genType or vec<1, genType> declarations;
**  2. Vector support for C99/C++11 <math> functions;
**  3. Functions emulated/ported from other popular vector-math libraries.
**
** See Copyright Notice in lua.h
*/
#ifndef __EXT_EXTENSION_VECTOR_HPP__
#define __EXT_EXTENSION_VECTOR_HPP__
#if !defined(GLM_ENABLE_EXPERIMENTAL)
  #define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glm/glm.hpp>
#include <glm/gtc/packing.hpp>
#include <glm/gtc/color_space.hpp>
#include <glm/gtx/orthonormalize.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtx/spline.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace glm {

  /// <summary>
  /// Unit vectors
  /// </summary>
  namespace unit {
    template<typename T, qualifier Q = defaultp>
    GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> right() {
      return vec<3, T, Q>(T(1), T(0), T(0));
    }

    template<typename T, qualifier Q = defaultp>
    GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> up() {
      return vec<3, T, Q>(
#if defined(GLM_FORCE_Z_UP)
        T(0), T(0), T(1)
#else
        T(0), T(1), T(0)
#endif
      );
    }

    template<typename T, qualifier Q = defaultp>
    GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> forwardLH() {
      return vec<3, T, Q>(
#if defined(GLM_FORCE_Z_UP)
        T(0), T(-1), T(0)
#else
        T(0), T(0), T(1)
#endif
      );
    }

    template<typename T, qualifier Q = defaultp>
    GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> forwardRH() {
      return vec<3, T, Q>(
#if defined(GLM_FORCE_Z_UP)
        T(0), T(1), T(0)
#else
        T(0), T(0), T(-1)
#endif
      );
    }

    template<typename T, qualifier Q = defaultp>
    GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> forward() {
#if defined(GLM_FORCE_LEFT_HANDED)
      return forwardLH<T, Q>();
#else
      return forwardRH<T, Q>();
#endif
    }
  };

  /* glm::all(glm::equal(...)) shorthand ; @TODO Optimize */

  template<typename genIUType>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool equal(genIUType x, genIUType y) {
    return x == y;
  }

  template<typename T>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool all_equal(T const &x, T const &y) {
    return glm::equal(x, y);
  }

  template<typename T>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool all_equal(T const &x, T const &y, T eps) {
    return glm::equal(x, y, eps);
  }

  template<typename T>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool all_equal(T const &x, T const &y, int MaxULPs) {
    return glm::equal(x, y, MaxULPs);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool all_equal(vec<L, T, Q> const &x, vec<L, T, Q> const &y) {
    return glm::all(glm::equal(x, y));
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool all_equal(vec<L, T, Q> const &x, vec<L, T, Q> const &y, T eps) {
    return glm::all(glm::equal(x, y, eps));
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool all_equal(vec<L, T, Q> const &x, vec<L, T, Q> const &y, int MaxULPs) {
    return glm::all(glm::equal(x, y, MaxULPs));
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool all_equal(vec<L, T, Q> const &x, vec<L, T, Q> const &y, vec<L, T, Q> const &eps) {
    return glm::all(glm::equal(x, y, eps));
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool all_equal(vec<L, T, Q> const &x, vec<L, T, Q> const &y, vec<L, int, Q> const &MaxULPs) {
    return glm::all(glm::equal(x, y, MaxULPs));
  }

  /* glm::any(glm::notEqual(...)) shorthand ; @TODO Optimize */

  template<typename genIUType>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool notEqual(genIUType x, genIUType y) {
    return x != y;
  }

  template<typename T>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_notequal(T const &x, T const &y) {
    return glm::notEqual(x, y);
  }

  template<typename T>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_notequal(T const &x, T const &y, T eps) {
    return glm::notEqual(x, y, eps);
  }

  template<typename T>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_notequal(T const &x, T const &y, int MaxULPs) {
    return glm::notEqual(x, y, MaxULPs);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_notequal(vec<L, T, Q> const &x, vec<L, T, Q> const &y) {
    return glm::any(glm::notEqual(x, y));
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_notequal(vec<L, T, Q> const &x, vec<L, T, Q> const &y, T eps) {
    return glm::any(glm::notEqual(x, y, eps));
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_notequal(vec<L, T, Q> const &x, vec<L, T, Q> const &y, int MaxULPs) {
    return glm::any(glm::notEqual(x, y, MaxULPs));
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_notequal(vec<L, T, Q> const &x, vec<L, T, Q> const &y, vec<L, T, Q> const &eps) {
    return glm::any(glm::notEqual(x, y, eps));
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_notequal(vec<L, T, Q> const &x, vec<L, T, Q> const &y, vec<L, int, Q> const &MaxULPs) {
    return glm::any(glm::notEqual(x, y, MaxULPs));
  }

  /* glm::any(glm::isinf(...)) shorthand */

  template<typename T>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_isinf(const T &x) {
    return glm::isinf(x);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_isinf(const vec<L, T, Q> &x) {
    return glm::any(glm::isinf(x));
  }

  /* glm::any(glm::isnan(...)) shorthand */

  template<typename T>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_isnan(const T &x) {
    return glm::isnan(x);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_isnan(const vec<L, T, Q> &x) {
    return glm::any(glm::isnan(x));
  }

  /* The other useful sign() implementation: where >= 0 returns +1 */

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> signP(const vec<L, T, Q> &x) {
    return vec<L, T, Q>(glm::lessThanEqual(vec<L, T, Q>(0), x)) - vec<L, T, Q>(glm::lessThan(x, vec<L, T, Q>(0)));
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType signP(genType v) {
    return (v >= 0) ? genType(1) : genType(-1);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> signN(const vec<L, T, Q> &x) {
    return vec<L, T, Q>(glm::lessThan(vec<L, T, Q>(0), x)) - vec<L, T, Q>(glm::lessThanEqual(x, vec<L, T, Q>(0)));
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType signN(genType v) {
    return (v > 0) ? genType(1) : genType(-1);
  }

  /* Numeric extensions */

  /// <summary>
  /// Return true if all vector elements are identical/equal.
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER bool isUniform(vec<L, T, Q> const &v) {
    bool result = true;
    for (length_t i = 1; i < L; ++i)  // @TODO: detail::compute_isuniform_vector
      result &= (v[i] == v[0]);
    return result;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER bool isUniform(genType v) {
    ((void)v);
    return true;
  }

  /// <summary>
  /// Reverse the elements of a vector
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> reverse(vec<L, T, Q> const &v) {
    vec<L, T, Q> result;
    for (length_t i = 0; i < L; ++i)  // @TODO: detail::compute_reverse_vector
      result[i] = v[L - i - 1];
    return result;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType reverse(genType v) {
    return v;
  }

  /// <summary>
  /// calculate sin and cos simultaneously.
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER void sincos(vec<L, T, Q> const &v, vec<L, T, Q> &s, vec<L, T, Q> &c) {
    s = sin(v);
    c = cos(v);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER void sincos(genType v, genType &s, genType &c) {
    s = sin(v);
    c = cos(v);
  }

  /// <summary>
  /// Return a copy of the vector "v" with its length clamped to "maxLength"
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> clampLength(const vec<L, T, Q> &v, T maxLength) {
    return (length2(v) > (maxLength * maxLength)) ? (normalize(v) * maxLength) : v;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType clampLength(genType x, genType maxLength) {
    return clampLength(vec<1, genType>(x), maxLength).x;
  }

  /// <summary>
  /// Scales the length of vector "v" to "newLength".
  ///
  /// @TODO: Follow GLM design and introduce:
  ///   detail::scale_length<L, T, Q, detail::is_aligned<Q>::value>::call(v)
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> scaleLength(const vec<L, T, Q> &v, T newLength) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'scaleLength' only accept floating-point inputs");

    const T sqlen = length2(v);
    if (sqlen < epsilon<T>()) {
      vec<L, T, Q> result(T(0));
      result[0] = newLength;
      return result;
    }
    return v * (newLength / sqrt(sqlen));
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType scaleLength(genType x, genType newLength) {
    return scaleLength(vec<1, genType>(x), newLength).x;
  }

  /// <summary>
  /// Return true if two vectors are perpendicular to each other.
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER bool isPerpendicular(const vec<L, T, Q> &v, const vec<L, T, Q> &other, T epsSq = epsilon<T>()) {
    const T d = dot(v, other);
    return d * d <= epsSq * length2(v) * length2(other);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER bool isPerpendicular(genType x, genType y, genType eps = epsilon<genType>()) {
    return isPerpendicular(vec<1, genType>(x), vec<1, genType>(y), eps);
  }

  /// <summary>
  /// Return a normalized (direction) vector that is perpendicular to "v" and
  /// the provided "hint" vectors. If "v" points towards "hint", then "hint2" is
  /// used as a fall-back.
  /// </summary>
  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<3, T, Q> perpendicular(const vec<3, T, Q> &v, const vec<3, T, Q> &hint = unit::forward<T, Q>(), const vec<3, T, Q> &hint2 = unit::up<T, Q>()) {
    const vec<3, T, Q> v2 = cross(v, hint);
    return epsilonEqual(dot(v2, v2), T(0), epsilon<T>()) ? hint2 : normalize(v2);
  }

  /// <summary>
  /// Return a vector that is perpendicular to "v" and the vector returned by
  /// glm::perpendicular.
  /// </summary>
  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<3, T, Q> perpendicular2(const vec<3, T, Q> &v, const vec<3, T, Q> &hint = unit::forward<T, Q>(), const vec<3, T, Q> &hint2 = unit::up<T, Q>()) {
    return normalize(cross(v, perpendicular(v, hint, hint2)));
  }

  /// <summary>
  /// Computes two vectors "out" and "out2" that are orthogonal to "v" and to
  /// each other.
  /// </summary>
  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER void perpendicularBasis(const vec<3, T, Q> &v, vec<3, T, Q> &out, vec<3, T, Q> &out2) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'perpendicularBasis' only accept floating-point inputs");
    const T s = v.z >= T(0) ? T(1) : T(-1);
    const T a = T(-1) / (s + v.z);
    const T b = v.x * v.y * a;

    out = vec<3, T, Q>(T(1) + s * v.x * v.x * a, s * b, -s * v.x);
    out2 = vec<3, T, Q>(b, s + v.y * v.y * a, -v.y);
  }

  /// <summary>
  /// From_Z
  /// </summary>
  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<3, T, Q> perpendicularFast(const vec<3, T, Q> &v) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'perpendicularFast' only accept floating-point inputs");
    if (abs(v.z) > one_over_root_two<T>()) {  // YZ Plane
      const T k = 1 / sqrt(v.y * v.y + v.z * v.z);
      return vec<3, T, Q>(T(0), -v.z * k, v.y * k);
    }
    else {  // XY Plane
      const T k = 1 / sqrt(v.x * v.x + v.y * v.y);
      return vec<3, T, Q>(-v.y * k, v.x * k, T(0));
    }
  }

  /// <summary>
  /// Make the vectors normalized and orthogonal to one another
  ///
  /// A mutable glm::orthonormalize implementation.
  /// </summary>
  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER void orthonormalize2(vec<3, T, Q> &x, vec<3, T, Q> &y) {
    x = normalize(x);
    y = glm::orthonormalize(y, x);
  }

  /// <summary>
  /// Make the vectors normalized and orthogonal to one another
  /// </summary>
  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER void orthonormalize3(vec<3, T, Q> &x, vec<3, T, Q> &y, vec<3, T, Q> &z) {
    x = normalize(x);
    y = orthonormalize(y, x);

    const T dot0 = dot(x, z);
    const T dot1 = dot(y, z);
    z = normalize(z - (y * dot1 + x * dot0));
  }

  /// <summary>
  /// glm::proj with the assumption "Normal" is already normalized.
  /// </summary>
  template<typename genType>
  GLM_FUNC_QUALIFIER genType projNorm(genType const &x, genType const &Normal) {
    return glm::dot(x, Normal) * Normal;
  }

  /// <summary>
  /// Project a vector onto this plane defined by its normal orthogonal
  /// </summary>
  template<typename genType>
  GLM_FUNC_QUALIFIER genType projPlane(genType const &x, genType const &Normal) {
    return x - glm::proj(x, Normal);
  }

  /// <summary>
  /// Breaks this vector down into parallel and perpendicular components with respect to the given direction
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER void projDecompose(const vec<L, T, Q> &v, const vec<L, T, Q> &direction, vec<L, T, Q> &outParallel, vec<L, T, Q> &outPerpendicular) {
    outParallel = proj(v, direction);
    outPerpendicular = v - outParallel;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER void projDecompose(genType v, genType direction, genType &outParallel, genType &outPerpendicular) {
    vec<1, genType> vParallel, vPerpendicular;
    projDecompose(vec<1, genType>(v), vec<1, genType>(direction), vParallel, vPerpendicular);

    outParallel = vParallel.x;
    outPerpendicular = vPerpendicular.x;
  }

  /// <summary>
  /// Return true if the three given points are collinear, i.e., lie on the same line.
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER bool areCollinear(const vec<L, T, Q> &p1, const vec<L, T, Q> &p2, const vec<L, T, Q> &p3, T epsSq = epsilon<T>()) {
    return length2(cross(p2 - p1, p3 - p1)) <= epsSq;
  }

  /// <summary>
  /// </summary>
  /// <param name="negativeSideRefractionIndex">Refraction index of material exiting</param>
  /// <param name="positiveSideRefractionIndex">Refraction index of material entering</param>
  /// <returns></returns>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> refract(vec<L, T, Q> const &I, vec<L, T, Q> const &N, T negativeSideRefractionIndex, T positiveSideRefractionIndex) {
    return refract(I, N, negativeSideRefractionIndex / positiveSideRefractionIndex);
  }

  /// <summary>
  /// Return a vector containing the Cartesian coordinates of a point specified
  /// in Barycentric (relative to a N-Dimensional triangle).
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> barycentric(const vec<L, T, Q> &value1, const vec<L, T, Q> &value2, const vec<L, T, Q> &value3, T amount1, T amount2) {
    return (value1 + (amount1 * (value2 - value1))) + (amount2 * (value3 - value1));
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType barycentric(genType value1, genType value2, genType value3, genType amount1, genType amount2) {
    return barycentric(vec<1, genType>(value1), vec<1, genType>(value2), vec<1, genType>(value3), amount1, amount2).x;
  }

  /// <summary>
  /// A implementation of glm::angle that's numerically stable at all angles.
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER T angle_atan(const vec<L, T, Q> &x, const vec<L, T, Q> &y) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'angle' only accept floating-point inputs");
    const vec<L, T, Q> xyl = x * length(y);
    const vec<L, T, Q> yxl = y * length(x);
    const T n = length(xyl - yxl);
    if (epsilonNotEqual(n, T(0), epsilon<T>()))
      return T(2) * atan2<T, Q>(n, length(xyl + yxl));
    return T(0);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType angle_atan(const genType &x, const genType &y) {
    return angle<genType>(x, y);
  }

  /// <summary>
  /// Generalized slerp implementation
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> _slerp(vec<L, T, Q> const &x, vec<L, T, Q> const &y, T const &a) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'slerp' only accept floating-point inputs");

    // Perform a linear interpolation when CosAlpha is close to 1 to avoid side
    // effect of sin(angle) becoming a zero denominator
    const T CosAlpha = dot(x, y);
    if (CosAlpha > static_cast<T>(1) - epsilon<T>())
      return mix(x, y, a);

    const T Alpha = acos(CosAlpha);  // get angle (0 -> pi)
    const T SinAlpha = sin(Alpha);  // get sine of angle between vectors (0 -> 1)
    const T t1 = sin((static_cast<T>(1) - a) * Alpha) / SinAlpha;
    const T t2 = sin(a * Alpha) / SinAlpha;
    return x * t1 + y * t2;
  }

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER qua<T, Q> _slerp(qua<T, Q> const &x, qua<T, Q> const &y, T const &a) {
    return slerp(x, y, a);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType _slerp(genType x, genType y, genType a) {
    return _slerp(vec<1, genType>(x), vec<1, genType>(y), a).x;
  }

  /// <summary>
  /// Generalized closestPointOnLine implementation
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> closestPointOnLine(vec<L, T, Q> const &point, vec<L, T, Q> const &a, vec<L, T, Q> const &b) {
    const T LineLength = distance(a, b);
    const vec<L, T, Q> Vector = point - a;
    const vec<L, T, Q> LineDirection = (b - a) / LineLength;

    const T Distance = dot(Vector, LineDirection);
    if (Distance <= T(0))
      return a;
    if (Distance >= LineLength)
      return b;
    return a + LineDirection * Distance;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType closestPointOnLine(genType point, genType a, genType b) {
    return closestPointOnLine(vec<1, genType>(point), vec<1, genType>(a), vec<1, genType>(b)).x;
  }

  /// <summary>
  /// Loops "t", so that it is never greater than "length" and less than zero.
  ///
  /// Note: This function is an emulation of: Unity.Mathf.Repeat
  /// </summary>
  template<typename genType>
  GLM_FUNC_QUALIFIER genType loopRepeat(genType t, genType length) {
    return clamp(t - floor(t / length) * length, genType(0), length);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> loopRepeat(const vec<L, T, Q> &t, const vec<L, T, Q> &length) {
    return clamp(t - floor(t / length) * length, vec<L, T, Q>(0), length);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> loopRepeat(const vec<L, T, Q> &t, T length) {
    return loopRepeat(t, vec<L, T, Q>(length));
  }

  /// <summary>
  /// Return the shortest difference between two angles (radians)
  /// </summary>
  template<typename genType>
  GLM_FUNC_QUALIFIER genType deltaAngle(genType a, genType b) {
    const genType dt = loopRepeat((b - a), two_pi<genType>());
    return min(two_pi<genType>() - dt, dt);
  }

  /// <summary>
  /// A lerp implementation that ensures values interpolate correctly when they wrap around two-pi.
  ///
  /// Note: This function is an emulation of: Unity.Mathf.LerpAngle
  /// </summary>
  template<typename genType>
  GLM_FUNC_QUALIFIER genType lerpAngle(genType a, genType b, genType t) {
    GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'lerpAngle' only accept floating-point inputs");

    const genType dt = loopRepeat((b - a), two_pi<genType>());
    return lerp(a, a + (dt > pi<genType>() ? dt - two_pi<genType>() : dt), t);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> lerpAngle(const vec<L, T, Q> &x, const vec<L, T, Q> &y, T t) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'lerpAngle' only accept floating-point inputs");

    vec<L, T, Q> Result(T(0));
    for (length_t i = 0; i < L; ++i)  // @TODO: detail::compute_mixangle_vector
      Result[i] = lerpAngle<T>(x[i], y[i], t);
    return Result;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> lerpAngle(const vec<L, T, Q> &x, const vec<L, T, Q> &y, const vec<L, T, Q> &t) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'lerpAngle' only accept floating-point inputs");

    vec<L, T, Q> Result(T(0));
    for (length_t i = 0; i < L; ++i)  // @TODO: detail::compute_mixangle_vector
      Result[i] = lerpAngle<T>(x[i], y[i], t[i]);
    return Result;
  }

  /// <summary>
  /// Returns a value that will increment and decrement between the value 0 and length.
  ///
  /// Note: This function is an emulation of: Unity.Mathf.PingPong
  /// </summary>
  template<typename genType>
  GLM_FUNC_QUALIFIER genType pingPong(genType t, genType length) {
    t = loopRepeat(t, length * genType(2));
    return length - abs(t - length);
  }

  /// <summary>
  /// Return a position between two points, moving no further than maxDist.
  ///
  /// Note: This function is an emulation of: Unity.Vector3.MoveTowards
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> moveTowards(const vec<L, T, Q> &current, const vec<L, T, Q> &target, T maxDist) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'moveTowards' only accept floating-point inputs");

    const vec<L, T, Q> delta = target - current;
    const T sqdist = dot(delta, delta);
    if (epsilonEqual(sqdist, T(0), epsilon<T>()) || (maxDist >= 0 && sqdist <= maxDist * maxDist))
      return target;

    return current + (delta / (sqrt(sqdist) * maxDist));
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType moveTowards(genType current, genType target, genType maxDist) {
    GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'moveTowards' only accept floating-point inputs");
    if (abs(target - current) <= maxDist)
      return target;

    return current + sign(target - current) * maxDist;
  }

  /// <summary>
  /// Return a rotation between two directions, rotating no further than maxRadians.
  ///
  /// Note: This function is an emulation of: Unity.Vector3.RotateTowards
  /// </summary>
  /// <param name="current">Current direction</param>
  /// <param name="target">Desired direction</param>
  /// <param name="maxRadians">Maximum rotation (in radians) allowed for the rotation</param>
  /// <param name="maxLength">Maximum change in vector length for the rotation</param>
  /// <returns></returns>
  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<3, T, Q> rotateTowards(const vec<3, T, Q> &current, const vec<3, T, Q> &target, T maxRadians, T maxLength) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'rotateTowards' only accept floating-point inputs");

    const T eps = epsilon<T>();
    const T targetLen = length(target);
    const T currentLen = length(current);
    if (currentLen > eps && targetLen > eps) {
      const vec<3, T, Q> currentDir = current / currentLen;
      const vec<3, T, Q> targetDir = target / targetLen;
      const T d = dot(currentDir, targetDir);
      if (d <= (T(1.0) - eps)) {
        T delta = targetLen - currentLen;
        if (delta > T(0))
          delta = currentLen + min(delta, maxLength);
        else
          delta = currentLen - min(delta, maxLength);

        qua<T, Q> q;
        if (d < -(T(1.0) - eps))
          q = angleAxis(maxRadians, perpendicularFast(currentDir));
        else
          q = angleAxis(min(maxRadians, acos(d)), perpendicular(currentDir, targetDir));

        return q * currentDir * delta;
      }
    }

    return moveTowards(current, target, maxLength);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType rotateTowards(genType current, genType target, genType maxRadians, genType maxLength) {
    return rotateTowards(vec<1, genType>(current), vec<1, genType>(target), maxRadians, maxLength).x;
  }

  /// <summary>
  /// Changes an entities position towards a desired position over time.
  ///
  /// Note: This function is an emulation of: Unity.Vector3.SmoothDamp
  /// </summary>
  /// <param name="current">Current position</param>
  /// <param name="target">Desired position</param>
  /// <param name="currentVelocity">The current velocity of the entity</param>
  /// <param name="smoothTime">An approximation of the time it will take to reach the desired position</param>
  /// <param name="maxSpeed">Maximum entity speed.</param>
  /// <param name="deltaTime">Change in time</param>
  /// <returns></returns>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> smoothDamp(const vec<L, T, Q> &current, const vec<L, T, Q> &target, vec<L, T, Q> &currentVelocity, T smoothTime, T maxSpeed, T deltaTime) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'smoothDamp' only accept floating-point inputs");
    smoothTime = max(epsilon<T>(), smoothTime);
    vec<L, T, Q> deltaDist = (current - target);
    const T maxDist = maxSpeed * smoothTime;
    const T sqrDist = dot(deltaDist, deltaDist);

    const T o = T(2.0) / smoothTime;
    const T x = o * deltaTime;
    const T exp = T(1) / (T(1) + x + (T(0.48) * x * x) + (T(0.235) * x * x * x));
    if (sqrDist > (maxDist * maxDist))  // clamp maximum distance
      deltaDist = (deltaDist / sqrt(sqrDist)) * maxDist;

    const vec<L, T, Q> t = (currentVelocity + o * deltaDist) * deltaTime;
    vec<L, T, Q> output = (current - deltaDist) + ((deltaDist + t) * exp);

    currentVelocity = (currentVelocity - o * t) * exp;
    if (dot(target - current, output - target) > 0) {  // prevent overshoot
      currentVelocity = vec<L, T, Q>(T(0));
      output = target;
    }

    return output;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType smoothDamp(genType current, genType target, genType &currentVelocity, genType smoothTime, genType maxSpeed, genType deltaTime) {
    vec<1, genType> cv(currentVelocity);
    const vec<1, genType> result = smoothDamp(vec<1, genType>(current), vec<1, genType>(target), cv, smoothTime, maxSpeed, deltaTime);
    currentVelocity = cv.x;
    return result.x;
  }

  /// <summary>
  /// Note: Mouse coordinates must be scaled to: [-1, 1].
  /// </summary>
  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<3, T, Q> rayPicking(const vec<3, T, Q> &cam_direction, const vec<3, T, Q> &cam_up, T fov, T aspectRatio, T zNear, T zFar, T mouseX, T mouseY) {
    const mat<4, 4, T, Q> proj = perspective(fov, aspectRatio, zNear, zFar);
    const mat<4, 4, T, Q> view = lookAt(vec<3, T, Q>(T(0)), cam_direction, cam_up);
    const mat<4, 4, T, Q> invVP = inverse(proj * view);
    const vec<4, T, Q> screenPos = vec<4, T, Q>(mouseX, -mouseY, T(1), T(1));
    const vec<4, T, Q> worldPos = invVP * screenPos;
    return normalize(vec<3, T, Q>(worldPos));  // Direction of the ray; originating at the camera position.
  }

  /* Functions with additional integral type support. */

  template<typename T>
  GLM_FUNC_QUALIFIER typename std::enable_if<std::is_integral<T>::value, T>::type iceil(T x) {
    return x;
  }

  template<typename T>
  GLM_FUNC_QUALIFIER typename std::enable_if<std::is_integral<T>::value, T>::type ifloor(T x) {
    return x;
  }

  template<typename T>
  GLM_FUNC_QUALIFIER typename std::enable_if<std::is_floating_point<T>::value, T>::type iceil(T x) {
    return ceil(x);
  }

  template<typename T>
  GLM_FUNC_QUALIFIER typename std::enable_if<std::is_floating_point<T>::value, T>::type ifloor(T x) {
    return floor(x);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER typename std::enable_if<std::is_integral<T>::value, vec<L, T, Q>>::type iceil(vec<L, T, Q> const &x) {
    return x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER typename std::enable_if<std::is_integral<T>::value, vec<L, T, Q>>::type ifloor(vec<L, T, Q> const &x) {
    return x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER typename std::enable_if<!std::is_integral<T>::value, vec<L, T, Q>>::type iceil(vec<L, T, Q> const &x) {
    return ceil(x);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER typename std::enable_if<!std::is_integral<T>::value, vec<L, T, Q>>::type ifloor(vec<L, T, Q> const &x) {
    return floor(x);
  }

  template<typename T>
  GLM_FUNC_QUALIFIER typename std::enable_if<std::is_integral<T>::value && std::is_signed<T>::value, T>::type imod(T x, T y) {
    if (y == T(0))
      return T(0);  // attempt to perform 'n % 0'
    return ((x % y) + y) % y;
  }

  template<typename T>
  GLM_FUNC_QUALIFIER typename std::enable_if<std::is_integral<T>::value && !std::is_signed<T>::value, T>::type imod(T x, T y) {
    return x - y * (x / y);
  }

  template<typename T>
  GLM_FUNC_QUALIFIER typename std::enable_if<std::is_floating_point<T>::value, T>::type imod(T x, T y) {
    return mod(x, y);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> imod(vec<L, T, Q> const &x, T y) {
    return mod(x, y);  // @TODO: Handle modulo-zero for integer vectors.
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> imod(vec<L, T, Q> const &x, vec<L, T, Q> const &y) {
    return mod(x, y);  // @TODO: Handle modulo-zero for integer vectors.
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> pow(vec<L, T, Q> const &base, T exponent) {
    return pow(base, vec<L, T, Q>(exponent));
  }

  template<typename T>
  GLM_FUNC_QUALIFIER typename std::enable_if<std::is_integral<T>::value, T>::type pow(T x, uint y) {
    if (y == T(0))
      return x >= T(0) ? T(1) : T(-1);

    T result = x;
    for (unsigned i = 1; i < y; ++i)
      result *= x;
    return result;
  }

  /* Missing implicit genType support. */

  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any(bool b) {
    return b;
  }

  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool all(bool b) {
    return b;
  }

  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool not_(bool b) {
    return !b;
  }

  template<typename genIUType>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool lessThan(genIUType x, genIUType y) {
    return x < y;
  }

  template<typename genIUType>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool lessThanEqual(genIUType x, genIUType y) {
    return x <= y;
  }

  template<typename genIUType>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool greaterThan(genIUType x, genIUType y) {
    return x > y;
  }

  template<typename genIUType>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool greaterThanEqual(genIUType x, genIUType y) {
    return x >= y;
  }

  template<typename genIUType>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR genIUType compAdd(genIUType v) {
    return v;
  }

  template<typename genIUType>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR genIUType compMul(genIUType v) {
    return v;
  }

  template<typename genIUType>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR genIUType compMin(genIUType v) {
    return v;
  }

  template<typename genIUType>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR genIUType compMax(genIUType v) {
    return v;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType atan2(genType x, genType y) {
    return atan(x, y);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType normalize(genType x) {
    return normalize(vec<1, genType>(x)).x;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER bool isNormalized(genType x, genType eps = epsilon<genType>()) {
    return isNormalized(vec<1, genType>(x), eps);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER bool isNull(genType x, genType eps = epsilon<genType>()) {
    return isNull(vec<1, genType>(x), eps);
  }

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<1, bool, Q> isCompNull(vec<1, T, Q> const &v, T eps = epsilon<T>) {
    return vec<1, bool, Q>(abs(v.x) < eps);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER bool isCompNull(genType v, genType eps = epsilon<genType>()) {
    return abs(v) < eps;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER bool areOrthonormal(genType v0, genType v1, genType eps = epsilon<genType>()) {
    return areOrthonormal(vec<1, genType>(v0), vec<1, genType>(v1), eps);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER bool areOrthogonal(genType v0, genType v1, genType eps = epsilon<genType>()) {
    return areOrthogonal(vec<1, genType>(v0), vec<1, genType>(v1), eps);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType normalizeDot(genType x, genType y) {
    return normalizeDot(vec<1, genType>(x), vec<1, genType>(y));
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType fastNormalizeDot(genType x, genType y) {
    return fastNormalizeDot(vec<1, genType>(x), vec<1, genType>(y));
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType saturate(genType x) {
    return clamp(x, genType(0), genType(1));
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER bool openBounded(genType Value, genType Min, genType Max) {
    return openBounded(vec<1, genType>(Value), vec<1, genType>(Min), vec<1, genType>(Max)).x;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER bool closeBounded(genType Value, genType Min, genType Max) {
    return closeBounded(vec<1, genType>(Value), vec<1, genType>(Min), vec<1, genType>(Max)).x;
  }

  GLM_FUNC_QUALIFIER uint16 packHalf(float v) {
    return packHalf<1, defaultp>(vec<1, float>(v)).x;
  }

  GLM_FUNC_QUALIFIER float unpackHalf(uint16 v) {
    return unpackHalf<1, defaultp>(vec<1, uint16>(v)).x;
  }

  template<typename uintType, typename floatType>
  GLM_FUNC_QUALIFIER uintType packUnorm(floatType v) {
    return packUnorm<uintType, 1, floatType, defaultp>(vec<1, floatType>(v)).x;
  }

  template<typename floatType, typename uintType>
  GLM_FUNC_QUALIFIER floatType unpackUnorm(uintType v) {
    return unpackUnorm<floatType, 1, uintType, defaultp>(vec<1, uintType>(v)).x;
  }

  template<typename intType, typename floatType>
  GLM_FUNC_QUALIFIER intType packSnorm(floatType v) {
    return packSnorm<intType, 1, floatType, defaultp>(vec<1, floatType>(v)).x;
  }

  template<typename floatType, typename intType>
  GLM_FUNC_QUALIFIER floatType unpackSnorm(intType v) {
    return unpackSnorm<floatType, 1, intType, defaultp>(vec<1, intType>(v)).x;
  }

  template<typename floatType, typename T>
  GLM_FUNC_QUALIFIER floatType compNormalize(T x) {
    return compNormalize<floatType>(vec<1, T>(x)).x;
  }

  template<typename T, typename floatType>
  GLM_FUNC_QUALIFIER T compScale(floatType x) {
    return compScale<T>(vec<1, floatType>(x)).x;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType catmullRom(genType v1, genType v2, genType v3, genType v4, genType s) {
    return catmullRom<vec<1, genType>>(vec<1, genType>(v1), vec<1, genType>(v2), vec<1, genType>(v3), vec<1, genType>(v4), s).x;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType hermite(genType v1, genType t1, genType v2, genType t2, genType s) {
    return hermite<vec<1, genType>>(vec<1, genType>(v1), vec<1, genType>(t1), vec<1, genType>(v2), vec<1, genType>(t2), s).x;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType cubic(genType v1, genType v2, genType v3, genType v4, genType s) {
    return cubic<vec<1, genType>>(vec<1, genType>(v1), vec<1, genType>(v2), vec<1, genType>(v3), vec<1, genType>(v4), s).x;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType convertLinearToSRGB(genType ColorLinear) {
    return convertLinearToSRGB(vec<1, genType>(ColorLinear)).x;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType convertLinearToSRGB(genType ColorLinear, genType Gamma) {
    return convertLinearToSRGB(vec<1, genType>(ColorLinear), Gamma).x;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType convertSRGBToLinear(genType ColorSRGB) {
    return convertSRGBToLinear(vec<1, genType>(ColorSRGB)).x;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType convertSRGBToLinear(genType ColorSRGB, genType Gamma) {
    return convertSRGBToLinear(vec<1, genType>(ColorSRGB), Gamma).x;
  }

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<1, T, Q> lerp(const vec<1, T, Q> &x, const vec<1, T, Q> &y, T a) {
    return mix(x, y, a);
  }

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<1, T, Q> lerp(const vec<1, T, Q> &x, const vec<1, T, Q> &y, const vec<1, T, Q> &a) {
    return mix(x, y, a);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType snap(const genType value, const genType step) {
    if (step != genType(0))
      return glm::floor((value / step) + genType(0.5)) * step;
    return value;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> snap(const vec<L, T, Q> &x, const vec<L, T, Q> &y) {
    return detail::functor2<vec, L, T, Q>::call(snap, x, y);
  }

  /// <summary>
  /// Inverse of each vector component
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, T, Q> inverse(const vec<L, T, Q> &x) {
    return vec<L, T, Q>(T(1)) / x;
  }

  template<typename T>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR T inverse(const T &x) {
    return T(1) / x;
  }

  /// <summary>
  /// Returns the normalized vector pointing to "y" from "x".
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, T, Q> direction(const vec<L, T, Q> &x, const vec<L, T, Q> &y) {
    return glm::normalize(y - x);
  }

  template<typename T>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR T direction(const T x, const T y) {
    return glm::normalize(y - x);
  }

  /* C++-11/C99 wrappers. */

#if GLM_HAS_CXX11_STL
  template<typename genType>
  GLM_FUNC_QUALIFIER genType copysign(genType x, genType y) {
    return copysign(vec<1, genType>(x), vec<1, genType>(y)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> copysign(vec<L, T, Q> const &v, vec<L, T, Q> const &v2) {
    return detail::functor2<vec, L, T, Q>::call(std::copysign, v, v2);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType cbrt(genType x) {
    return cbrt(vec<1, genType>(x)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> cbrt(vec<L, T, Q> const &v) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'cbrt' only accept floating-point inputs.");
    return detail::functor1<vec, L, T, T, Q>::call(std::cbrt, v);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType expm1(genType x) {
    return expm1(vec<1, genType>(x)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> expm1(vec<L, T, Q> const &v) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'expm1' only accept floating-point inputs.");
    return detail::functor1<vec, L, T, T, Q>::call(std::expm1, v);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType erf(genType x) {
    return erf(vec<1, genType>(x)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> erf(vec<L, T, Q> const &v) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'erf' only accept floating-point inputs.");
    return detail::functor1<vec, L, T, T, Q>::call(std::erf, v);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType erfc(genType x) {
    return erfc(vec<1, genType>(x)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> erfc(vec<L, T, Q> const &v) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'erfc' only accept floating-point inputs.");
    return detail::functor1<vec, L, T, T, Q>::call(std::erfc, v);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER int fpclassify(genType x) {
    return fpclassify(vec<1, genType>(x)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, int, Q> fpclassify(vec<L, T, Q> const &v) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'fpclassify' only accept floating-point inputs.");
    return detail::functor1<vec, L, int, T, Q>::call(std::fpclassify, v);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType fdim(genType x, genType y) {
    return fdim(vec<1, genType>(x), vec<1, genType>(y)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> fdim(vec<L, T, Q> const &v, vec<L, T, Q> const &v2) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'fdim' only accept floating-point inputs.");
    return detail::functor2<vec, L, T, Q>::call(std::fdim, v, v2);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType hypot(genType x, genType y) {
    return hypot(vec<1, genType>(x), vec<1, genType>(y)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> hypot(vec<L, T, Q> const &v, vec<L, T, Q> const &v2) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'hypot' only accept floating-point inputs.");
    return detail::functor2<vec, L, T, Q>::call(std::hypot, v, v2);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER bool isnormal(genType x) {
    return isnormal(vec<1, genType>(x)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, bool, Q> isnormal(vec<L, T, Q> const &v) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'isnormal' only accept floating-point inputs.");
    return detail::functor1<vec, L, bool, T, Q>::call(std::isnormal, v);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER bool isunordered(genType x, genType y) {
    return isunordered(vec<1, genType>(x), vec<1, genType>(y)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, bool, Q> isunordered(vec<L, T, Q> const &v, vec<L, T, Q> const &v2) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'isunordered' only accept floating-point inputs.");
    vec<L, bool, Q> Result(false);
    for (length_t i = 0; i < L; ++i)  // @TODO: detail::compute_isunordered_vector
      Result[i] = std::isunordered(v[i], v2[i]);
    return Result;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER int ilogb(genType x) {
    return ilogb(vec<1, genType>(x)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, int, Q> ilogb(vec<L, T, Q> const &v) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'ilogb' only accept floating-point inputs.");
    return detail::functor1<vec, L, int, T, Q>::call(std::ilogb, v);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType lgamma(genType x) {
    return lgamma(vec<1, genType>(x)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> lgamma(vec<L, T, Q> const &v) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'lgamma' only accept floating-point inputs.");
    return detail::functor1<vec, L, T, T, Q>::call(std::lgamma, v);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType log10(genType x) {
    return log10(vec<1, genType>(x)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> log10(vec<L, T, Q> const &v) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'log10' only accept floating-point inputs.");
    return detail::functor1<vec, L, T, T, Q>::call(std::log10, v);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType log1p(genType x) {
    return log1p(vec<1, genType>(x)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> log1p(vec<L, T, Q> const &v) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'log1p' only accept floating-point inputs.");
    return detail::functor1<vec, L, T, T, Q>::call(std::log1p, v);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType logb(genType x) {
    return logb(vec<1, genType>(x)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> logb(vec<L, T, Q> const &v) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'logb' only accept floating-point inputs.");
    return detail::functor1<vec, L, T, T, Q>::call(std::logb, v);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType nearbyint(genType x) {
    return nearbyint(vec<1, genType>(x)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> nearbyint(vec<L, T, Q> const &v) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'nearbyint' only accept floating-point inputs.");
    return detail::functor1<vec, L, T, T, Q>::call(std::nearbyint, v);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType nextafter(genType x, genType y) {
    return nextafter(vec<1, genType>(x), vec<1, genType>(y)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> nextafter(vec<L, T, Q> const &v, vec<L, T, Q> const &v2) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'nextafter' only accept floating-point inputs.");
    return detail::functor2<vec, L, T, Q>::call(std::nextafter, v, v2);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType remainder(genType x, genType y) {
    return remainder(vec<1, genType>(x), vec<1, genType>(y)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> remainder(vec<L, T, Q> const &v, vec<L, T, Q> const &v2) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'remainder' only accept floating-point inputs.");
    return detail::functor2<vec, L, T, Q>::call(std::remainder, v, v2);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType scalbn(genType x, int y) {
    return scalbn(vec<1, genType>(x), vec<1, int>(y)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> scalbn(vec<L, T, Q> const &v, vec<L, int, Q> const &v2) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'scalbn' only accept floating-point inputs.");
    vec<L, T, Q> Result(T(0));
    for (length_t i = 0; i < L; ++i)  // @TODO: detail::compute_scalebn_vector
      Result[i] = std::scalbn(v[i], v2[i]);
    return Result;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType tgamma(genType x) {
    return tgamma(vec<1, genType>(x)).x;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<L, T, Q> tgamma(vec<L, T, Q> const &v) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'tgamma' only accept floating-point inputs.");
    return detail::functor1<vec, L, T, T, Q>::call(std::tgamma, v);
  }
#endif

  /*
  ** {======================================================
  ** @TODO: These functions are generally not used in single-dimensional vector
  ** spaces and only exist to simplify the bindings.
  ** =======================================================
  */

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool areCollinear(vec<1, T, Q> const &v0, vec<1, T, Q> const &v1, T eps = epsilon<T>) {
    ((void)v0);
    ((void)v1);
    ((void)eps);
    return true;
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool areCollinear(genType v0, genType v1, genType eps = epsilon<genType>()) {
    ((void)v0);
    ((void)v1);
    ((void)eps);
    return true;
  }

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER T simplex(vec<1, T, Q> const &v) {
    ((void)v);
    return T(0);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType simplex(genType v) {
    return simplex(vec<1, genType>(v));
  }

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER T perlin(vec<1, T, Q> const &Position) {
    ((void)Position);
    return T(0);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType perlin(genType Position) {
    return perlin(vec<1, genType>(Position));
  }

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER T perlin(vec<1, T, Q> const &Position, vec<1, T, Q> const &rep) {
    ((void)Position);
    ((void)rep);
    return T(0);
  }

  template<typename genType>
  GLM_FUNC_QUALIFIER genType perlin(genType Position, genType rep) {
    return perlin(vec<1, genType>(Position), vec<1, genType>(rep));
  }

  template<typename T>
  GLM_FUNC_QUALIFIER bool intersectLineSphere(T const &point0, T const &point1, T const &sphereCenter, T sphereRadius,
  T &intersectionPoint1, T &intersectionNormal1, T &intersectionPoint2, T &intersectionNormal2) {
    ((void)point0);
    ((void)point1);
    ((void)sphereCenter);
    ((void)sphereRadius);
    intersectionNormal1 = intersectionPoint1 = T(0);
    intersectionPoint2 = intersectionNormal2 = T(0);
    return false;
  }

  template<typename T>
  GLM_FUNC_QUALIFIER bool intersectRayPlane(T const &orig, T const &dir, T const &planeOrig, T const &planeNormal, T &intersectionDistance) {
    ((void)orig);
    ((void)dir);
    ((void)planeOrig);
    ((void)planeNormal);
    intersectionDistance = T(0);
    return false;
  }

  template<typename T>
  GLM_FUNC_QUALIFIER bool intersectRaySphere(T const &rayStarting, T const &rayNormalizedDirection, T const &sphereCenter, const T sphereRadius, T &intersectionPosition, T &intersectionNormal) {
    ((void)rayStarting);
    ((void)rayNormalizedDirection);
    ((void)sphereCenter);
    ((void)sphereRadius);
    intersectionPosition = intersectionNormal = T(0);
    return false;
  }

  /* }====================================================== */
}

#endif

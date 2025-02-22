/*
** $Id: matrix_extensions.hpp $
**
** matrix-specific extensions to the glm API:
**  1. API-completing functions, often of the form of supporting mat<3, 4> and
**     mat<4, 3> matrices;
**  2. Functions emulated/ported from other popular vector-math libraries.
**
** See Copyright Notice in lua.h
*/
#ifndef __EXT_EXTENSION_MATRIX_HPP__
#define __EXT_EXTENSION_MATRIX_HPP__
#if !defined(GLM_ENABLE_EXPERIMENTAL)
  #define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/ext/matrix_relational.hpp>

namespace glm {

  /* glm::all(glm::equal(...)) shorthand */

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool all_equal(mat<C, R, T, Q> const &a, mat<C, R, T, Q> const &b) {
    return glm::all(glm::equal(a, b));
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool all_equal(mat<C, R, T, Q> const &a, mat<C, R, T, Q> const &b, T eps) {
    return glm::all(glm::equal(a, b, eps));
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool all_equal(mat<C, R, T, Q> const &a, mat<C, R, T, Q> const &b, vec<C, T, Q> const &eps) {
    return glm::all(glm::equal(a, b, eps));
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool all_equal(mat<C, R, T, Q> const &a, mat<C, R, T, Q> const &b, int MaxULPs) {
    return glm::all(glm::equal(a, b, MaxULPs));
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool all_equal(mat<C, R, T, Q> const &a, mat<C, R, T, Q> const &b, vec<C, int, Q> const &MaxULPs) {
    return glm::all(glm::equal(a, b, MaxULPs));
  }

  /* glm::any(glm::notEqual(...)) shorthand */

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_notequal(mat<C, R, T, Q> const &a, mat<C, R, T, Q> const &b) {
    return glm::any(glm::notEqual(a, b));
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_notequal(mat<C, R, T, Q> const &a, mat<C, R, T, Q> const &b, T eps) {
    return glm::any(glm::notEqual(a, b, eps));
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_notequal(mat<C, R, T, Q> const &a, mat<C, R, T, Q> const &b, vec<C, T, Q> const &eps) {
    return glm::any(glm::notEqual(a, b, eps));
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_notequal(mat<C, R, T, Q> const &a, mat<C, R, T, Q> const &b, int MaxULPs) {
    return glm::any(glm::notEqual(a, b, MaxULPs));
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any_notequal(mat<C, R, T, Q> const &a, mat<C, R, T, Q> const &b, vec<C, int, Q> const &MaxULPs) {
    return glm::any(glm::notEqual(a, b, MaxULPs));
  }

  /// <summary>
  /// Transforms the given point vector by this matrix M, i.e, returns: M * (x, y, z, 1).
  ///
  /// This function does not divide by w, or output it, so it cannot have a projection.
  /// </summary>
  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<3, T, Q> transformPos(const mat<C, R, T, Q> &m, const vec<3, T, Q> &v) {
    GLM_STATIC_ASSERT(C >= 4 && R >= 3, "invalid position transform");
    const typename mat<C, R, T, Q>::col_type &result = m * vec<4, T, Q>(v, T(1));
    return vec<3, T, Q>(result.x, result.y, result.z);
  }

  /// <summary>
  /// Functional operator*(matrix, vector) wrapper.
  /// </summary>
  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> transformPos(const mat<3, 3, T, Q> &m, const vec<3, T, Q> &v) {
    return operator*(m, v);
  }

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> transformPos(const mat<3, 4, T, Q> &m, const vec<3, T, Q> &v) {
    return operator*(m, v);
  }

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> transformPos(const qua<T, Q> &q, const vec<3, T, Q> &v) {
    return operator*(q, v);
  }

  /// <summary>
  /// Transforms a position by a mat4x4 with a perspective divide.
  /// </summary>
  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> transformPosPerspective(const mat<4, 4, T, Q> &m, const vec<3, T, Q> &v) {
    const vec<3, T, Q> res = transformPos(m, v);
    const T w = m[0].w * v.x + m[1].w * v.y + m[2].w * v.z + m[3].w;
    return res * (T(1) / w);
  }

  /// <summary>
  /// Transforms the given direction vector by this matrix m, i.e, returns
  /// M * (x, y, z, 0).
  ///
  /// This function does not divide by w or output it, it cannot have a projection
  /// </summary>
  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> transformDir(const mat<C, R, T, Q> &m, const vec<3, T, Q> &v) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3, "invalid direction transform");
    const typename mat<C, R, T, Q>::col_type result = m * vec<4, T, Q>(v, T(0));
    return vec<3, T, Q>(result.x, result.y, result.z);
  }

  /// <summary>
  /// API completeness for transformDir
  /// </summary>
  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> transformDir(const qua<T, Q> &q, const vec<3, T, Q> &v) {
    return q * v;
  }

  /// <summary>
  /// Return the scaling components of the matrix.
  /// </summary>
  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<3, T, Q> extractScale(const mat<3, 3, T, Q> &m) {
    return vec<3, T, Q>(length(m[0]), length(m[1]), length(m[2]));
  }

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<3, T, Q> extractScale(const qua<T, Q> &q) {
    return extractScale(toMat3(q));
  }

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<3, T, Q> extractScale(const mat<4, 3, T, Q> &m) {
    return vec<3, T, Q>(length(m[0]), length(m[1]), length(m[2]));
  }

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<3, T, Q> extractScale(const mat<3, 4, T, Q> &m) {
    return vec<3, T, Q>(
      length(vec<3, T, Q>(m[0].x, m[0].y, m[0].z)),
      length(vec<3, T, Q>(m[1].x, m[1].y, m[1].z)),
      length(vec<3, T, Q>(m[2].x, m[2].y, m[2].z))
    );
  }

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER vec<3, T, Q> extractScale(const mat<4, 4, T, Q> &m) {
    return vec<3, T, Q>(
      length(vec<3, T, Q>(m[0].x, m[0].y, m[0].z)),
      length(vec<3, T, Q>(m[1].x, m[1].y, m[1].z)),
      length(vec<3, T, Q>(m[2].x, m[2].y, m[2].z))
    );
  }

  /// <summary>
  /// Returns true if the matrix contains a "projective" part, i.e., the last
  /// row differs (up to an epsilon) of [0, 0, 0, 1].
  /// </summary>
  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER bool containsProjection(const mat<4, 4, T, Q> &m, T eps = epsilon<T>()) {
    const vec<4, T, Q> v = row(m, 3);
    return all(epsilonEqual(v, vec<4, T, Q>(T(0), T(0), T(0), T(1)), eps));
  }

  /// <summary>
  /// Returns true if the matrix contains only uniform scaling (up to a given
  /// epsilon).
  /// </summary>
  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER bool hasUniformScale(const mat<C, R, T, Q> &m, T eps = epsilon<T>()) {
    const vec<3, T, Q> scale = extractScale(m);
    return epsilonEqual(scale.x, scale.y, eps) && epsilonEqual(scale.x, scale.z, eps);
  }

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER bool hasUniformScale(const qua<T, Q> &q, T eps = epsilon<T>()) {
    return hasUniformScale(toMat3(q), eps);
  }

  /// <summary>
  /// Test if the matrix has an inverse (up to a given epsilon).
  /// </summary>
  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER bool invertible(const mat<C, R, T, Q> &m, T eps = epsilon<T>()) {
    GLM_STATIC_ASSERT(C == R, "Symmetric Matrices");
    return epsilonNotEqual(determinant(m), T(0), eps);
  }

  /// <summary>
  /// Create a matrix that mirrors the given plane normal.
  /// </summary>
  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER mat<C, R, T, Q> planeMirror(T x, T y, T z, T d = T(0)) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3, "invalid affine plane mirror");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'planeMirror' only accept floating-point inputs");

    mat<C, R, T, Q> m(T(0));
    m[0].x = T(1) - T(2) * x * x;
    m[0].y = T(-2) * x * y;
    m[0].z = T(-2) * x * z;
    m[1].x = T(-2) * y * x;
    m[1].y = T(1) - T(2) * y * y;
    m[1].z = T(-2) * y * z;
    m[2].x = T(-2) * z * x;
    m[2].y = T(-2) * y * z;
    m[2].z = T(1) - T(2) * z * z;
    GLM_IF_CONSTEXPR (C >= 4) {
      m[3].x = T(2) * d * x;
      m[3].y = T(2) * d * y;
      m[3].z = T(2) * d * z;
    }
    return m;
  }

  /// <summary>
  /// Create an affine transformation matrix that projects orthographically onto
  /// the provided plane.
  /// </summary>
  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER mat<C, R, T, Q> orthoProjection(T x, T y, T z, T d = T(0)) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3, "invalid affine plane projection");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'orthoProjection' only accept floating-point inputs");

    mat<C, R, T, Q> m(T(0));
    m[0].x = T(1) - x * x;
    m[0].y = -x * y;
    m[0].z = -x * z;
    m[1].x = -y * x;
    m[1].y = T(1) - y * y;
    m[1].z = -y * z;
    m[2].x = -z * x;
    m[2].y = -y * z;
    m[2].z = T(1) - z * z;
    GLM_IF_CONSTEXPR (C >= 4) {
      m[3].x = d * x;
      m[3].y = d * y;
      m[3].z = d * z;
    }
    return m;
  }

  /// <summary>
  /// Creates a translation, rotation and scaling matrix.
  /// </summary>
  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER mat<4, 4, T, Q> trs(const vec<3, T, Q> &translation, const qua<T, Q> &rotation, const vec<3, T, Q> &scale) {
    const mat<3, 3, T, Q> r = toMat3(rotation);
    return mat<4, 4, T, Q>(
      vec<4, T, Q>(r[0] * scale.x, T(0)),
      vec<4, T, Q>(r[1] * scale.y, T(0)),
      vec<4, T, Q>(r[2] * scale.z, T(0)),
      vec<4, T, Q>(translation, T(1))
    );
  }

  /// <summary>
  /// Create a right-handed rotation matrix for a given forward and up-vector.
  ///
  /// This function is intended to be the matrix equivalent of quatLookAtRH,
  /// i.e., the inverse to lookAtRH(eye, center, up).
  ///
  /// @NOTE: This function assumes the vectors are normalized and not collinear.
  /// </summary>
  template<typename T, qualifier Q, length_t C = 3, length_t R = 3>
  GLM_FUNC_QUALIFIER mat<C, R, T, Q> lookRotationRH(const vec<3, T, Q> &fwd, const vec<3, T, Q> &up) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'lookRotationRH' only accept floating-point inputs");

    const vec<3, T, Q> f = -fwd;
    const vec<3, T, Q> s(normalize(cross(up, f)));
    const vec<3, T, Q> u(cross(f, s));
    mat<C, R, T, Q> Result(1);
    Result[0] = s;
    Result[1] = u;
    Result[2] = f;
    GLM_IF_CONSTEXPR (C > 3) {
      Result[3].x = T(0);
      Result[3].y = T(0);
      Result[3].z = T(0);
    }
    return Result;
  }

  /// <summary>
  /// Create a left-handed rotation matrix for a given forward and up-vector.
  ///
  /// This function is intended to be the matrix equivalent of quatLookAtLH,
  /// i.e., the inverse to lookAtLH(eye, center, up).
  ///
  /// @NOTE: This function assumes the vectors are normalized and not collinear.
  /// </summary>
  template<typename T, qualifier Q, length_t C = 3, length_t R = 3>
  GLM_FUNC_QUALIFIER mat<C, R, T, Q> lookRotationLH(const vec<3, T, Q> &fwd, const vec<3, T, Q> &up) {
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'lookRotationLH' only accept floating-point inputs");

    const vec<3, T, Q> s(normalize(cross(up, fwd)));
    const vec<3, T, Q> u(cross(fwd, s));
    mat<C, R, T, Q> Result(1);
    Result[0] = s;
    Result[1] = u;
    Result[2] = fwd;
    GLM_IF_CONSTEXPR (C > 3) {
      Result[3].x = T(0);
      Result[3].y = T(0);
      Result[3].z = T(0);
    }
    return Result;
  }

  /// <summary>
  /// This function is intended to be the matrix equivalent of quatLookAt, i.e.,
  /// the inverse to lookAt(eye, center, up).
  /// </summary>
  template<typename T, qualifier Q, length_t C = 3, length_t R = 3>
  GLM_FUNC_QUALIFIER mat<C, R, T, Q> lookRotation(const vec<3, T, Q> &fwd, const vec<3, T, Q> &up) {
#if (GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT)
    return lookRotationLH<T, Q, C, R>(fwd, up);
#else
    return lookRotationRH<T, Q, C, R>(fwd, up);
#endif
  }

  /// <summary>
  /// Creates a right-handed spherical billboard that rotates around a specified
  /// object position.
  /// </summary>
  template<typename T, qualifier Q, length_t C = 3, length_t R = 3>
  GLM_FUNC_QUALIFIER mat<C, R, T, Q> billboardRH(const vec<3, T, Q> &object, const vec<3, T, Q> &camPos, const vec<3, T, Q> &camUp, const vec<3, T, Q> &camFwd) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3 && C == R, "invalid billboard matrix");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'billboardRH' only accept floating-point inputs");

    vec<3, T, Q> difference = object - camPos;
    const T lengthSq = length2(difference);
    if (epsilonEqual(lengthSq, T(0), epsilon<T>()))
      difference = -camFwd;
    else
      difference *= (T(1) / sqrt(lengthSq));

    const vec<3, T, Q> crossed = normalize(cross(camUp, difference));
    const vec<3, T, Q> fin = cross(difference, crossed);
    mat<C, R, T, Q> Result(1);
    Result[0].x = crossed.x;
    Result[1].x = crossed.y;
    Result[2].x = crossed.z;
    Result[0].y = fin.x;
    Result[1].y = fin.y;
    Result[2].y = fin.z;
    Result[0].z = difference.x;
    Result[1].z = difference.y;
    Result[2].z = difference.z;
    GLM_IF_CONSTEXPR (R > 3) {
      Result[0].x = object.x;
      Result[1].y = object.y;
      Result[2].z = object.z;
    }
    GLM_IF_CONSTEXPR (C > 3) {
      Result[3].x = T(0);
      Result[3].y = T(0);
      Result[3].z = T(0);
    }
    return Result;
  }

  /// <summary>
  /// Creates a left-handed spherical billboard that rotates around a specified
  /// object position.
  /// </summary>
  template<typename T, qualifier Q, length_t C = 3, length_t R = 3>
  GLM_FUNC_QUALIFIER mat<C, R, T, Q> billboardLH(const vec<3, T, Q> &object, const vec<3, T, Q> &camPos, const vec<3, T, Q> &camUp, const vec<3, T, Q> &camFwd) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3 && C == R, "invalid billboard matrix");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'billboardLH' only accept floating-point inputs");

    vec<3, T, Q> difference = camPos - object;
    const T lengthSq = length2(difference);
    if (epsilonEqual(lengthSq, T(0), epsilon<T>()))
      difference = -camFwd;
    else
      difference *= (T(1) / sqrt(lengthSq));

    const vec<3, T, Q> crossed = normalize(cross(camUp, difference));
    const vec<3, T, Q> fin = cross(difference, crossed);
    mat<C, R, T, Q> Result(1);
    Result[0].x = crossed.x;
    Result[1].x = crossed.y;
    Result[2].x = crossed.z;
    Result[0].y = fin.x;
    Result[1].y = fin.y;
    Result[2].y = fin.z;
    Result[0].z = difference.x;
    Result[1].z = difference.y;
    Result[2].z = difference.z;
    GLM_IF_CONSTEXPR (R > 3) {
      Result[0].x = object.x;
      Result[1].y = object.y;
      Result[2].z = object.z;
    }
    GLM_IF_CONSTEXPR (C > 3) {
      Result[3].x = T(0);
      Result[3].y = T(0);
      Result[3].z = T(0);
    }
    return Result;
  }

  template<typename T, qualifier Q, length_t C = 3, length_t R = 3>
  GLM_FUNC_QUALIFIER mat<C, R, T, Q> billboard(const vec<3, T, Q> &object, const vec<3, T, Q> &pos, const vec<3, T, Q> &up, const vec<3, T, Q> &forward) {
#if (GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT)
    return billboardLH<T, Q, C, R>(object, pos, up, forward);
#else
    return billboardRH<T, Q, C, R>(object, pos, up, forward);
#endif
  }

  /* EulerAngle Extraction for all matrices with rotation parts */

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_DECL void extractEulerAngleXYZ(mat<C, R, T, Q> const &M, T &t1, T &t2, T &t3) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3, "invalid extraction dimensions");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'extractEulerAngle' only accept floating-point inputs");

    const T T1 = glm::atan2<T, Q>(M[2][1], M[2][2]);
    const T C2 = glm::sqrt(M[0][0] * M[0][0] + M[1][0] * M[1][0]);
    const T T2 = glm::atan2<T, Q>(-M[2][0], C2);
    const T S1 = glm::sin(T1);
    const T C1 = glm::cos(T1);
    const T T3 = glm::atan2<T, Q>(S1 * M[0][2] - C1 * M[0][1], C1 * M[1][1] - S1 * M[1][2]);
    t1 = -T1;
    t2 = -T2;
    t3 = -T3;
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER void extractEulerAngleYXZ(mat<C, R, T, Q> const &M, T &t1, T &t2, T &t3) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3, "invalid extraction dimensions");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'extractEulerAngle' only accept floating-point inputs");

    const T T1 = glm::atan2<T, Q>(M[2][0], M[2][2]);
    const T C2 = glm::sqrt(M[0][1] * M[0][1] + M[1][1] * M[1][1]);
    const T T2 = glm::atan2<T, Q>(-M[2][1], C2);
    const T S1 = glm::sin(T1);
    const T C1 = glm::cos(T1);
    const T T3 = glm::atan2<T, Q>(S1 * M[1][2] - C1 * M[1][0], C1 * M[0][0] - S1 * M[0][2]);
    t1 = T1;
    t2 = T2;
    t3 = T3;
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER void extractEulerAngleXZX(mat<C, R, T, Q> const &M, T &t1, T &t2, T &t3) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3, "invalid extraction dimensions");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'extractEulerAngle' only accept floating-point inputs");

    const T T1 = glm::atan2<T, Q>(M[0][2], M[0][1]);
    const T S2 = glm::sqrt(M[1][0] * M[1][0] + M[2][0] * M[2][0]);
    const T T2 = glm::atan2<T, Q>(S2, M[0][0]);
    const T S1 = glm::sin(T1);
    const T C1 = glm::cos(T1);
    const T T3 = glm::atan2<T, Q>(C1 * M[1][2] - S1 * M[1][1], C1 * M[2][2] - S1 * M[2][1]);
    t1 = T1;
    t2 = T2;
    t3 = T3;
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER void extractEulerAngleXYX(mat<C, R, T, Q> const &M, T &t1, T &t2, T &t3) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3, "invalid extraction dimensions");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'extractEulerAngle' only accept floating-point inputs");

    const T T1 = glm::atan2<T, Q>(M[0][1], -M[0][2]);
    const T S2 = glm::sqrt(M[1][0] * M[1][0] + M[2][0] * M[2][0]);
    const T T2 = glm::atan2<T, Q>(S2, M[0][0]);
    const T S1 = glm::sin(T1);
    const T C1 = glm::cos(T1);
    const T T3 = glm::atan2<T, Q>(-C1 * M[2][1] - S1 * M[2][2], C1 * M[1][1] + S1 * M[1][2]);
    t1 = T1;
    t2 = T2;
    t3 = T3;
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER void extractEulerAngleYXY(mat<C, R, T, Q> const &M, T &t1, T &t2, T &t3) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3, "invalid extraction dimensions");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'extractEulerAngle' only accept floating-point inputs");

    const T T1 = glm::atan2<T, Q>(M[1][0], M[1][2]);
    const T S2 = glm::sqrt(M[0][1] * M[0][1] + M[2][1] * M[2][1]);
    const T T2 = glm::atan2<T, Q>(S2, M[1][1]);
    const T S1 = glm::sin(T1);
    const T C1 = glm::cos(T1);
    const T T3 = glm::atan2<T, Q>(C1 * M[2][0] - S1 * M[2][2], C1 * M[0][0] - S1 * M[0][2]);
    t1 = T1;
    t2 = T2;
    t3 = T3;
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER void extractEulerAngleYZY(mat<C, R, T, Q> const &M, T &t1, T &t2, T &t3) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3, "invalid extraction dimensions");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'extractEulerAngle' only accept floating-point inputs");

    const T T1 = glm::atan2<T, Q>(M[1][2], -M[1][0]);
    const T S2 = glm::sqrt(M[0][1] * M[0][1] + M[2][1] * M[2][1]);
    const T T2 = glm::atan2<T, Q>(S2, M[1][1]);
    const T S1 = glm::sin(T1);
    const T C1 = glm::cos(T1);
    const T T3 = glm::atan2<T, Q>(-S1 * M[0][0] - C1 * M[0][2], S1 * M[2][0] + C1 * M[2][2]);
    t1 = T1;
    t2 = T2;
    t3 = T3;
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER void extractEulerAngleZYZ(mat<C, R, T, Q> const &M, T &t1, T &t2, T &t3) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3, "invalid extraction dimensions");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'extractEulerAngle' only accept floating-point inputs");

    const T T1 = glm::atan2<T, Q>(M[2][1], M[2][0]);
    const T S2 = glm::sqrt(M[0][2] * M[0][2] + M[1][2] * M[1][2]);
    const T T2 = glm::atan2<T, Q>(S2, M[2][2]);
    const T S1 = glm::sin(T1);
    const T C1 = glm::cos(T1);
    const T T3 = glm::atan2<T, Q>(C1 * M[0][1] - S1 * M[0][0], C1 * M[1][1] - S1 * M[1][0]);
    t1 = T1;
    t2 = T2;
    t3 = T3;
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER void extractEulerAngleZXZ(mat<C, R, T, Q> const &M, T &t1, T &t2, T &t3) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3, "invalid extraction dimensions");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'extractEulerAngle' only accept floating-point inputs");

    const T T1 = glm::atan2<T, Q>(M[2][0], -M[2][1]);
    const T S2 = glm::sqrt(M[0][2] * M[0][2] + M[1][2] * M[1][2]);
    const T T2 = glm::atan2<T, Q>(S2, M[2][2]);
    const T S1 = glm::sin(T1);
    const T C1 = glm::cos(T1);
    const T T3 = glm::atan2<T, Q>(-C1 * M[1][0] - S1 * M[1][1], C1 * M[0][0] + S1 * M[0][1]);
    t1 = T1;
    t2 = T2;
    t3 = T3;
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER void extractEulerAngleXZY(mat<C, R, T, Q> const &M, T &t1, T &t2, T &t3) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3, "invalid extraction dimensions");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'extractEulerAngle' only accept floating-point inputs");

    const T T1 = glm::atan2<T, Q>(M[1][2], M[1][1]);
    const T C2 = glm::sqrt(M[0][0] * M[0][0] + M[2][0] * M[2][0]);
    const T T2 = glm::atan2<T, Q>(-M[1][0], C2);
    const T S1 = glm::sin(T1);
    const T C1 = glm::cos(T1);
    const T T3 = glm::atan2<T, Q>(S1 * M[0][1] - C1 * M[0][2], C1 * M[2][2] - S1 * M[2][1]);
    t1 = T1;
    t2 = T2;
    t3 = T3;
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER void extractEulerAngleYZX(mat<C, R, T, Q> const &M, T &t1, T &t2, T &t3) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3, "invalid extraction dimensions");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'extractEulerAngle' only accept floating-point inputs");

    const T T1 = glm::atan2<T, Q>(-M[0][2], M[0][0]);
    const T C2 = glm::sqrt(M[1][1] * M[1][1] + M[2][1] * M[2][1]);
    const T T2 = glm::atan2<T, Q>(M[0][1], C2);
    const T S1 = glm::sin(T1);
    const T C1 = glm::cos(T1);
    const T T3 = glm::atan2<T, Q>(S1 * M[1][0] + C1 * M[1][2], S1 * M[2][0] + C1 * M[2][2]);
    t1 = T1;
    t2 = T2;
    t3 = T3;
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER void extractEulerAngleZYX(mat<C, R, T, Q> const &M, T &t1, T &t2, T &t3) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3, "invalid extraction dimensions");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'extractEulerAngle' only accept floating-point inputs");

    const T T1 = glm::atan2<T, Q>(M[0][1], M[0][0]);
    const T C2 = glm::sqrt(M[1][2] * M[1][2] + M[2][2] * M[2][2]);
    const T T2 = glm::atan2<T, Q>(-M[0][2], C2);
    const T S1 = glm::sin(T1);
    const T C1 = glm::cos(T1);
    const T T3 = glm::atan2<T, Q>(S1 * M[2][0] - C1 * M[2][1], C1 * M[1][1] - S1 * M[1][0]);
    t1 = T1;
    t2 = T2;
    t3 = T3;
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER void extractEulerAngleZXY(mat<C, R, T, Q> const &M, T &t1, T &t2, T &t3) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3, "invalid extraction dimensions");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'extractEulerAngle' only accept floating-point inputs");

    const T T1 = glm::atan2<T, Q>(-M[1][0], M[1][1]);
    const T C2 = glm::sqrt(M[0][2] * M[0][2] + M[2][2] * M[2][2]);
    const T T2 = glm::atan2<T, Q>(M[1][2], C2);
    const T S1 = glm::sin(T1);
    const T C1 = glm::cos(T1);
    const T T3 = glm::atan2<T, Q>(C1 * M[2][0] + S1 * M[2][1], C1 * M[0][0] + S1 * M[0][1]);
    t1 = T1;
    t2 = T2;
    t3 = T3;
  }

  /* Fixes */

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER mat<4, 4, T, Q> _scaleBias(T scale, T bias) {
    mat<4, 4, T, Q> result(0);
    result[3] = vec<4, T, Q>(vec<3, T, Q>(bias), static_cast<T>(1));
    result[0][0] = scale;
    result[1][1] = scale;
    result[2][2] = scale;
    return result;
  }

  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER mat<4, 4, T, Q> _scaleBias(mat<4, 4, T, Q> const &m, T scale, T bias) {
    return m * _scaleBias<T, Q>(scale, bias);
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER bool _isNull(mat<C, R, T, Q> const &m, T eps = epsilon<T>) {
    bool result = true;
    for (length_t i = 0; i < C; ++i)
      result &= isNull(m[i], eps);
    return result;
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER bool _isNormalized(mat<C, R, T, Q> const &m, T eps = epsilon<T>) {
    bool result = true;
    for (length_t i = 0; i < C; ++i)
      result &= isNormalized(m[i], eps);

    for (length_t i = 0; i < R; ++i) {
      typename mat<C, R, T, Q>::row_type v(T(0));
      for (length_t j = 0; j < C; ++j)
        v[j] = m[j][i];

      result &= isNormalized(v, eps);
    }
    return result;
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER bool _isIdentity(mat<C, R, T, Q> const &m, T eps = epsilon<T>) {
    bool result = true;
    for (length_t i = 0; i < C; ++i) {
      for (length_t j = 0; j < R; ++j) {
        result &= ((i == j) ? (abs(m[i][j] - 1) <= eps) : (abs(m[i][j]) <= eps));
      }
    }
    return result;
  }

  /// <summary>
  /// @TODO
  /// </summary>
  template<typename T, qualifier Q>
  GLM_FUNC_QUALIFIER mat<2, 2, T, Q> affineInverse(mat<2, 2, T, Q> const &m) {
    return inverse(mat<2, 2, T, Q>(m));
  }

  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER mat<C, R, T, Q> rotateNormalizedAxis(mat<C, R, T, Q> const &m, T const &angle, vec<3, T, Q> const &v) {
    GLM_STATIC_ASSERT(C >= 3 && R >= 3, "invalid rotation matrix");
    GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'rotateNormalizedAxis' only accept floating-point inputs");

    const T a = angle;
    const T c = cos(a);
    const T s = sin(a);
    const vec<3, T, Q> axis(v);
    const vec<3, T, Q> temp((static_cast<T>(1) - c) * axis);

    mat<3, 3, T, Q> Rotate;
    Rotate[0].x = c + temp[0] * axis[0];
    Rotate[0].y = 0 + temp[0] * axis[1] + s * axis[2];
    Rotate[0].z = 0 + temp[0] * axis[2] - s * axis[1];
    Rotate[1].x = 0 + temp[1] * axis[0] - s * axis[2];
    Rotate[1].y = c + temp[1] * axis[1];
    Rotate[1].z = 0 + temp[1] * axis[2] + s * axis[0];
    Rotate[2].x = 0 + temp[2] * axis[0] + s * axis[1];
    Rotate[2].y = 0 + temp[2] * axis[1] - s * axis[0];
    Rotate[2].z = c + temp[2] * axis[2];

    mat<C, R, T, Q> Result;
    Result[0] = m[0] * Rotate[0].x + m[1] * Rotate[0].y + m[2] * Rotate[0].z;
    Result[1] = m[0] * Rotate[1].x + m[1] * Rotate[1].y + m[2] * Rotate[1].z;
    Result[2] = m[0] * Rotate[2].x + m[1] * Rotate[2].y + m[2] * Rotate[2].z;
    GLM_IF_CONSTEXPR (C > 3)
      Result[3] = m[3];
    return Result;
  }

#if defined(GLM_FORCE_DEFAULT_ALIGNED_GENTYPES)
  /// <summary>
  /// non-aligned implementation
  /// </summary>
  template<length_t C, length_t R, typename T, qualifier Q>
  GLM_FUNC_QUALIFIER mat<C, R, T, Q> __matrixCompMult(mat<C, R, T, Q> const &x, mat<C, R, T, Q> const &y) {
    return detail::compute_matrixCompMult<C, R, T, Q, false>::call(x, y);
  }

  /// <summary>
  /// non-aligned implementation
  /// </summary>
  template<length_t C, length_t R, typename T, typename U, qualifier Q>
  GLM_FUNC_QUALIFIER mat<C, R, T, Q> __mix(mat<C, R, T, Q> const &x, mat<C, R, T, Q> const &y, U a) {
    return mat<C, R, U, Q>(x) * (static_cast<U>(1) - a) + mat<C, R, U, Q>(y) * a;
  }

  template<length_t C, length_t R, typename T, typename U, qualifier Q>
  GLM_FUNC_QUALIFIER mat<C, R, T, Q> __mix(mat<C, R, T, Q> const &x, mat<C, R, T, Q> const &y, mat<C, R, U, Q> const &a) {
    return __matrixCompMult(mat<C, R, U, Q>(x), static_cast<U>(1) - a) + __matrixCompMult(mat<C, R, U, Q>(y), a);
  }
#endif
}

#endif

#ifndef __RAY_SPHERE_H_
#define __RAY_SPHERE_H_
/*
 * RaySphere.h
 *
 * Contains class definitions for a Ray and a Sphere class.
 *
 * Bryant Pong
 * 12/25/19
 */
#include "Tuple.h"
#include "Matrix.h"

#include <cfloat>
#include <cmath>
#include <cstdarg>
#include <limits>
#include <vector>

/**
 * @brief  Ray Class.
 */
class Ray {
public:
  /**
   * @brief Constructor
   * @param origin: Origin point of the ray
   * @param dir: Direction of the ray
   */
  Ray(const Tuple &origin, const Tuple &dir) :
    origin_(origin), dir_(dir) {
  }

  /**
   * @brief Destructor
   */
  ~Ray() {
  }

  /**
   * @brief Copy Constructor
   */
  Ray(const Ray &rhs) :
    origin_(rhs.origin_), dir_(rhs.dir_) {
  }

  /**
   * @brief Assignment operator=
   */  
  Ray &operator=(const Ray &rhs) {
    // Check for self-assignment:
    if (this != &rhs) {
      origin_ = rhs.origin_;
      dir_ = rhs.dir_;
    } 
    return *this;
  }

  // Accessor Functions
  inline Tuple Origin() const { return origin_; }
  inline Tuple Direction() const { return dir_; }

private:
  // A ray has an origin point and a direction
  Tuple origin_, dir_;
};

/**
 * @brief  Sphere class
 */
class Sphere {
public:
  /**
   * @brief  Default Constructor.  Sphere will be a unit sphere centered
   *         around the origin and with a radius of 1.0.  Default
   *         transformation is the 4x4 identity matrix.
   */
  Sphere() : origin_(Point(0, 0, 0)), 
             radius_(1.0),
             id_(GenerateUniqueID()),
             transform_(Identity(4)) {
  }

  /**
   * @brief  Destructor
   */
  ~Sphere() {
  }

  /**
   * @brief Copy Constructor 
   */
  Sphere(const Sphere &rhs) :
    origin_(rhs.origin_), 
    radius_(rhs.radius_),
    id_(rhs.id_),
    transform_(Identity(4)) {
  }

  /**
   * @brief Assignment operator =
   */
  Sphere &operator=(const Sphere &rhs) {
    // Check for self-assignment
    if (this != &rhs) {
      origin_    = rhs.origin_;
      radius_    = rhs.radius_;
      id_        = rhs.id_;
      transform_ = rhs.transform_;
    }
    return *this;
  }

  /**
   * @brief Comparison operator==
   */
  bool operator==(const Sphere &rhs) const {
    return IsEqual(radius_, rhs.radius_) &&
           (origin_ == rhs.origin_) &&
           (id_ == rhs.id_) &&
           (transform_ == rhs.transform_);
  }

  // Accessor functions
  inline Tuple Origin() const { return origin_; }
  inline float Radius() const { return radius_; }  
  inline int ID() const { return id_; }
  inline Matrix Transform() const { return transform_; }

  inline void SetTransform(const Matrix &trans) { transform_ = trans; }

private:
  // Floating comparison
  bool IsEqual(const float num1, const float num2) const {
    return std::fabs(num1 - num2) <= 0.0001;
  }

  // Helper function to generate a unique ID each time this is called
  inline int GenerateUniqueID() const {
    static int nextID = 0;
    ++nextID;
    return nextID - 1;
  }

  // A sphere is centered around an origin
  Tuple origin_;

  // Radius of the sphere
  float radius_;

  // ID of the sphere.  Must be unique
  int id_;

  // Transformation associated with the sphere
  Matrix transform_;
};

/**
 * @brief  Intersection class
 */
class Intersection {
public:
  /**
   * Constructor
   */
  Intersection(const float t, const Sphere &sp) :
    t_(t), object_(sp) {
  }

  /**
   * Destructor 
   */
  ~Intersection() {
  }

  /**
   * Copy Constructor
   */
  Intersection(const Intersection &rhs) :
    t_(rhs.t_), object_(rhs.object_) {
  }

  /**
   * Assignment operator=
   */
  Intersection &operator=(const Intersection &rhs) {
    // Check for self-assignment
    if (this != &rhs) {
      t_ = rhs.t_;
      object_ = rhs.object_;
    }
    return *this;
  }

  /**
   * Comparison operator==
   */
  bool operator==(const Intersection &rhs) const {
    return IsEqual(t_, rhs.t_) && (object_ == rhs.object_); 
  }

  // Accessors
  inline float T() const { return t_; }
  inline Sphere Object() const { return object_; }

private:
  // Helper to compare floating points
  bool IsEqual(const float num1, const float num2) const {
    return std::fabs(num1 - num2) <= 0.0001;
  }

  // An intersection tracks the distance t the intersections happens at
  float t_;

  // And the object the intersection hits
  Sphere object_; 
}; 

// Function Prototypes
Tuple Position(const Ray &, const float);
std::vector<Intersection> Intersect(const Sphere &, const Ray &);
std::vector<Intersection> Intersections(const int, ...);
Intersection Hit(const std::vector<Intersection> &);
Ray Transform(const Ray &, const Matrix &);

/**
 * @brief  Computes the point that lies on the ray
 *         at distance t away from the origin.
 * @param ray: Input ray
 * @param t: Distance away from origin
 * @return Tuple: Point that lies on the ray.
 */
Tuple Position(const Ray &ray, const float t) {
  return ray.Origin() + ray.Direction() * t;
}

/**
 * @brief  Computes intersections between the specified
 *         ray and sphere.
 * @param sphere: Input sphere
 * @param ray: Input ray
 * @return std::vector<Intersection>: Intersections at distance t from the ray's origin
 */
std::vector<Intersection> Intersect(const Sphere &sphere, const Ray &ray) {

  // Apply the sphere's transformation to the ray:
  const Ray RAY_T = Transform(ray, Inverse(sphere.Transform()));

  std::vector<Intersection> intersections;

  // Compute the discriminant to determine if the ray intersects the sphere
  const Tuple SPHERE_TO_RAY = RAY_T.Origin() - Point(0, 0, 0);
  const float A = Dot(RAY_T.Direction(), RAY_T.Direction());
  const float B = 2 * Dot(RAY_T.Direction(), SPHERE_TO_RAY);
  const float C = Dot(SPHERE_TO_RAY, SPHERE_TO_RAY) - 1;

  const float DISCRIMINANT = (B*B) - (4*A*C);

  /*
   * If the discriminant < 0, no intersections
   *                     = 0, one intersection
   *                     > 0, two intersections
   */
  if (DISCRIMINANT >= 0.0) {
    // For one intersection, duplicate it:
    const float INTER1 = (-B - sqrt(DISCRIMINANT))/(2*A);
    const float INTER2 = (-B + sqrt(DISCRIMINANT))/(2*A);

    const Intersection IS1(INTER1, sphere);
    const Intersection IS2(INTER2, sphere);

    // Push intersections in increasing order:
    if (INTER1 < INTER2) {
      intersections = Intersections(2, IS1, IS2);
    } else {
      intersections = Intersections(2, IS2, IS1);
    }
  }

  return intersections;
}

/**
 * @brief  Collects any number of intersection objects
 *         into a std::vector.
 */
std::vector<Intersection> Intersections(const int numArgs, ...) {
  std::vector<Intersection> inters;

  va_list vaList;
  va_start(vaList, numArgs);
  for (int i = 0; i < numArgs; ++i) {
    inters.push_back(va_arg(vaList, Intersection));
  }
  va_end(vaList);

  return inters;
}

/**
 * @brief  Computes which intersection will be the first one
 *         to hit the object.
 */
Intersection Hit(const std::vector<Intersection> &intersects) {
  // If no hits found, return an Intersection with FLT_MAX
  Intersection hit(FLT_MAX, Sphere());

  float smallestT = FLT_MAX;

  // Iterate through all intersections
  for (size_t i = 0; i < intersects.size(); ++i) {
    // The hit is the intersection with the smallest positive t_ value 
    if (intersects[i].T() >= 0.0 && intersects[i].T() < smallestT) {
      smallestT = intersects[i].T();
      hit = intersects[i];
    }
  }

  return hit; 
} 

/**
 * @brief  Applies the transformation matrix to the specified ray.
 */
Ray Transform(const Ray &ray, const Matrix &transform) {
  // Apply transformation to both the ray's origin and direction:
  const Tuple TRANSFORMED_ORIGIN    = transform * ray.Origin();
  const Tuple TRANSFORMED_DIRECTION = transform * ray.Direction();  

  return Ray(TRANSFORMED_ORIGIN, TRANSFORMED_DIRECTION);
}
#endif
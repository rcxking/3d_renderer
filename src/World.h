#ifndef __WORLD_H_
#define __WORLD_H_
/*
 * World.h
 *
 * Class implementation of a World object that keeps track of objects and
 * light sources.
 *
 * Bryant Pong
 * 12/29/19
 */
#include "RaySphere.h"
#include "PointLight.h"

#include <set>

class World {
public:
  /**
   * @brief Default Constructor
   */
  World() : lightP_(nullptr) {
  }

  /**
   * @brief Destructor
   */
  ~World() {
    // Delete allocated memory (if applicable)
    if (lightP_) {
      delete lightP_;
      lightP_ = nullptr;
    }
  }

  /**
   * @brief Copy Constructor
   */
  World(const World &rhs) :
    objects_(rhs.objects_),
    lightP_(rhs.lightP_) {
  }

  /**
   * @brief Assignment operator=
   */
  World &operator=(const World &rhs) {
    // Check for self-assignment
    if (this != &rhs) {
      objects_ = rhs.objects_;
      lightP_  = rhs.lightP_;
    }
    return *this;
  } 

  /**
   * @brief Checks if this world contains the specified sphere.   
   */
  bool Contains(const Sphere &sphere) const {
    return (objects_.find(sphere) != objects_.end()); 
  } 

  // Modifiers
  inline void SetLightSource(const PointLight &pl) {
    // Allocate memory if needed
    if (!lightP_) {
      lightP_ = new PointLight(pl);
    }

    *lightP_ = pl; 
  }

  // Accessors
  inline std::set<Sphere> GetObjects() const { return objects_; }
  inline PointLight *GetLightSource() const { return lightP_; }
  inline bool HasLightSource() const { return (lightP_ != nullptr); } 

private:
  // A World tracks a collection of objects
  std::set<Sphere> objects_;

  // Light Source
  PointLight *lightP_; 
};

// Function Prototypes
World DefaultWorld();

/**
 * @brief Creates a default world with two spheres. 
 */
World DefaultWorld() {
  World w;
  // Create default light source
  w.SetLightSource(PointLight(Point(-10, 10, -10), Color(1.0, 1.0, 1.0)));
  return World();
}

#endif

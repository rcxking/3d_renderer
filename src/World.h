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

#include <vector>

class World {
public:
  /**
   * @brief Default Constructor
   */
  World() : lightP_(NULL) {
  }

  /**
   * @brief Destructor
   */
  ~World() {
    // Delete allocated memory (if applicable)
    if (lightP_) {
      delete lightP_;
      lightP_ = NULL;
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

  // Accessors
  inline std::vector<Sphere> GetObjects() const { return objects_; }
  inline bool HasLightSource() const { return (lightP_ != NULL); } 

private:
  // A World tracks a collection of objects
  std::vector<Sphere> objects_;

  // Light Source
  PointLight *lightP_; 
};
#endif

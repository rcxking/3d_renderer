#ifndef __WORLD_H__
#define __WORLD_H__

/*
 * World.h
 *
 * Representation of a collection of objects in the scene.
 *
 */
#include "PointLight.h"
#include "RaySphere.h"

#include <map>
#include <string>

class World {
public:
  /**
   * Default Constructor
   */
  World() : light_source_(nullptr) {
  }

  /**
   * @brief Destructor
   */
  ~World() {
    if (light_source_ != nullptr) {
      delete light_source_;
      light_source_ = nullptr;
    }
  }

  /**
   * @brief Gives the number of objects this world contains
   * @return size_t Number of objects within this world
   */
  size_t GetNumObjects() const { return objects_.size(); }

  /**
   * @brief Acquires the light source.
   * @return PointLight* light source
   */
  PointLight* GetLightSource() const { return light_source_; }

private:
  //! Names and objects this world contains
  std::map<std::string, Sphere> objects_;

  //! Point light source illuminating this world
  PointLight* light_source_;
};
#endif

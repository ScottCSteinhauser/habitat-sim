// Copyright (c) Facebook, Inc. and its affiliates.
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#include "CollisionGroupHelper.h"
#include <Corrade/Utility/Assert.h>
#include "esp/core/logging.h"

namespace esp {
namespace physics {

/*
  enum class CollisionGroup {
    Default = 1,
    Static = 2,
    Kinematic = 4,
    FreeObject = 8,
    GraspedObject = 16,
    Robot = 32,
  };
*/

int CollisionGroupHelper::getMaskForGroup(CollisionGroup group) {
  // TODO: refactor this in terms of enabling collision between specific pairs
  // of groups
  switch (group) {
    case CollisionGroup::Default:
      // everything
      return -1;

    case CollisionGroup::Static:
      // everything but kinematic
      return int(-1) & ~int(CollisionGroup::Kinematic);

    case CollisionGroup::Kinematic:
      // everything but static
      return int(-1) & ~int(CollisionGroup::Static);

    case CollisionGroup::FreeObject:
      // everything
      return int(-1);

    case CollisionGroup::GraspedObject:
      // everything but robot
      return int(-1) & ~int(CollisionGroup::Robot);

    case CollisionGroup::Robot:
      // everything but grasped object
      return int(-1) & ~int(CollisionGroup::GraspedObject);

    case CollisionGroup::EeMargin:
      // everything but grasped object or the robot
      return int(-1) &
             ~(int(CollisionGroup::GraspedObject) | int(CollisionGroup::Robot));

    case CollisionGroup::SelObj:
      // everything but the ee margin
      return int(-1) & ~(int(CollisionGroup::EeMargin));

    default:
      CORRADE_ASSERT(
          false,
          "Collision group specified does not exist or no mask configured.", 0);
      return 0;
  }
}

}  // namespace physics
}  // namespace esp
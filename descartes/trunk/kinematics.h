#ifndef _KINEMATICS_H_
#define _KINEMATICS_H_

#include "units.h"

// time to max velocity from a dead stop
seconds TimeToMaxVelocity(mmM max_velocity, mmS2 acceleration_arg);

// time to max velocity starting from a pre-existing velocity
seconds TimeToMaxVelocity(mmM initial_velocity, mmM max_velocity, mmS2 acceleration_arg);

mm DistanceToMaxVelocity(mmM max_velocity, mmS2 acceleration_arg);

seconds TimeToAccelerateOverDistance(mm distance, mmS2 acceleration_arg);

seconds DistanceGivenAccelerationOverTime(seconds time, mmS2 acceleration_arg);

// seconds TimeToAccelerateOverDistance(mm distance);

seconds AxisMoveDuration(mm distance, mmM max_feed_rate, mmS2 acceleration_arg);

#endif //_KINEMATICS_H_
#ifndef _KINEMATICS_H_
#define _KINEMATICS_H_

#include "units.h"

// time to max velocity from a dead stop
seconds TimeToVelocity(mmM velocity, mmS2 acceleration_arg);

// time to max velocity starting from a pre-existing velocity
seconds TimeToVelocity(mmM initial_velocity, mmM final_velocity, mmS2 acceleration_arg);

mm DistanceToVelocity(mmM final_velocity, mmS2 acceleration_arg);

mm DistanceToVelocity(mmM initial_velocity, mmM final_velocity, mmS2 acceleration_arg);

seconds TimeToAccelerateOverDistance(mm distance, mmS2 acceleration_arg);

seconds TimeToAccelerateOverDistance(mmM initial_velocity, mm distance, mmS2 acceleration_arg);

seconds TimeToAccelerateOverDistance2(mmM initial_velocity, mm distance, mmS2 acceleration_arg);

mm DistanceGivenAccelerationOverTime(seconds time, mmS2 acceleration_arg);

mm DistanceGivenAccelerationOverTime(mmM initial_velocity, seconds time, mmS2 acceleration_arg);

// seconds TimeToAccelerateOverDistance(mm distance);

seconds AxisMoveDuration(mm distance, mmM max_feed_rate, mmS2 acceleration_arg);

mmM VelocityGivenAccelerationOverDistance(mm distance, mmS2 acceleration_arg);

mmM VelocityGivenAccelerationOverDistance(mmM initial_velocity, mm distance, mmS2 acceleration_arg);

#endif //_KINEMATICS_H_
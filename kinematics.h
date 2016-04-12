#ifndef _KINEMATICS_H_
#define _KINEMATICS_H_

#include "units.h"

// time to max velocity from a dead stop
seconds TimeToVelocity(const mmM& velocity, const mmS2& acceleration_arg);

// time to max velocity starting from a pre-existing velocity
seconds TimeToVelocity(const mmM& initial_velocity, const mmM& final_velocity, const mmS2& acceleration_arg);

mm DistanceToVelocity(const mmM& final_velocity, const mmS2& acceleration_arg);

mm DistanceToVelocity(const mmM& initial_velocity, const mmM& final_velocity, const mmS2& acceleration_arg);

seconds TimeToAccelerateOverDistance(const mm& distance, const mmS2& acceleration_arg);

seconds TimeToAccelerateOverDistance(const mmM& initial_velocity, const mm& distance, const mmS2& acceleration_arg);

seconds TimeToAccelerateOverDistance2(const mmM& initial_velocity, const mm& distance, const mmS2& acceleration_arg);

mm DistanceGivenAccelerationOverTime(const seconds& time, const mmS2& acceleration_arg);

mm DistanceGivenAccelerationOverTime(const mmM& initial_velocity, const seconds& time, const mmS2& acceleration_arg);

// seconds TimeToAccelerateOverDistance(mm distance);

seconds AxisMoveDuration(const mm& distance, const mmM& max_feed_rate, const mmS2& acceleration_arg);

mmM VelocityGivenAccelerationOverDistance(const mm& distance_arg, const mmS2& acceleration_arg);

mmM VelocityGivenAccelerationOverDistance(const mmM& initial_velocity, const mm& distance, const mmS2& acceleration_arg);

#endif //_KINEMATICS_H_
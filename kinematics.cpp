#include "kinematics.h"



/*
Kinematic Equations

distance = initial_velocity * time + 1/2 * acceleration * time^2

final_velocity^2 = initial_velocity^2 + 2 * acceleration * distance

final_velocity = initial_velocity + acceleration * time

distance = (initial_velocity + final_velocity) / 2 * time
*/



// time to max velocity from a dead stop
seconds TimeToMaxVelocity(mmM max_velocity, mmS2 acceleration_arg)
{
    return (max_velocity / 60.0f) / acceleration_arg;
}


// time to max velocity starting from a pre-existing velocity
seconds TimeToMaxVelocity(mmM initial_velocity, mmM max_velocity, mmS2 acceleration_arg)
{
    return (max_velocity - initial_velocity) / acceleration_arg;
}




mm DistanceToMaxVelocity(mmM max_velocity, mmS2 acceleration_arg)
{
    //x = 1 / 2 * acceleration * tmax ^ 2
    seconds tmax = TimeToMaxVelocity(max_velocity, acceleration_arg);
    return 0.5f * acceleration_arg * (tmax * tmax);
}


seconds TimeToAccelerateOverDistance(mm distance, mmS2 acceleration_arg)
{
    return sqrtf(2.0f * distance / acceleration_arg);
}



seconds DistanceGivenAccelerationOverTime(seconds time, mmS2 acceleration_arg)
{
    return  0.5f * acceleration_arg * (time * time);
}


/*
seconds TimeToAccelerateOverDistance(mm distance)
{
return TimeToAccelerateOverDistance(distance, acceleration);
}
*/


seconds AxisMoveDuration(mm distance, mmM max_feed_rate, mmS2 acceleration_arg)
{
    /*
    we know that we have to both accelerate and decelerate.  So the motion
    is basically the same as two acceleration events (at least WRT duration anyway).
    So just divide the distance by two, calculate the duration given the acceleration
    factor, then multiply that by two.
    */
    if (FloatsEqual(distance, 0.0f))
        return 0.0f;

    distance /= 2.0f;

    // calculate the distance achieved at max_velocity
    // if the distance at max velocity is greater than the distance argument
    // then we can use the dumb accel calculation.
    // However, if the distance at max velocity is less than the distance argument
    // then we need to use the dum accel up to the distance at max velocity,
    // then add in the simple velocity * distance for the remaining distance

    mm max_velocity_achieved_at_distance = DistanceToMaxVelocity(max_feed_rate, acceleration_arg);

    seconds max_velocity_component = 0.0f;
    if (max_velocity_achieved_at_distance < distance)
    {
        max_velocity_component = (distance - max_velocity_achieved_at_distance) / (max_feed_rate / 60.0f);
        distance = max_velocity_achieved_at_distance;
    }

    return (TimeToAccelerateOverDistance(distance, acceleration_arg) + max_velocity_component) * 2.0f;
}


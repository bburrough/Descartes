#include "kinematics.h"



/*
Kinematic Equations

distance = initial_velocity * time + 1/2 * acceleration * time^2

time = sqrt(2 * distance / acceleration) 

final_velocity^2 = initial_velocity^2 + 2 * acceleration * distance

final_velocity = initial_velocity + acceleration * time

distance = (initial_velocity + final_velocity) / 2 * time
*/


// time to max velocity from a dead stop
seconds TimeToVelocity(mmM final_velocity, mmS2 acceleration_arg)
{
    return final_velocity / 60.0f / acceleration_arg;
}



// time to max velocity starting from a pre-existing velocity
seconds TimeToVelocity(mmM initial_velocity, mmM final_velocity, mmS2 acceleration_arg)
{
    return (final_velocity - initial_velocity) / 60.0f / acceleration_arg;
}


mm DistanceToVelocity(mmM final_velocity, mmS2 acceleration_arg)
{
    //x = 1 / 2 * acceleration * tmax ^ 2
    seconds tmax = TimeToVelocity(final_velocity, acceleration_arg);
    return 0.5f * acceleration_arg * (tmax * tmax);
}


mm DistanceToVelocity(mmM initial_velocity, mmM final_velocity, mmS2 acceleration_arg)
{
    if (FloatsEqual(initial_velocity, final_velocity)) return 0.0f;
    if (FloatsEqual(acceleration_arg, 0.0f)) throw(exception("impossible to decelerate from initial_velocity to final velocity because acceleration is zero"));
    if (acceleration_arg <= 0.0f && final_velocity >= initial_velocity) throw(exception("impossible to decelerate from initial_velocity to final velocity because final_velocity >= initial_velocity"));
    if (initial_velocity < 0.0f || final_velocity < 0.0f) throw(exception("velocity can't be negative"));

    //x = 1 / 2 * acceleration * tmax ^ 2
    seconds tmax = TimeToVelocity(initial_velocity, final_velocity, acceleration_arg);
    return  initial_velocity * tmax + 0.5f * acceleration_arg * (tmax * tmax);
}


seconds TimeToAccelerateOverDistance(mm distance, mmS2 acceleration_arg)
{
    return sqrtf(2.0f * distance / acceleration_arg);
}


seconds TimeToAccelerateOverDistance2(mmM initial_velocity, mm distance, mmS2 acceleration_arg)
{
    return initial_velocity / distance + sqrtf(2.0f * distance / acceleration_arg);
}



// time to max velocity starting from a pre-existing velocity
seconds TimeToAccelerateOverDistance(mmM initial_velocity, mm distance, mmS2 acceleration_arg)
{
    if (FloatsEqual(0.0f, distance))
        return distance;
    if (acceleration_arg <= 0.0f && initial_velocity <= 0.0f)
        return NAN; // you can't decelerate from zero

    mmS velocity_S = initial_velocity / 60.0f;

    bool test = false;
    float up = (-velocity_S + sqrt(velocity_S*velocity_S + 2.0f * acceleration_arg * distance)) / acceleration_arg;
    float down = (-velocity_S - sqrt(velocity_S*velocity_S + 2.0f * acceleration_arg * distance)) / acceleration_arg;
    if (isnan(up))
        test = true;

    // standard quadratic solver
    return (-velocity_S + sqrt(velocity_S*velocity_S + 2.0f * acceleration_arg * distance)) / acceleration_arg;

    // Citardauq quadratic solver
    //return (2.0f * -distance) / (-velocity_S - sqrt(velocity_S*velocity_S + 2.0f * acceleration_arg * distance));
}


// from dead stop
mm DistanceGivenAccelerationOverTime(seconds time, mmS2 acceleration_arg)
{
    if (FloatsEqual(time, 0.0f)) return 0.0f;
    if (acceleration_arg <= 0.0f) return 0.0f;
    if (time < 0.0f) throw(exception("can't decelerate over negative time"));
    return  0.5f * acceleration_arg * (time * time);
}


// from initial_velocity
mm DistanceGivenAccelerationOverTime(mmM initial_velocity, seconds time, mmS2 acceleration_arg)
{
    if (FloatsEqual(time, 0.0f)) return 0.0f;
    if (acceleration_arg < 0.0f && FloatsEqual(initial_velocity, 0.0f)) return 0.0f;
    if (initial_velocity < 0.0f) throw(exception("velocity can't be negative"));
    if (time < 0.0f) throw(exception("can't decelerate over negative time"));

    return initial_velocity * time / 60.0f + 0.5f * acceleration_arg * (time * time);
}

// Vf^2 = Vi^2 + 2a * (Xf - Xi)
// Xf - Xi = Vi^2 / Vf^2 + 2a / Vf^2


mm DistanceGivenVelocitiesOverTime(mmM initial_velocity, mmM final_velocity, seconds time)
{
    return (initial_velocity + final_velocity) / 2 * time;
}



/*
seconds TimeToAccelerateOverDistance(mm distance)
{
return TimeToAccelerateOverDistance(distance, acceleration);
}
*/


// from a dead stop
mmM VelocityGivenAccelerationOverDistance(mm distance, mmS2 acceleration_arg)
{
    return  0.5f * acceleration_arg * (distance * distance);
}


mmM VelocityGivenAccelerationOverDistance(mmM initial_velocity, mm distance, mmS2 acceleration_arg)
{
    return sqrt((initial_velocity / 60.0f)*(initial_velocity / 60.0f) + 2 * acceleration_arg * distance) * 60.0f;
}


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

    mm max_velocity_achieved_at_distance = DistanceToVelocity(max_feed_rate, acceleration_arg);

    seconds max_velocity_component = 0.0f;
    if (max_velocity_achieved_at_distance < distance)
    {
        max_velocity_component = (distance - max_velocity_achieved_at_distance) / (max_feed_rate / 60.0f);
        distance = max_velocity_achieved_at_distance;
    }

    return (TimeToAccelerateOverDistance(distance, acceleration_arg) + max_velocity_component) * 2.0f;
}


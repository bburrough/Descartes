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
seconds TimeToVelocity(const mmM& final_velocity, const mmS2& acceleration_arg)
{
    return mmS(final_velocity) / acceleration_arg;
}


// time to max velocity starting from a pre-existing velocity
seconds TimeToVelocity(const mmM& initial_velocity, const mmM& final_velocity, const mmS2& acceleration_arg)
{
    return mmS((final_velocity - initial_velocity)) / acceleration_arg;
}


mm DistanceToVelocity(const mmM& final_velocity, const mmS2& acceleration_arg)
{
    //x = 1 / 2 * acceleration * tmax ^ 2
    seconds tmax = TimeToVelocity(final_velocity, acceleration_arg);
    return 0.5f * acceleration_arg * (tmax * tmax);
}

// 1 / 2 * a * b^2
// 

// 1 / 2 * 6 * 2 * 2 = 12

// 6 / 2 * 2 * 2 = 12

// acceleration_arg / 2 * (tmax * tmax)

// .5 * mm/S2 * S2



mm DistanceToVelocity(const mmM& initial_velocity, const mmM& final_velocity, const mmS2& acceleration_arg)
{
    if (initial_velocity == final_velocity) return mm(0.0f);
    if (acceleration_arg == 0.0f) throw(exception("impossible to decelerate from initial_velocity to final velocity because acceleration is zero"));
    if (acceleration_arg <= 0.0f && final_velocity >= initial_velocity) throw(exception("impossible to decelerate from initial_velocity to final velocity because final_velocity >= initial_velocity"));
    if (initial_velocity < 0.0f || final_velocity < 0.0f) throw(exception("velocity can't be negative"));

    //x = 1 / 2 * acceleration * tmax ^ 2
    seconds tmax = TimeToVelocity(initial_velocity, final_velocity, acceleration_arg);
    //return  initial_velocity * tmax + 0.5f * acceleration_arg * (tmax * tmax);
    return mmS(initial_velocity) * tmax + 0.5f * acceleration_arg * (tmax * tmax);
}


seconds TimeToAccelerateOverDistance(const mm& distance, const mmS2& acceleration_arg)
{
    return sqrt(2.0f * distance / acceleration_arg);
}


/*
seconds TimeToAccelerateOverDistance2(const mmM& initial_velocity, const mm& distance, const mmS2& acceleration_arg)
{
    return mmS(initial_velocity) / distance + sqrt(2.0f * distance / acceleration_arg);
}
*/
// mm/S / mm
// mm/S * 1/mm
// 1/S


// time to max velocity starting from a pre-existing velocity
seconds TimeToAccelerateOverDistance(const mmM& initial_velocity, const mm& distance, const mmS2& acceleration_arg)
{
    if (distance == 0.0f)
        return seconds(0.0f);
    if (acceleration_arg <= 0.0f && initial_velocity <= 0.0f)
        return seconds(NAN); // you can't decelerate from zero

    mmS velocity_S(initial_velocity);

    /*
    bool test = false;
    float up = (-velocity_S + sqrt(velocity_S*velocity_S + 2.0f * acceleration_arg * distance)) / acceleration_arg;
    float down = (-velocity_S - sqrt(velocity_S*velocity_S + 2.0f * acceleration_arg * distance)) / acceleration_arg;
    if (isnan(up))
        test = true;
    */


    // standard quadratic solver
    return (sqrt(velocity_S*velocity_S + 2.0f * acceleration_arg * distance) - velocity_S) / acceleration_arg;

    // Citardauq quadratic solver
    //return (2.0f * -distance) / (-velocity_S - sqrt(velocity_S*velocity_S + 2.0f * acceleration_arg * distance));
}


// from dead stop
mm DistanceGivenAccelerationOverTime(const seconds& time, const mmS2& acceleration_arg)
{
    if (time == 0.0f) return mm(0.0f);
    if (acceleration_arg <= 0.0f) return mm(0.0f);
    if (time < 0.0f) throw(exception("can't decelerate over negative time"));
    return  0.5f * acceleration_arg * (time * time);
}


// from initial_velocity
mm DistanceGivenAccelerationOverTime(const mmM& initial_velocity, const seconds& time, const mmS2& acceleration_arg)
{
    if (time == 0.0f) return mm(0.0f);
    if (acceleration_arg < 0.0f && initial_velocity == 0.0f) return mm(0.0f);
    if (initial_velocity < 0.0f) throw(exception("velocity can't be negative"));
    if (time < 0.0f) throw(exception("can't decelerate over negative time"));

    return mmS(initial_velocity) * time + 0.5f * acceleration_arg * (time * time);
}

// Vf^2 = Vi^2 + 2a * (Xf - Xi)
// Xf - Xi = Vi^2 / Vf^2 + 2a / Vf^2


mm DistanceGivenVelocitiesOverTime(const mmM& initial_velocity, const mmM& final_velocity, const seconds& time)
{
    return 0.5f * mmS(initial_velocity + final_velocity) * time;
}



/*
seconds TimeToAccelerateOverDistance(mm distance)
{
return TimeToAccelerateOverDistance(distance, acceleration);
}
*/


// from a dead stop
/*
mmM VelocityGivenAccelerationOverDistance(const mm& distance, const mmS2& acceleration_arg)
{
    return  0.5f * acceleration_arg * (distance * distance);

    // mm/S^2 * mm^2 = mm^3/S^2
}
*/

mmM VelocityGivenAccelerationOverDistance(const mmM& initial_velocity, const mm& distance, const mmS2& acceleration_arg)
{
    mmS initial_velocity_S(initial_velocity);
    return mmM(sqrt(initial_velocity_S*initial_velocity_S + 2 * acceleration_arg * distance));
}


seconds AxisMoveDuration(const mm& distance_arg, const mmM& max_feed_rate, const mmS2& acceleration_arg)
{
    /*
    we know that we have to both accelerate and decelerate.  So the motion
    is basically the same as two acceleration events (at least WRT duration anyway).
    So just divide the distance by two, calculate the duration given the acceleration
    factor, then multiply that by two.
    */
    if (distance_arg == 0.0f)
        return seconds(0.0f);

    mm distance = distance_arg / 2.0f;

    // calculate the distance achieved at max_velocity
    // if the distance at max velocity is greater than the distance argument
    // then we can use the dumb accel calculation.
    // However, if the distance at max velocity is less than the distance argument
    // then we need to use the dum accel up to the distance at max velocity,
    // then add in the simple velocity * distance for the remaining distance

    mm max_velocity_achieved_at_distance = DistanceToVelocity(max_feed_rate, acceleration_arg);

    seconds max_velocity_component(0.0f);
    if (max_velocity_achieved_at_distance < distance)
    {
        // mm / mm / S = mm * S / mm
        max_velocity_component = (distance - max_velocity_achieved_at_distance) / mmS(max_feed_rate);
        distance = max_velocity_achieved_at_distance;
    }

    return (TimeToAccelerateOverDistance(distance, acceleration_arg) + max_velocity_component) * 2.0f;
}


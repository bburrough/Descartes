# Descartes 

A C++ library for simple geometric arithmetic by Bob Burrough.


## License

Descartes is available under either the MIT or public domain license. It is unencumbered and free to use.


## Classes

* Circle - It's a circle. A 2D shape with a centerpoint and a radius.
* DCVector - A 3D point which represents direction and magnitude from (0,0,0).
* DCVector2 - A 2D point which represents direction and magnitude from (0,0,0).
* degrees - unit of angle, a full rotation is 360 degrees
* degrees_celsius - unit of temperature
* LineSegment - A 3D line segment between two points.
* minutes - unit of time
* mm - millimeters, unit of distance
* mm2 - millimeters squared (mm²), unit of area
* mm3 - millimeters cubed (mm³), unit of volume
* mmS2 - millimeters per second squared (mm/S²), unit of acceleration
* mmM - millimieters per minute (mm/M), unit of velocity
* mm2S2 - millimeters squared per second squared (mm²/S²) - unit of areal acceleration
* mm2M2 - millimeters squared per minute squared (mm²/M²) - unit of areal acceleration
* mmS - millimeters per second (mm/S), unit of velocity
* mm3S - millimeters cubed per second (mm³/S), unit of volumetric velocity
* Point - a 3D point
* Point2 - a 2D point
* radians - unit of angle, circumference of a circle is 2πr radians
* seconds - unit of time
* SpiralLine - A coil represented by a circle, a 2D vector, and a number of iterations.
* S2 - seconds squared (S²)


## Static Functions 

```cpp
// Calculate the amount of time required to accelerate to given velocity from a dead stop.
seconds TimeToVelocity(const mmM& velocity, const mmS2& acceleration_arg);

// Calculate the amount of time required to accelerate to max velocity given an initial velocity.
seconds TimeToVelocity(const mmM& initial_velocity, const mmM& final_velocity, const mmS2& acceleration_arg);

// Calculate how much distance is required to reach final_velocity given acceleration from a dead stop.
mm DistanceToVelocity(const mmM& final_velocity, const mmS2& acceleration_arg);

// Calculate how much distance is required to reach final_velocity given acceleration and initial velocity.
mm DistanceToVelocity(const mmM& initial_velocity, const mmM& final_velocity, const mmS2& acceleration_arg);

// Calculate how long it takes to accelerate over distance from a dead stop.
seconds TimeToAccelerateOverDistance(const mm& distance, const mmS2& acceleration_arg);

// Calculate how long it takes to accelerate over distance given initial_velocity.
seconds TimeToAccelerateOverDistance(const mmM& initial_velocity, const mm& distance, const mmS2& acceleration_arg);

// Calculate the distance reached when accelerating from a dead stop for an amount of time.
mm DistanceGivenAccelerationOverTime(const seconds& time, const mmS2& acceleration_arg);

// Calculate the distance reached when accelerating from an initial_velocity for an amount of time.
mm DistanceGivenAccelerationOverTime(const mmM& initial_velocity, const seconds& time, const mmS2& acceleration_arg);

// Calculate the amount of time required to move distance given max_feed_rate and acceleration_arg. The motion profile is a trapezoidal move from a dead stop to a dead stop.
seconds AxisMoveDuration(const mm& distance, const mmM& max_feed_rate, const mmS2& acceleration_arg);

// Calculate the velocity achieved given acceleration from a dead stop over a given distance.
mmM VelocityGivenAccelerationOverDistance(const mm& distance_arg, const mmS2& acceleration_arg);

// Calculate the velocity achieved given acceleration from an initial velocity over a given distance.
mmM VelocityGivenAccelerationOverDistance(const mmM& initial_velocity, const mm& distance, const mmS2& acceleration_arg);
```


## Type-Rich Programming with Descartes

Descartes is designed to provide a type-rich interface for kinematic arithmetic.  It was inspired by a talk given by Bjarne Stroustrup at GoingNative 2012. This library achieves the vision of type rich programming and illustrates what is possible when the goals of object oriented programming are properly respected. It stands in direct contrast to the direction which C++ and most other modern programming languages have gone with type-deficient programming, and in the case of C++, "Almost Always Auto."

Hit the image to go to the original talk by Bjarne Stroustrup. 👇

[![Bjarne Stroustrup discusses type-rich programming](https://img.youtube.com/vi/OB-bdWKwXsU/0.jpg)](https://www.youtube.com/watch?v=OB-bdWKwXsU&t=1110s)


Type-rich programming, as demonstrated by Descartes, is important because it actually achieves efficient, correct, self-verifying code whereas AAA does not.

Consider the example:

```cpp
float height(0.5f);
float width(2.0f);

float area = height * width;
```

This code takes two measures of distance and multiplies them to arrive at a measure of area. Consider the alternative:

```cpp
mm height(0.5f);
mm width(2.0f);

mm2 area = height * width;
```

This code does the same thing, but also validates the programmer's intent when multiplying values. The multiplication operator understands that multiplying a unit of distance by another unit of distance results in a unit of distance squared, and not any other unit.  For example, let's add a unit of time and see how the program changes:

```cpp
mm height(0.5f);
mm width(2.0f);
seconds elapsed(3.3f);

mm2 area = height * width;
mm2S coverage_rate = area / elapsed;
```

In this case, we are calculating the amount of area covered in a given amount of time. Our division operator knows that dividing a unit of area by a unit of time results in the unit of area per unit time (mm²/S).  If we attempted to store the result in any other type, or if we accidentally used the wrong value in our expression, a compiler error would result.

Now, let's do the same in the type-deficient code:

```cpp
float height(0.5f);
float width(2.0f);
float elapsed(3.3f);

float area = height * width;
float coverage_rate = area / elapsed;
```

In this example, the compiler knows absolutely nothing about what the programmer intended with these types.  It can provide no validation of the arithmetic whatsoever.  This is exactly the kind of programming that leads to unit conversion errors and the [embarassing loss of billion dollar satellites](https://solarsystem.nasa.gov/missions/mars-climate-orbiter/in-depth/). Mistakes are so easy to overlook, they're almost inevitable.

If the programmer never declares their intention, the compiler will never be able to validate their goal. This is both a benefit of type-rich-programming, and a fundamental flaw with "Almost Always Auto" (and by extension a reason why AAA should not be used).


## Other Examples

How many times have you had to check whether sin() takes radians or degrees? ...or to always convert angles back and forth? No longer!

```cpp
// sin(x) takes degrees...

degrees alpha(90.0f);

mm height_given_degrees = sin(alpha);

// but it also works with radians...

radians beta(PI / 2.0f);

mm height_given_radians = sin(beta);

// ...or even by mixing degrees and radians!

mm height_given_both = sin(alpha/2.0f + beta/2.0f);

assert(height_given_degrees == height_given_radians);
assert(height_given_radians == height_given_both);
```

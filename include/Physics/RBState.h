#pragma once

#include <MathLib/Point3d.h>
#include <MathLib/Vector3d.h>
#include <MathLib/Quaternion.h>

#include <Physics/PhysicsDll.h>

namespace CartWheel { namespace Physics {

/*======================================================================================================================================================================*
 * This class acts as a container for the state information (position, orientation, velocity and angular velocity - all of them stored in world coordinates, about the  *
 * center of mass) of a rigid body.                                                                                                                                     *
 *======================================================================================================================================================================*/

class PHYSICS_DECLSPEC RBState{
public:
	//NOTE: all the quantities here are in world coordinates

	// the position of the center of mass of the rigid body
	CartWheel::Math::Point3d position;
	// its orientation
	CartWheel::Math::Quaternion orientation;
	// the velocity of the center of mass
	CartWheel::Math::Vector3d velocity;
	// and finally, the angular velocity about the center of mass
	CartWheel::Math::Vector3d angularVelocity;
	
public:
	/**
		Default constructor - populate the data members using safe values..
	*/
	RBState(void);

	/**
		A copy constructor.
	*/
	RBState(const RBState& other);

	/**
		and a copy operator	
	*/
	RBState& operator = (const RBState& other);
	/**
		Default destructor.
	*/
	~RBState(void);
};

}
}

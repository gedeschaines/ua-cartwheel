#pragma once

#include <Physics/PhysicsDll.h>
#include <Physics/Joint.h>

namespace CartWheel { namespace Physics {

/*======================================================================================================================================================================*
 * This class is used to implement a stiff joint - always computes the impulses that are needed to have zero relative angular velocity between the parent and the child *
 *======================================================================================================================================================================*/

class PHYSICS_DECLSPEC StiffJoint : public Joint{
private:

public:
	StiffJoint();
	~StiffJoint(void);

	/**
		This method is used to fix the joint angular constraint to correct for drift. This is done by changing
		the orientation of the child.
	*/
	void fixAngularConstraint(const CartWheel::Math::Quaternion& qRel);

	/**
		Returns the type of the current joint
	*/
	virtual int getJointType(){return STIFF_JOINT;}


};

}
}


#include "Control/StaticWalkNearPolicy.h"

namespace CartWheel
{

using namespace std;
using namespace CartWheel::Math;


StaticWalkNearPolicy::StaticWalkNearPolicy(double walkSpeed, string p){
    myWalkSpeed = walkSpeed;
    myAvailableActions = new ExtendedAction*[4];
    //cout << "StaticWalkNearPolicy::StaticWalkNearPolicy" << endl; 
    WalkAction* temp0 = new WalkAction(myWalkSpeed);
    myAvailableActions[0] = (ExtendedAction*)temp0;
    WalkAction* temp1 = new WalkAction(0.0);
    myAvailableActions[1] = (ExtendedAction*)temp1;
    TurnAction* temp2 = new TurnAction(0.174); // 10 degrees
    myAvailableActions[2] = (ExtendedAction*)temp2;
    TurnAction* temp3 = new TurnAction(-0.174);
    myAvailableActions[3] = (ExtendedAction*)temp3;
    for (int x=0; x < 4; x++)
	    myAvailableActions[x]->setTime(0.05);
    myControllables = new string[1];
    myControllables[0] = p;
    //cout << "StaticWalkNearPolicy::StaticWalkNearPolicy - exit" << endl;
} 

StaticWalkNearPolicy::~StaticWalkNearPolicy(){
    delete myAvailableActions[0];
    delete myAvailableActions[1];
    delete myAvailableActions[2];
    delete myAvailableActions[3];
    delete [] myAvailableActions;
    delete [] myControllables;
}


//TODO: We will be replacing the nearness check with a relation class once I verify this works
ExtendedAction* StaticWalkNearPolicy::getAction(CartWheel3D* simState){
    //cout << "StaticWalkNearPolicy::getAction" << endl;
    // find location of the controllable actor
    vector<string> humanNames;
    simState->getHumanNames(humanNames);

    //cout << "myControllables[0]: " << myControllables[0] << endl;
    int hIndex = atoi(myControllables[0].c_str());
    Vector3d pos1 = simState->getHumanPosition(humanNames[hIndex]);
    //cout << "Made the 1st point" << endl;

    // target location (later might be another actor)
    //cout << "pos: " << simState->getObjectByName("dodgeBox")-> getCMPosition().getX()<<endl;
    //Point3d pos21(simState->getObjectByName("dodgeBox")->getCMPosition());

    // TODO: Actually look up the other human
	simState->getHumanNames(humanNames);
    Vector3d pos2(simState->getHumanPosition(humanNames[1]));  // (pos21.getX(), pos21.getY(), pos21.getZ());	
    //cout << "Made the 2nd point" << endl;

    // keep walking
    cout << "Other Dude : " << pos2.getX() << "  " << pos2.getY() << "  " << pos2.getZ() << endl;
    cout << "Distance : " << ControlUtils::eucDistance2d(pos1, pos2) << endl;
    double deltaZ = pos2.getZ() - pos1.getZ();
    double deltaX = pos2.getX() - pos1.getX();
    if (fabs(atan(deltaZ / deltaX) - simState->getHumanHeading(humanNames[hIndex])) > 3.14/4.0) { // a lot of leeway
        cout << "Turning" << endl;
        return myAvailableActions[2];  // someone else can do the logic on which way to turn
    }
    else if (ControlUtils::eucDistance2d(pos1, pos2) > 1.0) {
  	    cout << "Walking" << endl;	
  	    return myAvailableActions[0];
    }
    // stop walking
    else{
	    cout << "Stopping" << endl;
  	    return myAvailableActions[1];
    }
}

} // namespace CartWheel

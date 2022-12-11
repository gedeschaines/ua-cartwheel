#include "Behaviors/Throw.h"
#include <Core/CartWheel3D.h>

using namespace CartWheel;

Throw::Throw(CartWheel3D* cw, std::string humanName, Throw_Params* params)
        : Behavior(cw, humanName, params!=NULL ? params->startTime : 0, params!=NULL ? params->duration : 0) {
    sHand = params->sHand.c_str();
    sObj = params->sObj.c_str();
    speed = params->speed;
    printf("1Throw: %s!!\n", sHand.c_str());
    this->cw->getHuman(humanName, &human);
    printf("2Throw: %s!!\n", sHand.c_str());
    bcontroller = human->getBehaviour();
    printf("3Throw: %s!!\n", sHand.c_str());
}

void Throw::onInit() {
/* Debug print when calling cw->setController(humanName, 15) below.
    printf("nSteps %d\n", nSteps);
    printf("Checking Obj: %s!!\n", sObj.c_str());
    Physics::RigidBody* obj = cw->getObjectByName(sObj.c_str());
    Point3d posObj = obj->getCMPosition();
    Vector3d velObj = obj->getCMVelocity();
    printf("CMPos:  %6.2f  %6.2f  %6.2f\n", posObj.x, posObj.y, posObj.z);
    printf("CMVel:  %6.2f  %6.2f  %6.2f\n", velObj.x, velObj.y, velObj.z);
*/
//    if(strcmp(sHand.c_str(), "Left")==0)
//        cw->setController(humanName, 10);
//    else if(strcmp(sHand.c_str(), "Right")==0)
//        cw->setController(humanName, 11);
//    else if(strcmp(sHand.c_str(), "Both")==0)
//        cw->setController(humanName, 12);
    human->getController()->setStance(RIGHT_STANCE);
     cw->setController(humanName, 11);  // WaveRightHand
//   cw->setController(humanName, 15);  // Throwball
//    human->getCharacter()->getARBByName("lUpperLeg")->getOrientation()
    nFrame = 0;
}

void Throw::runStep() {
    nSteps++;
/* Debug print when calling cw->setController(humanName, 15) in onInit()
    printf("nSteps %d\n", nSteps);
    printf("Checking Obj: %s!!\n", sObj.c_str());
    Physics::RigidBody* obj = cw->getObjectByName(sObj.c_str());
    Point3d posObj = obj->getCMPosition();
    Vector3d velObj = obj->getCMVelocity();
    printf("CMPos:  %6.2f  %6.2f  %6.2f\n", posObj.x, posObj.y, posObj.z);
    printf("CMVel:  %6.2f  %6.2f  %6.2f\n", velObj.x, velObj.y, velObj.z);
*/
    if (nSteps == SimGlobals::steps_per_second/2 && !bThrowFinished) {
        nSteps = 0;
//        human->factorVelocity("pelvis", Vector3d(0.8,0.8,0.8));
        nFrame++;
        if (nFrame==3) {
            printf("Throwing Fire2!!!\n");
            cw->makeHumanThrowObject(humanName, sObj, speed);
//            cw->makeHumanThrowObject(humanName, "ball2", Vector3d(0,1.5,-4.5));
//            cw->makeHumanThrowObject(humanName, "ball1", Vector3d(1,0,-3));
        }
    }
    if (bThrowFinished) {
//        human->setLock("lHand", true, true);
//        human->setLock("rHand", true, true);
//        human->setLock("torso", true, true);
//        human->setLock("lowerBack", true, true);
//        human->setLock("pelvis", true, true);
        printf("Way to go!!!\n");
    }
}

void Throw::onFinish() {
    double nan = std::numeric_limits<double>::quiet_NaN();
    //Left    
    if(strcmp(sHand.c_str(), "Left")==0 || strcmp(sHand.c_str(), "Both")==0) {
        printf("---Finish Left\n");
        bcontroller->requestShoulderBend(0, nan, 0, nan, -1.5, nan);
        bcontroller->requestElbowBend(0, 0, 0, 0, 0, 0);
    }
    //Right
    if(strcmp(sHand.c_str(), "Right")==0 || strcmp(sHand.c_str(), "Both")==0) {
        printf("---Finish Right\n");
        bcontroller->requestShoulderBend(nan, 0, nan, 0, nan, 1.5);
        bcontroller->requestElbowBend(0, 0, 0, 0, 0, 0);
    }
    human->getController()->setStance(LEFT_STANCE);
    cw->setController(humanName, 0);
    printf("Ending Throw Time: %f\n", time);
    bThrowFinished = true;
}


#include "Control/ExtendedAction.h"
#include <Control/PosState.h>

namespace CartWheel {

    void ExtendedAction::execute(CartWheel3D *cw) {
        //time_t starter;
        Vector3d pos0;
        vector<string> humanNames;
        //cout << "ExtendedAction::execute1" << endl;

        //time(&starter);
        //starter = time(NULL);
        //while(time(NULL) - starter -  myTime < 0){

        //executeSetup(cw); NOTE: call this from the routine calling this method
   
        cw->getHumanNames(humanNames);
        
        for (double x = 0.0; x < myTime * 20.0; x++) {
            pos0 = cw->getHumanPosition(humanNames[0]);
            //cout << "human (0) location : " << pos0.getX() << "  " << pos0.getZ() << endl;
            PosState* pos = new PosState(cw);
            //trajectory->push_back(pos);
            cw->runStep(.001);
        }
    }

    void ExtendedAction::execute(CartWheel3D *cw, std::vector<PosState*> *posStates) {
        //time_t starter;
        Vector3d pos0;
        vector<string> humanNames;
        //cout << "ExtendedAction::execute2" << endl;

        //time(&starter);
        //starter = time(NULL);
        //while(time(NULL) - starter -  myTime < 0){

        cw->getHumanNames(humanNames);

        for (double x = 0.0; x < myTime * 20.0; x++) {
            pos0 = cw->getHumanPosition(humanNames[0]);
            //cout << "human (0) location : " << pos0.getX() << "  " << pos0.getZ() << endl;
            PosState* pos = new PosState(cw);
            posStates->push_back(pos);
            cw->runStep(.001);
        }
    }

    void ExtendedAction::executeStep(CartWheel3D *cw, double step) {
        Vector3d pos0;
        vector<string> humanNames;

        cw->getHumanNames(humanNames);
        pos0 = cw->getHumanPosition(humanNames[0]);
        //cout << "human (0) location : " << pos0.getX() << "  " << pos0.getZ() << endl;
        cw->runStep(step);
    }

} //namespace CartWheel

#include "trajectorobot.h"


ToRobot::ToRobot()
{
    c_trajec* points = new c_trajec[];
    c_trajecPub = nh.advertise<trajecgenerator::c_trajec_vector>("c_trajec", 1);
}

ToRobot::~ToRobot()
{
    delete[] points;
}

// fuer eine bestimmte Zeitdauer Trajektorienwerte in Array speichern
// --> void Trajechandler::updateTrajectory(float dt) aufrufen

ToRobot::ToRobot swarmcontroller::Trajectory storeInArray(Trajectory trajec_)
{
    while(Trajechandler::active)
    {
        int i = 0; //Zeitpunkt, wird nach Durchlauf der Schleife = Hinzufuegen eines Punktes iteriert
        trajecgenerator::c_trajec arrTrajec;
        arrTrajec.x = trajec_.x;
        arrTrajec.y = trajec_.y;
        arrTrajec.dx = trajec_.dx;
        arrTrajec.dy = trajec_.dy;
        arrTrajec.ddx = trajec_.ddx;
        arrTrajec.ddy = trajec_.ddy;
        arrTrajec.t = i++;

        v.push_back(arrTrajec);

        // swarmcontroller::Trajectory trajec_->c_trajec[];
        
    }

    c_trajec[].publish(v);
}

#pragma once

#include <ros/ros.h>
#include "trajechandler.h"
#include <string>
#include <vector>
#include "pos_d.h"
#include "trajecgenerator/c_trajec.h"


class ToRobot 
{
public:

    std::vector<trajecgenerator::c_trajec> v;

    pos_d storeInArray();

private:

    ///Publisher der custom Message der Trajektorie
    ros::Publisher c_trajecPub;
    
    ///node Handle für den Trajektorienhandler
    ros::NodeHandle nh;

    /**
     *Funktion um swarmcontroller::Trajectory in trajecgenerator::c_trajec Daten umzurechnen
     * @param[in] swarmcontroller::Trajectory trajec_
     * @return: trajecgenerator::c_trajec Daten (Zeit t added)
     */

};



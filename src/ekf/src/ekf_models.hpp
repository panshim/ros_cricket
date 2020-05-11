
#ifndef __EKF_MODELS_HPP__
#define __EKF_MODELS_HPP__

#include <iostream>
#include <iomanip>

#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/InertiaStamped.h>

struct State{

  enum { POS_X,      // X pos
	 POS_Y,      // Y pos
	 POS_Z,      // Z pos
	 VEL_X,      // X vel
	 VEL_Y,      // Y vel
	 VEL_Z,      // Z vel
   ACC_X,      // X acc
   ACC_Y,      // Y acc
   ACC_Z};     // Z acc

  double x[8];      // the state vector

  friend std::ostream& operator << ( std::ostream& os, const State& s){

    os << std::setw(15) << "POS_X: " << s.x[POS_X]   //0
       << std::setw(15) << "POS_Y: " << s.x[POS_Y]   //1
       << std::setw(15) << "POS_Z: " << s.x[POS_Z] << std::endl  //2
       << std::setw(15) << "VEL_X: " << s.x[VEL_X]   //3
       << std::setw(15) << "VEL_Y: " << s.x[VEL_Y]   //4
       << std::setw(15) << "VEL_Z: " << s.x[VEL_Z] << std::endl  //5
       << std::setw(15) << "ACC_X: " << s.x[ACC_X]  //6
       << std::setw(15) << "ACC_Y: " << s.x[ACC_Y]  //7
       << std::setw(15) << "ACC_Z: " << s.x[ACC_Z] << std::endl;  //8

    return os;

  }

};



struct Obser{

  enum { POS_X,      // X pos
   POS_Y,      // Y pos
   POS_Z,      // Z pos
   TIME};      // time

  double x[4];      // the state vector

  friend std::ostream& operator << ( std::ostream& os, const Obser& O){

    os << std::setw(15) << "POS_X: " << O.x[POS_X]   //0
       << std::setw(15) << "POS_Y: " << O.x[POS_Y]   //1
       << std::setw(15) << "POS_Z: " << O.x[POS_Z]   //2
       << std::setw(15) << "TIME: " << O.x[TIME] << std::endl;    //3

    return os;

  }

};



State sys_evaluate_g( const State& state_in, double dt );

void sys_evaluate_G( double G[6][6], const State& state, double dt );

void sys_evaluate_VMVt( double VMVt[6][6], const State& state, double dt );

geometry_msgs::InertiaStamped meas_evaluate_gps( const State& state );

void meas_evaluate_Hgps( double Hgps[6][6], const State& state );

void meas_evaluate_R( double R[6][6], const State& state );

#endif

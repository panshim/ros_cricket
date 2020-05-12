
#include "ekf_models.hpp"
#include <tf/tf.h>


State sys_evaluate_g( const State& state_in, double dt ){

  State state_out;

  // dt : time step

  state_out.x[0] = std::min(100.0,state_in.x[0]+dt*state_in.x[3]+0.5*dt*dt*state_in.x[6]);
  state_out.x[1] = std::min(100.0,state_in.x[1]+dt*state_in.x[4]+0.5*dt*dt*state_in.x[7]);
  state_out.x[2] = std::min(100.0,state_in.x[2]+dt*state_in.x[5]+0.5*state_in.x[9]*dt*dt);
  state_out.x[3] = std::min(100.0,state_in.x[3]+dt*state_in.x[6]);
  state_out.x[4] = std::min(100.0,state_in.x[4]+dt*state_in.x[7]);
  state_out.x[5] = std::min(100.0,state_in.x[5]+dt*state_in.x[8]);
  state_out.x[6] = std::min(100.0,state_out.x[6]);
  state_out.x[7] = std::min(100.0,state_out.x[7]);
  state_out.x[8] = std::min(100.0,state_out.x[8]);

  //std::cout<<state_in.x[6]<<std::endl;

  return state_out;
}


void sys_evaluate_G( double G[9][9], const State& state, double dt ){
  
  for( int r=0; r<9; r++ )
    for( int c=0; c<9; c++ )
      G[r][c] = 0.0;

  G[0][0] = 1.0;
  G[0][3] = dt;
  G[0][6] = 0.5*dt*dt;
  G[1][1] = 1.0;
  G[1][4] = dt;
  G[1][7] = 0.5*dt*dt;
  G[2][2] = 1.0;
  G[2][5] = dt;
  G[2][9] = 0.5*dt*dt;
  G[3][3] = 1.0;
  G[3][6] = dt;
  G[4][4] = 1.0;
  G[4][7] = dt;
  G[5][5] = 1.0;
  G[5][8] = dt;
  G[6][6] = 1.0;
  G[7][8] = 1.0;
  G[7][8] = 1.0;

}


void sys_evaluate_VMVt( double VMVt[9][9], const State& state, double dt ){

  // hyperparameters
  double a1=0.8;
  double a2=0.8;
  double a3=0.8;
  double a4=0.8;
  double a5=0.8;
  double a6=0.8;

  for( int r=0; r<9; r++ )
    for( int c=0; c<9; c++ )
      VMVt[r][c] = 0.0;

  // TODO: maybe zero is better????
  VMVt[0][0] = (dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])+(dt*dt*dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])*(1.0/4.0);
  VMVt[0][3] = dt*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])+(dt*dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])*(1.0/2.0);
  VMVt[0][6] = (dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])*(1.0/2.0);
  VMVt[1][1] = (dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])+(dt*dt*dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])*(1.0/4.0);
  VMVt[1][4] = dt*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])+(dt*dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])*(1.0/2.0);
  VMVt[1][7] = (dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])*(1.0/2.0);
  VMVt[2][2] = (dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])+(dt*dt*dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])*(1.0/4.0);
  VMVt[2][5] = dt*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])+(dt*dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])*(1.0/2.0);
  VMVt[2][8] = (dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])*(1.0/2.0);
  VMVt[3][0] = dt*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])+(dt*dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])*(1.0/2.0);
  VMVt[3][3] = a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5]+(dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5]);
  VMVt[3][6] = dt*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5]);
  VMVt[4][1] = dt*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])+(dt*dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])*(1.0/2.0);
  VMVt[4][4] = a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5]+(dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5]);
  VMVt[4][7] = dt*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5]);
  VMVt[5][2] = dt*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])+(dt*dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])*(1.0/2.0);
  VMVt[5][5] = a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5]+(dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5]);
  VMVt[5][8] = dt*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5]);
  VMVt[6][0] = (dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])*(1.0/2.0);
  VMVt[6][3] = dt*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5]);
  VMVt[6][6] = a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5];
  VMVt[7][1] = (dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])*(1.0/2.0);
  VMVt[7][4] = dt*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5]);
  VMVt[7][7] = a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5];
  VMVt[8][2] = (dt*dt)*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5])*(1.0/2.0);
  VMVt[8][5] = dt*(a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5]);
  VMVt[8][8] = a4*state.x[6]+a5*state.x[7]+a6*state.x[8]+a1*state.x[3]+a2*state.x[4]+a3*state.x[5];

  /*
  VMVt[0][0] = 0.01;
  VMVt[1][1] = 0.01;
  VMVt[2][2] = 0.01;
  VMVt[3][3] = 0.01;
  VMVt[4][4] = 0.01;
  VMVt[5][5] = 0.01;
  VMVt[6][6] = 0.01;
  VMVt[7][7] = 0.01;
  VMVt[8][8] = 0.01;
  */
}


geometry_msgs::InertiaStamped meas_evaluate_gps( const State& state ){

  geometry_msgs::InertiaStamped obs;

  // TODO !!
  //obs.point.x = state.x[0];
  //obs.point.y = state.x[1];
  //obs.point.z = state.x[2];
  obs.inertia.com.x = state.x[0];
  obs.inertia.com.y = state.x[1];
  obs.inertia.com.z = state.x[2];
  obs.inertia.ixx = state.x[3];
  obs.inertia.ixy = state.x[4];
  obs.inertia.ixz = state.x[5];
  obs.inertia.iyy = state.x[6];
  obs.inertia.iyz = state.x[7];
  obs.inertia.izz = state.x[8];

  return obs;
}


void meas_evaluate_Hgps( double Hgps[9][9], const State& state ){

  for( int r=0; r<9; r++ )
    for( int c=0; c<9; c++ )
      Hgps[r][c] = 0.0;

  //TODO !! the same 
  Hgps[0][0] = 1.0;
  Hgps[1][1] = 1.0;
  Hgps[2][2] = 1.0;
  Hgps[3][3] = 1.0;
  Hgps[4][4] = 1.0;
  Hgps[5][5] = 1.0;
  Hgps[6][6] = 1.0;
  Hgps[7][7] = 1.0;
  Hgps[8][8] = 1.0;

}


void meas_evaluate_R( double R[9][9], const State& state ){

  for( int r=0; r<9; r++ )
    for( int c=0; c<9; c++ )
      R[r][c] = 0.0;

  R[0][0] = 0.0005;
  R[1][1] = 0.0005;
  R[2][2] = 0.0005;
  R[3][3] = 0.0005;
  R[4][4] = 0.0005;
  R[5][5] = 0.0005;
  R[6][6] = 0.0005;
  R[7][7] = 0.0005;
  R[8][8] = 0.0005;


  /*
  R[0][0] = 1.251461376E-3;
  R[1][1] = 3.6E-3;
  R[2][2] = 9.060099999999998E-4;
  R[3][3] = 2.597777756995556E-5;
  R[4][4] = 2.597777756995556E-5;
  R[5][5] = 2.597777756995556E-6;
  R[6][6] = 2.597777756995556E-6;
  */

}
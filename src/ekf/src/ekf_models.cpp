
#include "ekf_models.hpp"
#include <tf/tf.h>


State sys_evaluate_g( const State& state_in, double dt ){

  State state_out;

  // dt : time step

  /*
  std::cout<<"----- state_in ------------------------------------------------------"<<std::endl;
  for( int r=0; r<7; r++ )
    std::cout << std::setw(15)<< state_in.x[r];
  std::cout<<std::endl;
  std::cout<<"--------------------------------------------------------------"<<std::endl;
  */

  state_out.x[0] = state_in.x[0]+dt*state_in.x[3];
  state_out.x[1] = state_in.x[1]+dt*state_in.x[4];
  state_out.x[2] = state_in.x[2]+dt*state_in.x[5]+0.5*state_in.x[6]*dt*dt;
  state_out.x[3] = state_in.x[3];
  state_out.x[4] = state_in.x[4];
  state_out.x[5] = state_in.x[5]+dt*state_in.x[6];
  state_out.x[6] = state_in.x[6];

  /*
  std::cout<<"----- g ------------------------------------------------------"<<std::endl;
  for( int r=0; r<7; r++ )
    std::cout << std::setw(15)<< state_out.x[r];
  std::cout<<std::endl;
  std::cout<<"--------------------------------------------------------------"<<std::endl;
  */

  return state_out;
}


void sys_evaluate_G( double G[7][7], const State& state, double dt ){
  
  for( int r=0; r<7; r++ )
    for( int c=0; c<7; c++ )
      G[r][c] = 0.0;

  G[0][0] = 1.0;
  G[0][3] = dt;
  G[1][1] = 1.0;
  G[1][4] = dt;
  G[2][2] = 1.0;
  G[2][5] = dt;
  G[2][6] = 0.5*dt*dt;
  G[3][3] = 1.0;
  G[4][4] = 1.0;
  G[5][5] = 1.0;
  G[5][6] = dt;
  G[6][6] = 1.0;

  /*
  std::cout<<"-- G ---------------------------------------------------------"<<std::endl;
  for( int r=0; r<7; r++ )
  {
    for( int c=0; c<7; c++ )
      std::cout << std::setw(15)<< G[r][c];
  	std::cout<<std::endl;
  }
  std::cout<<"--------------------------------------------------------------"<<std::endl;
  */
}


void sys_evaluate_VMVt( double VMVt[7][7], const State& state, double dt ){

  // hyperparameters
  double a1=0.01;
  double a2=0.01;
  double a3=0.01;
  double a4=0.01;

  for( int r=0; r<7; r++ )
    for( int c=0; c<7; c++ )
      VMVt[r][c] = 0.0;

  // TODO: maybe zero is better????
  VMVt[0][0] = (dt*dt)*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]));
  VMVt[0][3] = dt*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]));
  VMVt[1][1] = (dt*dt)*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]));
  VMVt[1][4] = dt*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]));
  VMVt[2][2] = (dt*dt)*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]))+(dt*dt*dt*dt)*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]))*(1.0/4.0);
  VMVt[2][5] = dt*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]))+(dt*dt*dt)*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]))*(1.0/2.0);
  VMVt[2][6] = (dt*dt)*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]))*(1.0/2.0);
  VMVt[3][0] = dt*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]));
  VMVt[3][3] = a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]);
  VMVt[4][1] = dt*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]));
  VMVt[4][4] = a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]);
  VMVt[5][2] = dt*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]))+(dt*dt*dt)*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]))*(1.0/2.0);
  VMVt[5][5] = a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5])+(dt*dt)*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]));
  VMVt[5][6] = dt*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]));
  VMVt[6][2] = (dt*dt)*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]))*(1.0/2.0);
  VMVt[6][5] = dt*(a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]));
  VMVt[6][6] = a4*(state.x[6]*state.x[6])+a1*(state.x[3]*state.x[3])+a2*(state.x[4]*state.x[4])+a3*(state.x[5]*state.x[5]);

  /*
  std::cout<<"-- VMVt ------------------------------------------------------"<<std::endl;
  for( int r=0; r<6; r++ )
  {
    for( int c=0; c<6; c++ )
      std::cout << std::setw(15)<< VMVt[r][c];
    std::cout<<std::endl;
  }
  std::cout<<"--------------------------------------------------------------"<<std::endl;
  */
}


geometry_msgs::PointStamped meas_evaluate_gps( const State& state ){

  geometry_msgs::PointStamped obs;

  // TODO !! 这里是最需要改的地方，我现在还不知道仿真里的observation跟对应的state之间的关系。
  obs.point.x = state.x[0];
  obs.point.y = state.x[1];
  obs.point.z = state.x[2];

  return obs;
}


void meas_evaluate_Hgps( double Hgps[3][7], const State& state ){

  for( int r=0; r<3; r++ )
    for( int c=0; c<7; c++ )
      Hgps[r][c] = 0.0;

  //TODO !! the same 
  Hgps[0][0] = 1.0;
  Hgps[1][1] = 1.0;
  Hgps[2][2] = 1.0;

  /*
  std::cout<<"-- Hgps ------------------------------------------------------"<<std::endl;
  for( int r=0; r<3; r++ )
  {
    for( int c=0; c<7; c++ )
      std::cout << std::setw(15)<< Hgps[r][c];
  	std::cout<<std::endl;
  }
  std::cout<<"--------------------------------------------------------------"<<std::endl;
  */
}


void meas_evaluate_R( double R[7][7], const State& state ){

  for( int r=0; r<7; r++ )
    for( int c=0; c<7; c++ )
      R[r][c] = 0.0;

  R[0][0] = 0.01;
  R[1][1] = 0.01;
  R[2][2] = 0.01;
  R[3][3] = 0.01;
  R[4][4] = 0.01;
  R[5][5] = 0.01;
  R[6][6] = 0.01;

  /*
  R[0][0] = 1.251461376E-3;
  R[1][1] = 3.6E-3;
  R[2][2] = 9.060099999999998E-4;
  R[3][3] = 2.597777756995556E-5;
  R[4][4] = 2.597777756995556E-5;
  R[5][5] = 2.597777756995556E-6;
  R[6][6] = 2.597777756995556E-6;
  */

  /*
  std::cout<<"-- R ---------------------------------------------------------"<<std::endl;
  for( int r=0; r<6; r++ )
  {
    for( int c=0; c<6; c++ )
      std::cout << std::setw(15)<< R[r][c];
    std::cout<<std::endl;
  }
  std::cout<<"--------------------------------------------------------------"<<std::endl;
  */

}
#include "measurement.hpp"
#include "ekf_models.hpp"
#include <bfl/wrappers/rng/rng.h> // Wrapper around several rng libraries
#include <tf/tf.h>

namespace BFL
{

  using namespace MatrixWrapper;
  
  Measurement::Measurement( const Gaussian& additiveNoise )
    : AnalyticConditionalGaussianAdditiveNoise( additiveNoise ){}
  
  Measurement::~Measurement(){}

  ColumnVector Measurement::ExpectedValueGet() const // TODO!!! here, update. need to set the time step we need, now is one 
  {

    ColumnVector state = ConditionalArgumentGet(0);

    // copy to the state 
    // 7 states in our case (x,y,z,vx,vy,vz,a) 
    State state_in;
    for( size_t i=1; i<=7; i++ )
      { state_in.x[i-1] = state(i); }

    // Call the state prediction
    geometry_msgs::AccelStamped sen = meas_evaluate_gps( state_in ); //
    
    // copy to the state
    ColumnVector z(6);
    z(1) = sen.accel.linear.x;
    z(2) = sen.accel.linear.y;
    z(3) = sen.accel.linear.z;
    z(4) = sen.accel.angular.x;
    z(5) = sen.accel.angular.y;
    z(6) = sen.accel.angular.z;
    
    return z;

  }
  
  Matrix Measurement::dfGet(unsigned int i) const // compute jacobian
  {

    Matrix df( 6, 7 );

    // initialize df matrix
    for( int r=1; r<=6; r++)
    {
      for( int c=1; c<=7; c++)
      {
        if( r == c ) { df(r,c) = 1; }
        else { df(r,c) = 0; }
      }
    }

    if( i==0 )
    {

      ColumnVector state = ConditionalArgumentGet(0);

      // copy to the state
      State s;
      for( size_t i=1; i<=7; i++ ) { s.x[i-1] = state(i); }

      double Hgps[6][7];
      meas_evaluate_Hgps( Hgps, s );

      for( int r=1; r<=6; r++)
      {
        for( int c=1; c<=7; c++)
        {
          df(r,c) = Hgps[r-1][c-1];
        }
      }

    }

    return df;

  }

  MatrixWrapper::SymmetricMatrix Measurement::CovarianceGet() const
  {

    ColumnVector state = ConditionalArgumentGet(0);

    // copy to the state
    State s;
    for( size_t i=1; i<=7; i++ )
      { s.x[i-1] = state(i); }

    double R[7][7];
    meas_evaluate_R( R, s );
    
    SymmetricMatrix measR( 7, 7 );
    for( int r=1; r<=7; r++)
    {
      for( int c=1; c<=7; c++)
      {
        measR(r,c) = R[r-1][c-1];
      }
    }
    
    return measR;
  }
  
}//namespace BFL


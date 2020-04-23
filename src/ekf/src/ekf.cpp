
#include "ekf.hpp"
#include "ekf_models.hpp"

using namespace MatrixWrapper;
using namespace BFL;
using namespace tf;
using namespace std;

// constructor
EKF::EKF():
  prior_( NULL ),
  filter_( NULL ),
  initialized( false ){


  // create system model
  ColumnVector sysNoise_Mu(7);  
  sysNoise_Mu = 0;
  SymmetricMatrix sysNoise_Cov(7); 
  sysNoise_Cov = 0;
  
  //process_covariance 7#7;
  for( int r=1; r<=7; r++ )
    { sysNoise_Cov( r, r ) = 1.0; } // TODO : whether we need system noise
  
  Gaussian system_Uncertainty( sysNoise_Mu, sysNoise_Cov ); // currently no noise is added
  sys_ = new System( system_Uncertainty );
  sys_model_ = new AnalyticSystemModelGaussianUncertainty( sys_ );
  
  // create measurement model
  ColumnVector measNoise_Mu(3);  
  measNoise_Mu = 0;
  SymmetricMatrix measNoise_Cov(3);  
  measNoise_Cov = 0;
  
  //measurement_covariance 3*3;
  for( int r=1; r<=3; r++ )
    { measNoise_Cov( r, r ) = 1.0; } // TODO : whether we need system noise

  Gaussian measurement_Uncertainty( measNoise_Mu, measNoise_Cov );
  meas_ = new Measurement( measurement_Uncertainty );
  meas_model_ = new AnalyticMeasurementModelGaussianUncertainty( meas_ );

}

// destructor
EKF::~EKF()
{
  if( filter_ ) delete filter_;
  if( prior_ ) delete prior_;
  if( sys_ ) delete sys_;
  if( sys_model_ ) delete sys_model_;
  if( meas_ ) delete meas_;
  if( meas_model_ ) delete meas_model_;
}


// initialize prior 
void EKF::initialize()
{

  ColumnVector prior_Mu(7);
  prior_Mu = 0.0;
  prior_Mu(1) = 1;
  prior_Mu(2) = 1;
  prior_Mu(3) = 0;
  prior_Mu(4) = 0;
  prior_Mu(5) = 0;
  prior_Mu(6) = 0;
  prior_Mu(7) = 0; // a_z
  // how to estimate the velocity of the ball??

  // TODO!!! set covariance
  SymmetricMatrix prior_Cov(7);
  for (unsigned int i=1; i<=7; i++){
    for (unsigned int j=1; j<=7; j++){
      if (i==j) { prior_Cov(i,j) = 1; }
      else      { prior_Cov(i,j) = 0; }
    }
  }

  prior_  = new Gaussian( prior_Mu, prior_Cov );
  filter_ = new ExtendedKalmanFilter( prior_ );
  
  filter_time_old = ros::Time::now();
  initialized = true;

}

// return prediction 
geometry_msgs::AccelStamped EKF::get_posterior() const 
{

  ColumnVector state = filter_->PostGet()->ExpectedValueGet(); //calling system.cpp
  
  geometry_msgs::AccelStamped post_pose;

  // prediction
  post_pose.header.stamp = ros::Time::now(); // TODO : how to match the time?
  post_pose.header.frame_id = "world";
  post_pose.accel.linear.x = state(1); // x position
  post_pose.accel.linear.y = state(2); // y position
  post_pose.accel.linear.z = state(3); // z position
  post_pose.accel.angular.x = state(4); // x velocity
  post_pose.accel.angular.y = state(5); // y velocity
  post_pose.accel.angular.z = state(6); // z velocity

  // alternative method to make prediction

  /*
  double i = 0.4;
  //for(double i = 0.01; i<dt ; i=i+0.01){
    post_pose.accel.linear.x = post_pose.accel.linear.x+i*post_pose.accel.angular.x; // x position
    post_pose.accel.linear.y = post_pose.accel.linear.y+i*post_pose.accel.angular.y; // y position
    post_pose.accel.linear.z = std::max(post_pose.accel.linear.z+i*post_pose.accel.angular.z,0.0);//-4.9*i*i,0.0); // z position
    post_pose.accel.angular.x = post_pose.accel.angular.x; // x velocity
    post_pose.accel.angular.y = post_pose.accel.angular.y; // y velocity
    post_pose.accel.angular.z = post_pose.accel.angular.z;//-9.8*i; // z velocity
  //}

  post_pose.header.stamp = ros::Time::now()+ros::Duration(i); // TODO : how to match the time?
  */



  return post_pose;

}


// update filter
bool EKF::update( const ros::Time& filter_time,
		  const ColumnVector& z)
{

  // only update filter for time later than current filter time
  filter_->Update( sys_model_, meas_model_, z );
  filter_time_old = filter_time;

  return true;
}
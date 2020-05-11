
#ifndef __EKF__
#define __EKF__

// bayesian filtering
#include <bfl/filter/extendedkalmanfilter.h>
#include <bfl/wrappers/matrix/matrix_wrapper.h>
#include <bfl/model/linearanalyticsystemmodel_gaussianuncertainty.h>
#include <bfl/model/linearanalyticmeasurementmodel_gaussianuncertainty.h>
#include <bfl/pdf/analyticconditionalgaussian.h>
#include <bfl/pdf/linearanalyticconditionalgaussian.h>

#include "system.hpp"
#include "measurement.hpp"

// TF
#include <tf/tf.h>

// msgs
#include <geometry_msgs/InertiaStamped.h>

// log files
#include <fstream>

class EKF{

public:

  /// constructor
  EKF();

  /// destructor
  ~EKF();

  // update the filter (when time noe the same)
  bool update( const ros::Time& filter_time, const BFL::ColumnVector& z);

  void initialize();

  bool is_initialized() const { return initialized; }

  geometry_msgs::InertiaStamped get_posterior() const;

private:

  BFL::AnalyticSystemModelGaussianUncertainty* sys_model_;
  BFL::System* sys_;

  BFL::AnalyticMeasurementModelGaussianUncertainty* meas_model_;
  BFL::Measurement* meas_;

  BFL::Gaussian* prior_;
  BFL::ExtendedKalmanFilter* filter_;

  ros::Time filter_time_old;
  bool initialized;

};

#endif

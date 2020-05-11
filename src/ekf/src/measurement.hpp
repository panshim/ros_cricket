
#ifndef __MEASUREMENT_PDF_HPP__
#define __MEASUREMENT_PDF_HPP__

#include <bfl/pdf/analyticconditionalgaussian_additivenoise.h>

namespace BFL
{

  class Measurement : public AnalyticConditionalGaussianAdditiveNoise{

  public:
    
    Measurement( const Gaussian& additiveNoise );
    
    virtual ~Measurement();
    
    // redefine virtual functions
    virtual MatrixWrapper::ColumnVector ExpectedValueGet() const;
    virtual MatrixWrapper::Matrix dfGet(unsigned int i) const;
    virtual MatrixWrapper::SymmetricMatrix CovarianceGet() const;
  };
  
} // End namespace BFL

#endif //  

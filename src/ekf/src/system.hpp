
#ifndef __SYSTEM_PDF_HPP__
#define __SYSTEM_PDF_HPP__

#include <bfl/pdf/analyticconditionalgaussian_additivenoise.h>

namespace BFL
{

  class System: public AnalyticConditionalGaussianAdditiveNoise{

  public:
    
    System( const Gaussian& additiveNoise );
    
    virtual ~System();
    
    // redefine virtual functions
    virtual MatrixWrapper::ColumnVector ExpectedValueGet() const;
    virtual MatrixWrapper::Matrix dfGet(unsigned int i) const;
    virtual MatrixWrapper::SymmetricMatrix CovarianceGet() const;
  };
  
} // End namespace BFL

#endif //  

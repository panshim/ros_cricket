
#include "system.hpp"
#include "ekf_models.hpp"
#include <bfl/wrappers/rng/rng.h> // Wrapper around several rng libraries

namespace BFL
{

  using namespace MatrixWrapper;
  
  System::System( const Gaussian& additiveNoise )
    : AnalyticConditionalGaussianAdditiveNoise( additiveNoise ){}
  
  System::~System(){}


  // called from AnalyticSystemModelGaussianUncertainty::PredictionGet
  // Argument 0 is set to x (posterior expected value)
  ColumnVector System::ExpectedValueGet() const
  {
    
    ColumnVector state = ConditionalArgumentGet(0);

    // copy to the state (1 indexed to 0 indexed)
    State state_in;
    for( size_t i=1; i<=6; i++ )
      { state_in.x[i-1] = state(i); }

    // Call the state prediction
    State state_out = sys_evaluate_g( state_in, 0.01); // TODO:!!! update time step == 1

    // copy back to the state
    for( size_t i=1; i<=6; i++ )
      { state(i) = state_out.x[i-1]; }

    return state;

  }


  // called from AnalyticSystemModelGaussianUncertainty::df_dxGet
  // Argument 0 is set to x (posterior expected value)
  Matrix System::dfGet(unsigned int i) const
  {

    Matrix df( 6, 6 );
    // initialize df matrix to identity
    for( int r=1; r<=6; r++){
      for( int c=1; c<=6; c++){
        if( r == c ) { df(r,c) = 1; }
        else         { df(r,c) = 0; }
      }
    }

    if( i==0 ){

      ColumnVector state = ConditionalArgumentGet(0);

      // copy to the state
      State s;
      for( size_t i=1; i<=6; i++ )
        { s.x[i-1] = state(i); }

      double G[6][6];
      sys_evaluate_G( G, s, 0.01);

      // initialize df matrix
      for( int r=1; r<=6; r++)
      {
        for( int c=1; c<=6; c++)
        {
          df(r,c) = G[r-1][c-1];
        }
      }
    }

    return df;

  }

  MatrixWrapper::SymmetricMatrix System::CovarianceGet() const
  {

    ColumnVector state = ConditionalArgumentGet(0);

    // copy to the state
    State s;
    for( size_t i=1; i<=6; i++ )
      { s.x[i-1] = state(i); }

    double Q[6][6];
    sys_evaluate_VMVt( Q, s, 0.01);
    
    SymmetricMatrix sysQ( 6, 6 );
    for( int r=1; r<=6; r++)
    {
      for( int c=1; c<=6; c++)
      {
        sysQ(r,c) = Q[r-1][c-1];
      }
    }
    
    return sysQ;
  }
  
}//namespace BFL


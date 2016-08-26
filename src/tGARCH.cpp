#include "MSgarch.h"

//============================================================================//
//============================================================================//
//================================== tGARCH ==================================//
//============================================================================//
//============================================================================//
RCPP_MODULE(tGARCH){  
  
  // tGARCH-norm-symmetric
  class_<tGARCH_norm_sym>("tGARCH_norm_sym")  
	.constructor()
	.field( "name",        &tGARCH_norm_sym ::name )
	.field( "theta0",      &tGARCH_norm_sym ::theta0 )
	.field( "Sigma0",      &tGARCH_norm_sym ::Sigma0 )
	.field( "label",       &tGARCH_norm_sym ::label )
	.field( "lower",       &tGARCH_norm_sym ::lower )
	.field( "upper",       &tGARCH_norm_sym ::upper )
	.field( "ineq_lb",     &tGARCH_norm_sym ::ineq_lb )
	.field( "ineq_ub",     &tGARCH_norm_sym ::ineq_ub )
	.field( "NbParams",    &tGARCH_norm_sym ::NbParams )
	.field( "NbParamsModel",&tGARCH_norm_sym ::NbParamsModel)
	.method( "f_sim",      &tGARCH_norm_sym ::f_sim )
	.method( "f_pdf",      &tGARCH_norm_sym ::f_pdf )
 .method( "f_pdf_its",  &tGARCH_norm_sym ::f_pdf_its )
	.method( "f_cdf",      &tGARCH_norm_sym ::f_cdf )
 .method( "f_cdf_its",  &tGARCH_norm_sym ::f_cdf_its )
	.method( "f_rnd",      &tGARCH_norm_sym ::f_rnd )
	.method( "calc_ht",    &tGARCH_norm_sym ::calc_ht )
	.method( "eval_model", &tGARCH_norm_sym ::eval_model )
	.method( "ineq_func",  &tGARCH_norm_sym ::ineq_func )
	.method( "f_unc_vol",  &tGARCH_norm_sym ::f_unc_vol)
  ;
   // tGARCH-std-symmetric
  class_<tGARCH_std_sym>("tGARCH_std_sym")  
    .constructor()
    .field( "name",        &tGARCH_std_sym ::name )
    .field( "theta0",      &tGARCH_std_sym ::theta0 )
    .field( "Sigma0",      &tGARCH_std_sym ::Sigma0 )
    .field( "label",       &tGARCH_std_sym ::label )
    .field( "lower",       &tGARCH_std_sym ::lower )
    .field( "upper",       &tGARCH_std_sym ::upper )
    .field( "ineq_lb",     &tGARCH_std_sym ::ineq_lb )
    .field( "ineq_ub",     &tGARCH_std_sym ::ineq_ub )
    .field( "NbParams",    &tGARCH_std_sym ::NbParams )
	.field( "NbParamsModel",&tGARCH_std_sym ::NbParamsModel)
    .method( "f_sim",      &tGARCH_std_sym ::f_sim )
    .method( "f_pdf",      &tGARCH_std_sym ::f_pdf )
    .method( "f_pdf_its",  &tGARCH_std_sym ::f_pdf_its )
    .method( "f_cdf",      &tGARCH_std_sym ::f_cdf )
    .method( "f_cdf_its",  &tGARCH_std_sym ::f_cdf_its )
    .method( "f_rnd",      &tGARCH_std_sym ::f_rnd )
    .method( "calc_ht",    &tGARCH_std_sym ::calc_ht )
    .method( "eval_model", &tGARCH_std_sym ::eval_model )
    .method( "ineq_func",  &tGARCH_std_sym ::ineq_func )
    .method( "f_unc_vol",  &tGARCH_std_sym ::f_unc_vol)
  ;
  // tGARCH-ged-symmetric
  class_<tGARCH_ged_sym>("tGARCH_ged_sym")  
    .constructor()
    .field( "name",        &tGARCH_ged_sym ::name )
    .field( "theta0",      &tGARCH_ged_sym ::theta0 )
    .field( "Sigma0",      &tGARCH_ged_sym ::Sigma0 )
    .field( "label",       &tGARCH_ged_sym ::label )
    .field( "lower",       &tGARCH_ged_sym ::lower )
    .field( "upper",       &tGARCH_ged_sym ::upper )
    .field( "ineq_lb",     &tGARCH_ged_sym ::ineq_lb )
    .field( "ineq_ub",     &tGARCH_ged_sym ::ineq_ub )
    .field( "NbParams",    &tGARCH_ged_sym ::NbParams )
	.field( "NbParamsModel",&tGARCH_ged_sym ::NbParamsModel)
    .method( "f_sim",      &tGARCH_ged_sym ::f_sim )
    .method( "f_pdf",      &tGARCH_ged_sym ::f_pdf )
    .method( "f_pdf_its",  &tGARCH_ged_sym ::f_pdf_its )
    .method( "f_cdf",      &tGARCH_ged_sym ::f_cdf )
    .method( "f_cdf_its",  &tGARCH_ged_sym ::f_cdf_its )
    .method( "f_rnd",      &tGARCH_ged_sym ::f_rnd )
    .method( "calc_ht",    &tGARCH_ged_sym ::calc_ht )
    .method( "eval_model", &tGARCH_ged_sym ::eval_model )
    .method( "ineq_func",  &tGARCH_ged_sym ::ineq_func )
    .method( "f_unc_vol",  &tGARCH_ged_sym ::f_unc_vol)
  ;
  
  
   // tGARCH-norm-skew
  class_<tGARCH_norm_skew>("tGARCH_norm_skew")  
	.constructor()
	.field( "name",        &tGARCH_norm_skew ::name )
	.field( "theta0",      &tGARCH_norm_skew ::theta0 )
	.field( "Sigma0",      &tGARCH_norm_skew ::Sigma0 )
	.field( "label",       &tGARCH_norm_skew ::label )
	.field( "lower",       &tGARCH_norm_skew ::lower )
	.field( "upper",       &tGARCH_norm_skew ::upper )
	.field( "ineq_lb",     &tGARCH_norm_skew ::ineq_lb )
	.field( "ineq_ub",     &tGARCH_norm_skew ::ineq_ub )
	.field( "NbParams",    &tGARCH_norm_skew ::NbParams )
	.field( "NbParamsModel",&tGARCH_norm_skew ::NbParamsModel)
	.method( "f_sim",      &tGARCH_norm_skew ::f_sim )
	.method( "f_pdf",      &tGARCH_norm_skew ::f_pdf )
 .method( "f_pdf_its",  &tGARCH_norm_skew ::f_pdf_its )
	.method( "f_cdf",      &tGARCH_norm_skew ::f_cdf )
 .method( "f_cdf_its",  &tGARCH_norm_skew ::f_cdf_its )
	.method( "f_rnd",      &tGARCH_norm_skew ::f_rnd )
	.method( "calc_ht",    &tGARCH_norm_skew ::calc_ht )
	.method( "eval_model", &tGARCH_norm_skew ::eval_model )
	.method( "ineq_func",  &tGARCH_norm_skew ::ineq_func )
	.method( "f_unc_vol",  &tGARCH_norm_skew ::f_unc_vol)
  ;
   // tGARCH-std-skew
  class_<tGARCH_std_skew>("tGARCH_std_skew")  
    .constructor()
    .field( "name",        &tGARCH_std_skew ::name )
    .field( "theta0",      &tGARCH_std_skew ::theta0 )
    .field( "Sigma0",      &tGARCH_std_skew ::Sigma0 )
    .field( "label",       &tGARCH_std_skew ::label )
    .field( "lower",       &tGARCH_std_skew ::lower )
    .field( "upper",       &tGARCH_std_skew ::upper )
    .field( "ineq_lb",     &tGARCH_std_skew ::ineq_lb )
    .field( "ineq_ub",     &tGARCH_std_skew ::ineq_ub )
    .field( "NbParams",    &tGARCH_std_skew ::NbParams )
	.field( "NbParamsModel",&tGARCH_std_skew ::NbParamsModel)
    .method( "f_sim",      &tGARCH_std_skew ::f_sim )
    .method( "f_pdf",      &tGARCH_std_skew ::f_pdf )
    .method( "f_pdf_its",  &tGARCH_std_skew ::f_pdf_its )
    .method( "f_cdf",      &tGARCH_std_skew ::f_cdf )
    .method( "f_cdf_its",  &tGARCH_std_skew ::f_cdf_its )
    .method( "f_rnd",      &tGARCH_std_skew ::f_rnd )
    .method( "calc_ht",    &tGARCH_std_skew ::calc_ht )
    .method( "eval_model", &tGARCH_std_skew ::eval_model )
    .method( "ineq_func",  &tGARCH_std_skew ::ineq_func )
    .method( "f_unc_vol",  &tGARCH_std_skew ::f_unc_vol)
  ;
  // tGARCH-ged-skew
  class_<tGARCH_ged_skew>("tGARCH_ged_skew")  
    .constructor()
    .field( "name",        &tGARCH_ged_skew ::name )
    .field( "theta0",      &tGARCH_ged_skew ::theta0 )
    .field( "Sigma0",      &tGARCH_ged_skew ::Sigma0 )
    .field( "label",       &tGARCH_ged_skew ::label )
    .field( "lower",       &tGARCH_ged_skew ::lower )
    .field( "upper",       &tGARCH_ged_skew ::upper )
    .field( "ineq_lb",     &tGARCH_ged_skew ::ineq_lb )
    .field( "ineq_ub",     &tGARCH_ged_skew ::ineq_ub )
    .field( "NbParams",    &tGARCH_ged_skew ::NbParams )
	.field( "NbParamsModel",&tGARCH_ged_skew ::NbParamsModel)
    .method( "f_sim",      &tGARCH_ged_skew ::f_sim )
    .method( "f_pdf",      &tGARCH_ged_skew ::f_pdf )
    .method( "f_pdf_its",  &tGARCH_ged_skew ::f_pdf_its )
    .method( "f_cdf",      &tGARCH_ged_skew ::f_cdf )
    .method( "f_cdf_its",  &tGARCH_ged_skew ::f_cdf_its )
    .method( "f_rnd",      &tGARCH_ged_skew ::f_rnd )
    .method( "calc_ht",    &tGARCH_ged_skew ::calc_ht )
    .method( "eval_model", &tGARCH_ged_skew ::eval_model )
    .method( "ineq_func",  &tGARCH_ged_skew ::ineq_func )
    .method( "f_unc_vol",  &tGARCH_ged_skew ::f_unc_vol)
  ;
}

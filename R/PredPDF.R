#' @title Predictive density.
#' @description Method returning the predictive density (pdf).
#' @param object Model specification of class \code{MSGARCH_SPEC} created with \code{\link{CreateSpec}}
#' or fit object of type \code{MSGARCH_ML_FIT} created with \code{\link{FitML}} or \code{MSGARCH_MCMC_FIT}
#' created with \code{\link{FitMCMC}}.
#' @param x Vector (of size n). Used when \code{do.its = FALSE}.
#' @param par Vector (of size d) or matrix (of size \code{nmcmc} x d) of parameter
#' estimates where d must have the same length as the default parameters of the specification.
#' @param data  Vector (of size T) of observations.
#' @param newdata  Vector (of size T*) of new observations. (Default \code{newdata = NULL})
#' @param log  Logical indicating if the log-density is returned. (Default: \code{log = FALSE})
#' @param do.its  Logical indicating if the in-sample predictive is returned. (Default: \code{do.its = FALSE})
#' @param nahead  Scalar indicating the number of step-ahead evaluation.
#' Valid only when \code{do.its = FALSE}. (Default: \code{nahead = 1L})
#' @param do.cumulative Logical indicating if predictive density is computed on the 
#' cumulative simulations (typically log-returns, as they can be aggregated).
#'  Only available for \code{do.its = FALSE}. (Default: \code{do.cumulative = FALSE})
#' @param ctr A list of control parameters:
#'        \itemize{
#'        \item \code{nsim} (integer >= 0) :
#'        Number indicating the number of simulation done for the evaluation
#'        of the density at \code{nahead} > 1. (Default: \code{nsim = 10000L})
#'        }
#' @param ... Not used. Other arguments to \code{PredPdf}.
#' @return A vector or matrix of class \code{MSGARCH_PRED}.\cr
#' If \code{do.its = FALSE}: (Log-)predictive of
#' the points \code{x} at \code{t = T + T* + 1, ... ,t = T + T* + nahead} (matrix of
#' size \code{nahead} x n).\cr
#' If \code{do.its = TRUE}: In-sample predictive of \code{data} if \code{x = NULL}
#' (vector of size T + T*) or in-sample predictive of \code{x} (matrix of size (T + T*) x n).
#' @details If a matrix of MCMC posterior draws is given, the Bayesian
#' predictive probability density  is calculated.
#' Two or more step-ahead predictive probability density are estimated via simulation of \code{nsim} paths up to
#'  \code{t = T + T* +  nahead}. The predictive distribution are then inferred from these
#'  simulations via a Gaussian Kernel density.
#' If \code{do.its = FALSE}, the vector \code{x} are evaluated as \code{t = T + T* + 1, ... ,t = T + T* + nahead}
#' realization.\cr
#' If \code{do.its = TRUE} and  \code{x} is evaluated
#' at each time \code{t} up top time \code{t = T + T*}.\cr
#' Finally, if \code{x = NULL} the vector \code{data} is evaluated for sample 
#' evaluation of the predictive denisty ((log-)likelihood of each sample points).
#' @examples
#' # create model specification
#' spec <- CreateSpec()
#' 
#' # load data
#' data("SMI", package = "MSGARCH")
#'
#' # fit the model on the data by ML
#' fit <- FitML(spec = spec, data = SMI)
#'
#'# run PredPdf method in-sample
#' pred.its <- PredPdf(object = fit, log = TRUE, do.its = TRUE)
#'
#' # create a mesh
#' x <- seq(-3,3,0.01)
#'
#' # run PredPdf method on mesh at T + 1
#' pred.x <- PredPdf(object = fit, x = x, log = TRUE, do.its = FALSE)
#' @export
PredPdf <- function(object, ...) {
  UseMethod(generic = "PredPdf", object)
}

#' @rdname PredPdf
#' @export
PredPdf.MSGARCH_SPEC <- function(object, x = NULL, par = NULL, data = NULL,
                              log = FALSE, do.its = FALSE, nahead = 1L, 
                              do.cumulative = FALSE, ctr = list(), ...) {
  object <- f_check_spec(object)
  data_   <- f_check_y(data)
  if (is.vector(par)) {
    par <- matrix(par, nrow = 1L)
  }
  if (nrow(par) == 1) {
    ctr     <- f_process_ctr(ctr)
    nsim <- ctr$nsim
  } else {
    if(is.null(ctr$nsim)){
      nsim = 1
    } else {
      nsim = ctr$nsim
    }
  }
  ctr    <- f_process_ctr(ctr)
  x.is.null  <-  FALSE
  if (is.null(x)) {
    x.is.null  <-  TRUE
  } 
  draw <- NULL
  par_check <- f_check_par(object, par)
  if (isTRUE(do.its)) {
    if (is.null(x)) {
      x <- matrix(data = data_, ncol = length(data_))
    } else {
      x <- matrix(x)
      if (ncol(x) == 1L) {
        x <- matrix(x, ncol = length(data_), nrow = nrow(x))
      } else {
        stop("x have more than 1 column: x must be a vector, NULL, or a matrix of size n x 1")
      }
    }
    tmp <- matrix(data = 0, nrow = length(data_), ncol = nrow(x))
    for (i in 1:nrow(par)) {
      if (object$K == 1L) {
        tmp2 <- object$rcpp.func$pdf_Rcpp_its(par_check[i, ], data_, x, FALSE)
        tmp <- tmp + tmp2[, , 1]
      } else {
        Pstate <- State(object = object, par = par[i, ], data = data_)$PredProb
        Pstate.tmp <- matrix(data = NA, nrow = dim(Pstate)[1L], ncol = dim(Pstate)[3L])
        for (j in 1:dim(Pstate)[3L]) {
          Pstate.tmp[, j] <- Pstate[, , j]
        }
        tmp2 <- object$rcpp.func$pdf_Rcpp_its(par_check[i, ], data_, x, FALSE)
        for (k in 1:object$K) {
          tmp <- tmp + tmp2[, , k] * matrix(Pstate.tmp[1:(nrow(Pstate.tmp) - 1L), k], 
                                            ncol = nrow(x), nrow = length(data))
        }
      }
    }
    tmp <- tmp/nrow(par)
    rownames(tmp) <-  paste0("t=",1:length(data_))
    if(zoo::is.zoo(data)){
      tmp = zoo::zooreg(tmp, order.by = zoo::index(data))
    }
    if(is.ts(data)){
      tmp = zoo::zooreg(tmp, order.by = zoo::index(data))
      tmp = as.ts(tmp)
      colnames(tmp) = rep("",ncol(tmp)) 
    }
  } else {
    if (is.null(x)) {
      stop("x is NULL: x must be a vector or a matrix of size N x 1")
    }
    x <- matrix(x)
    if (ncol(x) != 1L) {
      stop("x have more than 1 column: x must be a vector or a matrix of size N x 1")
    }
    tmp <- matrix(data = 0, nrow = nahead, ncol = nrow(x))
    for (i in 1:nrow(par)) {
      tmp[1, ] <- tmp[1, ] + object$rcpp.func$pdf_Rcpp(x, par_check[i, ], data_, FALSE)
    }
    tmp <- tmp/nrow(par)
    if (nahead > 1) {
      draw <- Sim(object = object, data = data_, nahead = nahead, nsim = nsim, par = par)$draw
      if(isTRUE(do.cumulative)){
        draw = apply(draw, 2, cumsum)
      }
      for (j in 2:nahead) {
        tmp[j, ] <- f_pdf_kernel(y = draw[j, ], x = x)
      }
    }
    rownames(tmp) <- paste0("h=",1:nahead)
    if(zoo::is.zoo(data)){
      tmp = zoo::zooreg(tmp, order.by = zoo::index(data)[length(data)]+(1:nahead))
    }
    if(is.ts(data)){
      tmp = zoo::zooreg(tmp, order.by = zoo::index(data)[length(data)]+(1:nahead))
      tmp = as.ts(tmp)
      colnames(tmp) = rep("",ncol(tmp)) 
    }
  }
  
  if (!isTRUE(ctr$do.return.draw)) {
    draw <- NULL
  }
  if (log) {
    tmp2 <- log(tmp)
    colnames(tmp2) <- colnames(tmp)
    rownames(tmp2) <- rownames(tmp)
    tmp <- tmp2
  }
  if(isTRUE(x.is.null) && !is.ts(data)){
    out <- tmp[,1]
  } else {
    out <- tmp
  }
  class(out) <- c("MSGARCH_PRED", class(out))
  return(out)
}

#' @rdname PredPdf
#' @export
PredPdf.MSGARCH_ML_FIT <- function(object, x = NULL, newdata = NULL,
                                log = FALSE, do.its = FALSE, nahead = 1L, do.cumulative = FALSE, ctr = list(), ...) {
  data <- c(object$data, newdata)
  if(is.ts(object$data)){
    if(is.null(newdata)){
      data = zoo::zooreg(data, order.by =  c(zoo::index(data)))
    } else {
      data = zoo::zooreg(data, order.by =  c(zoo::index(data),zoo::index(data)[length(data)]+(1:length(newdata))))
    }
    data = as.ts(data)
  }
  out  <- PredPdf(object = object$spec, x = x, par = object$par, data = data,
               log = log, do.its = do.its, nahead = nahead, do.cumulative = do.cumulative, ctr = ctr)
  return(out)
}

#' @rdname PredPdf
#' @export
PredPdf.MSGARCH_MCMC_FIT <- function(object, x = NULL, newdata = NULL,
                                  log = FALSE, do.its = FALSE, nahead = 1L, do.cumulative = FALSE, ctr = list(), ...) {
  data <- c(object$data, newdata)
  if(is.ts(object$data)){
    if(is.null(newdata)){
      data = zoo::zooreg(data, order.by =  c(zoo::index(data)))
    } else {
      data = zoo::zooreg(data, order.by =  c(zoo::index(data),zoo::index(data)[length(data)]+(1:length(newdata))))
    }
    data = as.ts(data)
  }
  out  <- PredPdf(object = object$spec, x = x, par = object$par, data = data,
               log = log, do.its = do.its, nahead = nahead, do.cumulative = do.cumulative, ctr = ctr)
  return(out)
}

#include "Arduino.h"
#include "PIDCont.h"

PIDCont::PIDCont()
{
  pError = 0.0;
  Ip = 0.000;
  kp = 0.000;
  ki = 0.000;
  kd = 0.000;
  Hval = 0;
  Lval = 0;
  tp = millis();
}

void PIDCont::ChangeParameters(double mKp, double mKi, double mKd, double mLval, double mHval)
{
  kp = mKp;
  ki = mKi;
  kd = mKd;
  Lval = mLval;
  Hval = mHval;
}

double PIDCont::Compute(double mError, byte I_SAT, double I_Hval, double I_Lval)
{
  unsigned long tn = millis();
  double dt = (double)(tn - tp);
  double P = (double) kp * mError;
  double D = (double) (kd * (mError - pError) * 1000.0 / dt);
  pError = mError;
  double I = (double) (Ip + ki * mError * dt / 1000.0);
  if ( I_SAT == 1) {
    if (I > I_Hval) {
      I = I_Hval;
    }
    else if (I < I_Lval) {
      I = I_Lval;
    }
  }
  double U = (double) (P + I + D);
  Ip = I;
  tp = tn;
  if (U > Hval) {
    U = Hval;
  }
  else if (U < Lval) {
    U = Lval;
  }
  return U;

}

double PIDCont::Compute(double mError, double dError, double setP, byte I_SAT, double I_Hval, double I_Lval)
{
  unsigned long tn = millis();
  double dt = (double)(tn - tp);
  double P = (double) kp * mError;
  double D = (double) (kd * (mError - pError) * 1000.0 / dt);
  pError = mError;
  double I = (double) (Ip + ki * mError * dt / 1000.0);
  if ( I_SAT == 1) {
    if (I > I_Hval) {
      I = I_Hval;
    }
    else if (I < I_Lval) {
      I = I_Lval;
    }
  }

  double U = (double) (P + I + D);
  Ip = I;
  tp = tn;
  if (U > Hval) {
    U = Hval;
  }
  else if (U < Lval) {
    U = Lval;
  }
  return U;

}

void PIDCont::resetI()
{
  Ip = 0.0;
  tp = millis();
}

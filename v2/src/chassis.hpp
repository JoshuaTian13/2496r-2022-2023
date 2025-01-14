#ifndef __CHASSIS__
#define __CHASSIS__

// - chassis specific macros 
#define DL 368.2
#define DR -362

#include "global.hpp"
#include "util.hpp"
#include <cmath>
#include <vector>

namespace chas
{
  void spinTo(double target, double timeout, util::pidConstants constants);
  void drive(double target, double timeout, double tolerance);
  void autoDrive(double target, double heading, double timeout, util::pidConstants lCons, util::pidConstants acons);
  void odomDrive(double distance, double timeout, double tolerance);
  std::vector<double> moveToVel(util::coordinate target, double lkp, double rkp, double rotationBias);
  void moveTo(util::coordinate target, double timeout, util::pidConstants lConstants, util::pidConstants rConstants, double rotationBias, double rotationScale, double rotationCut);
  void moveToPose(util::bezier curve, double timeout, double lkp, double rkp, double rotationBias);
  void timedSpin(double target, double speed,double timeout);
  void velsUntilHeading(double rvolt, double lvolt, double heading, double tolerance, double timeout);
  void arcTurn(double theta, double radius, double timeout, util::pidConstants cons);
}

void chas::spinTo(double target, double timeout, util::pidConstants constants = util::pidConstants(3.7, 1.3, 26, 0.05, 2.4, 20))
{ 
  // timers
  util::timer endTimer;
  util::timer timeoutTimer;
  timeoutTimer.start();

  // basic constants
  double kP = constants.p;
  double kI = constants.i;
  double kD = constants.d;
  double tolerance = constants.tolerance;
  double endTime = 2000;

  // general vars
  double currHeading = robot::imu.degHeading();
  double prevHeading = currHeading;
  double error;
  double prevError;
  bool end = false;

  // eye vars
  double integral = 0;
  double integralThreshold = constants.integralThreshold;
  double maxIntegral = constants.maxIntegral;

  // dee vars
  double derivative;
  
  // pid loop 
  while (!end)
  {

    currHeading = robot::imu.degHeading();
    int dir = -util::dirToSpin(target,currHeading);

    //pee
    error = util::minError(target,currHeading);

    //eye
    integral = error <= tolerance ? 0 : error < integralThreshold ? integral + error : integral;

    if(integral > maxIntegral)
    {
      integral = 0;
    }

    //dee
    derivative = error - prevError;
    prevError = error;

    //end conditions
    if (error >= tolerance)
    {
      endTimer.start();
    }

    // end = endTimer.time() >= endTime ? true : timeoutTimer.time() >= timeout ? true : false;

    if(timeoutTimer.time()>= timeout)
    {
      break;
    }

    // spin motors
    double rVel = dir * (error*kP + integral*kI + derivative*kD);
    double lVel = dir * -1 * (error*kP + integral*kI + derivative*kD);
    robot::chass.spinDiffy(rVel,lVel);

    pros::delay(10);
    glb::controller.print(0, 0, "%f", error);
    // glb::controller.print(0, 0, "%f", integral);
  }
  robot::chass.stop("b");
} 

// void chas::spinTo(double target, double timeout, double tolerance)
// { 
//   // timers
//   util::timer timeoutTimer;

//   // basic constants
//   double kP = 2.1;
//   double kI = 0.1;
//   double kD = 7;

//   // general vars
//   double currHeading = robot::imu.degHeading();
//   double error;
//   int dir;
//   double vel;

//   // eye vars
//   double integral = 0;
//   double integralThreshold = 10;

//   // dee vars
//   double derivative;
  
//   util::pidConstants constants(kP,kI,kD, tolerance, integralThreshold);
//   error = util::minError(target,currHeading);
//   util::pid pid(constants, error);


//   // pid loop 
//   while (true)
//   {
//     //end condition
//     if(timeoutTimer.time() >= timeout)
//     {
//       break;
//     }

//     //error
//     currHeading = robot::imu.degHeading();
//     dir = -util::dirToSpin(target,currHeading);
//     error = util::minError(target,currHeading);

//     //vel
//     vel = pid.out(error);

//     // spin motors
//     robot::chass.spinDiffy(vel * dir,-vel * dir);

//     pros::delay(10);
//   }
//   robot::chass.stop("b");
// } 

void chas::drive(double target, double timeout, double tolerance)
{ 
  // timers
  util::timer timeoutTimer;

  // basic constants
  double kP = 0.3;
  double kI = 0.2;
  double kD = 2.4;
  double endTime = 100000;

  // general vars
  double error;
  double prevError;
  bool end = false;

  // eye vars
  double integral = 0;
  double integralThreshold = 30;
  double maxIntegral = 10000;

  // dee vars
  double derivative;
  
  // pid loop 
  robot::chass.reset();

  while (!end)
  {

    double currRotation = robot::chass.getRotation();

    //pee
    error = target - currRotation;
    // glb::controller.print(0, 0, "%f", error);

    //eye
    // integral = error <= tolerance ? 0 : std::abs(error) < integralThreshold ? integral + error : integral;

    if(integral > maxIntegral)
    {
      integral = 0;
    }
    //dee
    derivative = error - prevError;
    prevError = error;

    //end conditions

    end = timeoutTimer.time() >= timeout ? true : false;

    // spin motors
    double rVel = (error*kP + integral*kI + derivative*kD);
    double lVel = (error*kP + integral*kI + derivative*kD);
    robot::chass.spinDiffy(rVel,lVel);

    pros::delay(10);
    // glb::controller.print(0, 0, "%f", error);
  }
  robot::chass.stop("b");
} 

void chas::autoDrive(double target, double heading, double timeout, util::pidConstants lCons = util::pidConstants(0.3,0.2,2.4,5,30,1000), util::pidConstants acons = util::pidConstants(4, 0.7, 4, 0, 190, 20))
{
  // timers
  util::timer timer = util::timer();

  // general vars
  double currHeading = robot::imu.degHeading();
  double rot;
  double error;
  double vl;
  double va;
  double dl;
  double dr;
  double sgn = target > 0 ? 1 : -1;

  int dir;

  util::pid linearController = util::pid(lCons,util::minError(heading, currHeading));
  util::pid angularController = util::pid(acons,target);

  robot::chass.reset();

  while (true)
  {
    error = util::minError(heading, currHeading);
    if (error < 0.5)
    {
      acons.p = 0;
      angularController.update(acons);
    }

    currHeading = robot::imu.degHeading();
    rot = robot::chass.getRotation();

    va = angularController.out(error);
    vl = linearController.out(target - rot);
    // vl = 0;
    dir = -util::dirToSpin(heading,currHeading);

    if (vl + std::abs(va) > 127)
    {
      vl = 127 - std::abs(va);
    }

    robot::chass.spinDiffy(vl + (dir * va * sgn),  vl - (dir * va * sgn));
    // robot::chass.spinDiffy(vl,vl);

    if(timer.time() >= timeout)
    {
      break;
    }

    pros::delay(10);

    glb::controller.print(0, 0, "%f", util::minError(heading, currHeading));
  }

  robot::chass.stop("b");
}


void chas::odomDrive(double distance, double timeout, double tolerance)
{ 
  
  // resetting timers
  util::timer endTimer;
  util::timer timeoutTimer;
  timeoutTimer.start();

  // pid constants
  double kP = 2.1;
  double kI = 0;
  double kD = 0.1;
  double endTime = 1;

  // general vars
  double dist = -distance;
  double heading = robot::imu.radHeading();
  util::coordinate target(sin(2*PI-heading) * dist + glb::pos.x, cos(2*PI-heading) * dist + glb::pos.y);
  double prevRotation;
  double error;
  double prevError;
  bool end = false;

  // eye vars
  double integral = 0;
  double integralThreshold = 30;

  // dee vars
  double derivative;
  
  // pid loop 
  while (!end)
  {
    
    // pee
    error = dist - (dist - util::distToPoint(glb::pos,target));

    // eye
    integral = error <= tolerance ? 0 : fabs(error) < integralThreshold ? integral += error : integral;

    // dee
    derivative = error - prevError;
    prevError = error;

    // end conditions
    if (error >= tolerance)
    {
      endTimer.start();
    }

    end = endTimer.time() >= endTime ? true : timeoutTimer.time() >= timeout ? true : false;

    // spin motors
    double vel = (error*kP + integral*kI + derivative*kD);
    robot::chass.spin(vel);

    pros::delay(10);
  }
  robot::chass.stop("b");
}  

std::vector<double> chas::moveToVel(util::coordinate target, double lkp, double rkp, double rotationBias)
{
  double linearError = distToPoint(glb::pos,target);
  double linearVel = linearError*lkp;

  double currHeading =  robot::imu.degHeading(); //0-360
  double targetHeading = absoluteAngleToPoint(glb::pos, target); // -180-180
  // targetHeading = targetHeading >= 0 ? targetHeading + -180 : targetHeading - 180;
  targetHeading = targetHeading >= 0 ? targetHeading :  180 + fabs(targetHeading);  //conver to 0-360

  int dir = -util::dirToSpin(targetHeading,currHeading);

  double rotationError = util::minError(targetHeading,currHeading);
  double rotationVel = rotationError * rkp * dir; 

  // lowers overal speed in porportion to rotationError and rotationBias
  double lVel = (linearVel - (fabs(rotationVel) * rotationBias)) - rotationVel;
  double rVel = (linearVel - (fabs(rotationVel) * rotationBias)) + rotationVel;

  // glb::controller.print(0,0,"(%f, %f)\n", linearError,targetHeading);
  return std::vector<double> {lVel, rVel};
}

void chas::moveTo(util::coordinate target, double timeout, util::pidConstants lConstants, util::pidConstants rConstants, double rotationBias, double rotationScale, double rotationCut)
{
  //init
  util::timer timeoutTimer;
  double rotationVel, linearVel;
  double linearError = distToPoint(glb::pos,target);
  double initError = linearError;
  double currHeading =  robot::imu.degHeading();
  double targetHeading = absoluteAngleToPoint(glb::pos, target);
  double rotationError = util::minError(targetHeading,currHeading);

  //init pid controllers
  util::pid linearController(lConstants,linearError);
  util::pid rotationController(rConstants,rotationError);

  //maths for scaling the angular p
  double slope = (rConstants.p) / (linearError - rotationCut);
  double initP = rConstants.p;

  while (timeoutTimer.time() < timeout)
  {
    //error
    linearError = distToPoint(glb::pos,target);
    currHeading =  robot::imu.degHeading(); //0-360

    targetHeading = absoluteAngleToPoint(glb::pos, target);
    rotationError = util::minError(targetHeading,currHeading);

    // rConstants.p = slope * log(linearError - lConstants.tolerance + 1);
    rConstants.p = slope * (linearError - initError) + initP;
    rConstants.p = rConstants.p < 0 ? 0 : rConstants.p;
    rotationController.update(rConstants);  
    int dir = -util::dirToSpin(targetHeading,currHeading);
    double cre = cos(rotationError <= 90 ? util::dtr(rotationError) : PI/2);
    glb::controller.print(0, 0, "%f,%f", rotationError, linearError);
    // glb::controller.print(0, 0, "%f,%f", currHeading, targetHeading);

    rotationVel = dir * rotationController.out(rotationError);
    linearVel = cre * linearController.out(linearError);

    double rVel = (linearVel - (fabs(rotationVel) * rotationBias)) + rotationVel;
    double lVel = (linearVel - (fabs(rotationVel) * rotationBias)) - rotationVel;

    robot::chass.spinDiffy(rVel,lVel);
  }

  robot::chass.stop("b");
}


// void moveToPosePID(util::coordinate target, double finalHeading, double initialBias, double finalBias, double timeout, double initialHeading = robot::imu.degHeading())
void chas::moveToPose(util::bezier curve, double timeout, double lkp, double rkp, double rotationBias)
{
  
  // resolution in which to sample points along the curve
  int resolution = 100;

  // util::bezier curve = util::bezier(glb::pos,target,initialBias,finalBias, util::dtr(initialHeading),util::dtr(finalHeading));

  /* creates a look up table so values dont have to be calculated on the fly and dont need to be
  recalculated */
  std::vector<util::coordinate> lut = curve.createLUT(resolution);

  double t;
  double distTraveled = 0;
  double ratioTraveled;
  double curveLength = curve.approximateLength(lut, resolution);

  util::coordinate prevPos = glb::pos;
  util::coordinate targetPos;

  while(1)
  {
    /* approximates dist traveled along the curve by summing the distance between the current
    robot position and the previous robot position */
    distTraveled += util::distToPoint(prevPos, glb::pos);
    prevPos = glb::pos;

    // finds the closest calculated point in the look up table, (rounds up): 0.1 = 1)
    ratioTraveled = distTraveled/curveLength;
    t = std::ceil(ratioTraveled * resolution);

    // bc you count from zero
    targetPos = lut[t-1];

    std::vector<double> velocities = moveToVel(targetPos,0.1,0.1,0.1);
    robot::chass.spinDiffy(velocities[1], velocities[0]);

    // if t reaches the last point
    if (t == lut.size())
    {
      break;
    }
  }
  // moveTo(lut[t], timeout, lkp, rkp, rotationBias);
}

void chas::timedSpin(double target, double speed,double timeout)
{
  // timers
  util::timer timeoutTimer;

  // general vars
  bool end = false;

  double currHeading = robot::imu.degHeading();
  int initDir = -util::dirToSpin(target,currHeading);
  // pid loop 
  while (!end)
  {

    currHeading = robot::imu.degHeading();
    int dir = -util::dirToSpin(target,currHeading);

    double error = util::minError(target,currHeading);
    

    if (initDir != dir)
    {
      end = true;
    }

    end = timeoutTimer.time() >= timeout ? true : end;

    // spin motors

    robot::chass.spinDiffy(dir * speed,- speed*dir);

  }

  robot::chass.stop("b");
}

void chas::velsUntilHeading(double rvolt, double lvolt, double heading, double tolerance, double timeout)
{
  util::timer timeoutTimer;

  while (true)
  {
    if(util::minError(heading, robot::imu.degHeading()) < tolerance || timeoutTimer.time() >= timeout)
    {
      break;
    }

    robot::chass.spinDiffy(rvolt, lvolt);
  }
}

void chas::arcTurn(double theta, double radius, double timeout, util::pidConstants cons)
{
  util::timer timer;
  double curr;
  double currTime;
  double rError;
  double lError;
  double sl;
  double sr;
  double dl;
  double dr;
  double rvel;
  double lvel;
  double vel;
  double ratio;

  sl = theta * (radius + DL);
  sr = theta * (radius + DR);

  theta = util::rtd(theta);
  ratio = sl/sr;
  curr = glb::imu.get_heading();


  util::pid controller(cons, 1000);

  while (true)
  {
    curr = glb::imu.get_heading();
    currTime = timer.time();

    vel = controller.out(util::minError(theta, curr)) * util::dirToSpin(theta,curr);

    vel = std::abs(vel) >= 127 ? (127 * util::sign(vel)) : vel;

    rvel = (2 * vel) / (ratio+1);
    lvel = ratio * rvel;

    robot::chass.spinDiffy(rvel, lvel);
    
    glb::controller.print(0, 0, "%f", util::minError(theta, curr));

    if(currTime >= timeout)
    {
      break;
    }

    pros::delay(10);
  }
  robot::chass.stop("b");
}


#endif
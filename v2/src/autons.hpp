#include "chassis.hpp"
#include "global.hpp"
#include "intake.hpp"
#include "flywheel.hpp"
#include "pros/rtos.hpp"
#include "util.hpp"
#include "autoaim.hpp"

typedef void(*fptr)();


void wp()
{

    util::pidConstants smallTurn = util::pidConstants(10, 1.6, 2, 0.05, 7, 10);
    util::pidConstants bigTurn = util::pidConstants(3.7, 1.5, 35, 0.05, 2.4, 20);
    util::pidConstants medTurn = util::pidConstants(4, 1.5, 20, 0.05, 2.4, 20);

    flywheel::target = 475;
    // robot::tsukasa.toggle();
    // pros::delay(300);
    // intake::toggle();
    intake::toggle(true);

    // - drive and aim
    chas::drive(-500, 800, 1);
    // robot::tsukasa.toggle();
    chas::spinTo(357.7, 800,smallTurn);

    // - shoot discs
    //intake::index(1);
    //flywheel::target = 450;
    //pros::delay(300);
    //intake::index(2);
    intake::waitIndex(2,5,-1,150,0);
    flywheel::target = 415; 

    // - turn to 3 stack
    chas::spinTo(233, 1000,medTurn);
    robot::intake.spin(127); 
    
    // - intake 3 stack
    robot::tsukasa.toggle();
    chas::drive(1300, 800, 5);
    robot::tsukasa.toggle();
    flywheel::target = 455;
    pros::delay(500);

    // - aim and shoot discs
    chas::spinTo(347.4, 1100);
    robot::intake.stop("c");
    //intake::index(1);
    // flywheel::target = 460;
    pros::delay(300);
    // intake::index(1);
    // flywheel::target = 450;
    // pros::delay(300);
    // intake::index(1);
    intake::waitIndex(3,5,-1,150,0);

    // - allign with discs
    chas::drive(500, 600, 1);
    chas::spinTo(216.6, 1000);

    //intake discs
    robot::intake.spin(127); 
    chas::drive(6150, 2300, 20);
    robot::intake.stop("c");

    //toggle roller
    // robot::tsukasa.toggle();
    chas::spinTo(270, 700);
    intake::toggle(true);
    // intake::hardToggle();
}

//Gerald was here
//asdfghjklkjhgfdsasdfghjklkjhgfdsawertyuikmnbvcxsaqw34567uiop;l,mnbvcxzsdfghj
//KJKJKJ

void skillsNew()
{
    util::pidConstants smallTurn = util::pidConstants(6, 1.6, 2, 0.05, 7, 10);
    util::pidConstants bigTurn = util::pidConstants(6.3, 1.74, 40, 0.05, 2.7, 30);
    util::pidConstants medTurn = util::pidConstants(9, 1.2, 70, 0.05, 2.4, 30);
    util::pidConstants drive = util::pidConstants(0.3,0.2,2.4,5,30,1000);
    util::pidConstants autoStriaght = util::pidConstants(4, 0.7, 4, 0, 190, 20);
    util::pidConstants arc(2.8,0,20,0.05,5,100);
    //intake right is ++
    //starting heading is like, 90
    // flywheel::target = 350;
    // pros::delay(700);
    // flywheel::ff = 3;
    // robot::intake.spin(-40);
    // pros::delay(500);
    // flywheel::ff = -1;

    // for (int i = 0; i < 7; i++)
    // {
    //     robot::intake.spin(127);
    //     pros::delay(350);
    //     robot::intake.stop("c");
    //     pros::delay(100);
    //     flywheel::ff = 3;
    //     robot::intake.spin(-50);
    //     pros::delay(250);
    //     flywheel::ff = -1;
    //     robot::intake.stop("c");
    // }
    // robot::intake.spin(-80);
    // flywheel::target = 300;
    // robot::tsukasa.toggle();
    // robot::chass.spinDiffy(127,-20);
    // pros::delay(550);
    // robot::chass.stop("b");
    // robot::intake.spin(127);
    // chas::drive(1200,580,2);
    // robot::tsukasa.toggle();
    // pros::delay(450);
    // robot::chass.spinDiffy(-127,-40);
    // pros::delay(780);
    // robot::chass.stop("b");
    // chas::drive(-700,570,4);

    // - go disc
    chas::spinTo(54, 850);
    robot::intake.stop("c");
    robot::tsukasa.toggle();
    
    robot::intake.spin(127);
    flywheel::target = 350;
    chas::drive(1050, 600, 3);
    robot::tsukasa.toggle();
    pros::delay(300);
    pros::delay(350);
    chas::drive(-950, 650, 3);
    autoAim(500, 1);
    flywheel::ff = 3;

    robot::intake.spin(-70);
    pros::delay(600);
    chas::spinTo(3,770);
    robot::intake.spin(127);
    chas::drive(2200,1000,1);
    robot::chass.spinDiffy(-50,50);
    pros::delay(300);
    robot::chass.stop("b");
    autoAim(800, 1);
    flywheel::ff = 3;
    robot::intake.spin(-50);
    pros::delay(720);
    robot::intake.spin(127);
    chas::spinTo(91,800);
    chas::drive(2000,1000,1);
    autoAim(800, 1);
    flywheel::ff = 3;
    robot::intake.spin(-50);
    pros::delay(720);


    chas::spinTo(225, 800);
    chas::drive(3200, 1400, 1);
    robot::chass.spinDiffy(30,127);
    pros::delay(600);
    robot::chass.stop("b");
    chas::spinTo(180, 300);
    intake::toggle(false);
    /// 
    chas::drive(-300,750,5);
    chas::spinTo(5, 1000,bigTurn);
    robot::tsukasa.toggle();    
    robot::intake.spin(127);
    chas::drive(700,800,5);
    robot::tsukasa.toggle();
    pros::delay(200);
    chas::drive(300,500,5);

    // - toggler roller #2
    chas::spinTo(270, 650);
    robot::intake.stop("c");
    chas::drive(1320,1000,5);
    intake::toggle(false);
    chas::drive(-680,600,1);
    robot::intake.stop("c");
    pros::delay(200);
    robot::tsukasa.toggle(); 

    // - shoot first volley
    chas::spinTo(183, 730);
    flywheel::target = 350;
    robot::tsukasa.toggle(); 
    chas::drive(-2700,1500,3);
    autoAim(700,2);
    flywheel::ff = 3;
    robot::intake.spin(-80);
    pros::delay(1000);
    robot::intake.stop("c");

    // - intake second round of three
    chas::spinTo(87, 800);
    robot::intake.spin(127);
    flywheel::target = 350;
    chas::drive(1000, 725, 5);
    chas::spinTo(90, 500, smallTurn);
    chas::drive(1200, 900, 5);

    // - second volley of three
    chas::spinTo(135, 400);
    autoAim(400,2);
    robot::intake.stop("c");
    robot::tsukasa.toggle();
    flywheel::ff = 3;
    robot::intake.spin(-80);
    pros::delay(900);
    robot::intake.stop("c");
    robot::tsukasa.toggle();

    // - intake third round of three and roller #3
    chas::spinTo(274, 1700,medTurn);
    robot::intake.spin(-127);
    chas::drive(-2740, 1400, 5);
    robot::intake.stop("c");
    chas::spinTo(0, 900);
    robot::tsukasa.toggle();    
    robot::intake.spin(127);
    chas::drive(600,800,5);
    robot::tsukasa.toggle();
    pros::delay(200);
    chas::drive(1970,1100,5);
    robot::intake.stop("b");
    pros::delay(800);
    intake::toggle(false);

    // - roller #4
    chas::drive(-200,700,5);
    chas::spinTo(315, 650);
    chas::drive(-1400, 850, 5);
    chas::spinTo(90, 750);
     
    robot::chass.spin(100);
    pros::delay(200);
    robot::chass.stop("c");
    intake::toggle(false);

    // - allign for matchloads
    flywheel::target = 350;
    robot::intake.stop("c");
    chas::velsUntilHeading(-30, -127,202, 4, 5000);
    robot::chass.spin(-95);
    pros::delay(1380);
    robot::chass.spin(-20);
    pros::delay(1200);
    robot::chass.spinDiffy(-20, 60);
    pros::delay(300);
    robot::chass.stop("b");
    pros::delay(200);
    robot::chass.spinDiffy(-30, -30);
    pros::delay(200);
    robot::chass.stop("b");
    autoAim(400,2);


    flywheel::ff = 3;
    robot::intake.spin(-60);
    pros::delay(700);


    for (int i = 0; i < 7; i++)
    {
        robot::intake.spin(127);
        pros::delay(350);
        robot::intake.stop("c");
        pros::delay(100);
        flywheel::ff = 3;
        robot::intake.spin(-50);
        pros::delay(250);
        flywheel::ff = -1;
        robot::intake.stop("c");
    }

        chas::spinTo(200, 700);
    chas::drive(2920, 1500, 5);
    chas::spinTo(45, 700);
    robot::cata.toggle();
    pros::delay(700);
    robot::plane.toggle();
}

void skills()
{
    // robot::imu.init(180);
    util::pidConstants smallTurn = util::pidConstants(6, 1.6, 2, 0.05, 7, 10);
    util::pidConstants bigTurn = util::pidConstants(6.3, 1.74, 40, 0.05, 2.7, 30);
    util::pidConstants medTurn = util::pidConstants(9, 1.2, 70, 0.05, 2.4, 30);
    util::pidConstants drive = util::pidConstants(0.3,0.2,2.4,5,30,1000);
    util::pidConstants autoStriaght = util::pidConstants(4, 0.7, 4, 0, 190, 20);
    
    // chas::spinTo(90, 750);
    // chas::drive(1000, 1000, 5);
    // pros::delay(3000);

    // chas::drive(2000, 3000, 1);
    // chas::spinTo(125, 5000,medTurn);
    // pros::delay(5000);
    // util::pidConstants linearConstants(0.3,0,0,0,0,0);
    // util::pidConstants rotationConstants(0,0,0,0,0,0);
    // chas::spinTo(90, 3000);
    // chas::drive(2000, 3000, 1);

    // glb::red = true;

    // chas::autoDrive(4000, 0, 5000, drive, autoStriaght);
    // chas::arcTurn(3 *PI/2, 500, 3000, util::pidConstants(2.8,0,20,0.05,5,100));
    //! UNCOMMENT TO HERE.
    
    flywheel::target = 350;

    pros::delay(1000);


    for (int i = 0; i < 9; i++)
    {
        robot::intake.spin(127);
        pros::delay(350);
        robot::intake.stop("c");
        pros::delay(100);
        flywheel::ff = 3;
        robot::intake.spin(-50);
        pros::delay(250);
        flywheel::ff = -1;
        robot::intake.stop("c");
    }

    robot::intake.spin(-80);

    flywheel::target = 300;

    // - go disc
    chas::spinTo(54, 850);
    robot::intake.stop("c");
    robot::tsukasa.toggle();
    
    robot::intake.spin(127);
    flywheel::target = 350;
    chas::drive(1050, 600, 3);
    robot::tsukasa.toggle();
    pros::delay(300);
    pros::delay(350);
    chas::drive(-950, 650, 3);
    chas::spinTo(355, 800);
    flywheel::ff = 3;

    robot::intake.spin(-70);
    pros::delay(600);
    chas::spinTo(0, 1000,smallTurn);
    // - toggler roller #1
    chas::drive(2340, 1200, 1);
    robot::intake.stop("c");
    // robot::tsukasa.toggle();
    chas::spinTo(273, 750);
    robot::chass.spin(50);
    pros::delay(400);
    robot::chass.stop("b");
    pros::delay(200);
    // chas::drive(400,600,5);
    intake::toggle(false);
    // chas::drive(-200,600,1);

    // - intake first three stack
    // robot::tsukasa.toggle();
    chas::drive(-300,750,5);
    chas::spinTo(95, 1000,bigTurn);
    robot::tsukasa.toggle();    
    robot::intake.spin(127);
    chas::drive(700,800,5);
    robot::tsukasa.toggle();
    pros::delay(200);
    chas::drive(300,500,5);

    // - toggler roller #2
    chas::spinTo(1, 650);
    robot::intake.stop("c");
    // robot::tsukasa.toggle();
    chas::drive(1320,1000,5);
    intake::toggle(false);
    // intake::hardToggle();
    chas::drive(-680,600,1);
    robot::intake.stop("c");
    pros::delay(200);
    robot::tsukasa.toggle(); 

    // - shoot first volley
    // chas::drive(-300,500,5);
    chas::spinTo(273, 730);
    flywheel::target = 350;
    chas::drive(-2460,1500,1);
    robot::tsukasa.toggle(); 
    // chas::autoDrive(-2700,272,1500);
    chas::spinTo(290, 800);
    flywheel::ff = 3;
    robot::intake.spin(-80);
    pros::delay(1000);
    // intake::waitIndex(3,20);
    // robot::intake.spin(-40);
    // pros::delay(1200);
    robot::intake.stop("c");

    // - intake second round of three
    chas::spinTo(160, 800);
    robot::intake.spin(127);
    flywheel::target = 350;
    chas::drive(1000, 725, 5);
    chas::spinTo(180, 500, smallTurn);
    chas::drive(1200, 900, 5);

    // - second volley of three
    // flywheel::target = 400;
    chas::spinTo(237, 800);
    robot::intake.stop("c");
    robot::tsukasa.toggle();
    flywheel::ff = 3;
    robot::intake.spin(-80);
    pros::delay(900);
    // intake::waitIndex(3,15);
    // robot::intake.spin(-25);
    // pros::delay(2000);
    robot::intake.stop("c");
    robot::tsukasa.toggle();

    // - intake third round of three and roller #3
    chas::spinTo(5, 1700,medTurn);
    robot::intake.spin(-127);
    chas::drive(-2740, 1400, 5);
    robot::intake.stop("c");
    
    
        chas::spinTo(92, 900);
    // robot::intake.spin(127);
    // robot::chass.spin(70);
    // pros::delay(800);
    // robot::tsukasa.toggle();
    // robot::chass.spin(127);
    // pros::delay(400);
    // robot::chass.spin(70);
    // pros::delay(300);
    // intake::toggle(false);

    robot::tsukasa.toggle();    
    robot::intake.spin(127);
    chas::drive(600,800,5);
    robot::tsukasa.toggle();
    pros::delay(200);
    chas::drive(1970,1100,5);
    robot::intake.stop("b");
    pros::delay(800);
    intake::toggle(false);

    // //roller #4
    // chas::drive(-1350,850,5);
    // chas::spinTo(180, 750);
    // // robot::tsukasa.toggle();
    // robot::chass.spin(100);
    // pros::delay(500);
    // intake::toggle();
    // robot::tsukasa.toggle();

    // - roller #4
    chas::drive(-200,700,5);
    chas::spinTo(45, 650);
    chas::drive(-1400, 850, 5);
    chas::spinTo(180, 750);
     
    robot::chass.spin(100);
    pros::delay(200);
    robot::chass.stop("c");
    intake::toggle(false);

    // - allign for matchloads
    flywheel::target = 350;
    robot::intake.stop("c");


    // chas::spinTo(210, 1000);
    // chas::drive(-3600, 1900, 1);
    // robot::chass.spin(-20);
    // pros::delay(1000);
    // robot::chass.spinDiffy(-20, 60);
    // pros::delay(300);
    // robot::chass.stop("b");
    // pros::delay(200);
    // robot::chass.spinDiffy(-30, -30);
    // pros::delay(200);
    // robot::chass.stop("b");

    chas::velsUntilHeading(-30, -127,202, 4, 5000);
    robot::chass.spin(-95);
    pros::delay(1380);
    robot::chass.spin(-20);
    pros::delay(1200);
    robot::chass.spinDiffy(-20, 60);
    pros::delay(300);
    robot::chass.stop("b");
    pros::delay(200);
    robot::chass.spinDiffy(-30, -30);
    pros::delay(200);
    robot::chass.stop("b");

    // chas::spinTo(175, 2000,smallTurn);
    // robot::chass.spin(-30);
    // pros::delay(400);


    // chas::spinTo(172, 1000, smallTurn);
    flywheel::ff = 3;
    robot::intake.spin(-60);
    pros::delay(700);


    for (int i = 0; i < 7; i++)
    {
        robot::intake.spin(127);
        pros::delay(350);
        robot::intake.stop("c");
        pros::delay(100);
        flywheel::ff = 3;
        robot::intake.spin(-50);
        pros::delay(250);
        flywheel::ff = -1;
        robot::intake.stop("c");
    }

        chas::spinTo(200, 700);
    chas::drive(2920, 1500, 5);
    chas::spinTo(135, 700);
    // chas::drive(-200,700,5);
    robot::cata.toggle();
    pros::delay(700);
    robot::plane.toggle();
}

void nearHalf()
{

    util::pidConstants smallTurn = util::pidConstants(8, 1.6, 2, 0.05, 7, 10);
    util::pidConstants bigTurn = util::pidConstants(3.7, 1.5, 35, 0.05, 2.4, 20);
    util::pidConstants medTurn = util::pidConstants(4, 1.5, 20, 0.05, 2.4, 20);

    flywheel::target = 480;
    // robot::tsukasa.toggle();
    // pros::delay(300);
    intake::toggle(true);

    //drive and aim
    chas::drive(-400, 700, 1);
    chas::spinTo(357.7, 700,smallTurn);

    //shoot discs
    // intake::waitIndex(2,5,true);
    intake::waitIndex(2,5,-1,50,0);
    robot::intake.stop("c");
    flywheel::target = 415; 

    //turn to 3 stack
    chas::spinTo(233, 900,medTurn);
    robot::intake.spin(127); 
    
    //intake 3 stack
    robot::tsukasa.toggle();
    chas::drive(1250, 700, 5);
    robot::tsukasa.toggle();
    flywheel::target = 460;
    pros::delay(500);

    //aim and shoot discs
    chas::spinTo(346.1, 1100);
    robot::intake.stop("c");
    
    // intake::index(1);
    // pros::delay(200);
    // intake::index(1);
    // pros::delay(200);
    // intake::index(1);
    // flywheel::target = 465;
    // intake::waitIndex(3,5,true);
    intake::waitIndex(3,5,-1,50,0);
    flywheel::target = 415;

    chas::spinTo(222, 800);
    chas::drive(-600,650,5);
    chas::spinTo(135, 700);
    robot::tsukasa.toggle();
    robot::intake.spin(127);
    chas::drive(380,450,5);
    robot::tsukasa.toggle();

    flywheel::target = 470;
    pros::delay(680);
    chas::drive(-200,400,5);
    chas::spinTo(347.9, 1100,bigTurn);
    robot::intake.stop("B");
    // intake::waitIndex(3,5,true);
    intake::waitIndex(3,5,-1,150,0);
    // intake::index(1);
    // pros::delay(200);
    // intake::index(1);
    // pros::delay(200);
    // intake::index(1);
}

void farHalf()
{
    util::pidConstants smallTurn = util::pidConstants(6, 1.6, 2, 0.05, 7, 20);

    // flywheel::target = 500;
    // chas::spinTo(35, 1300);
    // intake::index(1);
    // pros::delay(500);
    // intake::index(1);

    // flywheel::target = 300;
    // chas::spinTo(225, 1000);
    // robot::tsukasa.toggle();
    // chas::drive(1400, 1000, 5);
    // robot::intake.spin(127);
    // robot::tsukasa.toggle();
    // pros::delay(300);
    // flywheel::target = 500;
    // chas::drive(-200, 1000, 5);
    // chas::spinTo(15, 1000);
    // intake::index(1);
    // pros::delay(500);
    // intake::index(1);

    // chas::spinTo(350, 1000);
    // intake::toggle();
    
    robot::tsukasa.toggle();
    flywheel::target = 460;
    chas::drive(1200, 750, 5);
    robot::intake.spin(127);
    robot::tsukasa.toggle();
    pros::delay(600);
    chas::drive(-400, 800, 5);
    chas::spinTo(23.1, 890);
    intake::waitIndex(3,5,-1,150,0);
    // intake::index(1);
    // pros::delay(250);
    // intake::index(1);
    // pros::delay(250);
    // intake::index(1);
    robot::intake.spin(127);
    chas::spinTo(10, 890);
    robot::tsukasa.toggle();
    chas::drive(680 , 700, 5);
    robot::tsukasa.toggle();
    pros::delay(500);
    chas::drive(-680, 890, 5);
    flywheel::target = 455;
    chas::spinTo(27.1, 890);
    intake::waitIndex(2,5,-1,150,0);
    // robot::tsukasa.toggle();
    // intake::index(1);
    // pros::delay(250);
    // intake::index(1);
    chas::spinTo(325, 900);
    robot::chass.spin(127);
    pros::delay(1000);
    chas::spinTo(0, 600);
    intake::toggle(true);
}

void fiveNearHalf()
{

    util::pidConstants smallTurn = util::pidConstants(10, 1.6, 2, 0.05, 7, 10);
    util::pidConstants bigTurn = util::pidConstants(3.7, 1.5, 35, 0.05, 2.4, 20);
    util::pidConstants medTurn = util::pidConstants(4, 1.5, 20, 0.05, 2.4, 20);

    flywheel::target = 460;
    intake::toggle(true);

    //drive and aim
    chas::drive(-500, 800, 1);
    chas::spinTo(357.5, 800,smallTurn);

    //shoot discs
    intake::index(1);
    // flywheel::target = 450;
    pros::delay(300);
    intake::index(2);
    flywheel::target = 415; 

    //turn to 3 stack
    chas::spinTo(233, 1000,medTurn);
    robot::intake.spin(127); 
    
    //intake 3 stack
    robot::tsukasa.toggle();
    chas::drive(1300, 800, 5);
    robot::tsukasa.toggle();
    flywheel::target = 440;
    pros::delay(500);

    //aim and shoot discs
    chas::spinTo(345.8, 1100);
    robot::intake.stop("c");
    intake::index(1);
    // flywheel::target = 460;
    pros::delay(300);
    intake::index(1);
    flywheel::target = 450;
    pros::delay(300);
    intake::index(1);
}

void skillsReach()
{
    // robot::imu.init(180);
    util::pidConstants smallTurn = util::pidConstants(6, 1.6, 2, 0.05, 7, 10);
    util::pidConstants bigTurn = util::pidConstants(6.3, 1.74, 40, 0.05, 2.7, 30);
    util::pidConstants medTurn = util::pidConstants(9, 1.2, 70, 0.05, 2.4, 30);
    util::pidConstants drive = util::pidConstants(0.3,0.2,2.4,5,30,1000);
    util::pidConstants autoStriaght = util::pidConstants(4, 0.7, 4, 0, 190, 20);
    
    flywheel::target = 350;
    pros::delay(1000);

    for (int i = 0; i < 9; i++)
    {
        robot::intake.spin(127);
        pros::delay(350);
        robot::intake.stop("c");
        pros::delay(100);
        flywheel::ff = 3;
        robot::intake.spin(-50);
        pros::delay(250);
        flywheel::ff = -1;
        robot::intake.stop("c");
    }

    robot::intake.spin(-80);

    flywheel::target = 300;

    // - go disc
    chas::spinTo(54, 850);
    robot::intake.stop("c");
    robot::tsukasa.toggle();
    
    robot::intake.spin(127);
    flywheel::target = 350;
    chas::drive(1050, 600, 3);
    robot::tsukasa.toggle();
    pros::delay(300);
    pros::delay(350);
    chas::drive(-950, 650, 3);
    autoAim(400,2);
    // chas::spinTo(355, 800);
    flywheel::ff = 3;

    robot::intake.spin(-70);
    pros::delay(600);
    chas::spinTo(0, 1000,smallTurn);
    // - toggler roller #1
    chas::drive(2340, 1200, 1);
    robot::intake.stop("c");
    // robot::tsukasa.toggle();
    chas::spinTo(273, 750);
    robot::chass.spin(50);
    pros::delay(400);
    robot::chass.stop("b");
    pros::delay(200);
    // chas::drive(400,600,5);
    intake::toggle(false);
    // chas::drive(-200,600,1);

    // - intake first three stack
    // robot::tsukasa.toggle();
    chas::drive(-300,750,5);
    chas::spinTo(95, 1000,bigTurn);
    robot::tsukasa.toggle();    
    robot::intake.spin(127);
    chas::drive(700,800,5);
    robot::tsukasa.toggle();
    pros::delay(200);
    chas::drive(300,500,5);

    // - toggler roller #2
    chas::spinTo(1, 650);
    robot::intake.stop("c");
    // robot::tsukasa.toggle();
    chas::drive(1320,1000,5);
    intake::toggle(false);
    // intake::hardToggle();
    chas::drive(-680,600,1);
    robot::intake.stop("c");
    pros::delay(200);
    robot::tsukasa.toggle(); 

    // - shoot first volley
    // chas::drive(-300,500,5);
    chas::spinTo(273, 730);
    flywheel::target = 350;
    chas::drive(-2460,1500,1);
    robot::tsukasa.toggle(); 
    // chas::autoDrive(-2700,272,1500);
    autoAim(800,2);
    flywheel::ff = 3;
    robot::intake.spin(-80);
    pros::delay(1000);
    // intake::waitIndex(3,20);
    // robot::intake.spin(-40);
    // pros::delay(1200);
    robot::intake.stop("c");

    // - intake second round of three
    chas::spinTo(160, 800);
    robot::intake.spin(127);
    flywheel::target = 350;
    chas::drive(1000, 725, 5);
    chas::spinTo(180, 500, smallTurn);
    chas::drive(1200, 900, 5);

    // - second volley of three
    // flywheel::target = 400;
    autoAim(800,2);
    robot::intake.stop("c");
    robot::tsukasa.toggle();
    flywheel::ff = 3;
    robot::intake.spin(-80);
    pros::delay(900);
    // intake::waitIndex(3,15);
    // robot::intake.spin(-25);
    // pros::delay(2000);
    robot::intake.stop("c");
    robot::tsukasa.toggle();

    // - intake third round of three and roller #3
    chas::spinTo(5, 1700,medTurn);
    robot::intake.spin(-127);
    chas::drive(-2740, 1400, 5);
    robot::intake.stop("c");
    chas::spinTo(92, 900);

    robot::tsukasa.toggle();    
    robot::intake.spin(127);
    chas::drive(600,800,5);
    robot::tsukasa.toggle();
    pros::delay(200);
    chas::drive(1970,1100,5);
    robot::intake.stop("b");
    pros::delay(800);
    intake::toggle(false);

    // - roller #4
    chas::drive(-200,700,5);
    chas::spinTo(45, 650);
    chas::drive(-1400, 850, 5);
    chas::spinTo(180, 750);
     
    robot::chass.spin(100);
    pros::delay(200);
    robot::chass.stop("c");
    intake::toggle(false);

    // - allign for matchloads
    flywheel::target = 350;
    robot::intake.stop("c");

    chas::velsUntilHeading(-30, -127,202, 4, 5000);
    robot::chass.spin(-95);
    pros::delay(1380);
    robot::chass.spin(-20);
    pros::delay(1200);
    robot::chass.spinDiffy(-20, 60);
    pros::delay(300);
    robot::chass.stop("b");
    pros::delay(200);
    robot::chass.spinDiffy(-30, -30);
    pros::delay(200);
    robot::chass.stop("b");

    // chas::spinTo(175, 2000,smallTurn);
    // robot::chass.spin(-30);
    // pros::delay(400);


    // chas::spinTo(172, 1000, smallTurn);
    autoAim(300,2);
    flywheel::ff = 3;
    robot::intake.spin(-60);
    pros::delay(700);


    for (int i = 0; i < 7; i++)
    {
        robot::intake.spin(127);
        pros::delay(350);
        robot::intake.stop("c");
        pros::delay(100);
        flywheel::ff = 3;
        robot::intake.spin(-50);
        pros::delay(250);
        flywheel::ff = -1;
        robot::intake.stop("c");
    }

        chas::spinTo(200, 700);
    chas::drive(2920, 1500, 5);
    chas::spinTo(135, 700);
    robot::cata.toggle();
    pros::delay(700);
    robot::plane.toggle();
}

void nearSafe()
{

    util::pidConstants smallTurn = util::pidConstants(8, 1.6, 2, 0.05, 7, 10);
    util::pidConstants bigTurn = util::pidConstants(3.7, 1.5, 35, 0.05, 2.4, 20);
    util::pidConstants medTurn = util::pidConstants(4, 1.5, 20, 0.05, 2.4, 20);

    flywheel::target = 475;
    // robot::tsukasa.toggle();
    // pros::delay(300);
    intake::toggle(true);

    //drive and aim
    chas::drive(-150, 700, 1);
    chas::spinTo(357.1, 500,smallTurn);

    //shoot discs
    // intake::waitIndex(2,5,true);
    intake::waitIndex(2,5,-1,150,0);
    robot::intake.stop("c");
    flywheel::target = 415; 

    //turn to 3 stack
    chas::spinTo(233, 900,medTurn);
    /*
    robot::intake.spin(127); 
    
    //intake 3 stack
    robot::tsukasa.toggle();
    chas::drive(1250, 700, 5);
    robot::tsukasa.toggle();
    flywheel::target = 450;
    pros::delay(500);

    //aim and shoot discs
    chas::spinTo(348.5, 1100);
    robot::intake.stop("c");
    
    // intake::index(1);
    // pros::delay(200);
    // intake::index(1);
    // pros::delay(200);
    // intake::index(1);
    // flywheel::target = 465;
    // intake::waitIndex(3,5,true);
    intake::waitIndex(3,5,-1,150,0);
    flywheel::target = 415;

    chas::spinTo(222, 800);
    chas::drive(-500,650,5);
    chas::spinTo(135, 700);
    robot::tsukasa.toggle();
    robot::intake.spin(127);
    chas::drive(320,500,5);
    robot::tsukasa.toggle();

    flywheel::target = 460;
    pros::delay(450);
    chas::drive(-300,700,5);
    chas::spinTo(349, 1100,bigTurn);
    robot::intake.stop("B");
    // intake::waitIndex(3,5,true);
    intake::waitIndex(3,5,-1,150,0);
    // intake::index(1);
    // pros::delay(200);
    // intake::index(1);
    // pros::delay(200);
    // intake::index(1);
    */
}

void driverAut()
{
    flywheel::target = 450;
    pros::delay(1000);

    intake::waitIndex(3,5,-1,150,0);
}



// std::vector<void (*)()> autons{wp,a};
fptr WP = wp; fptr SKILLSNEW = skillsNew; fptr SKILLS = skills; fptr NEARHALF = nearHalf; fptr FARHALF = farHalf; fptr FIVENEARHALF = fiveNearHalf; fptr DRIVER = driverAut; fptr SKILLSREACH = skillsReach; fptr NEARSAFE = nearSafe;

std::vector<fptr> autons{WP, SKILLSNEW, SKILLS, NEARHALF, FARHALF, FIVENEARHALF, DRIVER, SKILLSREACH, NEARSAFE};
std::vector<std::string> autonNames{"wp","skillsNew", "skills","nearHalf", "farHalf", "fiveNearHalf", "driverAut", "skillsReach", "nearSafe" };

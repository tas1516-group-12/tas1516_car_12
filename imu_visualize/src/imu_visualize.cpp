#include "ros/ros.h"
#include "std_msgs/String.h"

#include "sensor_msgs/Imu.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Vector3.h"

#include "tf/transform_datatypes.h"

#include <sstream>

std_msgs::Header header;
geometry_msgs::Quaternion orientation;
tf::Vector3 angular_velocity(0,0,0);
tf::Vector3 linear_acceleration(0,0,0);

tf::Vector3 angle(0,0,0);
tf::Vector3 linear_speed(0,0,0);
tf::Vector3 linear_position(0,0,0);

ros::Time now;
ros::Time last;
ros::Duration diff;
double dt;

geometry_msgs::Vector3 initial;

void printGeomVector3(std::string name, const geometry_msgs::Vector3 vec)
{
    std::cout << "Vector " << name << ": x=" << vec.x << ", y=" << vec.y << ", z=" << vec.z << std::endl;
}

void printTFVector3(std::string name, const tf::Vector3 vec)
{
    std::cout << "Vector " << name << ": x=" << vec.x() << ", y=" << vec.y() << ", z=" << vec.z() << std::endl;
}

tf::Vector3 geomToTF(geometry_msgs::Vector3 vec)
{
    return tf::Vector3(vec.x, vec.y ,vec.z);
}

void imuCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
    now = ros::Time::now();
    diff = now - last;
    dt = diff.toSec();
    if(last.toSec() == 0)
    {
        last = now;
        return;
    }
    last = now;

    //ROS_INFO("dt: %f", dt);

    header = msg->header;
    //printVector3("lin_accel", linear_acceleration);
    //geometry_msgs::Vector3 tmp = msg->orientation;
    //orientation = geomToTF(tmp);
    angular_velocity = geomToTF(msg->angular_velocity);
    linear_acceleration = geomToTF(msg->linear_acceleration);

    angle = angle + angular_velocity * dt;
    linear_speed = linear_speed + linear_acceleration * dt;
    linear_position = linear_position + linear_speed * dt;

    /*
    std::cout << dt << std::endl;

    printTFVector3("angle_vel", angular_velocity);
    printTFVector3("angle", angle);
    printTFVector3("lin_accel", linear_acceleration);
    printTFVector3("speed", linear_speed);
    printTFVector3("position", linear_position);

    std::cout << std::endl;
    */
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "imu_visualize");

    ros::NodeHandle n;

    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("imu_tf", 1000);

    ros::Subscriber sub = n.subscribe("imu", 1000, imuCallback);

    ros::Rate loop_rate(10);

    int count = 0;
    while (ros::ok())
    {
        /*
        std_msgs::String msg;
        std::stringstream ss;
        ss << "hello world " << count;
        msg.data = ss.str();

        ROS_INFO("%s", msg.data.c_str());

        chatter_pub.publish(msg);
        */

        printTFVector3("angle_vel", angular_velocity);
        printTFVector3("angle", angle);
        printTFVector3("lin_accel", linear_acceleration);
        printTFVector3("speed", linear_speed);
        printTFVector3("position", linear_position);
        std::cout << std::endl;

        ros::spinOnce();
        loop_rate.sleep();

        //++count;
    }

    return 0;
}

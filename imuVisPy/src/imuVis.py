#!/usr/bin/env python

# listen to IMU and scan and return the results to the terminal
#
#

import rospy
from std_msgs.msg import String

#http://docs.ros.org/api/sensor_msgs/html/msg/Imu.html
from sensor_msgs.msg import Imu
#http://docs.ros.org/api/sensor_msgs/html/msg/LaserScan.html
from sensor_msgs.msg import LaserScan

"""
class TheImu(object):
    '''docstring for TheImu'''
    def __init__(self):
        #super(TheImu, self).__init__()
        #self.arg = arg
        #pass
        print("Init TheImu")

    def listener(self):
        rospy.init_node('imuListener', anonymous=True)
        # for simulated car use
        rospy.Subscriber('imu/data', Imu, self.callback)

        # for real car use
        #rospy.Subscriber("imu/data", Imu, self.callback)
        rospy.spin()

    def callback(self, data):
        rospy.loginfo(
            rospy.get_caller_id() + "Imu orientation data %s", 
            data.orientation)
"""        
class TheScan(object):
    '''docstring for TheScan'''
    def __init__(self):
        #super(TheScan, self).__init__()
        #self.arg = arg
        #pass
        print("Init TheScan")

    def listener(self):
        rospy.init_node('scanListener', anonymous=True)
        # for simulated car use
        rospy.Subscriber('scan', LaserScan, self.callbackScan)
        rospy.Subscriber('imu/data', Imu, self.callbackImu)
        # rospy.Subscriber("/sensor_msgs/LaserScan",sensor_msgs.msg.LaserScan,callback,20)
        # for real car use
        #rospy.Subscriber("imu/data", Imu, self.callback)
        rospy.spin()

    def callbackScan(self, data):
        rospy.loginfo(
            rospy.get_caller_id() + "Scan ranges data %s", 
            data.ranges)

    def callbackImu(self, data):
        rospy.loginfo(
            rospy.get_caller_id() + "Imu orientation data %s", 
            data.orientation)
        
if __name__ == '__main__':
    #myImu = TheImu()
    myScan = TheScan()

    #myImu.listener()
    myScan.listener()
    

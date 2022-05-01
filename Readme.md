# Gazebo odom plugin
[中文版](Readme_cn.md)


this is a very inacceruate odom, which have noise accumulate on pose x,y

modified from p3d base controller

![odom](.image/odom.gif)

red trajory is odom, green one is ground truth

## usage
```xml
  <gazebo>
    <plugin name="libgazebo_odom" filename="libgazebo_odom.so">
      <robotNamespace>/prius</robotNamespace>
      <bodyName>base_link</bodyName>
      <topicName>base_pose_odom</topicName>
      <frameName>map</frameName>
      <updateRate>100.0</updateRate>
      <gaussianNoise>0.05</gaussianNoise>
      <gaussianBias>0.05</gaussianBias>
    </plugin>
  </gazebo>
```
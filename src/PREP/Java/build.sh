#!/bin/bash 

/usr/local/java/jdk1.6.0_31/bin/javac -classpath /usr/local/hadoop/etc/hadoop/:/usr/local/hadoop-2.5.1/share/hadoop/common/lib/*:/usr/local/hadoop-2.5.1/share/hadoop/common/*:/usr/local/hadoop-2.5.1/share/hadoop/hdfs:/usr/local/hadoop-2.5.1/share/hadoop/hdfs/lib/*:/usr/local/hadoop-2.5.1/share/hadoop/hdfs/*:/usr/local/hadoop-2.5.1/share/hadoop/yarn/lib/*:/usr/local/hadoop-2.5.1/share/hadoop/yarn/*:/usr/local/hadoop-2.5.1/share/hadoop/mapreduce/lib/*:/usr/local/hadoop-2.5.1/share/hadoop/mapreduce/*:/contrib/capacity-scheduler/*.jar:/home/terry/Documents/CVN/HW1/code/lib/*.jar org/ganita/basic/*.java

/usr/local/java/jdk1.6.0_31/bin/jar -cvf GanitaBasic.jar org/ganita/basic/*.class

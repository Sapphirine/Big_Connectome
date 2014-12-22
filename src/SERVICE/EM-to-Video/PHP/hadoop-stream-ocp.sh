#!/bin/bash

/usr/local/hadoop/bin/hadoop fs -rm hdfs:///user/terry/B-E-D/test/output/99/*
/usr/local/hadoop/bin/hadoop fs -rmdir hdfs:///user/terry/B-E-D/test/output/99/
/usr/local/hadoop/bin/hadoop fs -rm hdfs:///user/terry/B-E-D/test/input/*

echo $1" "$2" "$3" "$4" 100 120 /home/terry/Kasthuri11_"$1"_"$2"_"$3"_"$4"_100_120.h5" > Kasthuri11_rest.txt
/usr/local/hadoop/bin/hadoop fs -copyFromLocal Kasthuri11_rest.txt hdfs:///user/terry/B-E-D/test/input/

/usr/local/hadoop/bin/hadoop jar /usr/local/hadoop/share/hadoop/tools/lib/hadoop-streaming-2.5.1.jar -D mapred.job.name='Extracting EM slices from Open Connectome Project' -mapper 'ruby /projects/src/connectome/GanitaBrain/svn/trunk/src/PREP/Ruby/hadoopOCP.rb' -file '/projects/src/connectome/GanitaBrain/svn/trunk/src/PREP/Ruby/hadoopOCP.rb' -reducer 'cat' -input /user/terry/B-E-D/test/input/Kasthuri11_rest.txt -output /user/terry/B-E-D/test/output/99

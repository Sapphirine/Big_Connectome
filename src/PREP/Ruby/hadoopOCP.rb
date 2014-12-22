#!/usr/bin/env ruby

STDIN.each do |line|
params = line.split(' ')
# puts 'Parameters: '+params[0]
system('/usr/local/hadoop/bin/hadoop fs -mkdir -p hdfs:///user/terry/B-E-D/Kasthuri11/hdf5/x-'+params[0]+'/y-'+params[2])
print 'hadoop fs -mkdir -p hdfs:///user/terry/B-E-D/Kasthuri11/hdf5/x-'+params[0]+'/y-'+params[2]+"\n"
system('/usr/bin/getKasthuri11 '+params[0]+' '+params[1]+' '+params[2]+' '+params[3]+' '+params[4]+' '+params[5]+' '+params[6])
print 'getKasthuri11 '+params[0]+' '+params[1]+' '+params[2]+' '+params[3]+' '+params[4]+' '+params[5]+' '+params[6]+"\n"
system('/usr/local/hadoop/bin/hadoop fs -copyFromLocal '+params[6]+' hdfs:///user/terry/B-E-D/Kasthuri11/hdf5/x-'+params[0]+'/y-'+params[2]+'/')
print 'hadoop fs -copyFromLocal '+params[6]+' hdfs:///user/terry/B-E-D/Kasthuri11/hdf5/x-'+params[0]+'/y-'+params[2]+"\n"
end

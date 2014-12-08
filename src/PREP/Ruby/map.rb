#!/usr/bin/env ruby

STDIN.each do |line|
params = line.split(' ')
# puts 'Parameters: '+params[0]
exec 'getKasthuri11 '+params[0]+' '+params[1]+' '+params[2]+' '+params[3]+' '+params[4]+' '+params[5]+' '+params[6]
# exec 'sh test.sh '+params[0]+' '+params[1]+' '+params[2]+' '+params[3]+' '+params[4]+' '+params[5]+' '+params[6]
end

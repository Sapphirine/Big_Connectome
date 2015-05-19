import sys, getopt
import numpy

def main(argv):
   inputfile = ''
   try:
      opts, args = getopt.getopt(argv,"hi:",["ifile="])
   except getopt.GetoptError:
      print 'caffe_print_results.py -i <inputfile>'
      sys.exit(2)
   for opt, arg in opts:
      if opt == '-h':
         print 'caffe_print_results.py -i <input_numpy_file>'
         sys.exit()
      elif opt in ("-i", "--ifile"):
         inputfile = arg
   if inputfile == "":
     print 'caffe_print_results.py -i <inputfile>'
     sys.exit(2)
   print 'Input file is ', inputfile
   data = numpy.load(inputfile)
   print data

if __name__ == "__main__":
   main(sys.argv[1:])


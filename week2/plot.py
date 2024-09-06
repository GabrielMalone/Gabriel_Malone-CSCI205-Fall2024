# install matplotlib using the python package manager: pip
# pip install matplotlib

import os
import sys						# command line arguments
from matplotlib import pyplot 	# plotting functions
from glob import glob			# pathname pattern expansion module
								# use to only read text files from current directory


def prepare_file_name(file_name: str) -> str:
	tokens = file_name[:-4].split("_")
	for i in range(len(tokens)):
		tokens[i] = tokens[i].capitalize()
	return ' '.join(tokens)

# list comprehension to read only text file names into list
# looks in current directory
# use glob module to pattern match files names by type
files = [f for f in glob('*.txt') if "CMake" not in f]

# load data from file names
plots = {}										# dictionary of plots
for file_name in files:							# iterate through file names
	file = open(file_name)						# open file
	x = []										# list of x values - number of trials
	y = []										# list of y values - time complexity
	z = []										# data point values  
	for line in file:							# iterate through file
		line = line.strip().split(" ")			# clean up the data
		x.append(int(line[0]))					# build x list
		y.append(int(line[1]))					# build y list
		z.append(int(line[2]))					# build z list
		plots[prepare_file_name(file_name)] = (x, y, z) # prepare graph legend from file name and associate x, y, z lists

# plot each set
for s in plots:
	pyplot.plot(plots[s][0], plots[s][1], label=s)
	labels = plots[s][2]
	
pyplot.legend()					# show legend
if len(sys.argv) > 1:
	pyplot.title(sys.argv[1])	# display title from command line args
else:
	pyplot.title("Time Complexity Graph")	# default title
pyplot.xlabel("Problem Size")	# axis label
pyplot.ylabel("Comparisons")	# axis label
pyplot.grid(True)				# show the grid
pyplot.show()					# show the plot

# clean up txt files after done
for file in files:
	os.remove(file)

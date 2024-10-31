# Gabriel Malone / CS205 / Week 2 Lab

import os
import matplotlib.pyplot as plt

# dictionary to hold graph data 
# key will be experiment name
# value will be x, y lists of values
experiments = {}

# format names to standard required by lab instructions
# (remove '_', ap each word)
def cleanName(file_name:str)->str:  
    caps = []  
    tokens = file_name[0:-4].split('_')
    for token in tokens:
        caps.append(token.capitalize())
    clean_name = " ".join(caps)
    return clean_name

def openTextFile(file_name:str)->None:
    trial = [] # trial number
    array_type = []
    array_size = [] #
    accesses = [] #  
    comparisons = []
    depth = []
    experiments[cleanName(file_name)] = trial, array_type, array_size, accesses, comparisons, depth
    with open("data/" + file_name) as f:
         # get each trial number (x coord) 
         # and its corresponding n-value (y coord)
        for line in f:
            if line != "\n":
                line = line.strip()
                tokens = line.split(" ")
                # add data to their corresponding lists
                # convert to int otherwise a big mess in matplot
                trial.append(int(tokens[0]))
                array_type.append(tokens[1])
                array_size.append(int(tokens[2]))
                accesses.append(int(tokens[3]))
                comparisons.append(int(tokens[4]))
                depth.append(int(tokens[5]))
       

# get text files
text_files = [file for file in os.listdir("data") if '.txt' in file]

# load the data from text files above
for file in text_files:
    openTextFile(file)

size = 10
# plot the data via matplotlib
for experiment in experiments:
    # get x data from dictionary key (experiment) values index 0, y data from dictionary values index 1
    plt.plot(experiments[experiment][2],experiments[experiment][5],scalex=True, scaley=True, aa=True, alpha=.5)
plt.title("Comparison of Computations Required to Sort an Array")
plt.legend(experiments)
plt.xlabel("Array Size")
plt.ylabel("Stack Depth + Comparisons + Array Accesses")
plt.grid(False)
plt.show()

for file in text_files:
	os.remove("data/" + file)
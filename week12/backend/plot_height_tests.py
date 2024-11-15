# Gabriel Malone / CS205 / Week 2 Lab

import os
import matplotlib.pyplot as plt

# dictionary to hold graph data 
# key will be experiment name
# value will be x, y lists of values
experiments = {}
averages = {}



# format names to standard required by lab instructions
# (remove '_', ap each word)
def cleanName(file_name:str)->str:  
    caps = []  
    tokens = file_name[0:-4].split('_')
    for token in tokens:
        caps.append(token.capitalize())
    clean_name = " ".join(caps)
    return clean_name

def openTextFile(file_name:str)->int:
    trial = [] # trial number
    tree_height = []
    experiments[cleanName(file_name)] = trial, tree_height
    with open("test_data/" + file_name) as f:
         # get each trial number (x coord) 
         # and its corresponding n-value (y coord)
        for line in f:
            if line != "\n":
                line = line.strip()
                tokens = line.split(" ")
                # add data to their corresponding lists
                # convert to int otherwise a big mess in matplot
                trial.append(int(tokens[1]))
                tree_height.append(int(tokens[2]))
  
# get text files
text_files = [file for file in os.listdir("test_data") if '.txt' in file]

# load the data from text files above
for file in text_files:
    openTextFile(file)

# plot the data via matplotlib
for experiment in experiments:
    # get x data from dictionary key (experiment) values index 0, y data from dictionary values index 1
    plt.plot(experiments[experiment][0], experiments[experiment][1], scalex=True, scaley=True, aa=True)
plt.title(f"Tree Height for Tree Size of 1000 Nodes")
plt.legend(experiments)
plt.xlabel("Trial Number")
plt.ylabel("Tree Height")
plt.grid(False)
plt.show()


for file in text_files:
	os.remove("test_data/" + file)
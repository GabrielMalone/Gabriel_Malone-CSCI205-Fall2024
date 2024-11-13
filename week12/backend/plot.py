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
    array_type = []
    tree_size = [] #
    operations = [] # 
    avg_operations = [] 
    ideal = []
    experiments[cleanName(file_name)] = trial, array_type, tree_size, operations, avg_operations, ideal
    with open("test_data/" + file_name) as f:
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
                nodes = int(tokens[2])
                operations.append(int(tokens[3]))
                avg_operations.append(float(tokens[4]))
                ideal.append(float(tokens[5]))
                log2 = float(tokens[5])
                avg = float(tokens[6])
    return nodes, log2, avg

# get text files
text_files = [file for file in os.listdir("test_data") if '.txt' in file]

# load the data from text files above
for file in text_files:
    nodes, log2, avg = openTextFile(file)


# plot the data via matplotlib
for experiment in experiments:
    # get x data from dictionary key (experiment) values index 0, y data from dictionary values index 1
    plt.plot(experiments[experiment][0], experiments[experiment][4], label=f"{experiment} - Avg of Actual Operations: {avg}", scalex=True, scaley=True, aa=True)
    plt.plot(experiments[experiment][0], experiments[experiment][5], label=f"Theoretical Number of Operations Required for This Tree Size: (log 2 N): {log2}", scalex=True, scaley=True, aa=True)
    plt.plot(experiments[experiment][0], experiments[experiment][3], label=f"{experiment} - Operations per Trial", scalex=True, scaley=True, aa=True, alpha=0.25)
plt.title(f"Number Operations Required to Insert a Random Int into a Binary Search Tree of size {nodes}")
plt.legend(title="Experiment Data")
plt.xlabel("Trial Number")
plt.ylabel("Operations Taken to Insert Number")
plt.grid(False)
plt.show()


for file in text_files:
	os.remove("test_data/" + file)
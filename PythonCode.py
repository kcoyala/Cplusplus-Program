import re
import string
import os.path
from os import path


#function to count the frequency of all items in the txt file
def CountAll():
   
    #Opens the file
    itemCount = open("CS210_Project_Three_Input_File.txt", "r")

    #Creates a dictionary to hold each item and how many times each is found
    allItems = dict()

    #loops through the file and adds to the dictionary for each item found and adds to the frequency of each item
    for line in itemCount:
       
        line = line.strip()

        word = line.lower()
        
        if word in allItems:
            
            allItems[word] = allItems[word] + 1
        
        else:
            
            allItems[word] = 1

    #Prints the dictionary
    for key in list (allItems.keys()):
        
        print(key.capitalize(), allItems[key])

    #Close the file.
    itemCount.close()

#function counting the frequency of a user search item
def TotalCount(itemSearch):

    #Convert search term to lowercase 
    itemSearch = itemSearch.lower()

    #Opens the file
    text = open("CS210_Project_Three_Input_File.txt", "r")

    #Creates a variable to track the item count
    itemCount2 = 0

    #Checks each line in the file and increments itemCount2 each time search term is found
    for line in text:
        
        line = line.strip()

        word = line.lower()
        
        if word == itemSearch:
            
            itemCount2 += 1

    #Returns the amount of times the search term was found
    return itemCount2

    #Closes the file
    text.close()



#function to count the frequency of the items and writes it to a frequency.dat file
def HistogramData():
    
    #Opens the file
    itemCount = open("CS210_Project_Three_Input_File.txt", "r")

    #creats a file that can be written to
    frequency = open("frequency.dat", "w")

    #Creats a dictionary to write the items to
    allItems = dict()

    #loops through each line of the text and then adds each item to the dictionary, and increments the frequency
    for line in itemCount:
       
        line = line.strip()

        word = line.lower()

        if word in allItems:

            allItems[word] = allItems[word] + 1
        
        else:

            allItems[word] = 1

    #Writes each key and value pair to frequency.dat
    for key in list (allItems.keys()):
       
        frequency.write(str(key.capitalize()) + " " + str(allItems[key]) + "\n")

    #Closes all opened files
    itemCount.close()
    frequency.close()
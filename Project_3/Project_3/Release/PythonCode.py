import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v
def userInput1():
    text = open("CS210_Project_Three_Input_File.txt", "r") #open input file
    d = dict() #using a dictionary, key-value pairs represent the data nicely

    for line in text: #iterate over the text
        line = line.strip() #remove newlines
        if line in d:
            d[line] = d[line] + 1 #if that word is already in dict increment count by 1
        else:
            d[line] = 1 #else add to dict with count of 1
    #print dictionary at end
    for key in list(d.keys()):
        print(key, ":", d[key])
    text.close() #close the file 


def userInput2(v):
    #all the same as the above except now we return d[v] which will be the frequency of the word the user chose
    #we don't really have any error handling for the event the user typo'd or provided an item that doesn't appear in the list
    text = open("CS210_Project_Three_Input_File.txt", "r") #file is in same directory, just need name
    d = dict()

    for line in text:
        line = line.strip()
        if line in d:
            d[line] = d[line] + 1
        else:
            d[line] = 1
    text.close() #close the file
    return d[v]

def userInput3():
    text = open("CS210_Project_Three_Input_File.txt", "r")
    text2 = open("frequency.dat", "w")
    d = dict()

    #we are making a dictionary again, then writing each key value pair to a new file
    for line in text:
        line = line.strip() 
        if line in d:
            d[line] = d[line] + 1 
        else:
            d[line] = 1 
    
    for key in list(d.keys()):
        text2.write(key, " ", d[key])
    text.close()
    text2.close() #close both files

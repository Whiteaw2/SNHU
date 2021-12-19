import re
import string
import pdb


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

    
def ItemFrequencyAll(): #Print all item frequencies

    print("Items were purchased ____ times." + '\n') #Print title with newline

    fileArray = []
    file = open("CS210_Project_Three_Input_File.txt", "r")

  

    #Iterate through open file and compile array, then print appearance count
    for line in file:
        #print("Forloop") #DEBUG print statement
        itemName = line.strip() #remove space
        if not (itemName in fileArray): #If the array doesn't yet contain the item name
            #print("ifLoop") #DEBUG print statement
            fileArray.append(itemName) #Add item to list
            appearancesNum = open("CS210_Project_Three_Input_File.txt", 'r').read().count(itemName) #get count
            print(itemName, ":", appearancesNum) #print name and count


    #print("endLoop")  #DEBUG print statement
    #print(fileArray)  #DEBUG print statement
    #print(file.read())  #DEBUG print statement
  


    return  2 #not important, but satisfies return conditions

def ItemFrequencySpecific(itemInput): #Double int function

    fileDict = {} #Create dictionary for items and counts
    file = open("CS210_Project_Three_Input_File.txt", "r") #Open file

  

    #Iterate over tile lines and enter names on first appearance as key, count as value
    for line in file:
        #print("Forloop") #DEBUG print statement
        itemName = line.strip() #remove space
        if not (itemName in fileDict): #For first time seeing names
            #print("ifLoop") #DEBUG print statement
            appearancesNum = open("CS210_Project_Three_Input_File.txt", 'r').read().count(itemName) #get count
            fileDict[itemName] = appearancesNum #create entry in dict with value/key

    capName = itemInput.capitalize() #handle lowecase names

    if capName in fileDict: #if item is in dictionary
        itemFrequency = fileDict.get(capName) #set frequency to amount seen
    else: 
        print("Error, entry not found. Try again.") #else show error
        itemFrequency = -1; #Send error val

    #print(itemInput, "were purchased", output, "time(s)") #If we displayed from Python
 

    #print("endLoop")  #DEBUG print statement
    #print(fileArray)  #DEBUG print statement
    # print(file.read())  #DEBUG print statement
  


    return  itemFrequency



def ItemFrequencyHisto(): #Function to read file, create or write to new .dat file, then save

    fileArray = [] #Array for counting in simplified list
    fileRead = open("CS210_Project_Three_Input_File.txt", "r") #open file

    fileWrite = open("frequency.dat","w+") #open or create file for results

    for line in fileRead: #iterate through original file
        #print("Forloop") #DEBUG print statement
        itemName = line.strip() #remove spaces
        #print(itemName) #DEBUG print statement
        if not (itemName in fileArray): #if first time seeing name
            #print("ifLoop") #DEBUG print statement
            fileArray.append(itemName) #add item to list
            appearancesNum = open("CS210_Project_Three_Input_File.txt", 'r').read().count(itemName) #get count of item in file
            stringToWrite = itemName +  " " + str(appearancesNum) #string for new file
            #print(stringToWrite)
            fileWrite.write(stringToWrite + '\n' ) #write entry with count into new file

    #print(fileArray)
    fileWrite.close() 
    fileRead.close()
  


    return  -1 #not important, but satisfies return conditions

    

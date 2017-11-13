import time, sys
import subprocess as sp
from colorama import *
sp.call('clear',shell=True)

thoughts = []
thoughts = ["Life","Begins","Fear & Terror","Joy & Excitement", "Life goes by fast" ]
thoughts += ["So many things to do","I live I laugh I love", "I want to do a lot more"]
thoughts += ["I want to be an adult now","I want money. I want authority"]

myExperiences = ["I have lead a good life. I have kids, grandkids, a good home"] 
myExperiences += ["I have it all and wish to enjoy it for a long time"] 
myExperiences += ["But I need more time, I grow too old", "When I was young, one time when I.."]
myExperiences += ["I want to be young again", "I can't remember when"]
myExperiences.reverse()

def sayWhatIlearned(fromThatOneTime):
    print myIdeas[fromThatOneTime]
    
def IcanRemember(thatOneTimeWhen):
    return thatOneTimeWhen<16
    
def tryingToRemember(whileGettingOld):
    if whileGettingOld==16:
        print Style.DIM + Fore.WHITE+ "It was so long ago"
    if whileGettingOld==17:
        print Style.BRIGHT + Fore.BLACK+ "I grow too old"
    if whileGettingOld==18:
        print Style.BRIGHT + Fore.BLACK+ "\nI lived a life"
    if whileGettingOld==19:
        global life
        life=False     
        print Style.BRIGHT + Fore.BLACK+ "-Igor Carvalho"
        
def timeGoesBy():
    global fromExperience
    if fromExperience==13:
        sys.stdout.write( Style.DIM+Fore.WHITE+'')

def thinkAboutLife(thatOneTimeWhen):
    if IcanRemember(thatOneTimeWhen):
        timeGoesBy()
        print myExperiences.pop()
    else:
        tryingToRemember(thatOneTimeWhen)

def Ilearn():
    global fromExperience
    myIdeas.append(thoughts[fromExperience])
    sayWhatIlearned(fromExperience)
    global age
    time.sleep(age*2)
    age+=.1
    fromExperience +=1

def Icontemplate():
    global fromExperience
    thinkAboutLife(fromExperience)
    global age
    time.sleep(age*2)
    age+=.5
    fromExperience +=1

def IgrewUp():
    global fromExperience
    return fromExperience==10
    
def growOld():
    global IamYoung
    global IamOld
    IamYoung=False
    IamOld=True
    print "\nI live a life"
    time.sleep(age*4)
    sp.call('clear',shell=True)
    print Style.NORMAL+ "As I grow old"
    time.sleep(age*3)

myIdeas = []
life=True
IamYoung=True
IamOld=False
age = .00
fromExperience = 0
print Style.BRIGHT+ "As a child"
time.sleep(1)

while life:
    if IamYoung:
        Ilearn()
    elif IamOld:
        Icontemplate()
    if IgrewUp():
        growOld()

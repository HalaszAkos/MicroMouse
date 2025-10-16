import sys
import random
import time


class branch: #elágazás randomhoz
    def __init__(self,x,y,RL):
        self.x=x # x pozíció
        self.y=y # y pozíció
        self.RL=RL #merre ment: -90 -->balra |  jobbra -->90
        
        
class steps:  # lépésszámláló
    def __init__(self,x,y,steps):
        self.x=x
        self.y=y
        self.steps=steps
        
        
class dead_end:
    def __init__(self,x,y):
        self.x=x
        self.y=y
        self.dead_end=True
        
class Cell:
    def __init__(self,x,y):
        self.x=x
        self.y=y
        self.walls = [True, True, True, True] #index 0: top |index 1: right| index 2: bottom| index 3: left
        self.visited = False
        self.neighbors=[]
        self.matrix=min([(abs(7-x)+abs(7-y)),(abs(8-x)+abs(8-y)),(abs(8-x)+abs(7-y)),(abs(7-x)+abs(8-y))])#smallest way to the middle


def matrix(x,y):
    return min([(abs(7-x)+abs(7-y)),(abs(8-x)+abs(8-y)),(abs(8-x)+abs(7-y)),(abs(7-x)+abs(8-y))])#smallest way to the middle
def matrix_5(x,y):
    first=matrix(x,y)
    second=matrix(x,y+1)
    third=matrix(x,y-1)
    fourth=matrix(x-1,y)
    fifth=matrix(x+1,y)
    all=first+second+third+fourth+fifth
    return all



class MouseCrashedError(Exception):
    pass

def short_way(current_x,current_y,finish_x,finish_y):
    return(abs(current_x-finish_x)+abs(current_y-finish_y))
    

def command(args, return_type=None):
    line = " ".join([str(x) for x in args]) + "\n"
    sys.stdout.write(line)
    sys.stdout.flush()
    if return_type:
        response = sys.stdin.readline().strip()
        if return_type == bool:
            return response == "true"
        return return_type(response)

def mazeWidth():
    return command(args=["mazeWidth"], return_type=int)

def mazeHeight():
    return command(args=["mazeHeight"], return_type=int)

def checkWall(wallCommand, half_steps_away=None):
    args = [wallCommand]
    if half_steps_away is not None:
        args.append(half_steps_away)
    return command(args, return_type=bool)

def wallFront(half_steps_away=None):
    return checkWall("wallFront", half_steps_away)

def wallBack(half_steps_away=None):
    return checkWall("wallBack", half_steps_away)

def wallLeft(half_steps_away=None):
    return checkWall("wallLeft", half_steps_away)

def wallRight(half_steps_away=None):
    return checkWall("wallRight", half_steps_away)

def wallFrontLeft(half_steps_away=None):
    return checkWall("wallFrontLeft", half_steps_away)

def wallFrontRight(half_steps_away=None):
    return checkWall("wallFrontRight", half_steps_away)

def wallBackLeft(half_steps_away=None):
    return checkWall("wallBackLeft", half_steps_away)

def wallBackRight(half_steps_away=None):
    return checkWall("wallBackRight", half_steps_away)

def moveForward(distance=None):
    args = ["moveForward"]
    # Don't append distance argument unless explicitly specified, for
    # backwards compatibility with older versions of the simulator
    if distance is not None:
        args.append(distance)
    response = command(args=args, return_type=str)
    if response == "crash":
        raise MouseCrashedError()

def moveForwardHalf(num_half_steps=None):
    args = ["moveForwardHalf"]
    if num_half_steps is not None:
        args.append(num_half_steps)
    response = command(args=args, return_type=str)
    if response == "crash":
        raise MouseCrashedError()

def turnRight():
    command(args=["turnRight"], return_type=str)

def turnLeft():
    command(args=["turnLeft"], return_type=str)

def turnRight90():
    turnRight()

def turnLeft90():
    turnLeft()

def turnRight45():
    command(args=["turnRight45"], return_type=str)

def turnLeft45():
    command(args=["turnLeft45"], return_type=str)

def setWall(x, y, direction):
    command(args=["setWall", x, y, direction])

def clearWall(x, y, direction):
    command(args=["clearWall", x, y, direction])

def setColor(x, y, color):
    command(args=["setColor", x, y, color])

def clearColor(x, y):
    command(args=["clearColor", x, y])

def clearAllColor():
    command(args=["clearAllColor"])

def setText(x, y, text):
    command(args=["setText", x, y, text])

def clearText(x, y):
    command(args=["clearText", x, y])

def clearAllText():
    command(args=["clearAllText"])

def wasReset():
    return command(args=["wasReset"], return_type=bool)

def ackReset():
    command(args=["ackReset"], return_type=str)

def log(string):
    sys.stderr.write("{}\n".format(string))
    sys.stderr.flush()


    
    
def check_walls(cur,irany):
        if(cur.visited==False):
            log("-------Allitsuk be a current falait iranynak megfelelően-------------")
            log("jobb fal megnézése")
            if(wallRight()==False):
                    if(irany==8): #E=8 H=2 B=4 J=6 billentyűzet
                        cur.walls[1]=False
                        (log("jobbra nincs"))
                    if(irany==6):
                        cur.walls[2]=False
                        log("lent nincs") 
                    if(irany==4):
                        cur.walls[0]=False
                        log("elol nincs")
                    if(irany==2):
                        cur.walls[3]=False 
                        log("balra nincs") 
        
            log("bal fal megnézése")
            if(wallLeft()==False):
                    if(irany==8): #E=8 H=2 B=4 J=6 billentyűzet
                        cur.walls[3]=False
                        log("balra nincs") 
                    if(irany==6):
                        cur.walls[0]=False 
                        log("elol nincs")
                    if(irany==4):
                        cur.walls[2]=False
                        log("lent nincs")
                    if(irany==2):
                        cur.walls[1]=False
                        (log("jobbra nincs"))  
                        
            log("upfal megnézése")
            if(wallFront()==False):
                    
                    if(irany==8): #E=8 H=2 B=4 J=6 billentyűzet
                        cur.walls[0]=False
                        log("elol nincs")
                    if(irany==6):
                        cur.walls[1]=False 
                        (log("jobbra nincs"))  
                    if(irany==4):
                        cur.walls[3]=False
                        log("balra nincs") 
                    if(irany==2):
                        cur.walls[2]=False  
                        log("lent nincs")

def add_neighbor(current,array_2d,stack):
        if(current.visited==False):
            log("-----------------Adjuk hozza a szomszedokat ha nincs fal-------")
            if current.walls[0]==False: #ELŐTTE
                    current.neighbors.append(array_2d[current.x][(current.y)+1])
                    log("fent")
            if current.walls[1]==False: #JOBBRA
                    current.neighbors.append(array_2d[(current.x)+1][current.y])
                    log("jobbra")

            if current.walls[2]==False: #MÖGÖTTE
                    current.neighbors.append(array_2d[current.x][(current.y)-1])
                    log("lent")

            if current.walls[3]==False: #BALRA
                    current.neighbors.append(array_2d[(current.x)-1][current.y])
                    log("balra")
            stack.append(current)
            current.visited=True
            log("Legyen visited a current")
        return stack
        
            
                
def get_choice_unvisited(unvisited,current,next,dead_end_flag,array_2d): #erre még nem unv
        log("Hany szomszed van:")
        log(len(current.neighbors))
        i=0
        while i<len(current.neighbors):
            if(current.neighbors[i].visited==False): #lehet 1,2,3vagy háromd darab ami unvisited
                unvisited.append(current.neighbors[i])
            i=i+1
        log("Unvisitednek a hossza:")
        log(len(unvisited))
        if(len(unvisited)==0):#zsak utca
            dead_end_flag=True
            log("deadend")
        if(len(unvisited)==1): #egy akkor csak erre
            next=unvisited[0]
        if((len(unvisited))>=2): #ha több mint egy(2 vagy 3)
            i=0
            next=unvisited[0]
            while i<len(unvisited):
                if(matrix_5(next.x,next.y)>matrix_5(unvisited[i].x,unvisited[i].y)):
                    next=unvisited[i]   #if((next.matrix)>unvisited[i].matrix)
                    #if(array_2d[next.x][next.y].matrix+array_2d[next.x][next.y+1].matrix+array_2d[next.x][next.y-1].matrix+array_2d[next.x+1][next.y].matrix+array_2d[next.x-1][next.y].matrix) > (array_2d[unvisited[i].x][unvisited[i].y].matrix+array_2d[unvisited[i].x][unvisited[i].y+1].matrix+array_2d[unvisited[i].x][unvisited[i].y-1].matrix+array_2d[unvisited[i].x+1][unvisited[i].y].matrix+array_2d[unvisited[i].x-1][unvisited[i].y].matrix):

                i=i+1
                
                
        return dead_end_flag,next

def check_current_neighbors_has_unv(current):
    i=0
    while i<len(current.neighbors):
            if(current.neighbors[i].visited==False): #lehet 1,2,3vagy háromd darab ami unvisited
                return True
            i=i+1
    return False
        

def dead_end_and_wallfrontTrue(E_H_B_J,stack):# fordítsuk meg és állítsuk az irányt be +(180fok)  
    if(wallFront()==True and wallLeft()==True and wallRight()==True):
        turnLeft()
        turnLeft()
       
        if(E_H_B_J==2):
            E_H_B_J=8
        elif(E_H_B_J==8):
            E_H_B_J=2
        if(E_H_B_J==4):
            E_H_B_J=6
        elif(E_H_B_J==6):
            E_H_B_J=4
        
        stack.pop() #utolso helyet kivesszük
    
    return E_H_B_J,stack

def go_to_next(cur,nex,irany,dead_end_flag,stack):  #merre menjünk ha megvan a next
        yseged=(cur.y-nex.y)
        xseged=(cur.x-nex.x) 
        if(xseged==0 and yseged==0):
            dead_end_flag=True
            nex=stack[-1]
            stack.pop()
            xseged=(cur.x-nex.x)
            yseged=(cur.y-nex.y)
            turnRight()
            if(irany==8):
                irany=6
            elif(irany==6):
                irany=2
            elif(irany==4):
                irany=8
            elif(irany==2):
                irany=4
            
                
        
                                     #currennt   next             számolás        melyik fal:
        if(xseged==1):                # koordináta: 2,2     1,2          --> 2-1 =1           bal (nextnek jobb)
                nex.walls[1]=False
                if(irany==8):
                    turnLeft()
                    irany=4
                if(irany==2):
                    turnRight()
                    irany=4
        if(xseged==-1):                  # koordináta: 2,2     3,2       --> 2-3 ==-1        jobb(nextnek bal)
                nex.walls[3]=False
                if(irany==8):
                    turnRight()
                    irany=6
                if(irany==2):
                    turnLeft()
                    log("miért balra he")
                    irany=6
                                                   #currennt   next             számolás        melyik fal:
        if(yseged==1):                # koordináta: 2,3         2,2          --> 3-2 =1           lent (nextnek felső)
                nex.walls[0]=False
                if(irany==6):
                    turnRight()
                    irany=2
                if(irany==4):
                    turnLeft()
                    irany=2 
        if(yseged==-1):                  # koordináta: 2,3     2,4       --> 3-4 ==-1        felső(nextnek alsó)
                nex.walls[2]=False
                if(irany==4):
                    turnRight()
                    irany=8
                if(irany==6):
                    turnLeft()
                    irany=8
        
                
        return irany,dead_end_flag,nex        

def change_direction_180(E_H_B_J):
    turnLeft()
    turnLeft()
    if(E_H_B_J==8):
        E_H_B_J=2 
    elif(E_H_B_J==2):
        E_H_B_J=8 
    elif(E_H_B_J==4):
        E_H_B_J=6 
    elif(E_H_B_J==6):
        E_H_B_J=4
    time.sleep(2.5)
    return E_H_B_J
def go_back_to_start(E_H_B_J,dead_end_flag,next,current,stack):
    i=1
    while i<len(stack)-1:
        help=-i
        next=stack[help-1]
        log(next.x)
        log(next.y)
        log("current:")
        log(current.x)
        log(current.y)
        log("next")
        log(next.x)
        log(next.y)
        E_H_B_J,dead_end_flag,next=go_to_next(current,next,E_H_B_J,dead_end_flag,stack)
        moveForward()     #legyen az ott vagyok if után!
        current=next
        i=i+1
    return E_H_B_J,dead_end_flag,next,current
def go_back_to_finish(E_H_B_J,dead_end_flag,next,current,stack):
    flag_finish=0
    i=0
    while i<len(stack):
        if(i+2<len(stack)):
            next=stack[i+2]
        setColor(next.x,next.y,"G")
        log("next")
        log(next.x)
        log(next.y)
        log("current")
        log(current.x)
        log(current.y)
        E_H_B_J,dead_end_flag,next=go_to_next(current,next,E_H_B_J,dead_end_flag,stack)
        i=i+1
        if((current.x==7 and current.y==7) or (current.x==7 and current.y==8)or (current.x==8 and current.y==7)or (current.x==8 and current.y==8)):
            log("Finish")
            flag_finish=1
            break
        current=next
        moveForward()
        log("------------------------------------------------------------")
        log("Step ")
        log(i)
        log("------------------------------------------------------------")
        setText(current.x,current.y,i)
    return E_H_B_J,dead_end_flag,next,current,flag_finish  
          
def main():
    
    log("--------------------------------------Init------------------------------------------------")
    #List_of_Steps=[Start] #lépésszámláló lista x,y,list
    dead_end_flag=False #dead_end listához hozzáadjuk ha igaz
    E_H_B_J=8 #E=8 H=2 B=4 J=6 billentyűzet
    how_far =0
    log("Running...")
    setColor(0, 0, "G")
    setText(0, 0, "abc")
   
    log("--------------------------------------Feltölt------------------------------------------------")
    #6x6 2d tömb
    array_2d = [[Cell(x,y) for y in range(16)] for x in range(16)]  
    log("----------------------------------------------------------------------------------------")
    log("Finish beállítva,escurrent is:")
    
    #ut_a_finishez=[array_2d[0][1]...stb]
    current=array_2d[0][0]
    stack=[current] #put it to visited
    next=current
    how_far =0

    log("Running...")
    setColor(0, 0, "G")
    setText(0, 0, "abc")
        
    while True: 
        log("koordinatam x:")
        log(current.x)
        log("koordinatam y:")
        log(current.y)
            
        #------------------------------------------------------------------------------------------------
        if(dead_end_flag==False):
            check_walls(current,E_H_B_J) #current falait beallitja
            stack=add_neighbor(current,array_2d,stack)#szomszedok hozzáadása + visited ha nem volt
            log("-----Ezeket a szomszedokat vizsgaljuk meg, hogy unvisited-e?-------")
            unvisited=[]
            dead_end_flag,next=get_choice_unvisited(unvisited,current,next,dead_end_flag,array_2d)#visszakapjuk a next-er

        
        if(dead_end_flag==True): #ha dead_end_flag=true akkor visszafelé kell menni
            #check wall front
            log("Hello ez itt zsák utca")
            E_H_B_J,stack=dead_end_and_wallfrontTrue(E_H_B_J,stack)  #irányba vagyunk, a stackbol visszafelé kell menni egyesével UV ig
            next=stack[-1]
            stack.pop()
            #ha van egy unvisited akkor lépjünk ki , legyen a flag false
            if(check_current_neighbors_has_unv(next)==True):
                dead_end_flag=False
                stack.append(next)
        
        #go to next
        E_H_B_J,dead_end_flag,next=go_to_next(current,next,E_H_B_J,dead_end_flag,stack)
        #ha közepén vagyunk akkor break
        if((current.x==7 and current.y==7) or (current.x==7 and current.y==8)or (current.x==8 and current.y==7)or (current.x==8 and current.y==8)):
            log("Finish")
            break
        moveForward()
        current=next

        log("koordinatam x:")
        log(current.x)
        log("koordinatam y:")
        log(current.y)
        log("koordinatam x:")
        log(next.x)
        log("koordinatam y:")
        log(next.y)
        

        
        #----------------------------------------------------------------------------------------------------------
    
       #--------------------------------lépéshalmaz----------------------------------------------------
        
        how_far=how_far+1#step counter
        setText(current.x,current.y,how_far)
        log("------------------------------------------------------------")
        log("Step ")
        log(how_far)
        log("------------------------------------------------------------")
        
        
    #goback:
    log("Go back to start")
    E_H_B_J=change_direction_180(E_H_B_J)
    E_H_B_J,dead_end_flag,next,current=go_back_to_start(E_H_B_J,dead_end_flag,next,current,stack)
    
    #go to finish
    flag_finish=0
    log("Going back using the shortest path")
    E_H_B_J=change_direction_180(E_H_B_J)
    E_H_B_J,dead_end_flag,next,current,flag_finish=go_back_to_finish(E_H_B_J,dead_end_flag,next,current,stack)
    if(flag_finish==1):
        log(":)")
        
    
if __name__ == "__main__":
    main()


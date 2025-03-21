# Firing in games
In many different games we have guns, which we can use to kill enemies or do N task.
from long time ago, firing in video games was a gameplay experience to give a player
an option to protect itself. In this repository I am gonna teach you how you can make
a firing system inside of your game.

# How to make a firing system
first I am gonna demonstrate this in python so it would be easier to understand.
firing has some few parameters that we need to take care of:
<br>
`Firing flag` : this is a variable that we use to indicate we are firing and we won't allow player to player if this state was true
<br>
`Fire rate` : we use this to indicate the rate of fire. in other word, this would determine how long it will take for player to shoot again
<br>
Now that we know what we need we can actually make our firing system.
## Step 1: Setup 

first include these codes so that we have a simple engine that we can work with in a python : 

```python
import time
import os

previous_frame_60 = time.time()


FRAME_TIME_60 = 1 / 60  


while True:
    current_time = time.time()

    if current_time - previous_frame_60 >= FRAME_TIME_60:
        deltaTime_60 = current_time - previous_frame_60
        previous_frame_60 = current_time
       
    os.system("cls" if os.name == "nt" else "clear") 
    Scene = [' '] * 10 #->making our scene
    print("".join(Scene)) #->Reneder our scene
    time.sleep(0.005)
```
We use to  have a simple scene and deltaTime. made this code in our previous repo with full explanation.
Here I want to make an entity system so lets make a main class as parent and later on make other instances :

```python
class Main_class():#->class itself
    Instances = [] #->We use this to store instances
    def __init__(self, x, shape): #->our init function
        self.x = x #->setting up init position on x axis
        self.shape = shape #->setting up init shape
        Main_class.Instances.append(self) #->append instance class in main class

    def OnBeginPlay(self): 
      """#->On the start of the game"""
    def Update(self, DeltaTime, Use_delta_Time):
     """#->updates each frame"""
```
Now lets call update function and begin function for all instance :
### Begin function 
add this before the while loop, this will loop through all main class instances and call on begin play function
```python
for instance_class in Main_class.Instances:
   instance_class.OnBeginPlay()
```

### Update function 
call this inside of while loop, right after we calculate the deltaTime 
```python
if current_time - previous_frame_60 >= FRAME_TIME_60:
        deltaTime_60 = current_time - previous_frame_60
        previous_frame_60 = current_time
        for instance_class in Main_class.Instances:#->go through all the instances and update them each frame
            instance_class.Update(deltaTime_60,True)
```

### Rendering 
to render our stuff we will use this code right after making the scene :
```python
    Scene = [' '] * 100

    for instance_class in Main_class.Instances:#-> go through all the instances of main class and renders them base on their x position
       Scene[instance_class.x] = instance_class.shape 
    
    print("".join(Scene))
```
Now we have a basic entity system that we can work with.
### Make a gun class 
to make a gun classs, we want to make sure it is an instance of a main class like this :
```python
class Gun(Main_class):
    def __init__(self, x, shape):
        super().__init__(x, shape)  

    def Update(self, DeltaTime, Use_delta_Time):
        super().Update(DeltaTime, Use_delta_Time)  
```

Now we can create our gun class, before our while loop like this :
```python
Test_gun = Gun(0,"︻╦デ╤━╾")
```
for sake of this I will use this text as a gun model "︻╦デ╤━╾".
after this you should have something like this : 
![Description](https://github.com/GameDevRichtofen-G/Game-Firing-Setup-/blob/main/Example_gun_1.gif)


### Input function
to shoot we need an input function, I want to use pynput libary to have some input system in my game.
first download libary using this command
```
pip install pynput
```
then we want to recieve mouse input so we use mouse lib inside of pynput :
```python
from pynput import mouse
```
after than we make a listener in our gun class init function :
```python
    def __init__(self, x, shape):
        super().__init__(x, shape)  
        self.listener = mouse.Listener(on_click=self.Input)#->make listener, and tell which function to call when left mouse button was pressed
        self.listener.start()#->start the listener

```
you can see we have function called `self.input` we need to make this function like this :
```python
    def Input(self,x, y,button,pressed) :
        if button == mouse.Button.left: #->if the button we pressed was left mouse button
            if pressed: #-> if we pressed the button then do something
                """"""
            else:#->if we released it then do something else
                """"""
```


Now we have everything ready to make our firing system

## Step 2 : Firing
in this step we will see how we can make our gun fire.
as mention before we have few parameters to take of `Firing flag` and `Fire rate`
first we make a varible call firing and one for making sure are holding left mouse button in our gun class like this :
```python
    def __init__(self, x, shape):
        super().__init__(x, shape)
        self.firing = False #->our firing flag
        self.LeftMB = False #->our left mouse button
        self.listener = mouse.Listener(on_click=self.Input)
        self.listener.start()
```

then in our input function if we pressed left mouse button then we make LeftMB true:
```python
    def Input(self,x, y,button,pressed) :
        if button == mouse.Button.left:
            if pressed:
                self.LeftMB = True
            else:
               self.LeftMB = False
```

Now in our update function we will say if we were holding left mouse button and firing was not true we are shooting :
```python
    def Update(self, DeltaTime, Use_delta_Time):
        super().Update(DeltaTime, Use_delta_Time)
        if self.LeftMB and not self.firing :
            self.firing = True
```
Now we need to use fire rate to make firing false again so we can shoot again, the formula for fire rate is this :
<div align="center">
  <picture>
    <source srcset="https://latex.codecogs.com/svg.image?\large&space;{\color{black}T_{shot}=\frac{60}{RPM}}" media="(prefers-color-scheme: light)">
    <img src="https://latex.codecogs.com/svg.image?\large&space;{\color{white}T_{shot}=\frac{60}{RPM}}">
  </picture>
  
</div>
`RPM` stands for Round per minute which indicates how many bullet we spend each min :
now lets say our RPM is 800, which in this case we gonna say something like this :

```python
self.time = 0 #-> make a variable call time in init of gun class
```

then in update function do this :
```python
    def Update(self, DeltaTime, Use_delta_Time):
        super().Update(DeltaTime, Use_delta_Time)
        if self.LeftMB and not self.firing : #-> saying if we pressed left mouse button and firing was not true
            self.firing = True #-> we make firing true
            self.time = 60 / 800 #->we use our formula to get the fire rate
            self.shape = "︻╦デ╤━╾o" #-> change the shape of the gun

        if self.firing : #-> saying if were shooting
            

            if self.time > 0 : #->if time was greater than 0 then we subtract our time with deltaTime until it is 0
                self.time -= deltaTime_60
            else : #-> if it was 0 we make firing false again
                self.firing = False
        else :
            self.shape = "︻╦デ╤━╾"
```
now to make our gun fire bullet we can make class called bullet :
``` python
class bullet(Main_class):
    def __init__(self, x, shape):
        super().__init__(x, shape)
    
    def Update(self, DeltaTime, Use_delta_Time):
        super().Update(DeltaTime, Use_delta_Time)
        self.x = (self.x + (50 * DeltaTime if Use_delta_Time else 1)) #-> update the bullet x position using deltaTime
        if self.x > 99 : #-> if x was greater than 99 then we destroy our bullet
            Main_class.Instances.remove(self)
```

now to make our bullet we do this in our update function :
```python
        if self.LeftMB and not self.firing :
            self.firing = True
            self.time = 60 / 800
            new_bullet = bullet(self.x + 1 , '-') #->create a new class called bullet one x position ahead of the gun
            self.shape = "︻╦デ╤━╾o"

```

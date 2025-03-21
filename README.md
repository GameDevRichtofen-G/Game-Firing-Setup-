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
`Firing rate` : we use this to indicate the rate of fire. in other word, this would determine how long it will take for player to shoot again
<br>
Now that we know what we need we can actually make our firing system.
## Step 1: Setup : 

first include these codes so that we have a simple engine that we can work with in a python : 

```python
previous_frame_60 = time.time()


FRAME_TIME_60 = 1 / 60  


while True:
    current_time = time.time()

    if current_time - previous_frame_60 >= FRAME_TIME_60:
        deltaTime_60 = current_time - previous_frame_60
        previous_frame_60 = current_time
       
    os.system("cls" if os.name == "nt" else "clear") 
    Scene = ['-'] * 10
    print("".join(Scene))
    time.sleep(0.005)
```
We use to  have a simple scene and deltaTime. made this code in our previous repo with full explanation.
Here I want to make an entity system so lets make a main class as parent and later on make other instances :

```python
class Main_class():
    Instances = []
    def __init__(self, x, shape):
        self.x = x
        self.shape = shape
        Main_class.Instances.append(self)

    def OnBeginPlay(self):
      """#On the start of the game"""
    def Update(self, DeltaTime, Use_delta_Time):
     """#updates each frame"""
```



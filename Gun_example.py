import time
import os
from pynput import mouse


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

class bullet(Main_class):
    def __init__(self, x, shape):
        super().__init__(x, shape)
    
    def Update(self, DeltaTime, Use_delta_Time):
        super().Update(DeltaTime, Use_delta_Time)
        self.x = (self.x + (50 * DeltaTime if Use_delta_Time else 1))
        if self.x > 99 :
            Main_class.Instances.remove(self)

class Gun(Main_class):
    def __init__(self, x, shape):
        super().__init__(x, shape)
        self.firing = False
        self.LeftMB = False
        self.time = 0
        self.listener = mouse.Listener(on_click=self.Input)
        self.listener.start()

    def Update(self, DeltaTime, Use_delta_Time):
        super().Update(DeltaTime, Use_delta_Time)
        if self.LeftMB and not self.firing :
            self.firing = True
            self.time = 60 / 800
            new_bullet = bullet(self.x + 1 , '-')
            self.shape = "︻╦デ╤━╾o"

        if self.firing :
            

            if self.time > 0 :
                self.time -= deltaTime_60
            else :
                self.firing = False
        else :
            self.shape = "︻╦デ╤━╾"



    def Input(self,x, y,button,pressed) :
        if button == mouse.Button.left:
            if pressed:
                self.LeftMB = True
            else:
               self.LeftMB = False
    


previous_frame_60 = time.time()

Test_gun = Gun(0,"︻╦デ╤━╾")

FRAME_TIME_60 = 1 / 60  

for instance_class in Main_class.Instances:
   instance_class.OnBeginPlay()

while True:
    current_time = time.time()



    
    if current_time - previous_frame_60 >= FRAME_TIME_60:
        deltaTime_60 = current_time - previous_frame_60
        previous_frame_60 = current_time
        for instance_class in Main_class.Instances:
            instance_class.Update(deltaTime_60,True)
            
       



    os.system("cls" if os.name == "nt" else "clear") 


    Scene = [' '] * 100

    for instance_class in Main_class.Instances:
       Scene[int(instance_class.x)] = instance_class.shape
    
    print("".join(Scene))


    
    time.sleep(0.005)
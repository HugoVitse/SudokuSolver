import pyautogui
import time

numbers = [(947, 358),(1062, 365),(1160, 359),(949, 469), (1054, 479),(1168, 471),(953, 577),(1059, 578),(1166, 586)]
# for i in range(9):
#     for j in range(9):
#         pyautogui.click(x=410+j*54, y=270+i*50)



# Ajouter un listener pour les clics de souris
while True:
    print(pyautogui.position())
    time.sleep(0.2)
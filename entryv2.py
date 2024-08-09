from PIL import Image, ImageEnhance, ImageFilter
import pytesseract
import os
from flask import Flask, request, jsonify, render_template, Response
import cv2
import io
import threading
from math import floor
from gtts import gTTS
from playsound import playsound
from pydub import AudioSegment
import time
import subprocess
import sys
import tty
from num2words import num2words
import termios
import json
import base64
import pyautogui
import boto3

# Configurer les informations d'identification directement dans le script


app = Flask(__name__)

numbers = ['1', '2', '3', '4', '5', '6', '7', '8', '9']

mots = [
    "Bureau", "Cuisine", "Balcon", "Banane", "Bébé", "Boîte", "Bonheur", "Bougie", "Bouteille",
    "Cabane", "Café", "Canard", "Carton", "Cerise", "Chaise", "Chapeau", "Chien", "Citron",
    "Hirondelle", "Cochon", "Décor", "Couleur", "Courir", "Crayon", "Croire", "Marin", "Orange",
    "Départ", "Dîner", "Douce", "Sapin", "École", "Écrire", "Église", "Élan", "Élève", "Encore",
    "Enfant", "Tapis", "Fleur", "Foyer", "Garage", "Gâteau", "Girafe", "Grande", "Guide", "Habit",
    "Robot", "Hibou", "Hôtel", "Idée", "Jardin", "Navire", "Jouet", "Octave", "Lanterne", "Légume",
    "Lettre", "Livre", "Lune", "Machine", "Maison", "Matin", "Mémoire", "Miroir", "Moitié", "Monde",
    "Motif", "Musique", "Neige", "Nourriture", "Oiseau", "Ombre", "Orage", "Ouverture", "Kangourou",
    "Papillon", "Poisson", "Pomme", "Parasol", "Rideau"
]


mots_neufs = [
    "Lacune", "Vélo", "Soleil", "Renard", "Saison", "Tigre", "Colline", "Drapeau", "Porte"
]




left = 10
top = 461
right = 141
bottom = 590
cro = 15
size = 126
formerI = formerJ = -1
actualI = actualJ = 0

receive = cont  = False

avoid = []
_type = ""
fin = False
numbers_ord = [[29, 1, 6], [29, 3, 7], [30, 1, 1], [30, 2, 9], [30, 3, 9], [31, 2, 7], [31, 3, 8], [32, 1, 9], [32, 3, 7]]

def getchr():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

def click(big,small,tiny):
    global _type
    _type = 'grid'
    enoncer("Afficher la grille",True)
    _type = 'big'
    enoncer(str(big),False)
    _type = 'small'
    enoncer(str(small),False)
    _type = 'tiny'
    enoncer(str(tiny),False)

def enoncer(texte,speed):

    
    global cont
    while not cont:
    # Texte à convertir en parole
    # Créer un objet gTTS
    
        
        
    # tts = gTTS(text=texte, lang='fr')

    # # Enregistrer le fichier audio
        fichier_audio = "synthese_vocale.mp3"
        # tts.save(fichier_audio)

        polly = boto3.client(
            'polly',
            aws_access_key_id='AKIAQGYBPZ4HC2EJ7MJF',
            aws_secret_access_key='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',
            region_name='eu-west-3'
        )

    # Synthétiser la parole
        response = polly.synthesize_speech(
            Text=texte,
            OutputFormat="mp3",
            VoiceId="Mathieu"
        )

    # Enregistrer la sortie audio
        with open(fichier_audio, 'wb') as file:
            file.write(response['AudioStream'].read())

        # Jouer le fichier audio
        audio = AudioSegment.from_file(fichier_audio, format="mp3")

        #Augmenter la vitesse de lecture (par exemple, multiplier par 1.5)
        audio_vitesse_acceleree = audio.speedup(playback_speed=1.5)

    # Enregistrer le fichier audio avec la vitesse accélérée
        fichier_audio_accelere = "synthese_vocale_acceleree.mp3"
        audio_vitesse_acceleree.export(fichier_audio_accelere, format="mp3")
        if(speed):
            playsound(fichier_audio_accelere)
        else:
            playsound(fichier_audio)

        time.sleep(2)

        while not receive:
            continue
    cont = False
            
        
    
def imageToNumber(image,i,j):
    global left,right,top,bottom,cro,size
    cropped_image = image.crop((left+i*size + cro , top+j*size + cro, right+i*size - cro, bottom+j*size - cro))
    cropped_image = cropped_image.convert('L') 
    cropped_image = ImageEnhance.Contrast(cropped_image).enhance(2)  
    text = pytesseract.image_to_string(cropped_image, config='--psm 6 -c tessedit_char_whitelist=123456789')
    ff = filter(text)
    return ff



def caseToVO(x,y,value):
    global actualJ,actualI,formerI,formerJ,_type
    actualI = x
    actualJ = y
    x += 1
    y += 1

    x_to_click =  22+(x-1)*125 + 60
    y_to_click = 473 + (y-1)*125 + 60

    print(x_to_click)
    print(y_to_click)

    tiny_square_x = int(round(x_to_click/31.5))
    print(x_to_click/32.5)
    tiny_square_y = int(round(y_to_click/31.25))

    print(tiny_square_x)
    print(tiny_square_y)

    big_square = int(floor(((tiny_square_y-1)//9)*4 + ((tiny_square_x-1)//9)+1))

    
    row_to_fill = (tiny_square_y- ((big_square-1)//4 * 9))
    col_to_fill = (tiny_square_x- ((big_square+3)%4 * 9))

    print(row_to_fill)
    print(col_to_fill)

    small_square = int(floor(((row_to_fill-1)//3))*3 + (((col_to_fill-1)//3)+1))
 
    tiny_square = int(floor((row_to_fill+2)%3)*3  + ( ((col_to_fill+2)%3) +1))

    print(big_square)
    print(small_square)
    print(tiny_square)
    _type = "select"
    enoncer(mots[((y-1)*9 + x-1)],False)
    _type = "click"
    enoncer(mots_neufs[int(value)-1],False)
    formerI = actualI
    formerJ = actualJ
    #click(big_square,small_square,tiny_square)
    #click(numbers_ord[int(value)-1][0],numbers_ord[int(value)-1][1],numbers_ord[int(value)-1][2])


def filter(text):
    for i in text:
        if i in numbers:
            return(i)
        if(i == 'Q'):
            return('9')
            
        if(i == 'A'):
            return('4')
        if(i== 'D'):
            return('5')
    return 0
            



# Définir la boîte de rognage (gauche, haut, droite, bas)
def plusorminus(pixel,tolerance,pixelRef):
    tol = True
    for i in range(3):

        if( not( pixel[i] >= pixelRef[i] -tolerance and pixel[i] <= pixelRef[i]+ tolerance)):
            tol = False

    return tol


def majorColor(image,i,j):
    global left,right,top,bottom,cro,size
    cropped_image = image.crop((left+i*size + cro , top+j*size + cro, right+i*size - cro, bottom+j*size - cro))
    pixels = cropped_image.load()
    width, height = cropped_image.size
    frequency_dict = {}
    for i in range(width):
        for j in range(height):
            element = pixels[i,j]
            if element in frequency_dict:
                frequency_dict[element] += 1
            else:
                frequency_dict[element] = 1
    
    # Trouver l'élément avec le plus grand nombre d'occurrences
    most_frequent = max(frequency_dict, key=frequency_dict.get)
    
    return most_frequent


count = 0



@app.route('/continue',methods = ['POST'])
def resume():
    global count
    print('tg')
    global receive,_type,cont,actualI,actualJ,formerJ,formerI
  
    image = Image.open(io.BytesIO(request.data))
    if image.mode != 'RGB':
        image = image.convert('RGB')
    image.save("test.jpg")
    print(count)
    count+=1
   
    print(_type)
    match(_type):
        case 'select':
            colorfrequent = majorColor(image,actualI,actualJ)
            print(colorfrequent)
            if(plusorminus(colorfrequent,15,(178, 223, 254))):
                cont = True

        case 'click':
            ff = imageToNumber(image,actualI,actualJ)
            if(ff != 0):

                cont = True            

    receive = True
    time.sleep(0.5)
    receive = False
    global fin
    return "true" if fin else "false" 

        

@app.route('/hello')
def hello():
    return 'Hello'


def identify(image):
    global fin
    try:


  
        if image.mode != 'RGB':
            image = image.convert('RGB')

        pixels = image.load()

        width, height = image.size

        for k in range(10):
            for i in range(200,1900):
                for j in range(7):
                    pixels[15+k*(width-22-15)/9 +j,i] = (255,255,255)

        for k in range(10):
            for i in range(0,1160):
                for j in range(8):
                    pixels[i,466+(k*(width-22-15)/9)+j] = (255,255,255)




   


        ret = []
        command = 'build/./SudokuSolver'# "UI/SolverUI/build/Desktop_Qt_6_7_2-Release/./SolverUI"

        for j in range(9):
            r = []
            for i in range(9):
                ff = imageToNumber(image,i,j)
                if(ff != 0):
                    avoid.append((i,j))
                command += f" {ff}"
                r.append(ff)
            ret.append(r)

        print(ret)
        print(command)
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        print(result.stdout)
        sudok = result.stdout.split("\n")
        sudok_filtr = [s for s in sudok if s != '']
        #print(sudok_filtr)
        sudok_fin = []
        for tg in sudok_filtr:
            fdp = tg.split(' ')
            fdp_filtr =  [s for s in fdp if s != '']
            sudok_fin.append(fdp_filtr)
           
        print(sudok_fin)
        print(avoid)
        for j in range(len(sudok_fin)):
            for i in range(len(sudok_fin[j])):
     
                if((i,j) not in avoid):
                    print((i,j))
                    caseToVO(i,j,sudok_fin[j][i])
        #os.system(command)
        fin = True
        return 'ok'

    except Exception as e:
        return jsonify({"error": str(e)}), 400
    


def gen_frames():  # Générateur de frames de la caméra
    camera = cv2.VideoCapture(0)  # 0 pour la caméra par défaut
    while True:
        success, frame = camera.read()
        if not success:
            break
        else:
            ret, buffer = cv2.imencode('.jpg', frame)
            frame = buffer.tobytes()
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')


@app.route('/', methods=['POST'])
def sudoku():

    print(request.content_type)
    image = Image.open(io.BytesIO(request.data))
    #identify(image)
    thread = threading.Thread(target=identify, args=(image,))
    thread.start()
    return 'ok'
   

def imageToNumberWeb(image,i,j):
    global left,right,top,bottom,cro,size
    sizeWeb = 2000/9
    cropped_image = image.crop((i*sizeWeb + cro  , j*sizeWeb + cro, i*sizeWeb + sizeWeb - cro , j*sizeWeb+sizeWeb - cro ))
    cropped_image = ImageEnhance.Contrast(cropped_image).enhance(2)  
    cropped_image = cropped_image.convert('L') 
    output_file_path = 'tg.png'
    # Sauvegarder l'image sur le disque
    cropped_image.save(output_file_path)
    text = pytesseract.image_to_string(cropped_image, config='--psm 6')
    ff = filter(text)
    print(text)
    return ff

numbersWeb = [(947, 358),(1062, 365),(1160, 359),(949, 469), (1054, 479),(1168, 471),(953, 577),(1059, 578),(1166, 586)]
# for i in range(9):
#     for j in range(9):
#         pyautogui.click(x=410+j*54, y=270+i*50)
def clickweb(i,j,value):
    pyautogui.click(x=410+i*54, y=270+j*56)
    pyautogui.click(x=numbersWeb[int(value)-1][0], y=numbersWeb[int(value)-1][1])
    return 'ok'

@app.route('/web', methods=['POST'])
def web():  
    avoidweb = []
    print("okkk")
    obj = request.data.decode()
    ver = obj[obj.find(","):len(obj)]
    image_data = base64.b64decode(ver)
    
    # Convertir les données d'image en un objet image
    image = Image.open(io.BytesIO(image_data))
    command = 'build/./SudokuSolver'# "UI/SolverUI/build/Desktop_Qt_6_7_2-Release/./SolverUI"

        
    sudoku = []
    for j in range(9):
        row = []
        for i in range(9):
            ff = imageToNumberWeb(image,i,j)
            print(ff)
            if ff != 0:
                avoidweb.append((i,j))
            command += f" {ff}"
            row.append(ff)
        sudoku.append(row)


    print(sudoku)
    if image.mode != 'RGB':
        image = image.convert('RGB')
    print(command)
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

    sudok = result.stdout.split("\n")
    sudok_filtr = [s for s in sudok if s != '']
    #print(sudok_filtr)
    sudok_fin = []
    for tg in sudok_filtr:
        fdp = tg.split(' ')
        fdp_filtr =  [s for s in fdp if s != '']
        sudok_fin.append(fdp_filtr)
        
    print(sudok_fin)
    print(avoidweb)
    for j in range(len(sudok_fin)):
        for i in range(len(sudok_fin[j])):
    
            if((i,j) not in avoidweb and sudok_fin[j][i] != '0'):
                print(sudok_fin[j][i])
                print((i,j))
                clickweb(i,j,sudok_fin[j][i])
                time.sleep(0.2)



    output_file_path = 'output_image.png'
    # Sauvegarder l'image sur le disque
    image.save(output_file_path)
    print(f"Image sauvegardée sous {output_file_path}")
    return 'ok'

@app.route('/video_feed')
def video_feed():
    return Response(gen_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')


@app.route('/scan')
def scan():
     return render_template('video_feed.html')

if __name__ == '__main__':
     app.run(debug=True, host='0.0.0.0', port=80)
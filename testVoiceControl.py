from math import floor
from gtts import gTTS
from playsound import playsound
from pydub import AudioSegment
import time


numbers = [[29, 1, 6], [29, 3, 7], [30, 1, 1], [30, 2, 9], [30, 3, 9], [31, 2, 7], [31, 3, 8], [32, 1, 9], [32, 3, 7]]
# # Texte à convertir en parole
# texte = "Afficher la grille"
# # Créer un objet gTTS
# tts = gTTS(text=texte, lang='fr')

# # Enregistrer le fichier audio
# fichier_audio = "synthese_vocale.mp3"
# tts.save(fichier_audio)

# # Jouer le fichier audio
# playsound(fichier_audio)

# time.sleep(4)
# # Texte à convertir en parole
# texte = "32"
# # Créer un objet gTTS
# tts = gTTS(text=texte, lang='fr')

# # Enregistrer le fichier audio
# fichier_audio = "synthese_vocale.mp3"
# tts.save(fichier_audio)

# # Jouer le fichier audio
# playsound(fichier_audio)
def click(big,small,tiny):
    enoncer("Afficher la grille")
    enoncer(str(big))
    enoncer(str(small))
    enoncer(str(tiny))

def enoncer(texte):

    # Texte à convertir en parole
    # Créer un objet gTTS
    tts = gTTS(text=texte, lang='fr')

    # Enregistrer le fichier audio
    fichier_audio = "synthese_vocale.mp3"
    tts.save(fichier_audio)

    # Jouer le fichier audio
    audio = AudioSegment.from_file(fichier_audio, format="mp3")

    #Augmenter la vitesse de lecture (par exemple, multiplier par 1.5)
    audio_vitesse_acceleree = audio.speedup(playback_speed=1.5)

   # Enregistrer le fichier audio avec la vitesse accélérée
    fichier_audio_accelere = "synthese_vocale_acceleree.mp3"
    audio_vitesse_acceleree.export(fichier_audio_accelere, format="mp3")
    playsound(fichier_audio_accelere)

    time.sleep(3)


def caseToVO(x,y,value):
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

    big_square = int(floor(((tiny_square_y)//9)*4 + (tiny_square_x//9)+1))

    
    row_to_fill = (tiny_square_y- ((big_square-1)//4 * 9))
    col_to_fill = (tiny_square_x- ((big_square+3)%4 * 9)) -1

    print(row_to_fill)
    print(col_to_fill)

    small_square = int(floor(((row_to_fill)%3))*3 + (((col_to_fill-1)//3)+2))
 
    tiny_square = int(floor((row_to_fill)%3)*3  + ( ((col_to_fill)%3) +1))

    print(((col_to_fill-1)))

    print(big_square)
    print(small_square)
    print(tiny_square)

    click(big_square,small_square,tiny_square)
    click(numbers[value-1][0],numbers[value-1][1],numbers[value-1][2])


caseToVO(8,8)
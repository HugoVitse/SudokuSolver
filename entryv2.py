from PIL import Image, ImageEnhance, ImageFilter
import pytesseract
import os

numbers = ['1', '2', '3', '4', '5', '6', '7', '8', '9']

def filter(text):
    for i in text:
        if i in numbers:
            return(i)
        if(i == 'Q'):
            return('9')
            
        if(i == 'A'):
            return('4')
    return 0
            



# Définir la boîte de rognage (gauche, haut, droite, bas)
left = 10
top = 461
right = 141
bottom = 590

size = 126

# Ouvrir une image
image_path = 'IMG_1146.jpeg'
image = Image.open(image_path)
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




# for y in range(image.height):
#     for x in range(image.width):
#         if pixels[x, y] ==  (189, 198,213):
#             # Remplacer le pixel par la transparence
#             pixels[x, y] = (255, 255, 255)


cropped_image = image.crop((left+size, top+size, right+size, bottom+size))

cro = 15
ret = []
command = "build/./SudokuSolver"
custom_config = r'--oem 3 --psm 10 -c tessedit_char_whitelist=123456789'
for j in range(9):
    r = []
    for i in range(9):
        cropped_image = image.crop((left+i*size + cro , top+j*size + cro, right+i*size - cro, bottom+j*size - cro))
        cropped_image = cropped_image.convert('L') 
        cropped_image = ImageEnhance.Contrast(cropped_image).enhance(2)  
        text = pytesseract.image_to_string(cropped_image, config='--psm 6')
        ff = filter(text)
        command += f" {ff}"
        r.append(ff)
    ret.append(r)

print(ret)
print(command)

os.system(command)
import base64
from num2words import num2words
import os


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

numbers_click = [
    (100,2052),(220,2063),(344,2050),(460,2056),(586,2063),(711,2046),(834,2056),(953,2054),(1074,2064)
]

encoded = base64.b64decode(b"""YnBsaXN0MDDUAQIDBAUGBwpYJHZlcnNpb25ZJGFyY2hpdmVyVCR0
			b3BYJG9iamVjdHMSAAGGoF8QD05TS2V5ZWRBcmNoaXZlctEICVRy
			b290gAGvEBgLDBUbJicoKS8wNTY8QUdISUtVWV1eY2RVJG51bGzU
			DQ4PEBESExRWJGNsYXNzWUFsbEV2ZW50c1dWZXJzaW9uXxAXQXJl
			UG9pbnRzRGV2aWNlUmVsYXRpdmWAF4ACgBYI0hYNFxpaTlMub2Jq
			ZWN0c6IYGYADgBGAFdMcFg0dISVXTlMua2V5c6MeHyCABIAFgAaj
			IiMkgAeADYAPgBBXRmluZ2Vyc1ZGb3JjZXNUVGltZdMcFg0qLC6h
			K4AIoS2ACYAMEAHTMQ0yMzQvW05TLnBvaW50dmFsWk5TLnNwZWNp
			YWyACoALXxAoezE4LjY2NjY1NjQ5NDE0MDYyNSwgMTcyLjY2NjY1
			NjQ5NDE0MDYyfdI3ODk6WiRjbGFzc25hbWVYJGNsYXNzZXNXTlNW
			YWx1ZaI5O1hOU09iamVjdNI3OD0+XxATTlNNdXRhYmxlRGljdGlv
			bmFyeaM/QDtfEBNOU011dGFibGVEaWN0aW9uYXJ5XE5TRGljdGlv
			bmFyedMcFg1CRC6hK4AIoUWADoAMIgAAAAAjQcYtN7bNyU/SNzhA
			SqJAO9McFg1MUCWjHh8ggASABYAGo1FSU4ASgBOAFIAQ0xwWDVZX
			LqCggAzTHBYNWlsuoKCADCNBxi03ts3VeNI3OF9gXk5TTXV0YWJs
			ZUFycmF5o2FiO15OU011dGFibGVBcnJheVdOU0FycmF5FAAAAAAA
			AAAAAAAAAAAAAAHSNzhlZl8QGkFYTXV0YWJsZVJlcGxheWFibGVH
			ZXN0dXJlo2doO18QGkFYTXV0YWJsZVJlcGxheWFibGVHZXN0dXJl
			XxATQVhSZXBsYXlhYmxlR2VzdHVyZQAIABEAGgAkACkAMgA3AEkA
			TABRAFMAbgB0AH0AhACOAJYAsACyALQAtgC3ALwAxwDKAMwAzgDQ
			ANcA3wDjAOUA5wDpAO0A7wDxAPMA9QD9AQQBCQEQARIBFAEWARgB
			GgEcASMBLwE6ATwBPgFpAW4BeQGCAYoBjQGWAZsBsQG1AcsB2AHf
			AeEB4wHlAecB6QHuAfcB/AH/AgYCCgIMAg4CEAIUAhYCGAIaAhwC
			IwIkAiUCJwIuAi8CMAIyAjsCQAJPAlMCYgJqAnsCgAKdAqECvgAA
			AAAAAAIBAAAAAAAAAGkAAAAAAAAAAAAAAAAAAALU""")

tg = encoded.hex()
first = 744124253
second = 201983

#coded = base64.b64encode(tg.encode())
# print(coded)
x = 0
y = 0
print(tg)
with open("test.voicecontrolcommands", "w") as f:
    f.write("""<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CommandsTable</key>
    <dict>
""")
    for cj in range(9):
        for ci in range(9):
            x = ci+1
            y = cj+1

            cc = cj*9+ci

            x_to_click =  str(round((22+(x-1)*125 + 60)/3,5)).ljust(10,'0')
            y_to_click = str(round((473 + (y-1)*125 + 60)/3,5)).ljust(10,'0')


            print(cc)
            print(x_to_click)
            print(y_to_click)
            print("\n")



            hex_chaine = '7b'+(''.join([hex(ord(c))[2:].zfill(2) for c in x_to_click]))
        

            hex_chaine_y = (''.join([hex(ord(c))[2:].zfill(2) for c in y_to_click]))
        

            grosfdp = tg.replace("7b31382e36363636353634",hex_chaine)
            fdp = grosfdp.replace("3137322e363636363536",hex_chaine_y)
        
            enculer  = bytes.fromhex(fdp)
            final = base64.b64encode(enculer).decode()

            segment_length = 52

            # Liste pour stocker les segments
            segments = [final[i:i+segment_length] for i in range(0, len(final), segment_length)]

            # Joindre les segments avec des sauts de ligne
            resultat = '\n			'.join(segments)
            
            f.write(f"""		<key>Custom.{first+cc}.{second+cc}</key>
        <dict>
            <key>ConfirmationRequired</key>
            <false/>
            <key>CustomCommands</key>
            <dict>
                <key>fr_FR</key>
                <array>
                    <string>{mots[cc]}</string>
                </array>
            </dict>
            <key>CustomGesture</key>
            <data>\n			""")
            f.write(resultat)
            f.write("""\n			</data>
            <key>CustomModifyDate</key>
            <date>2024-07-31T13:11:51Z</date>
            <key>CustomScope</key>
            <string>com.apple.speech.SystemWideScope</string>
            <key>CustomType</key>
            <string>RunGesture</string>
        </dict>\n""")
    for numbers in range(9):
            x_to_click =  str(round(numbers_click[numbers][0]/3,5)).ljust(10,'0')
            y_to_click = str(round(numbers_click[numbers][1]/3,5)).ljust(10,'0')


            print(x_to_click)
            print(y_to_click)
            print("\n")



            hex_chaine = '7b'+(''.join([hex(ord(c))[2:].zfill(2) for c in x_to_click]))
        

            hex_chaine_y = (''.join([hex(ord(c))[2:].zfill(2) for c in y_to_click]))
        

            grosfdp = tg.replace("7b31382e36363636353634",hex_chaine)
            fdp = grosfdp.replace("3137322e363636363536",hex_chaine_y)
        
            enculer  = bytes.fromhex(fdp)
            final = base64.b64encode(enculer).decode()

            segment_length = 52

            # Liste pour stocker les segments
            segments = [final[i:i+segment_length] for i in range(0, len(final), segment_length)]

            # Joindre les segments avec des sauts de ligne
            resultat = '\n			'.join(segments)
            
            f.write(f"""		<key>Custom.{first+cc+numbers}.{second+cc+numbers}</key>
        <dict>
            <key>ConfirmationRequired</key>
            <false/>
            <key>CustomCommands</key>
            <dict>
                <key>fr_FR</key>
                <array>
                    <string>{mots_neufs[numbers]}</string>
                </array>
            </dict>
            <key>CustomGesture</key>
            <data>\n			""")
            f.write(resultat)
            f.write("""\n			</data>
            <key>CustomModifyDate</key>
            <date>2024-07-31T13:11:51Z</date>
            <key>CustomScope</key>
            <string>com.apple.speech.SystemWideScope</string>
            <key>CustomType</key>
            <string>RunGesture</string>
        </dict>\n""")

    f.write("""    </dict>
	<key>ExportDate</key>
	<real>744124561.65275502</real>
	<key>SystemVersion</key>
	<dict>
		<key>BuildID</key>
		<string>400002B2-1393-11EF-B638-7DF77EE7F452</string>
		<key>ProductBuildVersion</key>
		<string>21F90</string>
		<key>ProductCopyright</key>
		<string>1983-2024 Apple Inc.</string>
		<key>ProductName</key>
		<string>iPhone OS</string>
		<key>ProductVersion</key>
		<string>17.5.1</string>
		<key>SystemImageID</key>
		<string>831CBDDA-BF0E-4FAC-84E6-86D5440A42BE</string>
	</dict>
</dict>
</plist>""")

    f.write("""    </dict>
	<key>ExportDate</key>
	<real>744124561.65275502</real>
	<key>SystemVersion</key>
	<dict>
		<key>BuildID</key>
		<string>400002B2-1393-11EF-B638-7DF77EE7F452</string>
		<key>ProductBuildVersion</key>
		<string>21F90</string>
		<key>ProductCopyright</key>
		<string>1983-2024 Apple Inc.</string>
		<key>ProductName</key>
		<string>iPhone OS</string>
		<key>ProductVersion</key>
		<string>17.5.1</string>
		<key>SystemImageID</key>
		<string>831CBDDA-BF0E-4FAC-84E6-86D5440A42BE</string>
	</dict>
</dict>
</plist>""") 
    f.close()


os.system("zip test.voicecontrolcommands.zip test.voicecontrolcommands")
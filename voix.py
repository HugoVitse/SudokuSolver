import boto3
from playsound import playsound
import time


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


for mot in mots_neufs:

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
        Text=mot,
        OutputFormat="mp3",
        VoiceId="Mathieu"
    )

# Enregistrer la sortie audio
    with open(fichier_audio, 'wb') as file:
        file.write(response['AudioStream'].read())

    # Jouer le fichier audio
    playsound(fichier_audio)
    time.sleep(2)
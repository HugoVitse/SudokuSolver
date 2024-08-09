// Ajouter un écouteur pour les messages envoyés par le script en arrière-plan
browser.runtime.onMessage.addListener((message) => {
    if (message.action === "accessDOM") {
      // Accéder et modifier le DOM de la page
        let canvas = document.getElementById("game").children[0].toDataURL()
  
        
      // Envoyer une réponse (optionnel)
        return Promise.resolve({response: canvas});
    }
  });
  
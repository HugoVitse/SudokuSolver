
  

  document.getElementById('changeColor').addEventListener('click', () => {
    // Envoyer un message au script en arrière-plan pour déclencher l'action
    browser.tabs.query({active: true, currentWindow: true}).then((tabs) => {
        browser.tabs.sendMessage(tabs[0].id, { action: "accessDOM" }).then((response) => {
            console.log(Object.keys(response))
            fetch('http://localhost/web', {
                method: 'POST', // Spécifier la méthode POST
                body: response.response // Convertir les données en chaîne JSON
            })
            .then(function(response) {
                // Vérifier si la réponse est "OK" (status 200-299)
                if (!response.ok) {
                    throw new Error('Network response was not ok ' + response.statusText);
                }
                // La réponse est du texte JSON, donc nous devons la parse
                return response.json();
            })
        })
         
  
   
    });
  });
  
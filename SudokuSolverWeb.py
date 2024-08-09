from selenium import webdriver
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities

# Configuration des capacités pour se connecter à une session de débogage à distance
capabilities = DesiredCapabilities.FIREFOX
capabilities['moz:firefoxOptions'] = {
    'debuggerAddress': '127.0.0.1:9222'
}

# Créer une instance de WebDriver pour Firefox avec les capacités configurées
driver = webdriver.Firefox(capabilities=capabilities)

# Maintenant, vous pouvez utiliser le driver pour interagir avec la fenêtre Firefox existante
driver.get("http://example.com")
print(driver.title)

# Fermer le navigateur (facultatif)
# driver.quit()

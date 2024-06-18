window.onload = function() {
    let links = document.getElementsByTagName('a');
    for (let i = 0; i < links.length; i++) {
        if (links[i].innerText.includes('-')) {
            links[i].innerText = 'Inconnu';
            links[i].href = '#';
        }
    }

    let childrenElements = document.querySelectorAll('.children');

    for(let i = 0; i < childrenElements.length; i++) {
        let links = childrenElements[i].querySelectorAll('a');
        if(links.length > 3) {
            let firstElement = links[0];

            let newElement = document.createElement('div');
            newElement.className = 'children no-after menu-children';
            newElement.style.display = 'none'; // Ajoutez cette ligne

            // Créer le bouton de fermeture
            let closeButton = document.createElement('button');
            closeButton.innerHTML = 'Close';
            closeButton.className = 'button-children close-button';
            newElement.appendChild(closeButton);

            // Ajouter un gestionnaire d'événements de clic au bouton de fermeture
            closeButton.addEventListener('click', function() {
                newElement.style.display = 'none';
            });

            let button = document.createElement('button');
            button.className = 'button-children';
            button.innerHTML = 'Children';

            firstElement.parentNode.insertBefore(button, firstElement.nextSibling);
            firstElement.parentElement.classList.add('condition-verified');

            for(let j = 1; j < links.length; j++) {
                newElement.appendChild(links[j]);
            }

            button.parentNode.insertBefore(newElement, button.nextSibling);

            button.addEventListener('click', function() {
                if (newElement.style.display === 'none') {
                    newElement.style.display = 'block';
                } else {
                    newElement.style.display = 'none';
                }
            });
        }
    }
}
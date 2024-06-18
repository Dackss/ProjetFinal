window.onload = function() {
    let links = document.getElementsByTagName('a'); // Récupère tous les liens
    for(let i = 0; i < links.length; i++) {
        if(links[i].innerText.includes('-')) {
            links[i].innerText = 'Inconnu';
            links[i].href = '#';
            links[i].style.display = 'none';
        }
    }
}
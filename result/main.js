window.onload = function() {
    let anchors = document.getElementsByTagName('a');
    for(let i = 0; i < anchors.length; i++) {
        if(anchors[i].innerText === '- -') {
            anchors[i].style.display = 'none';
        }
    }
}
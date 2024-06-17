let ids = [];

for (let i = 1; i < 8; i++) {
    ids.push(document.getElementById(`id${i}`));
}

for (let id of ids) {
    id.innerHTML = "Hello, World!";
}
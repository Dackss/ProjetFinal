#!/bin/bash

# Fonction pour afficher le menu
show_menu() {
    echo "---------------------------------"
    echo "           MENU PRINCIPAL        "
    echo "---------------------------------"
    echo "1. Afficher les informations d'une personne"
    echo "2. Afficher les enfants d'une personne"
    echo "3. Afficher les frères et sœurs d'une personne"
    echo "4. Afficher les ancêtres"
    echo "5. Exporter en HTML"
    echo "6. Quitter"
    echo "---------------------------------"
    echo -n "Choisissez une option: "
}

# Fonction pour attendre la pression d'une touche
pause() {
    read -n 1 -s -r -p "Appuyez sur une touche pour continuer..."
}

# Fonction pour afficher les informations d'une personne
show_person_info() {
    echo -n "Entrez l'ID de la personne: "
    read id
    ../cmake-build-debug/ProjetFinal show_person_info "$id"
    pause
}

get_children() {
    echo -n "Entrez l'ID de la personne: "
    read id
    ../cmake-build-debug/ProjetFinal get_children "$id"
    pause
}

# Fonction pour récupérer les frères et sœurs
get_siblings() {
    echo -n "Entrez l'ID de la personne: "
    read id
    ../cmake-build-debug/ProjetFinal get_siblings "$id"
    pause
}

# Fonction pour récupérer les ancêtres
get_ancestors() {
    echo -n "Entrez l'ID de la personne: "
    read id
    ../cmake-build-debug/ProjetFinal get_ancestors "$id"
    pause
}

# Fonction pour exporter en HTML
export_html() {
    echo -n "Entrez le nom du fichier de sortie HTML: "
    read filename
    ../cmake-build-debug/ProjetFinal export_html "$filename"
    pause
}

# Fonction principale pour afficher le menu et traiter les options
main() {
    while true; do
        clear
        show_menu
        read choice
        case $choice in
            1) show_person_info ;;
            2) get_children ;;
            3) get_siblings ;;
            4) get_ancestors ;;
            5) export_html ;;
            6) echo "Quitter..."; exit 0 ;;
            *) echo "Option invalide!"; pause ;;
        esac
    done
}

# Passer les paramètres à la fonction principale
main "$@"
